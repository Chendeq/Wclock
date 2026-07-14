#ifndef __WEATHER_H__
#define __WEATHER_H__

#include <stdint.h>

typedef struct
{
    char text[16];
    char code[4];
    int8_t low;
    int8_t high;
    uint8_t month;
    uint8_t day;
} weather_forecast_item_t;

typedef struct
{
    char city[16];
    char text[16];
    char code[4];
    int8_t temperature;
    uint8_t valid_now;
    uint8_t valid_daily;
    weather_forecast_item_t daily[3];
} weather_info_t;

void weather_init(void);
void weather_task_process(void);
void weather_notify_wifi_connected(void);
uint8_t weather_get_info(weather_info_t *info);

#endif
