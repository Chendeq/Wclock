#include "stm32f4xx.h"
#include "w25q128.h"
#include "delay.h"

uint16_t g_norflash_type = W25Q128;

void norflash_init(void)
{
    spi1_init();                            /* 初始化SPI1 */
    spi1_set_speed(SPI_SPEED_4);            /* 设置为高速模式 */
    g_norflash_type = norflash_read_id();   /* 读取FLASH ID */
}

//等待忙状态
static void norflash_wait_busy(void)
{
    while ((norflash_read_sr(1) & 0x01) == 0x01);   /* 等待BUSY位清零 */
}

//25QXX写使能
void norflash_write_enable(void)
{
    SPI1_CS(0);
    spi1_read_write_byte(FLASH_WriteEnable);   /* 发送写使能 */
    SPI1_CS(1);
}

/**
 * @brief       25QXX发送地址
 * @param       address : 要发送的地址
 * @retval      无
 */
static void norflash_send_address(uint32_t address)
{
    spi1_read_write_byte((uint8_t)((address) >> 16));     /* 发送 bit23 ~ bit16 地址 */
    spi1_read_write_byte((uint8_t)((address) >> 8));      /* 发送 bit15 ~ bit8  地址 */
    spi1_read_write_byte((uint8_t)address);               /* 发送 bit7  ~ bit0  地址 */
}

/**
 * @brief       读取25QXX的状态寄存器
 * @param       regno: 状态寄存器号，范围:1~3
 * @retval      状态寄存器值
 */
uint8_t norflash_read_sr(uint8_t regno)
{
    uint8_t byte = 0, command = 0;

    switch (regno)
    {
        case 1:
            command = FLASH_ReadStatusReg1;
            break;
        case 2:
            command = FLASH_ReadStatusReg2;
            break;
        case 3:
            command = FLASH_ReadStatusReg3;
            break;
        default:
            command = FLASH_ReadStatusReg1;
            break;
    }

    SPI1_CS(0);
    spi1_read_write_byte(command);      /* 发送读状态寄存器命令 */
    byte = spi1_read_write_byte(0Xff);  /* 读取一个字节 */
    SPI1_CS(1);
    
    return byte;
}

/**
 * @brief       写25QXX状态寄存器
 * @param       regno: 状态寄存器号，范围:1~3
 * @param       sr: 要写入状态寄存器的值
 * @retval      无
 */
void norflash_write_sr(uint8_t regno, uint8_t sr)
{
    uint8_t command = 0;

    switch (regno)
    {
        case 1:
            command = FLASH_WriteStatusReg1;
            break;
        case 2:
            command = FLASH_WriteStatusReg2;
            break;
        case 3:
            command = FLASH_WriteStatusReg3;
            break;
        default:
            command = FLASH_WriteStatusReg1;
            break;
    }

    SPI1_CS(0);
    spi1_read_write_byte(command);  /* 发送写状态寄存器命令 */
    spi1_read_write_byte(sr);       /* 写入一个字节 */
    SPI1_CS(1);
}

/**
 * @brief       读取芯片ID
 * @param       无
 * @retval      FLASH芯片ID
 */
uint16_t norflash_read_id(void)
{
    uint16_t deviceid;

    SPI1_CS(0);
    spi1_read_write_byte(FLASH_ManufactDeviceID);   /* 发送读ID命令 */
    spi1_read_write_byte(0);                        /* 写入3个dummy字节 */
    spi1_read_write_byte(0);
    spi1_read_write_byte(0);
    deviceid = spi1_read_write_byte(0xFF) << 8;     /* 读取高8位 */
    deviceid |= spi1_read_write_byte(0xFF);         /* 读取低8位 */
    SPI1_CS(1);

    return deviceid;
}

/**
 * @brief       读取SPI FLASH
 * @param       pbuf: 数据存储区
 * @param       addr: 开始读取的地址
 * @param       datalen: 要读取的字节数
 * @retval      无
 */
void norflash_read(uint8_t *pbuf, uint32_t addr, uint16_t datalen)
{
    uint16_t i;

    SPI1_CS(0);
    spi1_read_write_byte(FLASH_ReadData);   /* 发送读取命令 */
    norflash_send_address(addr);            /* 发送地址 */
    
    for (i = 0; i < datalen; i++)
    {
        pbuf[i] = spi1_read_write_byte(0XFF);   /* 循环读取 */
    }
    
    SPI1_CS(1);
}

/**
 * @brief       写入一页数据
 * @param       pbuf: 数据存储区
 * @param       addr: 开始写入的地址
 * @param       datalen: 要写入的字节数
 * @retval      无
 */
static void norflash_write_page(uint8_t *pbuf, uint32_t addr, uint16_t datalen)
{
    uint16_t i;

    norflash_write_enable();    /* 写使能 */

    SPI1_CS(0);
    spi1_read_write_byte(FLASH_PageProgram);    /* 发送写页命令 */
    norflash_send_address(addr);                /* 发送地址 */

    for (i = 0; i < datalen; i++)
    {
        spi1_read_write_byte(pbuf[i]);          /* 循环发送数据 */
    }
    
    SPI1_CS(1);
    norflash_wait_busy();       /* 等待写入完成 */
}

/**
 * @brief       无检查写SPI FLASH
 * @param       pbuf: 数据存储区
 * @param       addr: 开始写入的地址
 * @param       datalen: 要写入的字节数
 * @retval      无
 */
static void norflash_write_nocheck(uint8_t *pbuf, uint32_t addr, uint16_t datalen)
{
    uint16_t pageremain;
    pageremain = 256 - addr % 256;  /* 单页剩余的字节数 */

    if (datalen <= pageremain)
    {
        pageremain = datalen;
    }

    while (1)
    {
        norflash_write_page(pbuf, addr, pageremain);

        if (datalen == pageremain)
        {
            break;
        }
        else
        {
            pbuf += pageremain;
            addr += pageremain;
            datalen -= pageremain;

            if (datalen > 256)
            {
                pageremain = 256;
            }
            else
            {
                pageremain = datalen;
            }
        }
    }
}

/**
 * @brief       写SPI FLASH(带擦除操作)
 * @param       pbuf: 数据存储区
 * @param       addr: 开始写入的地址
 * @param       datalen: 要写入的字节数
 * @retval      无
 */
uint8_t g_norflash_buf[4096];   /* 缓存数组 */

void norflash_write(uint8_t *pbuf, uint32_t addr, uint16_t datalen)
{
    uint32_t secpos;
    uint16_t secoff;
    uint16_t secremain;
    uint16_t i;
    uint8_t *norflash_buf;

    norflash_buf = g_norflash_buf;
    secpos = addr / 4096;       /* 扇区地址 */
    secoff = addr % 4096;       /* 扇区内偏移 */
    secremain = 4096 - secoff;  /* 扇区剩余空间 */

    if (datalen <= secremain)
    {
        secremain = datalen;
    }

    while (1)
    {
        norflash_read(norflash_buf, secpos * 4096, 4096);   /* 读出整个扇区 */

        for (i = 0; i < secremain; i++)
        {
            if (norflash_buf[secoff + i] != 0XFF)
            {
                break;
            }
        }

        if (i < secremain)
        {
            norflash_erase_sector(secpos);
            for (i = 0; i < secremain; i++)
            {
                norflash_buf[i + secoff] = pbuf[i];
            }
            norflash_write_nocheck(norflash_buf, secpos * 4096, 4096);
        }
        else
        {
            norflash_write_nocheck(pbuf, addr, secremain);
        }

        if (datalen == secremain)
        {
            break;
        }
        else
        {
            secpos++;
            secoff = 0;
            pbuf += secremain;
            addr += secremain;
            datalen -= secremain;

            if (datalen > 4096)
            {
                secremain = 4096;
            }
            else
            {
                secremain = datalen;
            }
        }
    }
}

/**
 * @brief       擦除整块芯片
 * @param       无
 * @retval      无
 */
void norflash_erase_chip(void)
{
    norflash_write_enable();
    norflash_wait_busy();
    SPI1_CS(0);
    spi1_read_write_byte(FLASH_ChipErase);  /* 发送整片擦除命令 */
    SPI1_CS(1);
    norflash_wait_busy();
}

/**
 * @brief       擦除一个扇区
 * @param       saddr: 扇区地址
 * @retval      无
 */
void norflash_erase_sector(uint32_t saddr)
{
    saddr *= 4096;
    norflash_write_enable();
    norflash_wait_busy();
    SPI1_CS(0);
    spi1_read_write_byte(FLASH_SectorErase);    /* 发送扇区擦除命令 */
    norflash_send_address(saddr);               /* 发送地址 */
    SPI1_CS(1);
    norflash_wait_busy();
}