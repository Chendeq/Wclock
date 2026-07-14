#ifndef __SPL06_H
#define __SPL06_H

#include <stdint.h>
#include "iic.h"
#include "stm32f4xx.h"

// SPL06寄存器定义
#define PSR_B2_Addr 0x00
#define PSR_B1_Addr 0x01
#define PSR_B0_Addr 0x02
#define TMP_B2_Addr 0x03
#define TMP_B1_Addr 0x04
#define TMP_B0_Addr 0x05
#define PRS_CFG_Addr 0x06
#define TMP_CFG_Addr 0x07
#define MEAS_CFG_Addr 0x08
#define CFG_REG_Addr 0x09
#define RESET_Addr 0x0C
#define ID_Addr 0x0D

#define Temp_c0_Addr 0x10
#define Temp_c1_Addr 0x11
#define Temp_c2_Addr 0x12
#define Press_c0_Addr 0x13
#define Press_c1_Addr 0x14
#define Press_c2_Addr 0x15
#define Press_c3_Addr 0x16
#define Press_c4_Addr 0x17
#define Press_c5_Addr 0x18
#define Press_c6_Addr 0x19
#define Press_c7_Addr 0x1A
#define Press_c8_Addr 0x1B
#define Press_c9_Addr 0x1C
#define Press_c10_Addr 0x1D
#define Press_c11_Addr 0x1E
#define Press_c12_Addr 0x1F
#define Press_c13_Addr 0x20
#define Press_c14_Addr 0x21

// 常量定义
#define k_SPS1 524288.0f
#define k_SPS2 1572864.0f
#define k_SPS4 3670016.0f
#define k_SPS8 7864320.0f
#define k_SPS16 253952.0f
#define k_SPS32 516096.0f
#define k_SPS64 1040384.0f
#define k_SPS128 2088960.0f

#define Total_Number_24 16777216.0f
#define Total_Number_20 1048576.0f
#define Total_Number_16 65536.0f
#define Total_Number_12 4096.0f

// SPL06设备地址（SDO接地，地址为0x76<<1）
#define SPL06_ADDRESS 0x76
#define SPL06_WRADDRESS 0xEC
#define SPL06_RDADDRESS 0xED

// 函数声明
uint8_t SPL06_Init(void);
uint8_t SPL06_Read_Byte(uint8_t addr);
void SPL06_Write_Byte(uint8_t addr, uint8_t data);
void Parameter_Reading(int32_t *Pressure_Para, int32_t *Temperature_Para);
float Temperature_conversion(uint32_t Temp_Data, float k);
float Pressure_conversion(uint32_t Pressure_Data, float k);
float Scale_factor(uint8_t Config_k);
float Correcting_Pressure(int32_t *Pressure_Para, float Pressure, float Temperature);
float Correcting_Temperature(int32_t *Temperature_Para, float Temperature);
float SPL06_ReadPressure(void);
float SPL06_ReadTemperature(void);

#endif

//	uint8_t spl06_id = SPL06_Init();
//	LCD_ShowString(10,10,16,(uint8_t *)"SPL06 ID:",0);
//	LCD_ShowNum(100,10,spl06_id,2,16);

//		float pressure = SPL06_ReadPressure();
//		float temperature = SPL06_ReadTemperature();
//    	// 显示温度
//    	LCD_ShowString(10, 50, 16, (uint8_t *)"Temp(C):", 0);
//    	LCD_ShowFloat(100, 50, temperature, 2, 16);  // 显示2位小数
//		LCD_ShowString(200, 50, 16, (uint8_t *)"°C", 0);
//    
//    	// 显示气压
//    	LCD_ShowString(10, 80, 16, (uint8_t *)"Press(hPa):", 0);
//    	LCD_ShowFloat(130, 80, pressure, 2, 16);     // 显示2位小数
//		LCD_ShowString(170, 80, 16, (uint8_t *)"hPa", 0);
//        delay_ms(1000);
