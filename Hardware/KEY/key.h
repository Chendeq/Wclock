#ifndef __KEY_H
#define __KEY_H

#include <stdint.h>
#include "stm32f4xx.h"

void Key_Init(void);
uint8_t Key_GetNum(void);
uint8_t key_scan(uint8_t mode);

#endif
