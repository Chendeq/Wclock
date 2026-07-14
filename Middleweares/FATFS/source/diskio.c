/*-----------------------------------------------------------------------*/
/* Low level disk I/O module SKELETON for FatFs     (C)ChaN, 2019        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "diskio.h"		/* Declarations of disk functions */
#include "tf.h"
#include "string.h"
#include "w25q128.h"

/* Definitions of physical drive number for each drive */
#define SD_CARD		0	// SD卡
#define EX_FLASH	1	// 外部FLASH，W25Q128

// SD卡块大小
#define SD_BLOCKSIZE     512

/**
 * 对于25Q128 FLASH芯片，我们规定前8MB给FATFS使用，8MB之后
 * 紧接字库
 */

#define SPI_FLASH_SECTOR_SIZE   512
uint16_t SPI_FLASH_SECTOR_COUNT = 8 * 2048;   /* 25Q128，前8MB字节给FATFS占用 */
#define SPI_FLASH_BLOCK_SIZE    8               /* 每个BLOCK有8个扇区 */
//#define SPI_FLASH_FATFS_BASE    0               /* FATFS 在外部FLASH的起始地址 从0开始 */


/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{

    return 0;

}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	uint8_t res = 0;
    switch (pdrv) {
		
		case SD_CARD:          /* SD CARD */
			res = SD_Init();
			break;
		
		case EX_FLASH:    /* SPI Flash */
			norflash_init();
			SPI_FLASH_SECTOR_COUNT = 8 * 2048;
			break;
	
		default:
			res = 1;
			break;
    }
    if(res)
		return STA_NOINIT;
	else
		return 0;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	LBA_t sector,	/* Start sector in LBA */
	UINT count		/* Number of sectors to read */
)
{
	uint8_t res = 0;
	
	if(!count) return RES_PARERR;		// 读取数量不能为0

    switch (pdrv) {
		case SD_CARD: /* SD CARD */
			
			res = SD_ReadDisk(buff, sector, count);
			while(res)
			{
				SD_Init();
				res = SD_ReadDisk(buff, sector, count);
			}
			break;
	
		case EX_FLASH:
			
			for (; count > 0; count--)
			{
				norflash_read(buff, sector * SPI_FLASH_SECTOR_SIZE, SPI_FLASH_SECTOR_SIZE);
				sector++;
				buff += SPI_FLASH_SECTOR_SIZE;
			}

			res = 0;
			break;

		default:
			res = 1;
			break;
    }
    if(res == 0x00)
		return RES_OK;
	else
		return RES_ERROR;
		
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if FF_FS_READONLY == 0

DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	LBA_t sector,		/* Start sector in LBA */
	UINT count			/* Number of sectors to write */
)
{
    uint8_t res = 0;
	
	if(!count) return RES_PARERR;		// 读取数量不能为0

    switch (pdrv) {
		case SD_CARD: /* SD CARD */
			
			res = SD_WriteDisk((uint8_t*)buff, sector, count);
			while(res)
			{
				SD_Init();
				res = SD_WriteDisk((uint8_t*)buff, sector, count);
			}
			break;
	
		case EX_FLASH:
			
			for (; count > 0; count--)
			{
				norflash_write((uint8_t *)buff, sector * SPI_FLASH_SECTOR_SIZE, SPI_FLASH_SECTOR_SIZE);
				sector++;
				buff += SPI_FLASH_SECTOR_SIZE;
			}
	
			res = 0;
			break;
	
		default:
			res = 1;
			break;
    }
    if(res == 0x00)
		return RES_OK;
	else
		return RES_ERROR;
}

#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT status = RES_PARERR;
    if(pdrv == SD_CARD) 
	{
		switch (cmd) {
		    // Get R/W sector size (WORD)
			case GET_SECTOR_SIZE :
				*(WORD * )buff = SD_BLOCKSIZE;
				status = RES_OK;
				break;
			// Get erase block size in unit of sector (DWORD)
			case GET_BLOCK_SIZE :
				*(DWORD * )buff = SDCardInfo.CardBlockSize;
				status = RES_OK;
				break;
		
			case GET_SECTOR_COUNT:
				*(DWORD*)buff = SDCardInfo.CardCapacity/SDCardInfo.CardBlockSize;
				status = RES_OK;
				break;
			case CTRL_SYNC :
				status = RES_OK;
				break;
			default:
				status = RES_PARERR;
				break;
        }
	}

	else if(pdrv == EX_FLASH)
	{
		switch (cmd)
        {
			case CTRL_SYNC:
				status = RES_OK;
				break;
	
			case GET_SECTOR_SIZE:
				*(WORD *)buff = SPI_FLASH_SECTOR_SIZE;
				status = RES_OK;
				break;
	
			case GET_BLOCK_SIZE:
				*(WORD *)buff = SPI_FLASH_BLOCK_SIZE;
				status = RES_OK;
				break;
	
			case GET_SECTOR_COUNT:
				*(DWORD *)buff = SPI_FLASH_SECTOR_COUNT;
				status = RES_OK;
				break;
	
			default:
				status = RES_PARERR;
				break;
		}
	}
	else
		status = RES_ERROR;
    
    return status;
}

DWORD get_fattime(void)
{
    // 这里返回一个固定时间或者从RTC获取真实时间
    // 格式: [31:25] 年份从1980开始的偏移 (0..127)
    //        [24:21] 月份 (1..12)
    //        [20:16] 日 (1..31)
    //        [15:11] 小时 (0..23)
    //        [10:5]  分钟 (0..59)
    //        [4:0]   秒/2 (0..29)
    
    // 示例: 2023年10月15日 12:30:45
    return ((DWORD)(2023 - 1980) << 25) | // 年: 2023-1980=43
           ((DWORD)10 << 21) |            // 月: 10
           ((DWORD)15 << 16) |            // 日: 15
           ((DWORD)12 << 11) |            // 时: 12
           ((DWORD)30 << 5) |             // 分: 30
           ((DWORD)45 >> 1);              // 秒: 45/2=22
}

