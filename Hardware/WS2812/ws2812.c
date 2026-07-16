#include "ws2812.h"

#define WS2812_GPIO_PORT               GPIOB
#define WS2812_GPIO_PIN                GPIO_Pin_5
#define WS2812_GPIO_PIN_SOURCE         GPIO_PinSource5
#define WS2812_GPIO_CLK                RCC_AHB1Periph_GPIOB
#define WS2812_GPIO_AF                 GPIO_AF_TIM3

#define WS2812_TIM                     TIM3
#define WS2812_TIM_CLK                 RCC_APB1Periph_TIM3
#define WS2812_TIM_DMA_REQ             TIM_DMA_CC2
#define WS2812_TIM_CCR_ADDR            ((uint32_t)&TIM3->CCR2)

#define WS2812_DMA_CLK                 RCC_AHB1Periph_DMA1
#define WS2812_DMA_STREAM              DMA1_Stream5
#define WS2812_DMA_CHANNEL             DMA_Channel_5
#define WS2812_DMA_FLAG_TC             DMA_FLAG_TCIF5
#define WS2812_DMA_FLAG_TE             DMA_FLAG_TEIF5
#define WS2812_DMA_FLAG_DME            DMA_FLAG_DMEIF5
#define WS2812_DMA_FLAG_FE             DMA_FLAG_FEIF5
#define WS2812_DMA_FLAG_HT             DMA_FLAG_HTIF5
#define WS2812_DMA_ALL_FLAGS           (WS2812_DMA_FLAG_TC | WS2812_DMA_FLAG_TE | \
                                        WS2812_DMA_FLAG_DME | WS2812_DMA_FLAG_FE | \
                                        WS2812_DMA_FLAG_HT)

#define WS2812_PWM_FREQ_HZ             800000U
#define WS2812_RESET_US                80U
#define WS2812_BITS_PER_LED            24U
#define WS2812_RESET_SLOTS             ((WS2812_PWM_FREQ_HZ * WS2812_RESET_US) / 1000000U)
#define WS2812_PWM_BUF_LEN             ((WS2812_LED_NUM * WS2812_BITS_PER_LED) + WS2812_RESET_SLOTS)

static uint8_t ws2812_pixel_buf[WS2812_LED_NUM][3];
static uint16_t ws2812_pwm_buf[WS2812_PWM_BUF_LEN];
static uint16_t ws2812_pwm_period = 0U;
static uint16_t ws2812_pwm_t0h = 0U;
static uint16_t ws2812_pwm_t1h = 0U;
static uint8_t ws2812_is_busy = 0U;

static uint32_t ws2812_get_tim3_clock(void)
{
    RCC_ClocksTypeDef clocks;
    uint32_t tim_clock;

    RCC_GetClocksFreq(&clocks);
    tim_clock = clocks.PCLK1_Frequency;

    if (clocks.HCLK_Frequency != clocks.PCLK1_Frequency)
    {
        tim_clock *= 2U;
    }

    return tim_clock;
}

static void ws2812_gpio_init(void)
{
    GPIO_InitTypeDef gpio_init;

    RCC_AHB1PeriphClockCmd(WS2812_GPIO_CLK, ENABLE);

    GPIO_StructInit(&gpio_init);
    gpio_init.GPIO_Pin = WS2812_GPIO_PIN;
    gpio_init.GPIO_Mode = GPIO_Mode_AF;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd = GPIO_PuPd_NOPULL;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(WS2812_GPIO_PORT, &gpio_init);

    GPIO_PinAFConfig(WS2812_GPIO_PORT, WS2812_GPIO_PIN_SOURCE, WS2812_GPIO_AF);
}

static void ws2812_tim3_pwm_init(void)
{
    TIM_TimeBaseInitTypeDef tim_base_init;
    TIM_OCInitTypeDef tim_oc_init;
    uint32_t tim_clock = ws2812_get_tim3_clock();

    RCC_APB1PeriphClockCmd(WS2812_TIM_CLK, ENABLE);

    ws2812_pwm_period = (uint16_t)((tim_clock / WS2812_PWM_FREQ_HZ) - 1U);
    ws2812_pwm_t0h = (uint16_t)((tim_clock * 35U) / 100000000U);
    ws2812_pwm_t1h = (uint16_t)((tim_clock * 70U) / 100000000U);

    if (ws2812_pwm_t0h == 0U)
    {
        ws2812_pwm_t0h = 1U;
    }

    if (ws2812_pwm_t1h <= ws2812_pwm_t0h)
    {
        ws2812_pwm_t1h = ws2812_pwm_t0h + 1U;
    }

    TIM_DeInit(WS2812_TIM);

    TIM_TimeBaseStructInit(&tim_base_init);
    tim_base_init.TIM_Period = ws2812_pwm_period;
    tim_base_init.TIM_Prescaler = 0U;
    tim_base_init.TIM_ClockDivision = TIM_CKD_DIV1;
    tim_base_init.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(WS2812_TIM, &tim_base_init);

    TIM_OCStructInit(&tim_oc_init);
    tim_oc_init.TIM_OCMode = TIM_OCMode_PWM1;
    tim_oc_init.TIM_OutputState = TIM_OutputState_Enable;
    tim_oc_init.TIM_Pulse = 0U;
    tim_oc_init.TIM_OCPolarity = TIM_OCPolarity_High;
    TIM_OC2Init(WS2812_TIM, &tim_oc_init);
    TIM_OC2PreloadConfig(WS2812_TIM, TIM_OCPreload_Enable);

    TIM_ARRPreloadConfig(WS2812_TIM, ENABLE);
    TIM_DMACmd(WS2812_TIM, WS2812_TIM_DMA_REQ, ENABLE);
    TIM_Cmd(WS2812_TIM, DISABLE);
}

static void ws2812_dma_init(void)
{
    DMA_InitTypeDef dma_init;

    RCC_AHB1PeriphClockCmd(WS2812_DMA_CLK, ENABLE);

    DMA_Cmd(WS2812_DMA_STREAM, DISABLE);
    while (DMA_GetCmdStatus(WS2812_DMA_STREAM) != DISABLE)
    {
    }

    DMA_DeInit(WS2812_DMA_STREAM);
    DMA_ClearFlag(WS2812_DMA_STREAM, WS2812_DMA_ALL_FLAGS);

    DMA_StructInit(&dma_init);
    dma_init.DMA_Channel = WS2812_DMA_CHANNEL;
    dma_init.DMA_PeripheralBaseAddr = WS2812_TIM_CCR_ADDR;
    dma_init.DMA_Memory0BaseAddr = (uint32_t)ws2812_pwm_buf;
    dma_init.DMA_DIR = DMA_DIR_MemoryToPeripheral;
    dma_init.DMA_BufferSize = WS2812_PWM_BUF_LEN;
    dma_init.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    dma_init.DMA_MemoryInc = DMA_MemoryInc_Enable;
    dma_init.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    dma_init.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    dma_init.DMA_Mode = DMA_Mode_Normal;
    dma_init.DMA_Priority = DMA_Priority_High;
    dma_init.DMA_FIFOMode = DMA_FIFOMode_Disable;
    dma_init.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
    dma_init.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    dma_init.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    DMA_Init(WS2812_DMA_STREAM, &dma_init);
}

static void ws2812_encode_pixels(void)
{
    uint32_t led;
    uint32_t color;
    uint16_t index = 0U;
    uint8_t bit;

    for (led = 0U; led < WS2812_LED_NUM; led++)
    {
        color = ((uint32_t)ws2812_pixel_buf[led][0] << 16) |
                ((uint32_t)ws2812_pixel_buf[led][1] << 8) |
                ((uint32_t)ws2812_pixel_buf[led][2]);

        for (bit = 0U; bit < WS2812_BITS_PER_LED; bit++)
        {
            if ((color & (0x800000U >> bit)) != 0U)
            {
                ws2812_pwm_buf[index++] = ws2812_pwm_t1h;
            }
            else
            {
                ws2812_pwm_buf[index++] = ws2812_pwm_t0h;
            }
        }
    }

    while (index < WS2812_PWM_BUF_LEN)
    {
        ws2812_pwm_buf[index++] = 0U;
    }
}

void WS2812_Init(void)
{
    ws2812_gpio_init();
    ws2812_tim3_pwm_init();
    ws2812_dma_init();
    WS2812_Clear();
    WS2812_Refresh();
}

void WS2812_SetPixelRGB(uint16_t index, uint8_t red, uint8_t green, uint8_t blue)
{
    if (index >= WS2812_LED_NUM)
    {
        return;
    }

    ws2812_pixel_buf[index][0] = green;
    ws2812_pixel_buf[index][1] = red;
    ws2812_pixel_buf[index][2] = blue;
}

void WS2812_SetPixelGRB(uint16_t index, uint8_t green, uint8_t red, uint8_t blue)
{
    if (index >= WS2812_LED_NUM)
    {
        return;
    }

    ws2812_pixel_buf[index][0] = green;
    ws2812_pixel_buf[index][1] = red;
    ws2812_pixel_buf[index][2] = blue;
}

void WS2812_SetPixelColor(uint16_t index, uint32_t rgb)
{
    WS2812_SetPixelRGB(index,
                       (uint8_t)((rgb >> 16) & 0xFFU),
                       (uint8_t)((rgb >> 8) & 0xFFU),
                       (uint8_t)(rgb & 0xFFU));
}

void WS2812_FillRGB(uint8_t red, uint8_t green, uint8_t blue)
{
    uint16_t index;

    for (index = 0U; index < WS2812_LED_NUM; index++)
    {
        WS2812_SetPixelRGB(index, red, green, blue);
    }
}

void WS2812_Clear(void)
{
    WS2812_FillRGB(0U, 0U, 0U);
}

void WS2812_Refresh(void)
{
    if (ws2812_is_busy != 0U)
    {
        return;
    }

    ws2812_is_busy = 1U;
    ws2812_encode_pixels();

    DMA_Cmd(WS2812_DMA_STREAM, DISABLE);
    while (DMA_GetCmdStatus(WS2812_DMA_STREAM) != DISABLE)
    {
    }

    DMA_ClearFlag(WS2812_DMA_STREAM, WS2812_DMA_ALL_FLAGS);
    DMA_SetCurrDataCounter(WS2812_DMA_STREAM, WS2812_PWM_BUF_LEN);

    TIM_SetCompare2(WS2812_TIM, 0U);
    TIM_SetCounter(WS2812_TIM, 0U);

    DMA_Cmd(WS2812_DMA_STREAM, ENABLE);
    TIM_Cmd(WS2812_TIM, ENABLE);

    while (DMA_GetFlagStatus(WS2812_DMA_STREAM, WS2812_DMA_FLAG_TC) == RESET)
    {
    }

    TIM_Cmd(WS2812_TIM, DISABLE);
    DMA_Cmd(WS2812_DMA_STREAM, DISABLE);
    DMA_ClearFlag(WS2812_DMA_STREAM, WS2812_DMA_ALL_FLAGS);
    TIM_SetCompare2(WS2812_TIM, 0U);
    GPIO_ResetBits(WS2812_GPIO_PORT, WS2812_GPIO_PIN);

    ws2812_is_busy = 0U;
}

uint8_t WS2812_IsBusy(void)
{
    return ws2812_is_busy;
}
