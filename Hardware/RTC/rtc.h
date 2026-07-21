#ifndef __RTC_H__
#define __RTC_H__

#include <stdint.h>
#include "esp_at.h"

typedef struct
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    uint8_t weekday;
} rtc_date_time_t;

typedef struct
{
    uint8_t hour;
    uint8_t minute;
    uint8_t enabled;
} rtc_alarm_t;

#define RTC_ALARM_COUNT    2U

void rtc_init(void);
void rtc_set_time(const rtc_date_time_t *date_time);
void rtc_get_time(rtc_date_time_t *date_time);
uint8_t rtc_is_ready(void);
void rtc_set_time_from_esp(const esp_at_datetime_t *datetime);
void rtc_alarm_init(void);
uint8_t rtc_alarm_set(uint8_t index, const rtc_alarm_t *alarm);
uint8_t rtc_alarm_get(uint8_t index, rtc_alarm_t *alarm);
uint8_t rtc_alarm_set_enabled(uint8_t index, uint8_t enabled);
uint8_t rtc_alarm_check(const rtc_date_time_t *date_time, uint8_t *alarm_index);

#endif
