#ifndef __ADC_H
#define __ADC_H

#include "stm32f4xx.h"
#include <stdint.h>

#define ADC_BATTERY_EMPTY_MV   2700U
#define ADC_BATTERY_FULL_MV    4200U

void ADC_Battery_Init(void);
uint16_t ADC_Battery_ReadRaw(void);
uint16_t ADC_Battery_ReadVoltageMv(void);
uint16_t ADC_Battery_GetLastRaw(void);
uint16_t ADC_Battery_GetLastVoltageMv(void);
uint8_t ADC_Battery_ReadPercent(void);

#endif
