#ifndef __USART1_H
#define __USART1_H

#include <stdint.h>

void USART1_Init(void);
void USART1_SendByte(char ch);
void USART1_SendString(char *str);
void Serial_Printf(char *format, ...);
uint8_t USART1_GetRxData(void);

#endif
