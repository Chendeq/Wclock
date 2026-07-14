#include "string.h"
#include "lcd.h"
#include "gui.h"
#include "fonts.h"
#include "malloc.h"
#include "ff.h"
#include "Usart1.h"
#include "delay.h"
#include "w25q128.h"

/* 字库区域占用的总扇区数大小
 * 由于有多个LVGL字体，需要适当增加扇区数量
 * 总大小计算: 510+574+777+912+1198 ≈ 3971KB，加上UNIGBK约400KB，总共约4310KB
 * 每个扇区4KB，需要约1070个扇区，这里设置为1100确保足够
 */
#define FONTSECSIZE         1100

/* 字库存放起始地址
 * 从第8MB地址开始存放字库
 * 前面8MB大小被文件系统占用
 */
#define FONTINFOADDR        8 * 1024 * 1024

/* 用来保存字库基本信息，地址，大小等 */
_font_info ftinfo;

/* 字库存放在磁盘中的路径 */
char *const FONT_GBK_PATH[6] = 
{
    "/FONT/UNIGBK.BIN",        /* UNIGBK.BIN的存放位置 */
    "/FONT/lv_Font_7.bin",     /* LVGL字体7的存放位置  */
    "/FONT/lv_Font_8.bin",     /* LVGL字体8的存放位置  */
    "/FONT/lv_Font_10.bin",    /* LVGL字体10的存放位置 */
    "/FONT/lv_Font_12.bin",    /* LVGL字体12的存放位置 */
    "/FONT/lv_Font_14.bin",    /* LVGL字体14的存放位置 */
};

/* 更新时的提示信息 */
char *const FONT_UPDATE_REMIND_TBL[6] = 
{
    "Updating UNIGBK.BIN",     /* 提示正在更新UNIGBK.bin */
    "Updating LV_FONT7 ",      /* 提示正在更新LVGL字体7  */
    "Updating LV_FONT8 ",      /* 提示正在更新LVGL字体8  */
    "Updating LV_FONT10 ",     /* 提示正在更新LVGL字体10 */
    "Updating LV_FONT12 ",     /* 提示正在更新LVGL字体12 */
    "Updating LV_FONT14 ",     /* 提示正在更新LVGL字体14 */
};

/**
 * @brief       显示当前字体更新进度
 * @param       x, y    : 坐标
 * @param       size    : 字体大小
 * @param       totsize : 整个文件大小
 * @param       pos     : 当前文件指针位置
 * @retval      无
 */
static void fonts_progress_show(uint16_t x, uint16_t y, uint8_t size, uint32_t totsize, uint32_t pos)
{
    float prog;
    uint8_t t = 0xFF;
    prog = (float)pos / totsize;
    prog *= 100;

    if (t != prog)
    {
        Show_Str(x + 3 * size / 2, y, BLACK, WHITE, (uint8_t*)"%", size, 0);
        t = prog;

        if (t > 100)t = 100;

        LCD_ShowNum(x, y, t, 3, size);  /* 显示数值 */
    }
}

/**
 * @brief       更新某一个字库
 * @param       x, y    : 提示信息的显示地址
 * @param       size    : 提示信息字体大小
 * @param       fpath   : 字体路径
 * @param       fx      : 更新的内容
 *   @arg       0, ungbk;
 *   @arg       1, lv_font7;   
 *   @arg       2, lv_font8;
 *   @arg       3, lv_font10;
 *   @arg       4, lv_font12;
 *   @arg       5, lv_font14;   
 * @retval      0, 成功; 其他, 错误代码;
 */
static uint8_t fonts_update_fontx(uint16_t x, uint16_t y, uint8_t size, uint8_t *fpath, uint8_t fx)
{
    uint32_t flashaddr = 0;
    FIL *fftemp;
    uint8_t *tempbuf;
    uint8_t res;
    uint16_t bread;
    uint32_t offx = 0;
    uint8_t rval = 0;
    
    fftemp = (FIL *)mymalloc(SRAMIN, sizeof(FIL));  /* 分配内存 */
    if (fftemp == NULL) rval = 1;

    tempbuf = mymalloc(SRAMIN, 4096);               /* 分配4096个字节空间 */
    if (tempbuf == NULL) rval = 1;

    res = f_open(fftemp, (const TCHAR *)fpath, FA_READ);
    if (res) rval = 2;   /* 打开文件失败 */

    if (rval == 0)
    {
        switch (fx)
        {
            case 0: /* 更新 UNIGBK.BIN */
                ftinfo.ugbkaddr = FONTINFOADDR + sizeof(ftinfo);    /* 信息头之后，紧跟UNIGBK转换码表 */
                ftinfo.ugbksize = fftemp->obj.objsize;              /* UNIGBK大小 */
                flashaddr = ftinfo.ugbkaddr;
                break;

            case 1: /* 更新 LV_FONT_7.BIN */
                ftinfo.lv_font7_addr = ftinfo.ugbkaddr + ftinfo.ugbksize; /* UNIGBK之后，紧跟LVGL字体7 */
                ftinfo.lv_font7_size = fftemp->obj.objsize;               /* LVGL字体7大小 */
                flashaddr = ftinfo.lv_font7_addr;                         /* LVGL字体7的起始地址 */
                break;

            case 2: /* 更新 LV_FONT_8.BIN */
                ftinfo.lv_font8_addr = ftinfo.lv_font7_addr + ftinfo.lv_font7_size; /* LVGL字体7之后，紧跟LVGL字体8 */
                ftinfo.lv_font8_size = fftemp->obj.objsize;                         /* LVGL字体8大小 */
                flashaddr = ftinfo.lv_font8_addr;                                   /* LVGL字体8的起始地址 */
                break;

            case 3: /* 更新 LV_FONT_10.BIN */
                ftinfo.lv_font10_addr = ftinfo.lv_font8_addr + ftinfo.lv_font8_size; /* LVGL字体8之后，紧跟LVGL字体10 */
                ftinfo.lv_font10_size = fftemp->obj.objsize;                         /* LVGL字体10大小 */
                flashaddr = ftinfo.lv_font10_addr;                                   /* LVGL字体10的起始地址 */
                break;

            case 4: /* 更新 LV_FONT_12.BIN */
                ftinfo.lv_font12_addr = ftinfo.lv_font10_addr + ftinfo.lv_font10_size; /* LVGL字体10之后，紧跟LVGL字体12 */
                ftinfo.lv_font12_size = fftemp->obj.objsize;                          /* LVGL字体12大小 */
                flashaddr = ftinfo.lv_font12_addr;                                    /* LVGL字体12的起始地址 */
                break;

            case 5: /* 更新 LV_FONT_14.BIN */
                ftinfo.lv_font14_addr = ftinfo.lv_font12_addr + ftinfo.lv_font12_size; /* LVGL字体12之后，紧跟LVGL字体14 */
                ftinfo.lv_font14_size = fftemp->obj.objsize;                          /* LVGL字体14大小 */
                flashaddr = ftinfo.lv_font14_addr;                                    /* LVGL字体14的起始地址 */
                break;
        }

        while (res == FR_OK)   /* 循环执行 */
        {
            res = f_read(fftemp, tempbuf, 4096, (UINT *)&bread);    /* 读取数据 */
            if (res != FR_OK) break;    /* 执行错误 */

            norflash_write(tempbuf, offx + flashaddr, bread);       /* 写入数据 */
            offx += bread;
            fonts_progress_show(x, y, size, fftemp->obj.objsize, offx);  /* 进度显示 */

            if (bread != 4096) break;   /* 读完了 */
        }

        f_close(fftemp);
    }

    myfree(SRAMIN, fftemp);     /* 释放内存 */
    myfree(SRAMIN, tempbuf);    /* 释放内存 */
    
    return res;
}

/**
 * @brief       更新字体文件
 *   @note      所有字库一起更新
 * @param       x, y    : 提示信息的显示地址
 * @param       size    : 提示信息字体大小
 * @param       src     : 字库来源磁盘
 *   @arg       "0:", SD卡;
 *   @arg       "1:", FLASH盘
 * @retval      0, 成功; 其他, 错误代码;
 */
uint8_t fonts_update_font(uint16_t x, uint16_t y, uint8_t size, uint8_t *src)
{
    uint8_t *pname;
    uint32_t *buf;
    uint8_t res = 0;
    uint16_t i, j;
    FIL *fftemp;
    uint8_t rval = 0;
    res = 0xFF;
    ftinfo.fontok = 0xFF;
    
    pname = mymalloc(SRAMIN, 100);                          /* 申请100字节内存 */
    buf = mymalloc(SRAMIN, 4096);                           /* 申请4K字节内存 */
    fftemp = (FIL *)mymalloc(SRAMIN, sizeof(FIL));          /* 分配内存 */

    if (buf == NULL || pname == NULL || fftemp == NULL)
    {
        myfree(SRAMIN, fftemp);
        myfree(SRAMIN, pname);
        myfree(SRAMIN, buf);
        return 5;           /* 内存申请失败 */
    }

    for (i = 0; i < 6; i++) /* 先查找文件是否正常 - 改为6个文件 */
    {
        strcpy((char *)pname, (char *)src);                 /* copy src内容到pname */
        strcat((char *)pname, (char *)FONT_GBK_PATH[i]);    /* 追加具体文件路径 */
        res = f_open(fftemp, (const TCHAR *)pname, FA_READ);/* 尝试打开 */

        if (res)
        {
            rval |= 1 << 7; /* 标记打开文件失败 */
            break;          /* 出错了,直接退出 */
        }
        f_close(fftemp);    /* 关闭文件 */
    }

    myfree(SRAMIN, fftemp); /* 释放内存 */

    if (rval == 0)          /* 字库文件都存在 */
    {
        Show_Str(x, y, BLACK, WHITE, (uint8_t *)"Erasing sectors...", size, 0); /* 提示正在擦除扇区 */

        for (i = 0; i < FONTSECSIZE; i++)           /* 先擦除字库区域,提高写入速度 */
        {
            fonts_progress_show(x + 20 * size / 2, y, size, FONTSECSIZE, i);     /* 进度显示 */
            norflash_read((uint8_t *)buf, ((FONTINFOADDR / 4096) + i) * 4096, 4096); /* 读出整个扇区的内容 */

            for (j = 0; j < 1024; j++)              /* 校验数据 */
            {
                if (buf[j] != 0xFFFFFFFF) break;    /* 需要擦除 */
            }

            if (j != 1024)
            {
                norflash_erase_sector((FONTINFOADDR / 4096) + i); /* 需要擦除的扇区 */
            }
        }

        for (i = 0; i < 6; i++) /* 依次更新所有字库 - 改为6个文件 */
        {
            Show_Str(x, y, BLACK, WHITE, (uint8_t*)FONT_UPDATE_REMIND_TBL[i], size, 0);
            strcpy((char *)pname, (char *)src);                                     /* copy src内容到pname */
            strcat((char *)pname, (char *)FONT_GBK_PATH[i]);                        /* 追加具体文件路径 */
            res = fonts_update_fontx(x + 20 * size / 2, y, size, pname, i);         /* 更新字库 */

            if (res)
            {
                myfree(SRAMIN, buf);
                myfree(SRAMIN, pname);
                return 1 + i;
            }
        }

        /* 全部更新好了 */
        ftinfo.fontok = 0xAA;
        norflash_write((uint8_t *)&ftinfo, FONTINFOADDR, sizeof(ftinfo));           /* 保存字库信息 */
    }

    myfree(SRAMIN, pname);  /* 释放内存 */
    myfree(SRAMIN, buf);
    
    return rval;            /* 无错误 */
}

/**
 * @brief       单独更新LVGL字体7
 * @param       x, y    : 提示信息的显示地址
 * @param       size    : 提示信息字体大小
 * @param       src     : 字库来源磁盘
 * @retval      0, 成功; 其他, 错误代码;
 */
uint8_t lv_font_update_lv_font7(uint16_t x, uint16_t y, uint8_t size, uint8_t *src)
{
    uint8_t *pname;
    uint8_t res;
    
    pname = mymalloc(SRAMIN, 100);
    if (pname == NULL) return 1;
    
    strcpy((char *)pname, (char *)src);
    strcat((char *)pname, (char *)FONT_GBK_PATH[1]);  /* LVGL字体7路径 */
    
    Show_Str(x, y, BLACK, WHITE, (uint8_t*)FONT_UPDATE_REMIND_TBL[1], size, 0);
    res = fonts_update_fontx(x + 20 * size / 2, y, size, pname, 1);  /* 更新LVGL字体7 */
    
    if (res == 0) {
        /* 更新字库信息 */
        ftinfo.fontok = 0xAA;
        norflash_write((uint8_t *)&ftinfo, FONTINFOADDR, sizeof(ftinfo));
    }
    
    myfree(SRAMIN, pname);
    return res;
}

/**
 * @brief       单独更新LVGL字体8
 * @param       x, y    : 提示信息的显示地址
 * @param       size    : 提示信息字体大小
 * @param       src     : 字库来源磁盘
 * @retval      0, 成功; 其他, 错误代码;
 */
uint8_t lv_font_update_lv_font8(uint16_t x, uint16_t y, uint8_t size, uint8_t *src)
{
    uint8_t *pname;
    uint8_t res;
    
    pname = mymalloc(SRAMIN, 100);
    if (pname == NULL) return 1;
    
    strcpy((char *)pname, (char *)src);
    strcat((char *)pname, (char *)FONT_GBK_PATH[2]);  /* LVGL字体8路径 */
    
    Show_Str(x, y, BLACK, WHITE, (uint8_t*)FONT_UPDATE_REMIND_TBL[2], size, 0);
    res = fonts_update_fontx(x + 20 * size / 2, y, size, pname, 2);  /* 更新LVGL字体8 */
    
    if (res == 0) {
        /* 更新字库信息 */
        ftinfo.fontok = 0xAA;
        norflash_write((uint8_t *)&ftinfo, FONTINFOADDR, sizeof(ftinfo));
    }
    
    myfree(SRAMIN, pname);
    return res;
}

/**
 * @brief       单独更新LVGL字体10
 * @param       x, y    : 提示信息的显示地址
 * @param       size    : 提示信息字体大小
 * @param       src     : 字库来源磁盘
 * @retval      0, 成功; 其他, 错误代码;
 */
uint8_t lv_font_update_lv_font10(uint16_t x, uint16_t y, uint8_t size, uint8_t *src)
{
    uint8_t *pname;
    uint8_t res;
    
    pname = mymalloc(SRAMIN, 100);
    if (pname == NULL) return 1;
    
    strcpy((char *)pname, (char *)src);
    strcat((char *)pname, (char *)FONT_GBK_PATH[3]);  /* LVGL字体10路径 */
    
    Show_Str(x, y, BLACK, WHITE, (uint8_t*)FONT_UPDATE_REMIND_TBL[3], size, 0);
    res = fonts_update_fontx(x + 20 * size / 2, y, size, pname, 3);  /* 更新LVGL字体10 */
    
    if (res == 0) {
        /* 更新字库信息 */
        ftinfo.fontok = 0xAA;
        norflash_write((uint8_t *)&ftinfo, FONTINFOADDR, sizeof(ftinfo));
    }
    
    myfree(SRAMIN, pname);
    return res;
}

/**
 * @brief       单独更新LVGL字体12
 * @param       x, y    : 提示信息的显示地址
 * @param       size    : 提示信息字体大小
 * @param       src     : 字库来源磁盘
 * @retval      0, 成功; 其他, 错误代码;
 */
uint8_t lv_font_update_lv_font12(uint16_t x, uint16_t y, uint8_t size, uint8_t *src)
{
    uint8_t *pname;
    uint8_t res;
    
    pname = mymalloc(SRAMIN, 100);
    if (pname == NULL) return 1;
    
    strcpy((char *)pname, (char *)src);
    strcat((char *)pname, (char *)FONT_GBK_PATH[4]);  /* LVGL字体12路径 */
    
    Show_Str(x, y, BLACK, WHITE, (uint8_t*)FONT_UPDATE_REMIND_TBL[4], size, 0);
    res = fonts_update_fontx(x + 20 * size / 2, y, size, pname, 4);  /* 更新LVGL字体12 */
    
    if (res == 0) {
        /* 更新字库信息 */
        ftinfo.fontok = 0xAA;
        norflash_write((uint8_t *)&ftinfo, FONTINFOADDR, sizeof(ftinfo));
    }
    
    myfree(SRAMIN, pname);
    return res;
}

/**
 * @brief       单独更新LVGL字体14
 * @param       x, y    : 提示信息的显示地址
 * @param       size    : 提示信息字体大小
 * @param       src     : 字库来源磁盘
 * @retval      0, 成功; 其他, 错误代码;
 */
uint8_t lv_font_update_lv_font14(uint16_t x, uint16_t y, uint8_t size, uint8_t *src)
{
    uint8_t *pname;
    uint8_t res;
    
    pname = mymalloc(SRAMIN, 100);
    if (pname == NULL) return 1;
    
    strcpy((char *)pname, (char *)src);
    strcat((char *)pname, (char *)FONT_GBK_PATH[5]);  /* LVGL字体14路径 */
    
    Show_Str(x, y, BLACK, WHITE, (uint8_t*)FONT_UPDATE_REMIND_TBL[5], size, 0);
    res = fonts_update_fontx(x + 20 * size / 2, y, size, pname, 5);  /* 更新LVGL字体14 */
    
    if (res == 0) {
        /* 更新字库信息 */
        ftinfo.fontok = 0xAA;
        norflash_write((uint8_t *)&ftinfo, FONTINFOADDR, sizeof(ftinfo));
    }
    
    myfree(SRAMIN, pname);
    return res;
}

/**
 * @brief       获取LVGL字体7的地址
 * @param       无
 * @retval      LVGL字体7在Flash中的地址
 */
uint32_t lv_font_get_lv_font7_addr(void)
{
    return ftinfo.lv_font7_addr;
}

/**
 * @brief       获取LVGL字体8的地址
 * @param       无
 * @retval      LVGL字体8在Flash中的地址
 */
uint32_t lv_font_get_lv_font8_addr(void)
{
    return ftinfo.lv_font8_addr;
}

/**
 * @brief       获取LVGL字体10的地址
 * @param       无
 * @retval      LVGL字体10在Flash中的地址
 */
uint32_t lv_font_get_lv_font10_addr(void)
{
    return ftinfo.lv_font10_addr;
}

/**
 * @brief       获取LVGL字体12的地址
 * @param       无
 * @retval      LVGL字体12在Flash中的地址
 */
uint32_t lv_font_get_lv_font12_addr(void)
{
    return ftinfo.lv_font12_addr;
}

/**
 * @brief       获取LVGL字体14的地址
 * @param       无
 * @retval      LVGL字体14在Flash中的地址
 */
uint32_t lv_font_get_lv_font14_addr(void)
{
    return ftinfo.lv_font14_addr;
}

/**
 * @brief       初始化字体
 * @param       无
 * @retval      0, 字库完好; 其他, 字库丢失;
 */
uint8_t fonts_init(void)
{
    uint8_t t = 0;

    while (t < 10)  /* 连续读取10次,都是错误,说明确实是有问题,得更新字库了 */
    {
        t++;
        norflash_read((uint8_t *)&ftinfo, FONTINFOADDR, sizeof(ftinfo));    /* 读出ftinfo结构体数据 */

        if (ftinfo.fontok == 0xAA)
        {
            break;
        }
        
        delay_ms(20);
    }

    if (ftinfo.fontok != 0xAA)
    {
        return 1;
    }
    
    return 0;
}
