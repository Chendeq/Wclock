#ifndef __ADC_H
#define __ADC_H

#include "stm32f4xx.h"
#include <stdint.h>

#define ADC_BATTERY_EMPTY_MV   2700U
#define ADC_BATTERY_FULL_MV    4200U

void ADC_Battery_Init(void);
uint8_t ADC_Battery_StartSample(void);
uint8_t ADC_Battery_IsBusy(void);
uint8_t ADC_Battery_IsSampleReady(void);
void ADC_Battery_ClearSampleReady(void);
uint8_t ADC_Battery_GetLastPercent(void);
void DMA2_Stream0_IRQHandler(void);

#endif
