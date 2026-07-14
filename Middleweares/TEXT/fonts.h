#ifndef __FONTS_H
#define __FONTS_H

#include "sys.h"

/* 字体信息保存首地址
 * 占41个字节,第1个字节用于标记字库是否存在.后续每8个字节一组,分别保存起始地址和文件大小
 */
extern uint32_t FONTINFOADDR;

/* 字库信息结构体定义
 * 用来保存字库基本信息，地址，大小等
 */
__packed typedef struct
{
    uint8_t fontok;             /* 字库存在标志，0XAA，字库正常；其他，字库不存在 */
    uint32_t ugbkaddr;          /* unigbk的地址 */
    uint32_t ugbksize;          /* unigbk的大小 */
	uint32_t lv_font7_addr;     /* LVGL字体7地址*/
    uint32_t lv_font7_size;     /* LVGL字体7大小*/
    uint32_t lv_font8_addr;     /* LVGL字体8地址*/
    uint32_t lv_font8_size;     /* LVGL字体8大小*/
    uint32_t lv_font10_addr;    /* LVGL字体10地址*/
    uint32_t lv_font10_size;    /* LVGL字体10大小*/
    uint32_t lv_font12_addr;    /* LVGL字体12地址*/
    uint32_t lv_font12_size;    /* LVGL字体12大小*/
	uint32_t lv_font14_addr;    /* LVGL字体14地址*/
    uint32_t lv_font14_size;	/* LVGL字体14大小*/
} _font_info;

/* 字库信息结构体 */
extern _font_info ftinfo;

/* 字库更新函数 */
static uint8_t fonts_update_fontx(uint16_t x, uint16_t y, uint8_t size, uint8_t *fpath, uint8_t fx); /* 更新某一个字库 */
uint8_t fonts_update_font(uint16_t x, uint16_t y, uint8_t size, uint8_t *src);  /* 更新全部字库 */
uint8_t fonts_init(void);       /* 初始化字库 */

/* LVGL字体相关函数 */
uint8_t lv_font_update_lv_font7(uint16_t x, uint16_t y, uint8_t size, uint8_t *src);   /* 更新LVGL字体7 */
uint8_t lv_font_update_lv_font8(uint16_t x, uint16_t y, uint8_t size, uint8_t *src);   /* 更新LVGL字体8 */
uint8_t lv_font_update_lv_font10(uint16_t x, uint16_t y, uint8_t size, uint8_t *src);  /* 更新LVGL字体10 */
uint8_t lv_font_update_lv_font12(uint16_t x, uint16_t y, uint8_t size, uint8_t *src);  /* 更新LVGL字体12 */
uint8_t lv_font_update_lv_font14(uint16_t x, uint16_t y, uint8_t size, uint8_t *src);  /* 更新LVGL字体14 */

/* LVGL字体地址获取函数 */
uint32_t lv_font_get_lv_font7_addr(void);   /* 获取LVGL字体7地址 */
uint32_t lv_font_get_lv_font8_addr(void);   /* 获取LVGL字体8地址 */
uint32_t lv_font_get_lv_font10_addr(void);  /* 获取LVGL字体10地址 */
uint32_t lv_font_get_lv_font12_addr(void);  /* 获取LVGL字体12地址 */
uint32_t lv_font_get_lv_font14_addr(void);  /* 获取LVGL字体14地址 */

#endif
