#include "rtc.h"

#include <string.h>
#include "stm32f4xx_pwr.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_rtc.h"

#define RTC_INIT_MAGIC    0x32F2U
#define RTC_ALARM_BKP_MAGIC    0xA10CU
#define RTC_ALARM_BKP_BASE     RTC_BKP_DR1

static uint8_t g_rtc_ready = 0U;
static rtc_alarm_t g_rtc_alarm[RTC_ALARM_COUNT];
static uint8_t g_rtc_alarm_triggered[RTC_ALARM_COUNT];
static uint16_t g_rtc_alarm_last_year[RTC_ALARM_COUNT];
static uint8_t g_rtc_alarm_last_month[RTC_ALARM_COUNT];
static uint8_t g_rtc_alarm_last_day[RTC_ALARM_COUNT];

static void rtc_calendar_base_init(void)
{
    RTC_InitTypeDef rtc_init;

    RTC_StructInit(&rtc_init);
    rtc_init.RTC_HourFormat = RTC_HourFormat_24;
    rtc_init.RTC_AsynchPrediv = 127U;
    rtc_init.RTC_SynchPrediv = 255U;
    RTC_Init(&rtc_init);
}

void rtc_init(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
    PWR_BackupAccessCmd(ENABLE);

    if (RTC_ReadBackupRegister(RTC_BKP_DR0) != RTC_INIT_MAGIC)
    {
        RCC_LSEConfig(RCC_LSE_ON);
        while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
        {
        }

        RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
        RCC_RTCCLKCmd(ENABLE);
        RTC_WaitForSynchro();
        rtc_calendar_base_init();
        RTC_WriteBackupRegister(RTC_BKP_DR0, RTC_INIT_MAGIC);
    }
    else
    {
        RCC_RTCCLKCmd(ENABLE);
        RTC_WaitForSynchro();
    }

    g_rtc_ready = 1U;
}

static void rtc_get_time_once(rtc_date_time_t *date_time)
{
    RTC_DateTypeDef date;
    RTC_TimeTypeDef time;

    RTC_GetTime(RTC_Format_BIN, &time);
    RTC_GetDate(RTC_Format_BIN, &date);

    date_time->year = (uint16_t)(2000U + date.RTC_Year);
    date_time->month = date.RTC_Month;
    date_time->day = date.RTC_Date;
    date_time->weekday = date.RTC_WeekDay;
    date_time->hour = time.RTC_Hours;
    date_time->minute = time.RTC_Minutes;
    date_time->second = time.RTC_Seconds;
}

void rtc_set_time(const rtc_date_time_t *date_time)
{
    RTC_DateTypeDef date;
    RTC_TimeTypeDef time;

    if ((date_time == 0) || (g_rtc_ready == 0U))
    {
        return;
    }

    date.RTC_Year = (uint8_t)((date_time->year >= 2000U) ? (date_time->year - 2000U) : 0U);
    date.RTC_Month = date_time->month;
    date.RTC_Date = date_time->day;
    date.RTC_WeekDay = date_time->weekday;

    time.RTC_H12 = RTC_H12_AM;
    time.RTC_Hours = date_time->hour;
    time.RTC_Minutes = date_time->minute;
    time.RTC_Seconds = date_time->second;

    RTC_SetDate(RTC_Format_BIN, &date);
    RTC_SetTime(RTC_Format_BIN, &time);
    RTC_WaitForSynchro();
}

void rtc_get_time(rtc_date_time_t *date_time)
{
    if ((date_time == 0) || (g_rtc_ready == 0U))
    {
        return;
    }

    rtc_get_time_once(date_time);
}

uint8_t rtc_is_ready(void)
{
    return g_rtc_ready;
}

void rtc_set_time_from_esp(const esp_at_datetime_t *datetime)
{
    rtc_date_time_t rtc_time;

    if (datetime == 0)
    {
        return;
    }

    rtc_time.year = datetime->year;
    rtc_time.month = datetime->month;
    rtc_time.day = datetime->day;
    rtc_time.hour = datetime->hour;
    rtc_time.minute = datetime->minute;
    rtc_time.second = datetime->second;
    rtc_time.weekday = datetime->weekday;

    rtc_set_time(&rtc_time);
}

static uint32_t rtc_alarm_pack(const rtc_alarm_t *alarm)
{
    uint32_t value = 0U;

    if (alarm == 0)
    {
        return 0U;
    }

    value |= ((uint32_t)(alarm->enabled ? 1U : 0U) << 15);
    value |= ((uint32_t)(alarm->hour % 24U) << 8);
    value |= (uint32_t)(alarm->minute % 60U);

    return value;
}

static void rtc_alarm_unpack(uint32_t value, rtc_alarm_t *alarm)
{
    if (alarm == 0)
    {
        return;
    }

    alarm->enabled = (uint8_t)((value >> 15) & 0x01U);
    alarm->hour = (uint8_t)((value >> 8) & 0x1FU);
    alarm->minute = (uint8_t)(value & 0x3FU);

    if (alarm->hour >= 24U)
    {
        alarm->hour = 0U;
    }

    if (alarm->minute >= 60U)
    {
        alarm->minute = 0U;
    }
}

static void rtc_alarm_save(uint8_t index)
{
    if ((index >= RTC_ALARM_COUNT) || (g_rtc_ready == 0U))
    {
        return;
    }

    RTC_WriteBackupRegister((uint32_t)(RTC_ALARM_BKP_BASE + index + 1U), rtc_alarm_pack(&g_rtc_alarm[index]));
}

void rtc_alarm_init(void)
{
    uint8_t index;

    if (g_rtc_ready == 0U)
    {
        return;
    }

    if (RTC_ReadBackupRegister(RTC_ALARM_BKP_BASE) != RTC_ALARM_BKP_MAGIC)
    {
        for (index = 0U; index < RTC_ALARM_COUNT; index++)
        {
            g_rtc_alarm[index].hour = 8U;
            g_rtc_alarm[index].minute = 30U;
            g_rtc_alarm[index].enabled = 0U;
            rtc_alarm_save(index);
        }
        RTC_WriteBackupRegister(RTC_ALARM_BKP_BASE, RTC_ALARM_BKP_MAGIC);
    }
    else
    {
        for (index = 0U; index < RTC_ALARM_COUNT; index++)
        {
            rtc_alarm_unpack(RTC_ReadBackupRegister((uint32_t)(RTC_ALARM_BKP_BASE + index + 1U)),
                             &g_rtc_alarm[index]);
        }
    }

    memset(g_rtc_alarm_triggered, 0, sizeof(g_rtc_alarm_triggered));
    memset(g_rtc_alarm_last_year, 0, sizeof(g_rtc_alarm_last_year));
    memset(g_rtc_alarm_last_month, 0, sizeof(g_rtc_alarm_last_month));
    memset(g_rtc_alarm_last_day, 0, sizeof(g_rtc_alarm_last_day));
}

uint8_t rtc_alarm_set(uint8_t index, const rtc_alarm_t *alarm)
{
    if ((index >= RTC_ALARM_COUNT) || (alarm == 0))
    {
        return 0U;
    }

    g_rtc_alarm[index].hour = (uint8_t)(alarm->hour % 24U);
    g_rtc_alarm[index].minute = (uint8_t)(alarm->minute % 60U);
    g_rtc_alarm[index].enabled = alarm->enabled ? 1U : 0U;
    g_rtc_alarm_triggered[index] = 0U;
    rtc_alarm_save(index);

    return 1U;
}

uint8_t rtc_alarm_get(uint8_t index, rtc_alarm_t *alarm)
{
    if ((index >= RTC_ALARM_COUNT) || (alarm == 0))
    {
        return 0U;
    }

    *alarm = g_rtc_alarm[index];

    return 1U;
}

uint8_t rtc_alarm_set_enabled(uint8_t index, uint8_t enabled)
{
    if (index >= RTC_ALARM_COUNT)
    {
        return 0U;
    }

    g_rtc_alarm[index].enabled = enabled ? 1U : 0U;
    g_rtc_alarm_triggered[index] = 0U;
    rtc_alarm_save(index);

    return 1U;
}

uint8_t rtc_alarm_check(const rtc_date_time_t *date_time, uint8_t *alarm_index)
{
    uint8_t index;

    if ((date_time == 0) || (alarm_index == 0))
    {
        return 0U;
    }

    for (index = 0U; index < RTC_ALARM_COUNT; index++)
    {
        if ((g_rtc_alarm_last_year[index] != date_time->year) ||
            (g_rtc_alarm_last_month[index] != date_time->month) ||
            (g_rtc_alarm_last_day[index] != date_time->day))
        {
            g_rtc_alarm_triggered[index] = 0U;
        }

        if ((g_rtc_alarm[index].enabled != 0U) &&
            (g_rtc_alarm_triggered[index] == 0U) &&
            (date_time->hour == g_rtc_alarm[index].hour) &&
            (date_time->minute == g_rtc_alarm[index].minute) &&
            (date_time->second == 0U))
        {
            g_rtc_alarm_triggered[index] = 1U;
            g_rtc_alarm_last_year[index] = date_time->year;
            g_rtc_alarm_last_month[index] = date_time->month;
            g_rtc_alarm_last_day[index] = date_time->day;
            *alarm_index = index;
            return 1U;
        }
    }

    return 0U;
}
