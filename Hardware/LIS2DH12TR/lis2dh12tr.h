#ifndef __LIS2DH12TR_H
#define __LIS2DH12TR_H

#include "iic.h"

#include <stdint.h>

// LIS2DH12TR I2C地址
#define LIS2DH12TR_WrADDRESS 0x30 // SA0 接地
#define LIS2DH12TR_RdADDRESS 0x31

// LIS2DH12TR寄存器地址
#define LIS2DH12TR_WHO_AM_I         0x0F  
#define LIS2DH12TR_TEMP_CFG_REG     0x1F
#define LIS2DH12TR_CTRL_REG1        0x20
#define LIS2DH12TR_CTRL_REG2        0x21
#define LIS2DH12TR_CTRL_REG3        0x22
#define LIS2DH12TR_CTRL_REG4        0x23
#define LIS2DH12TR_CTRL_REG5        0x24
#define LIS2DH12TR_CTRL_REG6        0x25
#define LIS2DH12TR_REFERENCE        0x26
#define LIS2DH12TR_STATUS_REG       0x27
#define LIS2DH12TR_OUT_X_L          0x28
#define LIS2DH12TR_OUT_X_H          0x29
#define LIS2DH12TR_OUT_Y_L          0x2A
#define LIS2DH12TR_OUT_Y_H          0x2B
#define LIS2DH12TR_OUT_Z_L          0x2C
#define LIS2DH12TR_OUT_Z_H          0x2D
#define LIS2DH12TR_FIFO_CTRL_REG    0x2E
#define LIS2DH12TR_FIFO_SRC_REG     0x2F
#define LIS2DH12TR_INT1_CFG         0x30
#define LIS2DH12TR_INT1_SRC         0x31
#define LIS2DH12TR_INT1_THS         0x32
#define LIS2DH12TR_INT1_DURATION    0x33
#define LIS2DH12TR_INT2_CFG         0x34
#define LIS2DH12TR_INT2_SRC         0x35
#define LIS2DH12TR_INT2_THS         0x36
#define LIS2DH12TR_INT2_DURATION    0x37
#define LIS2DH12TR_CLICK_CFG        0x38
#define LIS2DH12TR_CLICK_SRC        0x39
#define LIS2DH12TR_CLICK_THS        0x3A
#define LIS2DH12TR_TIME_LIMIT       0x3B
#define LIS2DH12TR_TIME_LATENCY     0x3C
#define LIS2DH12TR_TIME_WINDOW      0x3D
#define LIS2DH12TR_ACT_THS          0x3E
#define LIS2DH12TR_ACT_DUR          0x3F

/* 量程选择 (CTRL_REG4的FS[1:0]) */
#define LIS2DH12TR_RANGE_2G         0x00  // ±2g
#define LIS2DH12TR_RANGE_4G         0x10  // ±4g
#define LIS2DH12TR_RANGE_8G         0x20  // ±8g
#define LIS2DH12TR_RANGE_16G        0x30  // ±16g

/* 输出数据率选择 (CTRL_REG1的ODR[3:0]) */
#define LIS2DH12TR_ODR_POWERDOWN    0x00
#define LIS2DH12TR_ODR_1HZ          0x10
#define LIS2DH12TR_ODR_10HZ         0x20
#define LIS2DH12TR_ODR_25HZ         0x30
#define LIS2DH12TR_ODR_50HZ         0x40
#define LIS2DH12TR_ODR_100HZ        0x50
#define LIS2DH12TR_ODR_200HZ        0x60
#define LIS2DH12TR_ODR_400HZ        0x70
#define LIS2DH12TR_ODR_1K62HZ_LP    0x80
#define LIS2DH12TR_ODR_1K344HZ_NM   0x90
#define LIS2DH12TR_ODR_5K376HZ_LP   0x90

/* FIFO模式 (FIFO_CTRL_REG的FM[1:0]) */
#define LIS2DH12TR_FIFO_BYPASS      0x00
#define LIS2DH12TR_FIFO_MODE        0x40
#define LIS2DH12TR_FIFO_STREAM      0x80
#define LIS2DH12TR_FIFO_STREAM_FIFO 0xC0

// LIS2DH12TR初始化
uint8_t LIS2DH12TR_Init(void);
uint8_t LIS2DH12TR_CheckID(void);
uint8_t LIS2DH12TR_ReadRegister(uint8_t reg);
void LIS2DH12TR_WriteRegister(uint8_t reg, uint8_t value);
void LIS2DH12TR_ReadAcceleration(int16_t *x, int16_t *y, int16_t *z); // 连续读取 6 字节 XYZ 数据
float LIS2DH12TR_ConvertToG(int16_t raw, uint8_t range);              // 将原始数据转换为 g 单位
void LIS2DH12TR_SetRange(uint8_t range);                              // 设置量程
void LIS2DH12TR_SetDataRate(uint8_t datarate);                        // 设置输出数据率

void LIS2DH12TR_EnableFIFO(uint8_t enable, uint8_t mode, uint8_t watermark);
uint8_t LIS2DH12TR_GetFIFOLevel(void);
void LIS2DH12TR_FIFOReset(void);

#endif
