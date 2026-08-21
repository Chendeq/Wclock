#include "adc.h"
#include "delay.h"

#define ADC_BATT_GPIO_PORT GPIOC
#define ADC_BATT_GPIO_PIN GPIO_Pin_0
#define ADC_BATT_GPIO_CLK RCC_AHB1Periph_GPIOC
#define ADC_BATT_CHANNEL ADC_Channel_10

#define BATT_DET_GPIO_PORT GPIOC
#define BATT_DET_GPIO_PIN GPIO_Pin_1
#define BATT_DET_GPIO_CLK RCC_AHB1Periph_GPIOC

#define ADC_BATT_DMA_CLK RCC_AHB1Periph_DMA2
#define ADC_BATT_DMA_STREAM DMA2_Stream0
#define ADC_BATT_DMA_CHANNEL DMA_Channel_0
#define ADC_BATT_DMA_IRQn DMA2_Stream0_IRQn
#define ADC_BATT_DMA_TC_FLAG DMA_FLAG_TCIF0
#define ADC_BATT_DMA_TE_FLAG DMA_FLAG_TEIF0
#define ADC_BATT_DMA_ALL_FLAGS (DMA_FLAG_FEIF0 | DMA_FLAG_DMEIF0 | DMA_FLAG_TEIF0 | DMA_FLAG_HTIF0 | DMA_FLAG_TCIF0)

#define ADC_BATT_SAMPLE_COUNT 8U
#define ADC_REFERENCE_MV 3300U
#define ADC_RESOLUTION_MAX 4095U
#define ADC_BATT_R_TOP_OHM 30000U
#define ADC_BATT_R_BOTTOM_OHM 15000U
#define ADC_BATT_DIVIDER_NUM (ADC_BATT_R_TOP_OHM + ADC_BATT_R_BOTTOM_OHM)
#define ADC_BATT_DIVIDER_DEN ADC_BATT_R_BOTTOM_OHM
#define ADC_BATT_SETTLE_DELAY_MS 5U

static volatile uint16_t adc_battery_last_raw;
static volatile uint16_t adc_battery_last_voltage_mv;
static volatile uint8_t adc_battery_last_percent;
static volatile uint16_t adc_battery_dma_buffer[ADC_BATT_SAMPLE_COUNT];
static volatile uint8_t adc_battery_sampling;
static volatile uint8_t adc_battery_sample_ready;

static void adc_battery_switch(uint8_t enable)
{
    if (enable != 0U)
    {
        GPIO_SetBits(BATT_DET_GPIO_PORT, BATT_DET_GPIO_PIN);
    }
    else
    {
        GPIO_ResetBits(BATT_DET_GPIO_PORT, BATT_DET_GPIO_PIN);
    }
}

static uint8_t adc_battery_calc_percent(uint32_t battery_mv)
{
    uint32_t percent;

    if (battery_mv <= ADC_BATTERY_EMPTY_MV)
    {
        return 0U;
    }

    if (battery_mv >= ADC_BATTERY_FULL_MV)
    {
        return 100U;
    }

    percent = (battery_mv - ADC_BATTERY_EMPTY_MV) * 100U;
    percent /= (ADC_BATTERY_FULL_MV - ADC_BATTERY_EMPTY_MV);

    return (uint8_t)percent;
}

static void adc_battery_dma_init(void)
{
    DMA_InitTypeDef dma_init;
    NVIC_InitTypeDef nvic_init;

    DMA_Cmd(ADC_BATT_DMA_STREAM, DISABLE);
    while (DMA_GetCmdStatus(ADC_BATT_DMA_STREAM) != DISABLE)
    {
    }

    DMA_DeInit(ADC_BATT_DMA_STREAM);
    DMA_StructInit(&dma_init);
    dma_init.DMA_Channel = ADC_BATT_DMA_CHANNEL;
    dma_init.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR;
    dma_init.DMA_Memory0BaseAddr = (uint32_t)adc_battery_dma_buffer;
    dma_init.DMA_DIR = DMA_DIR_PeripheralToMemory;
    dma_init.DMA_BufferSize = ADC_BATT_SAMPLE_COUNT;
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
    DMA_Init(ADC_BATT_DMA_STREAM, &dma_init);

    DMA_ClearFlag(ADC_BATT_DMA_STREAM, ADC_BATT_DMA_ALL_FLAGS);
    DMA_ITConfig(ADC_BATT_DMA_STREAM, DMA_IT_TC | DMA_IT_TE, ENABLE);

    nvic_init.NVIC_IRQChannel = ADC_BATT_DMA_IRQn;
    nvic_init.NVIC_IRQChannelPreemptionPriority = 2;
    nvic_init.NVIC_IRQChannelSubPriority = 2;
    nvic_init.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&nvic_init);
}

static void adc_battery_prepare_dma_transfer(void)
{
    uint32_t index;

    DMA_Cmd(ADC_BATT_DMA_STREAM, DISABLE);
    while (DMA_GetCmdStatus(ADC_BATT_DMA_STREAM) != DISABLE)
    {
    }

    for (index = 0U; index < ADC_BATT_SAMPLE_COUNT; index++)
    {
        adc_battery_dma_buffer[index] = 0U;
    }

    DMA_ClearFlag(ADC_BATT_DMA_STREAM, ADC_BATT_DMA_ALL_FLAGS);
    ADC_BATT_DMA_STREAM->M0AR = (uint32_t)adc_battery_dma_buffer;
    ADC_BATT_DMA_STREAM->NDTR = ADC_BATT_SAMPLE_COUNT;
    DMA_Cmd(ADC_BATT_DMA_STREAM, ENABLE);
}

static void adc_battery_stop_hw(void)
{
    ADC_Cmd(ADC1, DISABLE);
    DMA_Cmd(ADC_BATT_DMA_STREAM, DISABLE);
    while (DMA_GetCmdStatus(ADC_BATT_DMA_STREAM) != DISABLE)
    {
    }
    ADC_ClearFlag(ADC1, ADC_FLAG_EOC | ADC_FLAG_OVR);
    adc_battery_switch(0U);
}

static void adc_battery_complete_sampling(void)
{
    uint32_t sum = 0U;
    uint32_t index;
    uint32_t adc_mv;
    uint32_t battery_mv;

    for (index = 0U; index < ADC_BATT_SAMPLE_COUNT; index++)
    {
        sum += adc_battery_dma_buffer[index];
    }

    adc_battery_last_raw = (uint16_t)(sum / ADC_BATT_SAMPLE_COUNT);
    adc_mv = ((uint32_t)adc_battery_last_raw * ADC_REFERENCE_MV + (ADC_RESOLUTION_MAX / 2U)) / ADC_RESOLUTION_MAX;
    battery_mv = (adc_mv * ADC_BATT_DIVIDER_NUM + (ADC_BATT_DIVIDER_DEN / 2U)) / ADC_BATT_DIVIDER_DEN;
    adc_battery_last_voltage_mv = (uint16_t)battery_mv;
    adc_battery_last_percent = adc_battery_calc_percent(battery_mv);

    adc_battery_sampling = 0U;
    adc_battery_sample_ready = 1U;
}

static void adc_battery_reset_after_error(void)
{
    adc_battery_stop_hw();
    adc_battery_sampling = 0U;
}

void ADC_Battery_Init(void)
{
    GPIO_InitTypeDef gpio_init;
    ADC_CommonInitTypeDef adc_common_init;
    ADC_InitTypeDef adc_init;

    RCC_AHB1PeriphClockCmd(ADC_BATT_GPIO_CLK | BATT_DET_GPIO_CLK | ADC_BATT_DMA_CLK, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

    GPIO_StructInit(&gpio_init);
    gpio_init.GPIO_Pin = ADC_BATT_GPIO_PIN;
    gpio_init.GPIO_Mode = GPIO_Mode_AN;
    gpio_init.GPIO_PuPd = GPIO_PuPd_NOPULL;
    GPIO_Init(ADC_BATT_GPIO_PORT, &gpio_init);

    gpio_init.GPIO_Pin = BATT_DET_GPIO_PIN;
    gpio_init.GPIO_Mode = GPIO_Mode_OUT;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd = GPIO_PuPd_NOPULL;
    gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(BATT_DET_GPIO_PORT, &gpio_init);

    adc_battery_switch(0U);

    ADC_CommonStructInit(&adc_common_init);
    adc_common_init.ADC_Mode = ADC_Mode_Independent;
    adc_common_init.ADC_Prescaler = ADC_Prescaler_Div4;
    adc_common_init.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
    adc_common_init.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
    ADC_CommonInit(&adc_common_init);

    ADC_StructInit(&adc_init);
    adc_init.ADC_Resolution = ADC_Resolution_12b;
    adc_init.ADC_ScanConvMode = DISABLE;
    adc_init.ADC_ContinuousConvMode = ENABLE;
    adc_init.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    adc_init.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
    adc_init.ADC_DataAlign = ADC_DataAlign_Right;
    adc_init.ADC_NbrOfConversion = 1;
    ADC_Init(ADC1, &adc_init);

    ADC_RegularChannelConfig(ADC1, ADC_BATT_CHANNEL, 1, ADC_SampleTime_480Cycles);
    ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE);
    ADC_DMACmd(ADC1, ENABLE);
    ADC_Cmd(ADC1, ENABLE);

    adc_battery_last_raw = 0U;
    adc_battery_last_voltage_mv = 0U;
    adc_battery_last_percent = 0U;
    adc_battery_sampling = 0U;
    adc_battery_sample_ready = 0U;

    adc_battery_dma_init();
}

uint8_t ADC_Battery_StartSample(void)
{
    if (adc_battery_sampling != 0U)
    {
        return 0U;
    }

    adc_battery_sampling = 1U;
    adc_battery_sample_ready = 0U;
    adc_battery_switch(1U);
    delay_ms(ADC_BATT_SETTLE_DELAY_MS);

    adc_battery_prepare_dma_transfer();
    ADC_Cmd(ADC1, ENABLE);
    ADC_ClearFlag(ADC1, ADC_FLAG_EOC | ADC_FLAG_OVR);
    ADC_SoftwareStartConv(ADC1);

    return 1U;
}

uint8_t ADC_Battery_IsBusy(void)
{
    return adc_battery_sampling;
}

uint8_t ADC_Battery_IsSampleReady(void)
{
    return adc_battery_sample_ready;
}

void ADC_Battery_ClearSampleReady(void)
{
    adc_battery_sample_ready = 0U;
}

uint8_t ADC_Battery_GetLastPercent(void)
{
    return adc_battery_last_percent;
}


void DMA2_Stream0_IRQHandler(void)
{
    if (DMA_GetFlagStatus(ADC_BATT_DMA_STREAM, ADC_BATT_DMA_TC_FLAG) != RESET)
    {
        DMA_ClearFlag(ADC_BATT_DMA_STREAM, ADC_BATT_DMA_ALL_FLAGS);
        adc_battery_stop_hw();
        adc_battery_complete_sampling();
    }

    if (DMA_GetFlagStatus(ADC_BATT_DMA_STREAM, ADC_BATT_DMA_TE_FLAG) != RESET)
    {
        DMA_ClearFlag(ADC_BATT_DMA_STREAM, ADC_BATT_DMA_ALL_FLAGS);
        adc_battery_reset_after_error();
    }
}
