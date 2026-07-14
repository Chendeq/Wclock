#ifndef __LED_H
#define __LED_H

#include "stm32f4xx.h"  
/* 翻转LED */
#define LED0_TOGGLE() GPIO_ToggleBits(GPIOE, GPIO_Pin_4)

void LED_Init(void);
void LED_Control(uint8_t state);

#endif
