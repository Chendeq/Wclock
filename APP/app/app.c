#include "app.h"
#include "FreeRTOS.h"
#include "semphr.h"
#include "lcd.h"
#include "lvgl.h"
#include "rtc.h"
#include "wifi.h"
#include "widgets_init.h"

#define APP_UI_LOCK_TICKS      pdMS_TO_TICKS(5)
#define APP_SENSOR_LOCK_TICKS  pdMS_TO_TICKS(20)
#define APP_CTRL_LOCK_TICKS    pdMS_TO_TICKS(50)

static SemaphoreHandle_t appStateMutex;

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
    weather_info_t weather;
} app_state_t;

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
    int8_t outdoor_temp;
    uint8_t weather_valid_now;
} app_ui_cache_t;

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
    .weather = {0}
};

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
    .outdoor_temp = 0x7FU,
    .weather_valid_now = 0xFFU
};

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
        "星期五", "星期六", "星期日"
    };

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

void app_init(void)
{
    if (appStateMutex == NULL)
    {
        appStateMutex = xSemaphoreCreateMutex();
    }

    rtc_init();
    if (rtc_is_ready() != 0U)
    {
        rtc_get_time(&g_app_state.rtc_time);
        g_app_state.rtc_ok = 1U;
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

    if (app_lock(APP_UI_LOCK_TICKS) != pdTRUE)
    {
        return;
    }

    g_app_state.brightness_percent = LCD_Backlight_Get();
    snapshot = g_app_state;
    app_unlock();

    temp_tenths = float_to_tenths(snapshot.temp);
    humi_tenths = float_to_tenths(snapshot.humi);
    pressure_int = (int32_t)snapshot.pressure;

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

    if (lv_slider_get_value(ui->main_screen_light_slider) != snapshot.brightness_percent)
    {
        lv_slider_set_value(ui->main_screen_light_slider, snapshot.brightness_percent, LV_ANIM_OFF);
    }

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

// uint8_t app_get_auto_brightness(void)
// {
//     uint8_t enabled = 0;

//     if (app_lock(APP_CTRL_LOCK_TICKS) == pdTRUE)
//     {
//         enabled = g_app_state.auto_brightness_enabled;
//         app_unlock();
//     }

//     return enabled;
// }

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

// void app_get_sensor_snapshot(sensor_snapshot_t *snapshot)
// {
//     if (snapshot == NULL)
//     {
//         return;
//     }

//     if (app_lock(APP_CTRL_LOCK_TICKS) == pdTRUE)
//     {
//         snapshot->lux = g_app_state.lux;
//         snapshot->temp = g_app_state.temp;
//         snapshot->humi = g_app_state.humi;
//         snapshot->pressure = g_app_state.pressure;
//         snapshot->battery_percent = g_app_state.battery_percent;
//         snapshot->bh1750_ok = g_app_state.bh1750_ok;
//         snapshot->sht30_ok = g_app_state.sht30_ok;
//         snapshot->spl06_ok = g_app_state.spl06_ok;
//         snapshot->battery_ok = g_app_state.battery_ok;
//         app_unlock();
//     }
// }

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
