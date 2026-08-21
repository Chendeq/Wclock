#include "rtos_task.h"
#include "app.h"
#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "lvgl.h"
#include "events_init.h"
#include "gui_guider.h"
#include "bh1750.h"
#include "sht30.h"
#include "spl06.h"
#include "iic2_bus.h"
#include "adc.h"
#include "wifi.h"
#include "weather.h"

#define SENSOR_TASK_PERIOD_MS               200U
#define SENSOR_BATTERY_SAMPLE_INTERVAL_MS   (5U * 60U * 1000U)
#define SENSOR_BATTERY_SAMPLE_TICKS         (SENSOR_BATTERY_SAMPLE_INTERVAL_MS / SENSOR_TASK_PERIOD_MS)

lv_ui guider_ui;

static TaskHandle_t lvglTask_handler;
static TaskHandle_t sensorTask_handler;
static TaskHandle_t wifiTask_handler;

static void lvgl_task(void *pvParameters)
{
    TickType_t last_ui_update_tick = 0;

    (void)pvParameters;

    setup_ui(&guider_ui);

    /*
     * LVGL相关调用统一放在本任务执行。
     * 其他任务只负责采集数据或推进状态机，不直接碰界面对象，
     * 这样可以避免跨任务操作LVGL带来的竞争和显示异常。
     */
    while (1)
    {
        uint32_t wait_ms;
        TickType_t now = xTaskGetTickCount();

        if ((now - last_ui_update_tick) >= pdMS_TO_TICKS(250))
        {
            app_time_update_from_rtc();
            app_alarm_poll();
            app_update_main_screen_ui(&guider_ui);
            app_alarm_show_if_active(&guider_ui);
            app_update_wifi_screen_ui(&guider_ui);
            app_update_calendar_screen_ui(&guider_ui);
            app_update_weather_screen_ui(&guider_ui);
            last_ui_update_tick = now;
        }

        wait_ms = lv_timer_handler();
        if ((wait_ms == UINT32_MAX) || (wait_ms > 50U))
        {
            wait_ms = 50U;
        }
        if (wait_ms < 5U)
        {
            wait_ms = 5U;
        }

        vTaskDelay(pdMS_TO_TICKS(wait_ms));
    }
}

static void wifi_task(void *pvParameters)
{
    static uint8_t weather_connected_latched = 0U;

    (void)pvParameters;

    wifi_init();
    weather_init();

    /*
     * WiFi连接和天气请求都设计成非阻塞状态机：
     * 每20ms推进一步，既能保持联网流程持续进行，
     * 又不会因为等待AT响应或HTTP结果而卡住其他任务。
     */
    while (1)
    {
        wifi_status_t wifi_status;

        wifi_task_process();
        weather_task_process();

        wifi_status = wifi_get_status();
        if ((wifi_status == WIFI_STATUS_CONNECTED) ||
            (wifi_status == WIFI_STATUS_TIME_SYNC_FAILED))
        {
            if (weather_connected_latched == 0U)
            {
                weather_notify_wifi_connected();
                weather_connected_latched = 1U;
            }
        }
        else
        {
            weather_connected_latched = 0U;
        }

        vTaskDelay(pdMS_TO_TICKS(20));
    }
}

static void sensor_task(void *pvParameters)
{
    uint32_t tick = 0;
    uint32_t battery_tick = SENSOR_BATTERY_SAMPLE_TICKS;
    /*
     * battery_tick 初值直接设为阈值，
     * 这样系统上电后第一轮循环就会先测一次电池电压，
     * 后面再按5分钟周期重新测量。
     */
    sht30_data_t sht30_data;

    (void)pvParameters;

    IIC2_Bus_Init();
    ADC_Battery_Init();
    BH1750_Init();
    SHT30_Init();
    SPL06_Init();

    while (1)
    {
        float lux = BH1750_Get_Lux();

        app_sensor_update_lux(lux);
        app_apply_auto_brightness_step();

        /*
         * 电池电压不需要高频采样。
         * 这里每5分钟读一次，既能反映电量变化，
         * 又能减少分压电阻和ADC检测带来的额外耗电。
         */
        if ((battery_tick >= SENSOR_BATTERY_SAMPLE_TICKS) &&
            (ADC_Battery_IsBusy() == 0U))
        {
            if (ADC_Battery_StartSample() != 0U)
            {
                battery_tick = 0U;
            }
        }

        if (ADC_Battery_IsSampleReady() != 0U)
        {
            app_sensor_update_battery(ADC_Battery_GetLastPercent(), 1U);
            ADC_Battery_ClearSampleReady();
        }

        /*
         * 任务本身每200ms运行一次，
         * 但温湿度和气压没必要跟环境光一样高频更新，
         * 所以每5个节拍采一次，实际约为1秒一更。
         */
        if ((tick % 5U) == 0U)
        {
            if (SHT30_Read_Data(&sht30_data) == 0U)
            {
                app_sensor_update_sht30(sht30_data.temp, sht30_data.humi, 1);
            }
            else
            {
                app_sensor_update_sht30(0.0f, 0.0f, 0);
            }

            float pressure = SPL06_ReadPressure();
            app_sensor_update_spl06(pressure, (pressure > 0.0f) ? 1U : 0U);
        }

        tick++;
        battery_tick++;
        vTaskDelay(pdMS_TO_TICKS(SENSOR_TASK_PERIOD_MS));
    }
}

void task_init(void)
{
    app_init();

    taskENTER_CRITICAL();

    xTaskCreate((TaskFunction_t)lvgl_task,
                (const char *)"lvgl_task",
                (uint16_t)2048,
                (void *)NULL,
                (UBaseType_t)6,
                (TaskHandle_t *)&lvglTask_handler);

    xTaskCreate((TaskFunction_t)sensor_task,
                (const char *)"sensor_task",
                (uint16_t)768,
                (void *)NULL,
                (UBaseType_t)4,
                (TaskHandle_t *)&sensorTask_handler);

    xTaskCreate((TaskFunction_t)wifi_task,
                (const char *)"wifi_task",
                (uint16_t)512,
                (void *)NULL,
                (UBaseType_t)3,
                (TaskHandle_t *)&wifiTask_handler);

    taskEXIT_CRITICAL();

    vTaskStartScheduler();
}
