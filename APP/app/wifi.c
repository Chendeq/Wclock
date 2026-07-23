#include "wifi.h"

#include <stdio.h>
#include <string.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "esp_at.h"
#include "rtc.h"

#define WIFI_LOCK_TICKS              pdMS_TO_TICKS(20)
#define WIFI_SSID_MAX_LEN            32U
#define WIFI_PASSWORD_MAX_LEN        32U
#define WIFI_RESP_BUFFER_SIZE        512U
#define WIFI_CMD_BUFFER_SIZE         96U
#define WIFI_SNTP_RETRY_MAX          5U

typedef enum
{
    WIFI_SM_IDLE = 0,
    WIFI_SM_SEND_AT,
    WIFI_SM_WAIT_AT,
    WIFI_SM_SEND_MODE,
    WIFI_SM_WAIT_MODE,
    WIFI_SM_SEND_AUTOCONN,
    WIFI_SM_WAIT_AUTOCONN,
    WIFI_SM_SEND_JOIN,
    WIFI_SM_WAIT_JOIN,
    WIFI_SM_SEND_STATE,
    WIFI_SM_WAIT_STATE,
    WIFI_SM_SEND_SNTP_CFG,
    WIFI_SM_WAIT_SNTP_CFG,
    WIFI_SM_SEND_SNTP_TIME,
    WIFI_SM_WAIT_SNTP_TIME
} wifi_sm_state_t;

/*
 * WiFi连接上下文：
 * 把入网流程拆成多个AT命令阶段逐步推进，
 * status 负责给界面显示当前联网状态，
 * state/deadline 负责驱动状态机和超时控制，
 * request_pending 用来承接外部提交的连接请求。
 */
typedef struct
{
    wifi_status_t status;
    wifi_sm_state_t state;
    TickType_t deadline;
    char ssid[WIFI_SSID_MAX_LEN + 1U];
    char password[WIFI_PASSWORD_MAX_LEN + 1U];
    uint8_t request_pending;
    uint8_t sntp_retry_count;
} wifi_context_t;

static SemaphoreHandle_t wifiMutex;
static uint8_t wifi_initialized = 0U;
static wifi_context_t g_wifi_ctx = {
    .status = WIFI_STATUS_IDLE,
    .state = WIFI_SM_IDLE,
    .deadline = 0U,
    .ssid = {0},
    .password = {0},
    .request_pending = 0U,
    .sntp_retry_count = 0U
};

static void wifi_finish_locked(wifi_status_t status);

static BaseType_t wifi_lock(TickType_t timeout)
{
    if (wifiMutex == NULL)
    {
        return pdFALSE;
    }

    return xSemaphoreTake(wifiMutex, timeout);
}

static void wifi_unlock(void)
{
    if (wifiMutex != NULL)
    {
        xSemaphoreGive(wifiMutex);
    }
}

static uint8_t wifi_has_invalid_char(const char *str)
{
    while ((str != 0) && (*str != '\0'))
    {
        if ((*str == '"') || (*str == '\r') || (*str == '\n'))
        {
            return 1U;
        }
        str++;
    }

    return 0U;
}

void wifi_init(void)
{
    if (wifiMutex == NULL)
    {
        wifiMutex = xSemaphoreCreateMutex();
    }

    if (wifi_initialized == 0U)
    {
        ESP_AT_Init();
        wifi_initialized = 1U;
    }
}

static void wifi_start_wait_state(wifi_sm_state_t next_state, uint32_t timeout_ms)
{
    g_wifi_ctx.state = next_state;
    g_wifi_ctx.deadline = xTaskGetTickCount() + pdMS_TO_TICKS(timeout_ms);
}

const char *wifi_status_to_text(wifi_status_t status)
{
    switch (status)
    {
    case WIFI_STATUS_IDLE:
        return "Idle";
    case WIFI_STATUS_CONNECTING:
        return "Connecting...";
    case WIFI_STATUS_CONNECTED:
        return "Connected";
    case WIFI_STATUS_SYNC_TIME:
        return "Syncing time...";
    case WIFI_STATUS_PARAM_ERROR:
        return "Invalid SSID/PWD";
    case WIFI_STATUS_MODULE_ERROR:
        return "ESP32-C3 no response";
    case WIFI_STATUS_TIME_SYNC_FAILED:
        return "Time sync failed";
    case WIFI_STATUS_AUTH_FAILED:
        return "Auth failed";
    case WIFI_STATUS_CONNECT_FAILED:
    default:
        return "Connect failed";
    }
}

wifi_status_t wifi_get_status(void)
{
    wifi_status_t status = WIFI_STATUS_IDLE;

    if (wifi_lock(WIFI_LOCK_TICKS) == pdTRUE)
    {
        status = g_wifi_ctx.status;
        wifi_unlock();
    }

    return status;
}

wifi_status_t wifi_request_connect(const char *ssid, const char *password)
{
    wifi_status_t result = WIFI_STATUS_CONNECTING;

    wifi_init();

    if ((ssid == 0) || (password == 0) || (ssid[0] == '\0') || (password[0] == '\0'))
    {
        if (wifi_lock(WIFI_LOCK_TICKS) == pdTRUE)
        {
            wifi_finish_locked(WIFI_STATUS_PARAM_ERROR);
            wifi_unlock();
        }
        return WIFI_STATUS_PARAM_ERROR;
    }

    if ((wifi_has_invalid_char(ssid) != 0U) || (wifi_has_invalid_char(password) != 0U))
    {
        if (wifi_lock(WIFI_LOCK_TICKS) == pdTRUE)
        {
            wifi_finish_locked(WIFI_STATUS_PARAM_ERROR);
            wifi_unlock();
        }
        return WIFI_STATUS_PARAM_ERROR;
    }

    if (wifi_lock(WIFI_LOCK_TICKS) != pdTRUE)
    {
        return WIFI_STATUS_CONNECT_FAILED;
    }

    strncpy(g_wifi_ctx.ssid, ssid, WIFI_SSID_MAX_LEN);
    g_wifi_ctx.ssid[WIFI_SSID_MAX_LEN] = '\0';
    strncpy(g_wifi_ctx.password, password, WIFI_PASSWORD_MAX_LEN);
    g_wifi_ctx.password[WIFI_PASSWORD_MAX_LEN] = '\0';
    /*
     * 这里只缓存参数并提交请求，不立即阻塞式发送AT命令。
     * 真正的联网流程在 wifi_task_process() 中一拍一拍推进，
     * 这样调用方不用等待，界面和其他任务也能继续运行。
     */
    g_wifi_ctx.request_pending = 1U;
    g_wifi_ctx.sntp_retry_count = 0U;
    g_wifi_ctx.status = WIFI_STATUS_CONNECTING;
    g_wifi_ctx.state = WIFI_SM_IDLE;
    wifi_unlock();

    return result;
}

static uint8_t wifi_response_contains(const char *response, const char *keyword)
{
    if ((response == 0) || (keyword == 0) || (keyword[0] == '\0'))
    {
        return 0U;
    }

    return (strstr(response, keyword) != 0) ? 1U : 0U;
}

static uint8_t wifi_is_timeout(TickType_t deadline, TickType_t now)
{
    return ((int32_t)(now - deadline) >= 0) ? 1U : 0U;
}

static void wifi_finish_locked(wifi_status_t status)
{
    g_wifi_ctx.status = status;
    g_wifi_ctx.state = WIFI_SM_IDLE;
    g_wifi_ctx.deadline = 0U;
    g_wifi_ctx.sntp_retry_count = 0U;
}

static void wifi_start_sntp_sync_locked(void)
{
    /*
     * 连上路由器后继续走SNTP校时流程。
     * 即使最终校时失败，系统也可能仍然具备联网能力，
     * 所以后续会把“联网成功”和“时间同步成功”分开处理。
     */
    g_wifi_ctx.status = WIFI_STATUS_SYNC_TIME;
    g_wifi_ctx.sntp_retry_count = 0U;
    g_wifi_ctx.state = WIFI_SM_SEND_SNTP_CFG;
}

void wifi_task_process(void)
{
    char response[WIFI_RESP_BUFFER_SIZE];
    char cmd[WIFI_CMD_BUFFER_SIZE];
    TickType_t now;

    wifi_init();

    if (wifi_lock(WIFI_LOCK_TICKS) != pdTRUE)
    {
        return;
    }

    if (g_wifi_ctx.request_pending != 0U)
    {
        /* 收到新的连接请求后，从AT握手阶段重新开始整套入网流程。 */
        g_wifi_ctx.request_pending = 0U;
        g_wifi_ctx.status = WIFI_STATUS_CONNECTING;
        g_wifi_ctx.state = WIFI_SM_SEND_AT;
    }

    now = xTaskGetTickCount();
    (void)ESP_AT_GetResponseSnapshot(response, sizeof(response));

    switch (g_wifi_ctx.state)
    {
    case WIFI_SM_IDLE:
        break;

    case WIFI_SM_SEND_AT:
        /* 先确认模组有响应，再继续后面的配置流程。 */
        ESP_AT_ClearResponse();
        ESP_AT_SendCmdAsync("AT");
        wifi_start_wait_state(WIFI_SM_WAIT_AT, 1000U);
        break;

    case WIFI_SM_WAIT_AT:
        if (wifi_response_contains(response, "OK"))
        {
            /* 模组握手成功，继续设置 STA 模式。 */
            g_wifi_ctx.state = WIFI_SM_SEND_MODE;
        }
        else if (wifi_response_contains(response, "ERROR") || wifi_response_contains(response, "FAIL"))
        {
            wifi_finish_locked(WIFI_STATUS_MODULE_ERROR);
        }
        else if (wifi_is_timeout(g_wifi_ctx.deadline, now))
        {
            wifi_finish_locked(WIFI_STATUS_MODULE_ERROR);
        }
        break;

    case WIFI_SM_SEND_MODE:
        /* 切到 STA 模式，准备主动连接路由器。 */
        ESP_AT_ClearResponse();
        ESP_AT_SendCmdAsync("AT+CWMODE=1");
        wifi_start_wait_state(WIFI_SM_WAIT_MODE, 1000U);
        break;

    case WIFI_SM_WAIT_MODE:
        if (wifi_response_contains(response, "OK"))
        {
            g_wifi_ctx.state = WIFI_SM_SEND_AUTOCONN;
        }
        else if (wifi_response_contains(response, "ERROR") || wifi_response_contains(response, "FAIL"))
        {
            wifi_finish_locked(WIFI_STATUS_CONNECT_FAILED);
        }
        else if (wifi_is_timeout(g_wifi_ctx.deadline, now))
        {
            wifi_finish_locked(WIFI_STATUS_CONNECT_FAILED);
        }
        break;

    case WIFI_SM_SEND_AUTOCONN:
        /* 关闭模组自动重连，让项目自己接管联网时序。 */
        ESP_AT_ClearResponse();
        ESP_AT_SendCmdAsync("AT+CWAUTOCONN=0");
        wifi_start_wait_state(WIFI_SM_WAIT_AUTOCONN, 1000U);
        break;

    case WIFI_SM_WAIT_AUTOCONN:
        /* 自动连接开关不是关键路径，成功失败都继续后续入网。 */
        if (wifi_response_contains(response, "OK") ||
            wifi_response_contains(response, "ERROR") ||
            wifi_response_contains(response, "FAIL") ||
            wifi_is_timeout(g_wifi_ctx.deadline, now))
        {
            g_wifi_ctx.state = WIFI_SM_SEND_JOIN;
        }
        break;

    case WIFI_SM_SEND_JOIN:
        /* 用缓存好的 SSID/密码发起正式入网请求。 */
        ESP_AT_ClearResponse();
        snprintf(cmd, sizeof(cmd), "AT+CWJAP=\"%s\",\"%s\"", g_wifi_ctx.ssid, g_wifi_ctx.password);
        ESP_AT_SendCmdAsync(cmd);
        wifi_start_wait_state(WIFI_SM_WAIT_JOIN, 20000U);
        break;

    case WIFI_SM_WAIT_JOIN:
        if (wifi_response_contains(response, "OK"))
        {
            /* 已收到入网成功应答，再查询当前链路状态做确认。 */
            g_wifi_ctx.state = WIFI_SM_SEND_STATE;
        }
        else if (wifi_response_contains(response, "+CWJAP:1") ||
                 wifi_response_contains(response, "+CWJAP:2") ||
                 wifi_response_contains(response, "+CWJAP:3") ||
                 wifi_response_contains(response, "+CWJAP:4"))
        {
            wifi_finish_locked(WIFI_STATUS_AUTH_FAILED);
        }
        else if (wifi_response_contains(response, "ERROR") || wifi_response_contains(response, "FAIL"))
        {
            wifi_finish_locked(WIFI_STATUS_CONNECT_FAILED);
        }
        else if (wifi_is_timeout(g_wifi_ctx.deadline, now))
        {
            wifi_finish_locked(WIFI_STATUS_CONNECT_FAILED);
        }
        break;

    case WIFI_SM_SEND_STATE:
        /* 查询模组当前联网状态，判断是否真的拿到连接。 */
        ESP_AT_ClearResponse();
        ESP_AT_SendCmdAsync("AT+CWSTATE?");
        wifi_start_wait_state(WIFI_SM_WAIT_STATE, 1000U);
        break;

    case WIFI_SM_WAIT_STATE:
        if (wifi_response_contains(response, "+CWSTATE:2") ||
            wifi_response_contains(response, "+CWSTATE:3"))
        {
            /* 确认已连网后进入 SNTP 校时阶段。 */
            wifi_start_sntp_sync_locked();
        }
        else if (wifi_response_contains(response, "+CWSTATE:"))
        {
            wifi_finish_locked(WIFI_STATUS_CONNECT_FAILED);
        }
        else if (wifi_response_contains(response, "ERROR") || wifi_response_contains(response, "FAIL"))
        {
            /* 状态查询失败时，仍尝试继续校时流程，兼容部分固件响应差异。 */
            wifi_start_sntp_sync_locked();
        }
        else if (wifi_is_timeout(g_wifi_ctx.deadline, now))
        {
            /* 查询超时也继续往下走，避免因为状态查询卡死整条联网链路。 */
            wifi_start_sntp_sync_locked();
        }
        break;

    case WIFI_SM_SEND_SNTP_CFG:
        /* 先打开 SNTP 功能，再单独请求一次网络时间。 */
        ESP_AT_ClearResponse();
        ESP_AT_EnableSntp();
        wifi_start_wait_state(WIFI_SM_WAIT_SNTP_CFG, 2000U);
        break;

    case WIFI_SM_WAIT_SNTP_CFG:
        if (wifi_response_contains(response, "OK"))
        {
            /* SNTP 配置完成后，进入具体取时阶段。 */
            g_wifi_ctx.status = WIFI_STATUS_SYNC_TIME;
            g_wifi_ctx.sntp_retry_count = 0U;
            g_wifi_ctx.state = WIFI_SM_SEND_SNTP_TIME;
        }
        else if (wifi_response_contains(response, "ERROR") || wifi_response_contains(response, "FAIL"))
        {
            wifi_finish_locked(WIFI_STATUS_TIME_SYNC_FAILED);
        }
        else if (wifi_is_timeout(g_wifi_ctx.deadline, now))
        {
            wifi_finish_locked(WIFI_STATUS_TIME_SYNC_FAILED);
        }
        break;

    case WIFI_SM_SEND_SNTP_TIME:
        /* 主动拉取一次时间，成功后写入RTC。 */
        ESP_AT_ClearResponse();
        ESP_AT_RequestSntpTime();
        wifi_start_wait_state(WIFI_SM_WAIT_SNTP_TIME, 5000U);
        break;

    case WIFI_SM_WAIT_SNTP_TIME:
        if (wifi_response_contains(response, "+CIPSNTPTIME:"))
        {
            esp_at_datetime_t datetime;

            if (ESP_AT_ParseSntpTime(response, &datetime) != 0U)
            {
                /* 时间解析成功后写入RTC，联网流程正式完成。 */
                rtc_set_time_from_esp(&datetime);
                wifi_finish_locked(WIFI_STATUS_CONNECTED);
            }
            else if (g_wifi_ctx.sntp_retry_count < WIFI_SNTP_RETRY_MAX)
            {
                /* 已拿到返回但解析失败时，按重试上限继续请求。 */
                g_wifi_ctx.status = WIFI_STATUS_SYNC_TIME;
                g_wifi_ctx.sntp_retry_count++;
                g_wifi_ctx.state = WIFI_SM_SEND_SNTP_TIME;
            }
            else
            {
                wifi_finish_locked(WIFI_STATUS_TIME_SYNC_FAILED);
            }
        }
        else if (wifi_response_contains(response, "ERROR") || wifi_response_contains(response, "FAIL"))
        {
            if (g_wifi_ctx.sntp_retry_count < WIFI_SNTP_RETRY_MAX)
            {
                /* 模组明确报错时同样允许有限次重试。 */
                g_wifi_ctx.status = WIFI_STATUS_SYNC_TIME;
                g_wifi_ctx.sntp_retry_count++;
                g_wifi_ctx.state = WIFI_SM_SEND_SNTP_TIME;
            }
            else
            {
                wifi_finish_locked(WIFI_STATUS_TIME_SYNC_FAILED);
            }
        }
        else if (wifi_is_timeout(g_wifi_ctx.deadline, now))
        {
            if (g_wifi_ctx.sntp_retry_count < WIFI_SNTP_RETRY_MAX)
            {
                /* 超时按同一套重试策略处理，避免偶发网络波动导致直接失败。 */
                g_wifi_ctx.status = WIFI_STATUS_SYNC_TIME;
                g_wifi_ctx.sntp_retry_count++;
                g_wifi_ctx.state = WIFI_SM_SEND_SNTP_TIME;
            }
            else
            {
                wifi_finish_locked(WIFI_STATUS_TIME_SYNC_FAILED);
            }
        }
        break;

    default:
        wifi_finish_locked(WIFI_STATUS_CONNECT_FAILED);
        break;
    }

    wifi_unlock();
}
