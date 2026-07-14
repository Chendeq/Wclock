#ifndef __W25Q128_H
#define __W25Q128_H

#include "spi.h"

#define W25Q128     0XEF17          /* W25Q128  设备ID */

/* 指令表 */
#define FLASH_WriteEnable           0x06 
#define FLASH_WriteDisable          0x04 
#define FLASH_ReadStatusReg1        0x05 
#define FLASH_ReadStatusReg2        0x35 
#define FLASH_ReadStatusReg3        0x15 
#define FLASH_WriteStatusReg1       0x01 
#define FLASH_WriteStatusReg2       0x31 
#define FLASH_WriteStatusReg3       0x11 
#define FLASH_ReadData              0x03 
#define FLASH_FastReadData          0x0B 
#define FLASH_FastReadDual          0x3B 
#define FLASH_FastReadQuad          0xEB  
#define FLASH_PageProgram           0x02 
#define FLASH_PageProgramQuad       0x32 
#define FLASH_BlockErase            0xD8 
#define FLASH_SectorErase           0x20 
#define FLASH_ChipErase             0xC7 
#define FLASH_PowerDown             0xB9 
#define FLASH_ReleasePowerDown      0xAB 
#define FLASH_DeviceID              0xAB 
#define FLASH_ManufactDeviceID      0x90 
#define FLASH_JedecDeviceID         0x9F 
#define FLASH_Enable4ByteAddr       0xB7
#define FLASH_Exit4ByteAddr         0xE9
#define FLASH_SetReadParam          0xC0 
#define FLASH_EnterQPIMode          0x38
#define FLASH_ExitQPIMode           0xFF


/* 静态函数声明 */
static void norflash_wait_busy(void);
static void norflash_send_address(uint32_t address);
static void norflash_write_page(uint8_t *pbuf, uint32_t addr, uint16_t datalen);
static void norflash_write_nocheck(uint8_t *pbuf, uint32_t addr, uint16_t datalen);


/* 普通函数 */
void norflash_init(void);                   /* 初始化25QXX */
uint16_t norflash_read_id(void);            /* 读取FLASH ID */
void norflash_write_enable(void);           /* 写使能 */
uint8_t norflash_read_sr(uint8_t regno);    /* 读取状态寄存器 */
void norflash_write_sr(uint8_t regno, uint8_t sr);   /* 写状态寄存器 */

void norflash_erase_chip(void);             /* 整片擦除 */
void norflash_erase_sector(uint32_t saddr); /* 扇区擦除 */
void norflash_read(uint8_t *pbuf, uint32_t addr, uint16_t datalen);     /* 读取flash */
void norflash_write(uint8_t *pbuf, uint32_t addr, uint16_t datalen);    /* 写入flash */

#endif