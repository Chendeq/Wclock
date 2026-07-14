#include "adc.h"

#define ADC_BATT_GPIO_PORT          GPIOC
#define ADC_BATT_GPIO_PIN           GPIO_Pin_0
#define ADC_BATT_GPIO_CLK           RCC_AHB1Periph_GPIOC
#define ADC_BATT_CHANNEL            ADC_Channel_10

#define BATT_DET_GPIO_PORT          GPIOC
#define BATT_DET_GPIO_PIN           GPIO_Pin_1
#define BATT_DET_GPIO_CLK           RCC_AHB1Periph_GPIOC

#define ADC_BATT_SAMPLE_COUNT       8U
#define ADC_REFERENCE_MV            3300U
#define ADC_RESOLUTION_MAX          4095U
#define ADC_BATT_R_TOP_OHM          30000U
#define ADC_BATT_R_BOTTOM_OHM       15000U

static void adc_battery_switch(uint8_t enable)
{
    if (enable)
    {
        GPIO_SetBits(BATT_DET_GPIO_PORT, BATT_DET_GPIO_PIN);
    }
    else
    {
        GPIO_ResetBits(BATT_DET_GPIO_PORT, BATT_DET_GPIO_PIN);
    }
}

static void adc_battery_settle_delay(void)
{
    volatile uint32_t i;

    for (i = 0; i < 120000U; i++)
    {
        __NOP();
    }
}

void ADC_Battery_Init(void)
{
    GPIO_InitTypeDef gpio_init;
    ADC_CommonInitTypeDef adc_common_init;
    ADC_InitTypeDef adc_init;

    RCC_AHB1PeriphClockCmd(ADC_BATT_GPIO_CLK | BATT_DET_GPIO_CLK, ENABLE);
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
    adc_init.ADC_ContinuousConvMode = DISABLE;
    adc_init.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    adc_init.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
    adc_init.ADC_DataAlign = ADC_DataAlign_Right;
    adc_init.ADC_NbrOfConversion = 1;
    ADC_Init(ADC1, &adc_init);

    ADC_Cmd(ADC1, ENABLE);
}

uint16_t ADC_Battery_ReadRaw(void)
{
    uint32_t sum = 0;
    uint32_t index;

    adc_battery_switch(1U);
    adc_battery_settle_delay();

    ADC_RegularChannelConfig(ADC1, ADC_BATT_CHANNEL, 1, ADC_SampleTime_144Cycles);
    ADC_ClearFlag(ADC1, ADC_FLAG_EOC);
    ADC_SoftwareStartConv(ADC1);
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET)
    {
    }
    (void)ADC_GetConversionValue(ADC1);

    for (index = 0; index < ADC_BATT_SAMPLE_COUNT; index++)
    {
        ADC_RegularChannelConfig(ADC1, ADC_BATT_CHANNEL, 1, ADC_SampleTime_144Cycles);
        ADC_ClearFlag(ADC1, ADC_FLAG_EOC);
        ADC_SoftwareStartConv(ADC1);

        while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET)
        {
        }

        sum += ADC_GetConversionValue(ADC1);
    }

    adc_battery_switch(0U);

    return (uint16_t)(sum / ADC_BATT_SAMPLE_COUNT);
}

uint16_t ADC_Battery_ReadVoltageMv(void)
{
    uint32_t raw = ADC_Battery_ReadRaw();
    uint32_t adc_mv = (raw * ADC_REFERENCE_MV) / ADC_RESOLUTION_MAX;
    uint32_t battery_mv = adc_mv * (ADC_BATT_R_TOP_OHM + ADC_BATT_R_BOTTOM_OHM);

    battery_mv /= ADC_BATT_R_BOTTOM_OHM;

    return (uint16_t)battery_mv;
}

uint8_t ADC_Battery_ReadPercent(void)
{
    uint16_t battery_mv = ADC_Battery_ReadVoltageMv();
    uint32_t percent;

    if (battery_mv <= ADC_BATTERY_EMPTY_MV)
    {
        return 0U;
    }

    if (battery_mv >= ADC_BATTERY_FULL_MV)
    {
        return 100U;
    }

    percent = (uint32_t)(battery_mv - ADC_BATTERY_EMPTY_MV) * 100U;
    percent /= (ADC_BATTERY_FULL_MV - ADC_BATTERY_EMPTY_MV);

    return (uint8_t)percent;
}
