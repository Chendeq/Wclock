#ifndef __WIFI_H__
#define __WIFI_H__

#include <stdint.h>

typedef enum
{
    WIFI_STATUS_IDLE = 0,
    WIFI_STATUS_CONNECTING,
    WIFI_STATUS_CONNECTED,
    WIFI_STATUS_SYNC_TIME,
    WIFI_STATUS_PARAM_ERROR,
    WIFI_STATUS_MODULE_ERROR,
    WIFI_STATUS_TIME_SYNC_FAILED,
    WIFI_STATUS_AUTH_FAILED,
    WIFI_STATUS_CONNECT_FAILED
} wifi_status_t;

void wifi_init(void);
void wifi_task_process(void);
wifi_status_t wifi_request_connect(const char *ssid, const char *password);
wifi_status_t wifi_get_status(void);
const char *wifi_status_to_text(wifi_status_t status);

#endif
