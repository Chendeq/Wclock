#ifndef __APP_H__
#define __APP_H__

#include <stdint.h>
#include "gui_guider.h"
#include "rtc.h"
#include "weather.h"

void app_init(void);
void app_update_main_screen_ui(lv_ui *ui);
void app_update_wifi_screen_ui(lv_ui *ui);
void app_update_calendar_screen_ui(lv_ui *ui);
void app_update_weather_screen_ui(lv_ui *ui);
void app_update_alarm_screen_ui(lv_ui *ui);
void app_time_update_from_rtc(void);
void app_alarm_poll(void);
void app_alarm_select(uint8_t index);
uint8_t app_alarm_get_selected(void);
void app_alarm_prepare_set_ui(lv_ui *ui);
void app_alarm_set_from_rollers(lv_ui *ui);
void app_alarm_set_enabled(uint8_t index, uint8_t enabled);
void app_alarm_stop(lv_ui *ui);
void app_alarm_show_if_active(lv_ui *ui);
void app_sensor_update_lux(float lux);
void app_sensor_update_sht30(float temp, float humi, uint8_t ok);
void app_sensor_update_spl06(float pressure, uint8_t ok);
void app_sensor_update_battery(uint8_t percent, uint8_t ok);
void app_apply_auto_brightness_step(void);
void app_set_auto_brightness(uint8_t enabled);
void app_set_manual_brightness(uint8_t percent);
uint8_t app_get_brightness_percent(void);
void app_update_weather_info(const weather_info_t *info);

#endif
