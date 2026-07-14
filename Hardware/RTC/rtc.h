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

void rtc_init(void);
void rtc_set_time(const rtc_date_time_t *date_time);
void rtc_get_time(rtc_date_time_t *date_time);
uint8_t rtc_is_ready(void);
void rtc_set_time_from_esp(const esp_at_datetime_t *datetime);

#endif
