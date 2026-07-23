#include "app.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "lcd.h"
#include "lvgl.h"
#include "rtc.h"
#include "wifi.h"
#include "widgets_init.h"
#include "beep.h"

#define APP_UI_LOCK_TICKS pdMS_TO_TICKS(5)
#define APP_SENSOR_LOCK_TICKS pdMS_TO_TICKS(20)
#define APP_CTRL_LOCK_TICKS pdMS_TO_TICKS(50)

static SemaphoreHandle_t appStateMutex;

/*
 * 全局运行状态：
 * 1. 传感器任务持续写入环境光、温湿度、气压、电池等数据；
 * 2. WiFi/天气相关任务写入联网状态和天气信息；
 * 3. LVGL任务每次刷新界面前先复制这里的内容，再统一更新控件。
 * 这样做可以把“业务状态”和“界面绘制”解耦，避免多个任务直接操作LVGL。
 */
typedef struct
{
    float lux;
    float lux_filtered;
    float temp;
    float humi;
    float pressure;
    uint8_t battery_percent;
    uint8_t bh1750_ok;
    uint8_t sht30_ok;
    uint8_t spl06_ok;
    uint8_t battery_ok;
    uint8_t auto_brightness_enabled;
    uint8_t brightness_percent;
    rtc_date_time_t rtc_time;
    uint8_t rtc_ok;
    rtc_alarm_t alarm[RTC_ALARM_COUNT];
    uint8_t alarm_ringing;
    uint8_t ringing_alarm_index;
    weather_info_t weather;
} app_state_t;

/*
 * UI缓存：
 * 保存上一次已经显示到界面上的关键值。
 * 刷新主界面时会先把当前状态格式化，再和缓存比较；
 * 只有内容真的变了才调用LVGL更新控件，减少无意义重绘。
 */
typedef struct
{
    int32_t temp_tenths;
    int32_t humi_tenths;
    int32_t pressure_int;
    uint8_t brightness_percent;
    uint8_t battery_percent;
    uint8_t sht30_ok;
    uint8_t spl06_ok;
    uint8_t battery_ok;
    uint8_t auto_brightness_enabled;
    uint8_t wifi_status;
    uint8_t rtc_ok;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    uint8_t year_low;
    uint8_t month;
    uint8_t day;
    uint8_t weekday;
    uint8_t alarm_enabled[RTC_ALARM_COUNT];
    uint8_t alarm_hour[RTC_ALARM_COUNT];
    uint8_t alarm_minute[RTC_ALARM_COUNT];
    uint8_t alarm_ringing;
    int8_t outdoor_temp;
    uint8_t weather_valid_now;
} app_ui_cache_t;

static uint8_t g_selected_alarm_index = 0U;

static app_state_t g_app_state = {
    .lux = 0.0f,
    .lux_filtered = 0.0f,
    .temp = 0.0f,
    .humi = 0.0f,
    .pressure = 0.0f,
    .battery_percent = 0,
    .bh1750_ok = 0,
    .sht30_ok = 0,
    .spl06_ok = 0,
    .battery_ok = 0,
    .auto_brightness_enabled = 0,
    .brightness_percent = 50,
    .rtc_time = {2026, 1, 1, 0, 0, 0, 4},
    .rtc_ok = 0,
    .alarm = {
        {8, 30, 0},
        {8, 30, 0}},
    .alarm_ringing = 0U,
    .ringing_alarm_index = 0U,
    .weather = {0}};

static app_ui_cache_t g_ui_cache = {
    .temp_tenths = INT32_MIN,
    .humi_tenths = INT32_MIN,
    .pressure_int = INT32_MIN,
    .brightness_percent = 0xFFU,
    .battery_percent = 0xFFU,
    .sht30_ok = 0xFFU,
    .spl06_ok = 0xFFU,
    .battery_ok = 0xFFU,
    .auto_brightness_enabled = 0xFFU,
    .wifi_status = 0xFFU,
    .rtc_ok = 0xFFU,
    .hour = 0xFFU,
    .minute = 0xFFU,
    .second = 0xFFU,
    .year_low = 0xFFU,
    .month = 0xFFU,
    .day = 0xFFU,
    .weekday = 0xFFU,
    .alarm_enabled = {0xFFU, 0xFFU},
    .alarm_hour = {0xFFU, 0xFFU},
    .alarm_minute = {0xFFU, 0xFFU},
    .alarm_ringing = 0xFFU,
    .outdoor_temp = 0x7FU,
    .weather_valid_now = 0xFFU};

static BaseType_t app_lock(TickType_t timeout)
{
    if (appStateMutex == NULL)
    {
        return pdFALSE;
    }

    return xSemaphoreTake(appStateMutex, timeout);
}

static void app_unlock(void)
{
    if (appStateMutex != NULL)
    {
        xSemaphoreGive(appStateMutex);
    }
}

static uint8_t clamp_percent(int32_t value)
{
    if (value < LCD_BACKLIGHT_MIN)
    {
        return LCD_BACKLIGHT_MIN;
    }
    if (value > LCD_BACKLIGHT_MAX)
    {
        return LCD_BACKLIGHT_MAX;
    }
    return (uint8_t)value;
}

/*
 * 环境光到背光亮度的分段曲线：
 * 暗环境下保持较低亮度，避免刺眼；
 * 室内正常光照缓慢抬升亮度；
 * 强光环境继续提高，保证屏幕仍然可读。
 * 这里不用简单线性映射，是为了让实际观感更平滑。
 */
static uint8_t map_lux_to_brightness(float lux)
{
    float target;

    if (lux <= 20.0f)
    {
        target = 15.0f;
    }
    else if (lux <= 100.0f)
    {
        target = 15.0f + (lux - 20.0f) * (20.0f / 80.0f);
    }
    else if (lux <= 500.0f)
    {
        target = 35.0f + (lux - 100.0f) * (30.0f / 400.0f);
    }
    else if (lux <= 2000.0f)
    {
        target = 65.0f + (lux - 500.0f) * (35.0f / 1500.0f);
    }
    else
    {
        target = 100.0f;
    }

    return clamp_percent((int32_t)(target + 0.5f));
}

static int32_t float_to_tenths(float value)
{
    if (value >= 0.0f)
    {
        return (int32_t)(value * 10.0f + 0.5f);
    }

    return (int32_t)(value * 10.0f - 0.5f);
}

static void format_fixed_1_with_prefix(char *text, uint32_t size, const char *prefix, int32_t tenths, const char *suffix)
{
    int32_t abs_tenths;

    if ((text == NULL) || (size == 0U) || (prefix == NULL) || (suffix == NULL))
    {
        return;
    }

    abs_tenths = (tenths < 0) ? -tenths : tenths;
    lv_snprintf(text, size, "%s%s%d.%d%s",
                prefix,
                (tenths < 0) ? "-" : "",
                (int)(abs_tenths / 10),
                (int)(abs_tenths % 10),
                suffix);
}

static void format_int_value_with_prefix(char *text, uint32_t size, const char *prefix, int32_t value, const char *suffix)
{
    if ((text == NULL) || (size == 0U) || (prefix == NULL) || (suffix == NULL))
    {
        return;
    }

    lv_snprintf(text, size, "%s%d%s", prefix, (int)value, suffix);
}

static const char *app_get_weekday_text(uint8_t weekday)
{
    static const char *weekday_texts[7] = {
        "星期一", "星期二", "星期三", "星期四",
        "星期五", "星期六", "星期日"};

    if ((weekday >= 1U) && (weekday <= 7U))
    {
        return weekday_texts[weekday - 1U];
    }

    return "--";
}

static const char *app_weather_icon_path(const char *code)
{
    if (code == NULL)
    {
        return "0:/PICTURE/weather_icon/yin.bin";
    }

    if ((strcmp(code, "0") == 0) ||
        (strcmp(code, "1") == 0) ||
        (strcmp(code, "2") == 0) ||
        (strcmp(code, "3") == 0))
    {
        return "0:/PICTURE/weather_icon/qing.bin";
    }

    return "0:/PICTURE/weather_icon/yin.bin";
}

static void app_alarm_format(char *text, uint32_t size, const rtc_alarm_t *alarm)
{
    if ((text == NULL) || (size == 0U) || (alarm == NULL))
    {
        return;
    }

    lv_snprintf(text, size, "%02u:%02u", alarm->hour, alarm->minute);
}

static void app_alarm_sync_from_rtc(void)
{
    uint8_t index;

    for (index = 0U; index < RTC_ALARM_COUNT; index++)
    {
        (void)rtc_alarm_get(index, &g_app_state.alarm[index]);
    }
}

static uint8_t app_alarm_get_roller_hour(lv_obj_t *roller)
{
    uint16_t selected;

    if (roller == NULL)
    {
        return 0U;
    }

    selected = lv_roller_get_selected(roller);

    if (selected >= 23U)
    {
        return 0U;
    }

    return (uint8_t)(selected + 1U);
}

static uint8_t app_alarm_get_roller_minute(lv_obj_t *minute_tens, lv_obj_t *minute_ones)
{
    uint8_t tens = 0U;
    uint8_t ones = 0U;

    if (minute_tens != NULL)
    {
        tens = (uint8_t)lv_roller_get_selected(minute_tens);
        if (tens > 5U)
        {
            tens = 0U;
        }
    }

    if (minute_ones != NULL)
    {
        ones = (uint8_t)lv_roller_get_selected(minute_ones);
        if (ones > 9U)
        {
            ones = 0U;
        }
    }

    return (uint8_t)((tens * 10U) + ones);
}

static uint16_t app_alarm_hour_to_roller_index(uint8_t hour)
{
    if (hour == 0U)
    {
        return 23U;
    }

    return (uint16_t)(hour - 1U);
}

void app_init(void)
{
    if (appStateMutex == NULL)
    {
        appStateMutex = xSemaphoreCreateMutex();
    }

    rtc_init();
    rtc_alarm_init();
    app_alarm_sync_from_rtc();
    if (rtc_is_ready() != 0U)
    {
        rtc_get_time(&g_app_state.rtc_time);
        g_app_state.rtc_ok = 1U;
    }
}

void app_update_alarm_screen_ui(lv_ui *ui)
{
    rtc_alarm_t alarm[RTC_ALARM_COUNT];
    char text[8];

    if ((ui == NULL) || (ui->alarm_screen == NULL))
    {
        return;
    }

    if (app_lock(APP_UI_LOCK_TICKS) != pdTRUE)
    {
        return;
    }

    alarm[0] = g_app_state.alarm[0];
    alarm[1] = g_app_state.alarm[1];
    app_unlock();

    app_alarm_format(text, sizeof(text), &alarm[0]);
    lv_label_set_text(ui->alarm_screen_alarm_label_1, text);
    if (alarm[0].enabled)
    {
        lv_obj_add_state(ui->alarm_screen_alarm_sw_1, LV_STATE_CHECKED);
    }
    else
    {
        lv_obj_clear_state(ui->alarm_screen_alarm_sw_1, LV_STATE_CHECKED);
    }

    app_alarm_format(text, sizeof(text), &alarm[1]);
    lv_label_set_text(ui->alarm_screen_alarm_label_2, text);
    if (alarm[1].enabled)
    {
        lv_obj_add_state(ui->alarm_screen_alarm_sw_2, LV_STATE_CHECKED);
    }
    else
    {
        lv_obj_clear_state(ui->alarm_screen_alarm_sw_2, LV_STATE_CHECKED);
    }
}

void app_update_main_screen_ui(lv_ui *ui)
{
    app_state_t snapshot;
    int32_t temp_tenths;
    int32_t humi_tenths;
    int32_t pressure_int;
    char text[32];

    if ((ui == NULL) || (ui->main_screen == NULL) || (lv_scr_act() != ui->main_screen))
    {
        return;
    }

    /*
     * 先在互斥锁保护下快速复制一份状态快照，然后立刻释放锁。
     * 后面的字符串格式化、控件比较、LVGL刷新都放到锁外执行，
     * 这样可以减少锁占用时间，避免传感器任务/WiFi任务长时间等待。
     */
    if (app_lock(APP_UI_LOCK_TICKS) != pdTRUE)
    {
        return;
    }

    g_app_state.brightness_percent = LCD_Backlight_Get();
    snapshot = g_app_state;
    app_unlock();

    /* 先把浮点传感器值转成便于比较和显示的整数格式。 */
    temp_tenths = float_to_tenths(snapshot.temp);
    humi_tenths = float_to_tenths(snapshot.humi);
    pressure_int = (int32_t)snapshot.pressure;

    /* 传感器有效时显示实时值，无效时统一显示占位文本。 */
    if (snapshot.sht30_ok)
    {
        format_fixed_1_with_prefix(text, sizeof(text), "温度:", temp_tenths, "℃");
    }
    else
    {
        lv_snprintf(text, sizeof(text), "温度:--.-℃");
    }
    if ((g_ui_cache.sht30_ok != snapshot.sht30_ok) ||
        (g_ui_cache.temp_tenths != temp_tenths) ||
        (strcmp(lv_label_get_text(ui->main_screen_temperature_label), text) != 0))
    {
        lv_label_set_text(ui->main_screen_temperature_label, text);
        g_ui_cache.temp_tenths = temp_tenths;
    }

    if (snapshot.sht30_ok)
    {
        format_fixed_1_with_prefix(text, sizeof(text), "湿度:", humi_tenths, "%RH");
    }
    else
    {
        lv_snprintf(text, sizeof(text), "湿度:--.-%%RH");
    }
    if ((g_ui_cache.sht30_ok != snapshot.sht30_ok) ||
        (g_ui_cache.humi_tenths != humi_tenths) ||
        (strcmp(lv_label_get_text(ui->main_screen_humidity_label), text) != 0))
    {
        lv_label_set_text(ui->main_screen_humidity_label, text);
        g_ui_cache.humi_tenths = humi_tenths;
    }

    if (snapshot.spl06_ok)
    {
        format_int_value_with_prefix(text, sizeof(text), "气压:", pressure_int, "hPa");
    }
    else
    {
        lv_snprintf(text, sizeof(text), "气压:----hPa");
    }
    if ((g_ui_cache.spl06_ok != snapshot.spl06_ok) ||
        (g_ui_cache.pressure_int != pressure_int) ||
        (strcmp(lv_label_get_text(ui->main_screen_air_pressure_label), text) != 0))
    {
        lv_label_set_text(ui->main_screen_air_pressure_label, text);
        g_ui_cache.pressure_int = pressure_int;
    }

    lv_snprintf(text, sizeof(text), "%u%%", snapshot.brightness_percent);
    if ((g_ui_cache.brightness_percent != snapshot.brightness_percent) ||
        (strcmp(lv_label_get_text(ui->main_screen_light_value_label), text) != 0))
    {
        lv_label_set_text(ui->main_screen_light_value_label, text);
        g_ui_cache.brightness_percent = snapshot.brightness_percent;
    }

    if (snapshot.battery_ok)
    {
        lv_snprintf(text, sizeof(text), "%u%%", snapshot.battery_percent);
    }
    else
    {
        lv_snprintf(text, sizeof(text), "--%%");
    }
    if ((g_ui_cache.battery_ok != snapshot.battery_ok) ||
        (g_ui_cache.battery_percent != snapshot.battery_percent) ||
        (strcmp(lv_label_get_text(ui->main_screen_battery_label), text) != 0))
    {
        lv_label_set_text(ui->main_screen_battery_label, text);
        g_ui_cache.battery_percent = snapshot.battery_percent;
    }

    /* 只有滑条值和当前背光不一致时才更新，避免无效重绘。 */
    if (lv_slider_get_value(ui->main_screen_light_slider) != snapshot.brightness_percent)
    {
        lv_slider_set_value(ui->main_screen_light_slider, snapshot.brightness_percent, LV_ANIM_OFF);
    }

    /* 自动亮度打开后禁用手动滑条，关闭后恢复手动控制。 */
    if ((g_ui_cache.auto_brightness_enabled != snapshot.auto_brightness_enabled) && snapshot.auto_brightness_enabled)
    {
        lv_obj_add_state(ui->main_screen_auto_light_sw, LV_STATE_CHECKED);
        lv_obj_add_state(ui->main_screen_light_slider, LV_STATE_DISABLED);
    }
    else if ((g_ui_cache.auto_brightness_enabled != snapshot.auto_brightness_enabled) && !snapshot.auto_brightness_enabled)
    {
        lv_obj_clear_state(ui->main_screen_auto_light_sw, LV_STATE_CHECKED);
        lv_obj_clear_state(ui->main_screen_light_slider, LV_STATE_DISABLED);
    }

    if (snapshot.rtc_ok)
    {
        lv_snprintf(text, sizeof(text), "%02u:%02u:%02u",
                    snapshot.rtc_time.hour,
                    snapshot.rtc_time.minute,
                    snapshot.rtc_time.second);
    }
    else
    {
        lv_snprintf(text, sizeof(text), "--:--:--");
    }
    if ((g_ui_cache.rtc_ok != snapshot.rtc_ok) ||
        (g_ui_cache.hour != snapshot.rtc_time.hour) ||
        (g_ui_cache.minute != snapshot.rtc_time.minute) ||
        (g_ui_cache.second != snapshot.rtc_time.second) ||
        (strcmp(lv_label_get_text(ui->main_screen_time_label), text) != 0))
    {
        lv_label_set_text(ui->main_screen_time_label, text);
        g_ui_cache.hour = snapshot.rtc_time.hour;
        g_ui_cache.minute = snapshot.rtc_time.minute;
        g_ui_cache.second = snapshot.rtc_time.second;
    }

    if ((g_ui_cache.rtc_ok != snapshot.rtc_ok) ||
        (g_ui_cache.weekday != snapshot.rtc_time.weekday) ||
        (strcmp(lv_label_get_text(ui->main_screen_week_label),
                snapshot.rtc_ok ? app_get_weekday_text(snapshot.rtc_time.weekday) : "--") != 0))
    {
        lv_label_set_text(ui->main_screen_week_label,
                          snapshot.rtc_ok ? app_get_weekday_text(snapshot.rtc_time.weekday) : "--");
        g_ui_cache.weekday = snapshot.rtc_time.weekday;
    }

    if (snapshot.rtc_ok)
    {
        lv_snprintf(text, sizeof(text), "%u/%u/%u",
                    snapshot.rtc_time.year,
                    snapshot.rtc_time.month,
                    snapshot.rtc_time.day);
    }
    else
    {
        lv_snprintf(text, sizeof(text), "----/--/--");
    }
    if ((g_ui_cache.rtc_ok != snapshot.rtc_ok) ||
        (g_ui_cache.year_low != (uint8_t)(snapshot.rtc_time.year % 100U)) ||
        (g_ui_cache.month != snapshot.rtc_time.month) ||
        (g_ui_cache.day != snapshot.rtc_time.day) ||
        (strcmp(lv_label_get_text(ui->main_screen_date_label), text) != 0))
    {
        lv_label_set_text(ui->main_screen_date_label, text);
        g_ui_cache.year_low = (uint8_t)(snapshot.rtc_time.year % 100U);
        g_ui_cache.month = snapshot.rtc_time.month;
        g_ui_cache.day = snapshot.rtc_time.day;
    }

    /* 天气未刷新成功前，主界面保持 "--" 占位，避免显示旧数据。 */
    if (snapshot.weather.valid_now)
    {
        lv_snprintf(text, sizeof(text), "%d℃", snapshot.weather.temperature);
    }
    else
    {
        lv_snprintf(text, sizeof(text), "--℃");
    }
    if ((g_ui_cache.weather_valid_now != snapshot.weather.valid_now) ||
        (g_ui_cache.outdoor_temp != snapshot.weather.temperature) ||
        (strcmp(lv_label_get_text(ui->main_screen_extern_temp_label), text) != 0))
    {
        lv_label_set_text(ui->main_screen_extern_temp_label, text);
        g_ui_cache.outdoor_temp = snapshot.weather.temperature;
    }

    if ((g_ui_cache.weather_valid_now != snapshot.weather.valid_now) ||
        (strcmp(lv_label_get_text(ui->main_screen_wea_status_label),
                snapshot.weather.valid_now ? snapshot.weather.text : "--") != 0))
    {
        lv_label_set_text(ui->main_screen_wea_status_label,
                          snapshot.weather.valid_now ? snapshot.weather.text : "--");
    }

    if (strcmp(lv_label_get_text(ui->main_screen_address_label),
               snapshot.weather.city[0] != '\0' ? snapshot.weather.city : "贵港") != 0)
    {
        lv_label_set_text(ui->main_screen_address_label,
                          snapshot.weather.city[0] != '\0' ? snapshot.weather.city : "贵港");
    }

    /* 本轮UI刷新结束后，再统一回写缓存供下轮比较使用。 */
    g_ui_cache.sht30_ok = snapshot.sht30_ok;
    g_ui_cache.spl06_ok = snapshot.spl06_ok;
    g_ui_cache.battery_ok = snapshot.battery_ok;
    g_ui_cache.auto_brightness_enabled = snapshot.auto_brightness_enabled;
    g_ui_cache.rtc_ok = snapshot.rtc_ok;
    g_ui_cache.weather_valid_now = snapshot.weather.valid_now;
}

void app_update_wifi_screen_ui(lv_ui *ui)
{
    wifi_status_t status;
    const char *status_text;

    if ((ui == NULL) || (ui->wifi_screen == NULL) || (ui->wifi_screen_connect_status_label == NULL) || (lv_scr_act() != ui->wifi_screen))
    {
        return;
    }

    status = wifi_get_status();
    status_text = wifi_status_to_text(status);
    if ((g_ui_cache.wifi_status != (uint8_t)status) ||
        (strcmp(lv_label_get_text(ui->wifi_screen_connect_status_label), status_text) != 0))
    {
        lv_label_set_text(ui->wifi_screen_connect_status_label, status_text);
        g_ui_cache.wifi_status = (uint8_t)status;
    }
}

void app_update_calendar_screen_ui(lv_ui *ui)
{
    rtc_date_time_t rtc_time;
    uint8_t rtc_ok;
    static uint16_t last_year = 0U;
    static uint8_t last_month = 0U;
    static uint8_t last_day = 0U;

    if ((ui == NULL) || (ui->calendar_screen == NULL) || (ui->calendar_screen_calendar == NULL) || (lv_scr_act() != ui->calendar_screen))
    {
        return;
    }

    if (app_lock(APP_UI_LOCK_TICKS) != pdTRUE)
    {
        return;
    }

    rtc_time = g_app_state.rtc_time;
    rtc_ok = g_app_state.rtc_ok;
    app_unlock();

    if (rtc_ok == 0U)
    {
        return;
    }

    if ((last_year == rtc_time.year) &&
        (last_month == rtc_time.month) &&
        (last_day == rtc_time.day) &&
        (calendar_screen_calendar_highlihted_days[0].year == rtc_time.year) &&
        (calendar_screen_calendar_highlihted_days[0].month == rtc_time.month) &&
        (calendar_screen_calendar_highlihted_days[0].day == rtc_time.day))
    {
        return;
    }

    lv_calendar_set_today_date(ui->calendar_screen_calendar,
                               rtc_time.year,
                               rtc_time.month,
                               rtc_time.day);
    lv_calendar_set_showed_date(ui->calendar_screen_calendar,
                                rtc_time.year,
                                rtc_time.month);
    calendar_screen_calendar_highlihted_days[0].year = rtc_time.year;
    calendar_screen_calendar_highlihted_days[0].month = rtc_time.month;
    calendar_screen_calendar_highlihted_days[0].day = rtc_time.day;
    lv_calendar_set_highlighted_dates(ui->calendar_screen_calendar,
                                      calendar_screen_calendar_highlihted_days,
                                      1);
    last_year = rtc_time.year;
    last_month = rtc_time.month;
    last_day = rtc_time.day;
}

void app_update_weather_screen_ui(lv_ui *ui)
{
    weather_info_t weather;
    char text[32];

    if ((ui == NULL) || (ui->weather_screen == NULL) || (lv_scr_act() != ui->weather_screen))
    {
        return;
    }

    if (!weather_get_info(&weather) || !weather.valid_daily)
    {
        return;
    }

    lv_label_set_text(ui->weather_screen_weather_title_label, "天气预报");

    lv_label_set_text(ui->weather_screen_day_label_1, "今天");
    lv_snprintf(text, sizeof(text), "%u.%u", weather.daily[0].month, weather.daily[0].day);
    lv_label_set_text(ui->weather_screen_date_label_1, text);
    lv_label_set_text(ui->weather_screen_wea_label_1, weather.daily[0].text);
    lv_img_set_src(ui->weather_screen_day_img_1, app_weather_icon_path(weather.daily[0].code));
    lv_snprintf(text, sizeof(text), "%d℃~%d℃", weather.daily[0].low, weather.daily[0].high);
    lv_label_set_text(ui->weather_screen_daytime_tem_label_1, text);

    lv_label_set_text(ui->weather_screen_day_label_2, "明天");
    lv_snprintf(text, sizeof(text), "%u.%u", weather.daily[1].month, weather.daily[1].day);
    lv_label_set_text(ui->weather_screen_date_label_2, text);
    lv_label_set_text(ui->weather_screen_wea_label_2, weather.daily[1].text);
    lv_img_set_src(ui->weather_screen_day_img_2, app_weather_icon_path(weather.daily[1].code));
    lv_snprintf(text, sizeof(text), "%d℃~%d℃", weather.daily[1].low, weather.daily[1].high);
    lv_label_set_text(ui->weather_screen_daytime_tem_label_2, text);

    lv_label_set_text(ui->weather_screen_day_label_3, "后天");
    lv_snprintf(text, sizeof(text), "%u.%u", weather.daily[2].month, weather.daily[2].day);
    lv_label_set_text(ui->weather_screen_date_label_3, text);
    lv_label_set_text(ui->weather_screen_wea_label_3, weather.daily[2].text);
    lv_img_set_src(ui->weather_screen_day_img_3, app_weather_icon_path(weather.daily[2].code));
    lv_snprintf(text, sizeof(text), "%d℃~%d℃", weather.daily[2].low, weather.daily[2].high);
    lv_label_set_text(ui->weather_screen_daytime_tem_label_3, text);
}

void app_time_update_from_rtc(void)
{
    rtc_date_time_t rtc_time;

    if (rtc_is_ready() == 0U)
    {
        return;
    }

    rtc_get_time(&rtc_time);

    if (app_lock(APP_SENSOR_LOCK_TICKS) == pdTRUE)
    {
        g_app_state.rtc_time = rtc_time;
        g_app_state.rtc_ok = 1U;
        app_unlock();
    }
}

void app_alarm_poll(void)
{
    rtc_date_time_t rtc_time;
    uint8_t alarm_index = 0U;

    if (rtc_is_ready() == 0U)
    {
        return;
    }

    rtc_get_time(&rtc_time);
    if (rtc_alarm_check(&rtc_time, &alarm_index) == 0U)
    {
        return;
    }

    /*
     * rtc_alarm_check() 内部已经处理了“同一闹钟同一天只触发一次”的逻辑，
     * 这里不重复做判定，只负责把当前响铃状态写入APP层，
     * 供主界面弹窗显示和蜂鸣器控制使用。
     */
    if (app_lock(APP_CTRL_LOCK_TICKS) == pdTRUE)
    {
        g_app_state.alarm_ringing = 1U;
        g_app_state.ringing_alarm_index = alarm_index;
        app_unlock();
    }

    Beep_Control(1U);
}

void app_alarm_select(uint8_t index)
{
    if (index < RTC_ALARM_COUNT)
    {
        g_selected_alarm_index = index;
    }
}

uint8_t app_alarm_get_selected(void)
{
    return g_selected_alarm_index;
}

void app_alarm_prepare_set_ui(lv_ui *ui)
{
    rtc_alarm_t alarm;
    uint8_t index = g_selected_alarm_index;
    if ((ui == NULL) || (index >= RTC_ALARM_COUNT))
    {
        return;
    }

    if (app_lock(APP_UI_LOCK_TICKS) != pdTRUE)
    {
        return;
    }

    alarm = g_app_state.alarm[index];
    app_unlock();

    if (ui->alarm_set_screen_hour_roller != NULL)
    {
        lv_roller_set_selected(ui->alarm_set_screen_hour_roller,
                               app_alarm_hour_to_roller_index(alarm.hour),
                               LV_ANIM_OFF);
    }

    if (ui->alarm_set_screen_minute_roller_1 != NULL)
    {
        lv_roller_set_selected(ui->alarm_set_screen_minute_roller_1,
                               (uint16_t)(alarm.minute / 10U),
                               LV_ANIM_OFF);
    }

    if (ui->alarm_set_screen_minute_roller_2 != NULL)
    {
        lv_roller_set_selected(ui->alarm_set_screen_minute_roller_2,
                               (uint16_t)(alarm.minute % 10U),
                               LV_ANIM_OFF);
    }
}

void app_alarm_set_from_rollers(lv_ui *ui)
{
    rtc_alarm_t alarm;
    uint8_t index = g_selected_alarm_index;

    if ((ui == NULL) || (index >= RTC_ALARM_COUNT))
    {
        return;
    }

    alarm.hour = app_alarm_get_roller_hour(ui->alarm_set_screen_hour_roller);
    alarm.minute = app_alarm_get_roller_minute(ui->alarm_set_screen_minute_roller_1,
                                               ui->alarm_set_screen_minute_roller_2);
    alarm.enabled = 1U;

    if (rtc_alarm_set(index, &alarm) == 0U)
    {
        return;
    }

    if (app_lock(APP_CTRL_LOCK_TICKS) == pdTRUE)
    {
        g_app_state.alarm[index] = alarm;
        app_unlock();
    }
}

void app_alarm_set_enabled(uint8_t index, uint8_t enabled)
{
    if (index >= RTC_ALARM_COUNT)
    {
        return;
    }

    if (rtc_alarm_set_enabled(index, enabled) == 0U)
    {
        return;
    }

    if (app_lock(APP_CTRL_LOCK_TICKS) == pdTRUE)
    {
        g_app_state.alarm[index].enabled = enabled ? 1U : 0U;
        app_unlock();
    }
}

void app_alarm_stop(lv_ui *ui)
{
    Beep_Control(0U);

    if (app_lock(APP_CTRL_LOCK_TICKS) == pdTRUE)
    {
        g_app_state.alarm_ringing = 0U;
        app_unlock();
    }

    if ((ui != NULL) && (ui->main_screen_ararm_cont != NULL))
    {
        lv_obj_add_flag(ui->main_screen_ararm_cont, LV_OBJ_FLAG_HIDDEN);
    }
}

void app_alarm_show_if_active(lv_ui *ui)
{
    uint8_t ringing;
    uint8_t alarm_index;
    rtc_alarm_t alarm;
    char text[8];

    if ((ui == NULL) || (ui->main_screen == NULL) || (lv_scr_act() != ui->main_screen))
    {
        return;
    }

    if (app_lock(APP_UI_LOCK_TICKS) != pdTRUE)
    {
        return;
    }

    ringing = g_app_state.alarm_ringing;
    alarm_index = g_app_state.ringing_alarm_index;
    if (alarm_index >= RTC_ALARM_COUNT)
    {
        alarm_index = 0U;
    }
    alarm = g_app_state.alarm[alarm_index];
    app_unlock();

    if (ringing == 0U)
    {
        lv_obj_add_flag(ui->main_screen_ararm_cont, LV_OBJ_FLAG_HIDDEN);
        return;
    }

    app_alarm_format(text, sizeof(text), &alarm);
    lv_label_set_text(ui->main_screen_alarm_label, text);
    lv_obj_clear_flag(ui->main_screen_ararm_cont, LV_OBJ_FLAG_HIDDEN);
}

void app_sensor_update_lux(float lux)
{
    if (app_lock(APP_SENSOR_LOCK_TICKS) == pdTRUE)
    {
        g_app_state.bh1750_ok = (lux > 0.0f) ? 1U : 0U;
        g_app_state.lux = lux;
        if (g_app_state.lux_filtered <= 0.1f)
        {
            g_app_state.lux_filtered = lux;
        }
        else
        {
            g_app_state.lux_filtered = g_app_state.lux_filtered * 0.8f + lux * 0.2f;
        }

        if (g_app_state.auto_brightness_enabled)
        {
            g_app_state.brightness_percent = map_lux_to_brightness(g_app_state.lux_filtered);
        }
        app_unlock();
    }
}

void app_sensor_update_sht30(float temp, float humi, uint8_t ok)
{
    if (app_lock(APP_SENSOR_LOCK_TICKS) == pdTRUE)
    {
        g_app_state.sht30_ok = ok ? 1U : 0U;
        if (ok)
        {
            g_app_state.temp = temp;
            g_app_state.humi = humi;
        }
        app_unlock();
    }
}

void app_sensor_update_spl06(float pressure, uint8_t ok)
{
    if (app_lock(APP_SENSOR_LOCK_TICKS) == pdTRUE)
    {
        g_app_state.spl06_ok = ok ? 1U : 0U;
        if (ok)
        {
            g_app_state.pressure = pressure;
        }
        app_unlock();
    }
}

void app_sensor_update_battery(uint8_t percent, uint8_t ok)
{
    if (app_lock(APP_SENSOR_LOCK_TICKS) == pdTRUE)
    {
        g_app_state.battery_ok = ok ? 1U : 0U;
        if (ok)
        {
            g_app_state.battery_percent = percent;
        }
        app_unlock();
    }
}

void app_apply_auto_brightness_step(void)
{
    uint8_t current;
    uint8_t target;
    uint8_t enabled;

    if (app_lock(APP_SENSOR_LOCK_TICKS) != pdTRUE)
    {
        return;
    }

    enabled = g_app_state.auto_brightness_enabled;
    target = g_app_state.brightness_percent;
    app_unlock();

    if (!enabled)
    {
        return;
    }

    current = LCD_Backlight_Get();
    if (current == target)
    {
        return;
    }

    current = (current < target) ? (uint8_t)(current + 1U) : (uint8_t)(current - 1U);
    LCD_Backlight_Set(current);
}

void app_set_auto_brightness(uint8_t enabled)
{
    if (app_lock(APP_CTRL_LOCK_TICKS) == pdTRUE)
    {
        g_app_state.auto_brightness_enabled = enabled ? 1U : 0U;
        if (!g_app_state.auto_brightness_enabled)
        {
            g_app_state.brightness_percent = LCD_Backlight_Get();
        }
        app_unlock();
    }
}

void app_set_manual_brightness(uint8_t percent)
{
    uint8_t clamped = clamp_percent(percent);

    LCD_Backlight_Set(clamped);

    if (app_lock(APP_CTRL_LOCK_TICKS) == pdTRUE)
    {
        g_app_state.auto_brightness_enabled = 0;
        g_app_state.brightness_percent = clamped;
        app_unlock();
    }
}

uint8_t app_get_brightness_percent(void)
{
    uint8_t brightness = LCD_Backlight_Get();

    if (app_lock(APP_CTRL_LOCK_TICKS) == pdTRUE)
    {
        brightness = g_app_state.brightness_percent;
        app_unlock();
    }

    return brightness;
}

void app_update_weather_info(const weather_info_t *info)
{
    if (info == NULL)
    {
        return;
    }

    if (app_lock(APP_CTRL_LOCK_TICKS) == pdTRUE)
    {
        memcpy(&g_app_state.weather, info, sizeof(weather_info_t));
        app_unlock();
    }
}
