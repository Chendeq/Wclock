#ifndef __SRAM_H
#define __SRAM_H

#include <stdint.h>

/* SRAM 基地址，对应 FSMC Bank3 (NE3) */
#define SRAM_BASE_ADDR     ((uint32_t)0x68000000)

/* 函数声明 */
void SRAM_Init(void);
void SRAM_WriteBuffer(uint16_t *pBuffer, uint32_t uwWriteAddr, uint32_t uwHalfWordCount);
void SRAM_ReadBuffer(uint16_t *pBuffer, uint32_t uwReadAddr, uint32_t uwHalfWordCount);
uint16_t SRAM_Test(void);



#endif
