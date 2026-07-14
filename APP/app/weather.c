#include "weather.h"

#include <stdio.h>
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "wifi.h"
#include "esp_at.h"
#include "app.h"

#define WEATHER_LOCK_TICKS            pdMS_TO_TICKS(20)
#define WEATHER_CITY_QUERY            "guigang"
#define WEATHER_CITY_NAME             "贵港"
#define WEATHER_API_KEY               "S1rY4Z32dKSlhZ2DD"
#define WEATHER_REFRESH_INTERVAL_MS   (5U * 60U * 1000U)
#define WEATHER_RESP_BUFFER_SIZE      1024U
#define WEATHER_URL_BUFFER_SIZE       192U

typedef enum
{
    WEATHER_SM_IDLE = 0,
    WEATHER_SM_WAIT_NOW,
    WEATHER_SM_WAIT_DAILY
} weather_sm_state_t;

typedef struct
{
    weather_sm_state_t state;
    TickType_t deadline;
    TickType_t next_refresh_tick;
    uint8_t pending_refresh;
    weather_info_t info;
} weather_context_t;

static SemaphoreHandle_t weatherMutex;
static uint8_t weather_initialized = 0U;
static weather_context_t g_weather_ctx = {
    .state = WEATHER_SM_IDLE,
    .deadline = 0U,
    .next_refresh_tick = 0U,
    .pending_refresh = 0U};

static BaseType_t weather_lock(TickType_t timeout)
{
    if (weatherMutex == NULL)
    {
        return pdFALSE;
    }

    return xSemaphoreTake(weatherMutex, timeout);
}

static void weather_unlock(void)
{
    if (weatherMutex != NULL)
    {
        xSemaphoreGive(weatherMutex);
    }
}

static uint8_t weather_is_timeout(TickType_t deadline, TickType_t now)
{
    return ((int32_t)(now - deadline) >= 0) ? 1U : 0U;
}

static void weather_start_wait(weather_sm_state_t state, uint32_t timeout_ms)
{
    g_weather_ctx.state = state;
    g_weather_ctx.deadline = xTaskGetTickCount() + pdMS_TO_TICKS(timeout_ms);
}

static uint8_t weather_copy_json_string(const char *json, const char *key, char *out, uint16_t size)
{
    char pattern[32];
    const char *start;
    const char *end;
    uint16_t len;

    if ((json == NULL) || (key == NULL) || (out == NULL) || (size == 0U))
    {
        return 0U;
    }

    snprintf(pattern, sizeof(pattern), "\"%s\":\"", key);
    start = strstr(json, pattern);
    if (start == NULL)
    {
        return 0U;
    }

    start += strlen(pattern);
    end = strchr(start, '"');
    if (end == NULL)
    {
        return 0U;
    }

    len = (uint16_t)(end - start);
    if (len >= size)
    {
        len = (uint16_t)(size - 1U);
    }

    memcpy(out, start, len);
    out[len] = '\0';
    return 1U;
}

static uint8_t weather_copy_indexed_json_string(const char *json, const char *key, uint8_t index, char *out, uint16_t size)
{
    char pattern[32];
    const char *cursor;
    uint8_t count = 0U;

    if ((json == NULL) || (key == NULL) || (out == NULL) || (size == 0U))
    {
        return 0U;
    }

    snprintf(pattern, sizeof(pattern), "\"%s\":\"", key);
    cursor = json;
    while ((cursor = strstr(cursor, pattern)) != NULL)
    {
        if (count == index)
        {
            const char *start = cursor + strlen(pattern);
            const char *end = strchr(start, '"');
            uint16_t len;

            if (end == NULL)
            {
                return 0U;
            }

            len = (uint16_t)(end - start);
            if (len >= size)
            {
                len = (uint16_t)(size - 1U);
            }

            memcpy(out, start, len);
            out[len] = '\0';
            return 1U;
        }

        count++;
        cursor += strlen(pattern);
    }

    return 0U;
}

static int weather_parse_int(const char *str)
{
    int value = 0;
    int sign = 1;

    if (str == NULL)
    {
        return 0;
    }

    if (*str == '-')
    {
        sign = -1;
        str++;
    }

    while ((*str >= '0') && (*str <= '9'))
    {
        value = value * 10 + (*str - '0');
        str++;
    }

    return value * sign;
}

static uint8_t weather_copy_indexed_date(const char *json, uint8_t index, uint8_t *month, uint8_t *day)
{
    char date_text[16];
    int year_value;
    int month_value;
    int day_value;

    if (!weather_copy_indexed_json_string(json, "date", index, date_text, sizeof(date_text)))
    {
        return 0U;
    }

    if (sscanf(date_text, "%d-%d-%d", &year_value, &month_value, &day_value) != 3)
    {
        return 0U;
    }

    *month = (uint8_t)month_value;
    *day = (uint8_t)day_value;
    return 1U;
}

static uint8_t weather_parse_now(const char *json, weather_info_t *info)
{
    char temp_text[8];

    if ((json == NULL) || (info == NULL))
    {
        return 0U;
    }

    strncpy(info->city, WEATHER_CITY_NAME, sizeof(info->city) - 1U);
    info->city[sizeof(info->city) - 1U] = '\0';

    if (!weather_copy_json_string(json, "text", info->text, sizeof(info->text)))
    {
        return 0U;
    }
    if (!weather_copy_json_string(json, "code", info->code, sizeof(info->code)))
    {
        return 0U;
    }
    if (!weather_copy_json_string(json, "temperature", temp_text, sizeof(temp_text)))
    {
        return 0U;
    }

    info->temperature = (int8_t)weather_parse_int(temp_text);
    info->valid_now = 1U;
    return 1U;
}

static uint8_t weather_parse_daily(const char *json, weather_info_t *info)
{
    uint8_t i;
    char low_text[8];
    char high_text[8];

    if ((json == NULL) || (info == NULL))
    {
        return 0U;
    }

    for (i = 0U; i < 3U; i++)
    {
        if (!weather_copy_indexed_json_string(json, "text_day", i, info->daily[i].text, sizeof(info->daily[i].text)))
        {
            return 0U;
        }
        if (!weather_copy_indexed_json_string(json, "code_day", i, info->daily[i].code, sizeof(info->daily[i].code)))
        {
            return 0U;
        }
        if (!weather_copy_indexed_json_string(json, "low", i, low_text, sizeof(low_text)))
        {
            return 0U;
        }
        if (!weather_copy_indexed_json_string(json, "high", i, high_text, sizeof(high_text)))
        {
            return 0U;
        }
        if (!weather_copy_indexed_date(json, i, &info->daily[i].month, &info->daily[i].day))
        {
            return 0U;
        }

        info->daily[i].low = (int8_t)weather_parse_int(low_text);
        info->daily[i].high = (int8_t)weather_parse_int(high_text);
    }

    info->valid_daily = 1U;
    return 1U;
}

static uint8_t weather_has_httpclient_result(const char *response)
{
    if (response == NULL)
    {
        return 0U;
    }

    if (strstr(response, "+HTTPCLIENT:") == NULL)
    {
        return 0U;
    }

    return (strstr(response, "\"results\"") != NULL) ? 1U : 0U;
}

static uint8_t weather_is_wifi_ready(void)
{
    wifi_status_t status = wifi_get_status();

    return ((status == WIFI_STATUS_CONNECTED) ||
            (status == WIFI_STATUS_TIME_SYNC_FAILED)) ? 1U : 0U;
}

static uint8_t weather_try_update_now(const char *response)
{
    if (!weather_has_httpclient_result(response))
    {
        return 0U;
    }

    if ((strstr(response, "\"now\"") == NULL) &&
        (strstr(response, "\"temperature\"") == NULL))
    {
        return 0U;
    }

    if (!weather_parse_now(response, &g_weather_ctx.info))
    {
        return 0U;
    }

    app_update_weather_info(&g_weather_ctx.info);
    return 1U;
}

static uint8_t weather_try_update_daily(const char *response)
{
    if (!weather_has_httpclient_result(response))
    {
        return 0U;
    }

    if (strstr(response, "\"daily\"") == NULL)
    {
        return 0U;
    }

    if (!weather_parse_daily(response, &g_weather_ctx.info))
    {
        return 0U;
    }

    app_update_weather_info(&g_weather_ctx.info);
    return 1U;
}

void weather_init(void)
{
    if (weatherMutex == NULL)
    {
        weatherMutex = xSemaphoreCreateMutex();
    }

    if (weather_initialized != 0U)
    {
        return;
    }

    if (weather_lock(WEATHER_LOCK_TICKS) == pdTRUE)
    {
        memset(&g_weather_ctx.info, 0, sizeof(g_weather_ctx.info));
        strncpy(g_weather_ctx.info.city, WEATHER_CITY_NAME, sizeof(g_weather_ctx.info.city) - 1U);
        g_weather_ctx.info.city[sizeof(g_weather_ctx.info.city) - 1U] = '\0';
        g_weather_ctx.state = WEATHER_SM_IDLE;
        g_weather_ctx.deadline = 0U;
        g_weather_ctx.next_refresh_tick = 0U;
        g_weather_ctx.pending_refresh = 0U;
        weather_initialized = 1U;
        weather_unlock();
    }
}

void weather_notify_wifi_connected(void)
{
    if (weather_lock(WEATHER_LOCK_TICKS) == pdTRUE)
    {
        g_weather_ctx.pending_refresh = 1U;
        g_weather_ctx.next_refresh_tick = 0U;
        weather_unlock();
    }
}

uint8_t weather_get_info(weather_info_t *info)
{
    if (info == NULL)
    {
        return 0U;
    }

    if (weather_lock(WEATHER_LOCK_TICKS) != pdTRUE)
    {
        return 0U;
    }

    memcpy(info, &g_weather_ctx.info, sizeof(weather_info_t));
    weather_unlock();
    return (uint8_t)((info->valid_now || info->valid_daily) ? 1U : 0U);
}

void weather_task_process(void)
{
    char response[WEATHER_RESP_BUFFER_SIZE];
    char url[WEATHER_URL_BUFFER_SIZE];
    TickType_t now;

    weather_init();

    if (weather_is_wifi_ready() == 0U)
    {
        return;
    }

    if (weather_lock(WEATHER_LOCK_TICKS) != pdTRUE)
    {
        return;
    }

    now = xTaskGetTickCount();
    (void)ESP_AT_GetResponseSnapshot(response, sizeof(response));

    if ((g_weather_ctx.state == WEATHER_SM_IDLE) &&
        (g_weather_ctx.pending_refresh || (g_weather_ctx.next_refresh_tick == 0U) || weather_is_timeout(g_weather_ctx.next_refresh_tick, now)))
    {
        g_weather_ctx.pending_refresh = 0U;
        g_weather_ctx.info.valid_now = 0U;
        g_weather_ctx.info.valid_daily = 0U;
        snprintf(url, sizeof(url),
                 "http://api.seniverse.com/v3/weather/now.json?key=%s&location=%s&language=zh-Hans&unit=c",
                 WEATHER_API_KEY,
                 WEATHER_CITY_QUERY);
        ESP_AT_ClearResponse();
        ESP_AT_HttpGet(url);
        weather_start_wait(WEATHER_SM_WAIT_NOW, 8000U);
        weather_unlock();
        return;
    }

    switch (g_weather_ctx.state)
    {
    case WEATHER_SM_IDLE:
        break;

    case WEATHER_SM_WAIT_NOW:
        if (weather_try_update_now(response))
        {
            snprintf(url, sizeof(url),
                     "http://api.seniverse.com/v3/weather/daily.json?key=%s&location=%s&language=zh-Hans&unit=c&start=0&days=3",
                     WEATHER_API_KEY,
                     WEATHER_CITY_QUERY);
            ESP_AT_ClearResponse();
            ESP_AT_HttpGet(url);
            weather_start_wait(WEATHER_SM_WAIT_DAILY, 8000U);
        }
        else if (weather_is_timeout(g_weather_ctx.deadline, now))
        {
            g_weather_ctx.state = WEATHER_SM_IDLE;
            g_weather_ctx.next_refresh_tick = now + pdMS_TO_TICKS(WEATHER_REFRESH_INTERVAL_MS);
        }
        break;

    case WEATHER_SM_WAIT_DAILY:
        if (weather_try_update_daily(response))
        {
            g_weather_ctx.state = WEATHER_SM_IDLE;
            g_weather_ctx.next_refresh_tick = now + pdMS_TO_TICKS(WEATHER_REFRESH_INTERVAL_MS);
        }
        else if (weather_is_timeout(g_weather_ctx.deadline, now))
        {
            g_weather_ctx.state = WEATHER_SM_IDLE;
            g_weather_ctx.next_refresh_tick = now + pdMS_TO_TICKS(WEATHER_REFRESH_INTERVAL_MS);
        }
        break;

    default:
        g_weather_ctx.state = WEATHER_SM_IDLE;
        g_weather_ctx.next_refresh_tick = now + pdMS_TO_TICKS(WEATHER_REFRESH_INTERVAL_MS);
        break;
    }

    weather_unlock();
}
