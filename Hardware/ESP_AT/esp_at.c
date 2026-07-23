#include "esp_at.h"

#include <stdio.h>
#include <string.h>
#include "misc.h"
#include "stm32f4xx_dma.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_usart.h"

#define ESP_AT_UART                  USART2
#define ESP_AT_UART_GPIO_PORT        GPIOA
#define ESP_AT_UART_GPIO_CLK         RCC_AHB1Periph_GPIOA
#define ESP_AT_UART_CLK              RCC_APB1Periph_USART2
#define ESP_AT_UART_TX_PIN           GPIO_Pin_2
#define ESP_AT_UART_RX_PIN           GPIO_Pin_3
#define ESP_AT_UART_TX_SOURCE        GPIO_PinSource2
#define ESP_AT_UART_RX_SOURCE        GPIO_PinSource3
#define ESP_AT_UART_AF               GPIO_AF_USART2
#define ESP_AT_BAUDRATE              115200U
#define ESP_AT_RX_BUFFER_SIZE        1536U
#define ESP_AT_TX_DMA_STREAM         DMA1_Stream6
#define ESP_AT_TX_DMA_CHANNEL        DMA_Channel_4
#define ESP_AT_TX_DMA_FLAG_TCIF      DMA_FLAG_TCIF6

static const char *esp_at_months[12] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

static const char *esp_at_weekdays[7] = {
    "Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"
};

static uint8_t esp_at_initialized = 0U;
static volatile char esp_at_rx_buffer[ESP_AT_RX_BUFFER_SIZE];
static volatile uint16_t esp_at_rx_len = 0U;
static char esp_at_tx_buffer[256];

static void esp_at_drain_uart_rx(void)
{
    while (USART_GetFlagStatus(ESP_AT_UART, USART_FLAG_RXNE) != RESET)
    {
        (void)USART_ReceiveData(ESP_AT_UART);
    }
}

static void esp_at_dma_init(void)
{
    DMA_InitTypeDef dma_init;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
    DMA_DeInit(ESP_AT_TX_DMA_STREAM);
    while (DMA_GetCmdStatus(ESP_AT_TX_DMA_STREAM) != DISABLE)
    {
    }

    dma_init.DMA_Channel = ESP_AT_TX_DMA_CHANNEL;
    dma_init.DMA_PeripheralBaseAddr = (uint32_t)&ESP_AT_UART->DR;
    dma_init.DMA_Memory0BaseAddr = (uint32_t)esp_at_tx_buffer;
    dma_init.DMA_DIR = DMA_DIR_MemoryToPeripheral;
    dma_init.DMA_BufferSize = 0U;
    dma_init.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    dma_init.DMA_MemoryInc = DMA_MemoryInc_Enable;
    dma_init.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
    dma_init.DMA_MemoryDataSize = DMA_MemoryDataSize_Byte;
    dma_init.DMA_Mode = DMA_Mode_Normal;
    dma_init.DMA_Priority = DMA_Priority_Medium;
    dma_init.DMA_FIFOMode = DMA_FIFOMode_Disable;
    dma_init.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
    dma_init.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    dma_init.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    DMA_Init(ESP_AT_TX_DMA_STREAM, &dma_init);
}

static void esp_at_append_rx_char(uint8_t ch)
{
    if (esp_at_rx_len < (ESP_AT_RX_BUFFER_SIZE - 1U))
    {
        esp_at_rx_buffer[esp_at_rx_len++] = (char)ch;
        esp_at_rx_buffer[esp_at_rx_len] = '\0';
    }
}

void ESP_AT_Init(void)
{
    GPIO_InitTypeDef gpio_init;
    USART_InitTypeDef usart_init;
    NVIC_InitTypeDef nvic_init;

    if (esp_at_initialized != 0U)
    {
        return;
    }

    RCC_AHB1PeriphClockCmd(ESP_AT_UART_GPIO_CLK, ENABLE);
    RCC_APB1PeriphClockCmd(ESP_AT_UART_CLK, ENABLE);

    gpio_init.GPIO_Pin = ESP_AT_UART_TX_PIN | ESP_AT_UART_RX_PIN;
    gpio_init.GPIO_Mode = GPIO_Mode_AF;
    gpio_init.GPIO_Speed = GPIO_High_Speed;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(ESP_AT_UART_GPIO_PORT, &gpio_init);

    GPIO_PinAFConfig(ESP_AT_UART_GPIO_PORT, ESP_AT_UART_TX_SOURCE, ESP_AT_UART_AF);
    GPIO_PinAFConfig(ESP_AT_UART_GPIO_PORT, ESP_AT_UART_RX_SOURCE, ESP_AT_UART_AF);

    usart_init.USART_BaudRate = ESP_AT_BAUDRATE;
    usart_init.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    usart_init.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
    usart_init.USART_Parity = USART_Parity_No;
    usart_init.USART_StopBits = USART_StopBits_1;
    usart_init.USART_WordLength = USART_WordLength_8b;
    USART_Init(ESP_AT_UART, &usart_init);
    USART_DMACmd(ESP_AT_UART, USART_DMAReq_Tx, ENABLE);
    USART_ITConfig(ESP_AT_UART, USART_IT_RXNE, ENABLE);
    USART_Cmd(ESP_AT_UART, ENABLE);
    esp_at_dma_init();


    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

    nvic_init.NVIC_IRQChannel = USART2_IRQn;
    nvic_init.NVIC_IRQChannelPreemptionPriority = 6;
    nvic_init.NVIC_IRQChannelSubPriority = 0;
    nvic_init.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic_init);

    ESP_AT_ClearResponse();
    esp_at_initialized = 1U;
}

void ESP_AT_ClearResponse(void)
{
    __disable_irq();
    esp_at_rx_len = 0U;
    esp_at_rx_buffer[0] = '\0';
    __enable_irq();
    esp_at_drain_uart_rx();
}

static void esp_at_send_string(const char *str)
{
    uint16_t len;

    if (str == 0)
    {
        return;
    }

    len = (uint16_t)strlen(str);
    if (len == 0U)
    {
        return;
    }

    if (len >= sizeof(esp_at_tx_buffer))
    {
        len = (uint16_t)(sizeof(esp_at_tx_buffer) - 1U);
    }

    memcpy(esp_at_tx_buffer, str, len);
    esp_at_tx_buffer[len] = '\0';

    DMA_Cmd(ESP_AT_TX_DMA_STREAM, DISABLE);
    while (DMA_GetCmdStatus(ESP_AT_TX_DMA_STREAM) != DISABLE)
    {
    }
    DMA_ClearFlag(ESP_AT_TX_DMA_STREAM, ESP_AT_TX_DMA_FLAG_TCIF);
    ESP_AT_TX_DMA_STREAM->M0AR = (uint32_t)esp_at_tx_buffer;
    ESP_AT_TX_DMA_STREAM->NDTR = len;
    DMA_Cmd(ESP_AT_TX_DMA_STREAM, ENABLE);

    while (DMA_GetFlagStatus(ESP_AT_TX_DMA_STREAM, ESP_AT_TX_DMA_FLAG_TCIF) == RESET)
    {
    }
    DMA_ClearFlag(ESP_AT_TX_DMA_STREAM, ESP_AT_TX_DMA_FLAG_TCIF);

    while (USART_GetFlagStatus(ESP_AT_UART, USART_FLAG_TC) == RESET)
    {
    }
}

void ESP_AT_SendCmdAsync(const char *cmd)
{
    if (cmd == 0)
    {
        return;
    }

    ESP_AT_Init();
    esp_at_send_string(cmd);
    esp_at_send_string("\r\n");
}

void ESP_AT_SendRaw(const char *data)
{
    if (data == 0)
    {
        return;
    }

    ESP_AT_Init();
    esp_at_send_string(data);
}

uint16_t ESP_AT_GetResponseSnapshot(char *buffer, uint16_t size)
{
    uint16_t copy_len;

    if ((buffer == 0) || (size == 0U))
    {
        return 0U;
    }

    __disable_irq();
    copy_len = esp_at_rx_len;
    if (copy_len >= size)
    {
        copy_len = (uint16_t)(size - 1U);
    }
    memcpy(buffer, (const void *)esp_at_rx_buffer, copy_len);
    buffer[copy_len] = '\0';
    __enable_irq();

    return copy_len;
}

void ESP_AT_PrepareSend(uint16_t len)
{
    char cmd[24];

    snprintf(cmd, sizeof(cmd), "AT+CIPSEND=%u", (unsigned int)len);
    ESP_AT_SendCmdAsync(cmd);
}

void ESP_AT_HttpGet(const char *url)
{
    char cmd[192];

    if (url == 0)
    {
        return;
    }

    snprintf(cmd, sizeof(cmd), "AT+HTTPCLIENT=2,1,\"%s\",,,2", url);
    ESP_AT_SendCmdAsync(cmd);
}

void ESP_AT_EnableSntp(void)
{
    ESP_AT_SendCmdAsync("AT+CIPSNTPCFG=1,8");
}

void ESP_AT_RequestSntpTime(void)
{
    ESP_AT_SendCmdAsync("AT+CIPSNTPTIME?");
}

static uint8_t esp_at_parse_month(const char *month)
{
    uint8_t i;

    for (i = 0U; i < 12U; i++)
    {
        if (strcmp(month, esp_at_months[i]) == 0)
        {
            return (uint8_t)(i + 1U);
        }
    }

    return 0U;
}

static uint8_t esp_at_parse_weekday(const char *weekday)
{
    uint8_t i;

    for (i = 0U; i < 7U; i++)
    {
        if (strcmp(weekday, esp_at_weekdays[i]) == 0)
        {
            return (uint8_t)(i + 1U);
        }
    }

    return 0U;
}

uint8_t ESP_AT_ParseSntpTime(const char *response, esp_at_datetime_t *datetime)
{
    const char *time_ptr;
    char weekday[4];
    char month[4];

    if ((response == 0) || (datetime == 0))
    {
        return 0U;
    }

    time_ptr = strstr(response, "+CIPSNTPTIME:");
    if (time_ptr == 0)
    {
        return 0U;
    }

    weekday[0] = '\0';
    month[0] = '\0';

    if (sscanf(time_ptr, "+CIPSNTPTIME:%3s %3s %hhu %hhu:%hhu:%hhu %hu",
               weekday,
               month,
               &datetime->day,
               &datetime->hour,
               &datetime->minute,
               &datetime->second,
               &datetime->year) != 7)
    {
        return 0U;
    }

    datetime->month = esp_at_parse_month(month);
    datetime->weekday = esp_at_parse_weekday(weekday);

    if ((datetime->month == 0U) || (datetime->weekday == 0U))
    {
        return 0U;
    }

    if ((datetime->year < 2024U) ||
        (datetime->month > 12U) ||
        (datetime->day == 0U) || (datetime->day > 31U) ||
        (datetime->hour > 23U) ||
        (datetime->minute > 59U) ||
        (datetime->second > 59U))
    {
        return 0U;
    }

    return 1U;
}

void USART2_IRQHandler(void)
{
    if (USART_GetITStatus(ESP_AT_UART, USART_IT_RXNE) != RESET)
    {
        esp_at_append_rx_char((uint8_t)(USART_ReceiveData(ESP_AT_UART) & 0xFFU));
        USART_ClearITPendingBit(ESP_AT_UART, USART_IT_RXNE);
    }
}
