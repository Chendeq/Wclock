#include "adc.h"

#define ADC_BATT_GPIO_PORT          GPIOC
#define ADC_BATT_GPIO_PIN           GPIO_Pin_0
#define ADC_BATT_GPIO_CLK           RCC_AHB1Periph_GPIOC
#define ADC_BATT_CHANNEL            ADC_Channel_10

#define BATT_DET_GPIO_PORT          GPIOC
#define BATT_DET_GPIO_PIN           GPIO_Pin_1
#define BATT_DET_GPIO_CLK           RCC_AHB1Periph_GPIOC

#define ADC_BATT_SAMPLE_COUNT       8U
#define ADC_BATT_DUMMY_COUNT        2U
#define ADC_REFERENCE_MV            3300U
#define ADC_RESOLUTION_MAX          4095U
#define ADC_BATT_R_TOP_OHM          30000U
#define ADC_BATT_R_BOTTOM_OHM       15000U
#define ADC_BATT_DIVIDER_NUM        (ADC_BATT_R_TOP_OHM + ADC_BATT_R_BOTTOM_OHM)
#define ADC_BATT_DIVIDER_DEN        ADC_BATT_R_BOTTOM_OHM

static uint16_t adc_battery_last_raw;
static uint16_t adc_battery_last_voltage_mv;

/*
 * PC1控制电池检测分压回路的开关。
 * 只有真正采样时才拉高使能，平时关闭，
 * 这样可以减少分压电阻长期挂在电池上的静态损耗。
 */
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

    for (i = 0; i < 300000U; i++)
    {
        __NOP();
    }
}

/*
 * PC0作为ADC输入读取分压后的电池电压，
 * PC1作为检测使能脚控制分压回路是否接入。
 * 这种接法适合低功耗场景下的电池电量检测。
 */
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

    /*
     * 刚打开分压回路时，分压点电压和ADC采样保持电容都需要一点稳定时间。
     * 先做几次丢弃转换，可以避开刚上电那一瞬间的不稳定值，
     * 后面再进入正式平均采样。
     */
    for (index = 0; index < ADC_BATT_DUMMY_COUNT; index++)
    {
        ADC_RegularChannelConfig(ADC1, ADC_BATT_CHANNEL, 1, ADC_SampleTime_480Cycles);
        ADC_ClearFlag(ADC1, ADC_FLAG_EOC);
        ADC_SoftwareStartConv(ADC1);
        while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET)
        {
        }
        (void)ADC_GetConversionValue(ADC1);
    }

    for (index = 0; index < ADC_BATT_SAMPLE_COUNT; index++)
    {
        /* 多次采样求平均，降低瞬时抖动对电量显示的影响。 */
        ADC_RegularChannelConfig(ADC1, ADC_BATT_CHANNEL, 1, ADC_SampleTime_480Cycles);
        ADC_ClearFlag(ADC1, ADC_FLAG_EOC);
        ADC_SoftwareStartConv(ADC1);

        while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET)
        {
        }

        sum += ADC_GetConversionValue(ADC1);
    }

    adc_battery_switch(0U);

    /*
     * 记录最近一次平均后的原始ADC值。
     * 当界面电量显示异常时，可以直接结合这个值判断：
     * 是采样链路有问题，还是后面的电压/百分比换算有问题。
     */
    adc_battery_last_raw = (uint16_t)(sum / ADC_BATT_SAMPLE_COUNT);

    return adc_battery_last_raw;
}

uint16_t ADC_Battery_ReadVoltageMv(void)
{
    uint32_t raw = ADC_Battery_ReadRaw();
    uint32_t adc_mv;
    uint32_t battery_mv;

    /*
     * 计算过程分两步：
     * 1. 先把ADC原始值换算成ADC引脚上的毫伏值；
     * 2. 再根据分压比还原成电池端实际电压。
     * 用分步整数运算是为了降低32位乘法溢出的风险，同时保留四舍五入。
     */
    adc_mv = (raw * ADC_REFERENCE_MV + (ADC_RESOLUTION_MAX / 2U)) / ADC_RESOLUTION_MAX;
    battery_mv = (adc_mv * ADC_BATT_DIVIDER_NUM + (ADC_BATT_DIVIDER_DEN / 2U)) / ADC_BATT_DIVIDER_DEN;

    adc_battery_last_voltage_mv = (uint16_t)battery_mv;

    return adc_battery_last_voltage_mv;
}

uint16_t ADC_Battery_GetLastRaw(void)
{
    return adc_battery_last_raw;
}

uint16_t ADC_Battery_GetLastVoltageMv(void)
{
    return adc_battery_last_voltage_mv;
}

uint8_t ADC_Battery_ReadPercent(void)
{
    uint16_t battery_mv = ADC_Battery_ReadVoltageMv();
    uint32_t percent;

    /*
     * 这里按单节锂电池的工作范围做线性百分比映射：
     * 2.7V 视为0%，4.2V 视为100%。
     * 这种算法简单直观，适合作为界面电量提示，
     * 但它不是严格的SOC曲线估算。
     */
    if (battery_mv <= ADC_BATTERY_EMPTY_MV)
    {
        /* 低于空电阈值时直接钳到 0%。 */
        return 0U;
    }

    if (battery_mv >= ADC_BATTERY_FULL_MV)
    {
        /* 高于满电阈值时直接钳到 100%。 */
        return 100U;
    }

    /* 中间区间做线性插值，得到界面显示用百分比。 */
    percent = (uint32_t)(battery_mv - ADC_BATTERY_EMPTY_MV) * 100U;
    percent /= (ADC_BATTERY_FULL_MV - ADC_BATTERY_EMPTY_MV);

    return (uint8_t)percent;
}
