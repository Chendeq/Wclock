#include "rtc.h"

#include <string.h>
#include "stm32f4xx_pwr.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_rtc.h"

#define RTC_INIT_MAGIC    0x32F2U

static uint8_t g_rtc_ready = 0U;

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
