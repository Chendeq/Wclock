#ifndef __BH1750_H
#define __BH1750_H

#include "stm32f4xx.h"
#include <stdint.h>
#include "iic.h"

// BH1750设备地址（ADDR引脚接地）
#define BH1750_ADDRESS 0x23
#define BH1750_WrAddress (BH1750_ADDRESS << 1)       // 写地址0x46
#define BH1750_RdAddress ((BH1750_ADDRESS << 1) | 1) // 读地址0x47

// BH1750指令定义
#define BH1750_POWER_DOWN 0x00  // 断电模式
#define BH1750_POWER_ON 0x01   // 上电模式
#define BH1750_RESET 0x07     // 重置数据寄存器（需在上电模式下执行）
#define BH1750_CONT_H_RES_MODE 0x10 // 连续高分辨率模式
#define BH1750_CONT_H_RES_MODE2 0x11 // 连续高分辨率模式2
#define BH1750_CONT_L_RES_MODE 0x13 // 连续低分辨率模式
#define BH1750_ONE_TIME_H_RES_MODE 0x20 // 单次高分辨率模式
#define BH1750_ONE_TIME_H_RES_MODE2 0x21 // 单次高分辨率模式2
#define BH1750_ONE_TIME_L_RES_MODE 0x23 // 单次低分辨率模式

// 定义BH1750设备结构体
extern iic_device_t bh1750_dev;

// 函数声明
void BH1750_Init(void);
void BH1750_Write_Cmd(uint8_t cmd);
uint16_t BH1750_Read_Light(void);
float BH1750_Get_Lux(void);

#endif

//	char strbuf[64];
//		float lux = BH1750_Get_Lux();
//		sprintf(strbuf,"Lux: %.2f",lux);
//		LCD_ShowString(10,10,16,strbuf,0);
//        
//        delay_ms(1000);
