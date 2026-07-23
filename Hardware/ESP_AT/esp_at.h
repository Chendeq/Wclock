#ifndef __ESP_AT_H__
#define __ESP_AT_H__

#include <stdint.h>

typedef struct
{
    uint16_t year;
    uint8_t month;
    uint8_t day;
    uint8_t hour;
    uint8_t minute;
    uint8_t second;
    uint8_t weekday;
} esp_at_datetime_t;

void ESP_AT_Init(void);
void ESP_AT_ClearResponse(void);
void ESP_AT_SendCmdAsync(const char *cmd);
void ESP_AT_SendRaw(const char *data);
uint16_t ESP_AT_GetResponseSnapshot(char *buffer, uint16_t size);
void ESP_AT_PrepareSend(uint16_t len);
void ESP_AT_HttpGet(const char *url);
void ESP_AT_EnableSntp(void);
void ESP_AT_RequestSntpTime(void);
uint8_t ESP_AT_ParseSntpTime(const char *response, esp_at_datetime_t *datetime);

#endif
