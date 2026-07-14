#ifndef __SHT30_H
#define __SHT30_H

#include <stdint.h>
#include "iic.h"

typedef struct {
    float temp;      // 温度，单位℃
    float humi;      // 湿度，单位%RH
    uint8_t status;  // 状态：0-成功，1-失败
} sht30_data_t;


// SHT30地址
// SHT30 I2C地址（7位地址）
#define SHT30_ADDRESS      0x44    // ADDR引脚接地时的7位地址
#define SHT30_WrADDRESS   (SHT30_ADDRESS << 1)      // 写地址：0x88
#define SHT30_RdADDRESS    ((SHT30_ADDRESS << 1) | 1) // 读地址：0x89

// SHT30命令
#define SHT30_MEAS_HIGHREP_STRETCH 0x2C06 // 高重复性测量，时钟拉伸(Clock Stretching)使能，测量精度最高，但测量时间最长，适用于对精度要求高的应用场景
#define SHT30_MEAS_MEDREP_STRETCH  0x2C0D // 中等重复性测量，时钟拉伸(Clock Stretching)使能，平衡精度和测量时间，适用于大多数常规应用
#define SHT30_MEAS_LOWREP_STRETCH  0x2C10 // 低重复性测量，时钟拉伸(Clock Stretching)使能，测量速度最快，但精度最低，适用于对响应速度要求高的场景
#define SHT30_MEAS_HIGHREP         0x2400 // 高重复性测量，时钟拉伸禁用，需要轮询数据就绪状态，精度最高，适用于主控需要同时处理其他任务的情况
#define SHT30_MEAS_MEDREP          0x240B // 中等重复性测量，时钟拉伸禁用，需要轮询数据就绪状态，平衡精度和系统资源占用
#define SHT30_MEAS_LOWREP          0x2416 // 低重复性测量，时钟拉伸禁用，需要轮询数据就绪状态，测量速度最快，适用于对响应速度要求高的场景

// 默认使用的测量命令
#define SHT30_DEFAULT_CMD   SHT30_MEAS_HIGHREP

void SHT30_Init(void);
uint8_t SHT30_Read_Data(sht30_data_t* data);
uint8_t SHT30_Read_Data_With_Cmd(uint16_t cmd, sht30_data_t* data);
uint8_t SHT30_Check(void);
float SHT30_Convert_Temperature(uint16_t raw_temp);
float SHT30_Convert_Humidity(uint16_t raw_humi);
uint8_t SHT30_Check_CRC8(uint8_t msb, uint8_t lsb, uint8_t crc);

#endif


//	char str[8];
//// 读取数据
//		if (SHT30_Read_Data(&data) == 0) {
//			// 显示数据
//			sprintf(str,"%.1f",data.temp);        // 保留 1 位小数
//			LCD_ShowString(60,10,16,(uint8_t*)str,0);
//			sprintf(str,"%.1f",data.humi);
//			LCD_ShowString(60,30,16,(uint8_t*)str,0);
//		} else {
//			LCD_ShowString(10,50,16,(uint8_t*)("Read Failed"),0);
//		}

//		delay_ms(1000);

