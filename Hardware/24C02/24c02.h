#ifndef __24C02_H
#define __24C02_H

#include <stdint.h>

#define AT24C02_WrADDRESS 0xA0 // 写地址
#define AT24C02_RdADDRESS 0xA1 // 读地址

uint8_t AT24CXX_ReadOneByte(uint16_t ReadAddr);                                   // 在指定地址读取一个字节
void AT24CXX_WriteOneByte(uint16_t WriteAddr, uint8_t DataToWrite);               // 在指定地址写入一个字节
void AT24CXX_WriteLenByte(uint16_t WriteAddr, uint32_t DataToWrite, uint8_t Len); // 在指定地址开始写入指定长度的数据
uint32_t AT24CXX_ReadLenByte(uint16_t ReadAddr, uint8_t Len);                     // 在指定地址开始读取指定长度的数据
void AT24CXX_Write(uint16_t WriteAddr, uint8_t *pBuffer, uint16_t NumToWrite);    // 从指定地址开始写入指定长度的数据
void AT24CXX_Read(uint16_t ReadAddr, uint8_t *pBuffer, uint16_t NumToRead);       // 从指定地址开始读取指定长度的数据

uint8_t AT24CXX_Check(void); // 检查器件
void AT24CXX_Init(void);     // 初始化IIC
#endif
