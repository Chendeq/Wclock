#ifndef __LCD_H
#define __LCD_H

#include "sys.h"
#include "stdlib.h"

/*================= LCD 重要参数集合 =================*/
typedef struct
{
    uint16_t width;     // 屏幕宽度（像素）
    uint16_t height;    // 屏幕高度（像素）
    uint16_t id;        // 驱动芯片 ID（如 9341）
    uint8_t  dir;       // 扫描方向：0-竖屏 1-横屏 2-180° 3-270°
    uint16_t wramcmd;   // 开始写 GRAM 指令
    uint16_t rramcmd;   // 开始读 GRAM 指令
    uint16_t setxcmd;   // 设置 X 坐标指令
    uint16_t setycmd;   // 设置 Y 坐标指令
}_lcd_dev;

/* 在 lcd.c 中真正定义的全局变量 */
extern _lcd_dev lcddev;      // 保存当前 LCD 参数
extern uint16_t POINT_COLOR; // 当前画笔颜色（默认黑色）
extern uint16_t BACK_COLOR;  // 当前背景颜色（默认白色）

/*--------------- 用户可改宏 ---------------*/
#define USE_HORIZONTAL   0      // 0-不旋转 1-90° 2-180° 3-270°
#define LCD_USE8BIT_MODEL 0     // 0-16 位并口 1-8 位并口

/*--------------- 屏幕物理尺寸 ---------------*/
#define LCD_W 240
#define LCD_H 320

/*================= 常用颜色宏 =================*/
#define WHITE       0xFFFF
#define BLACK       0x0000
#define BLUE        0x001F
#define BRED        0xF81F
#define GRED        0xFFE0
#define GBLUE       0x07FF
#define RED         0xF800
#define MAGENTA     0xF81F
#define GREEN       0x07E0
#define CYAN        0x7FFF
#define YELLOW      0xFFE0
#define BROWN       0xBC40
#define BRRED       0xFC07
#define GRAY        0x8430
#define DARKBLUE    0x01CF
#define LIGHTBLUE   0x7D7C
#define GRAYBLUE    0x5458
#define LIGHTGREEN  0x841F
#define LIGHTGRAY   0xEF5B
#define LGRAY       0xC618
#define LGRAYBLUE   0xA651
#define LBBLUE      0x2B12

/*================= 引脚/寄存器映射 =================*/
#define LED  15                  // 背光控制引脚 PB15
#define LCD_LED PBout(LED)       // 背光宏
#define LCD_BACKLIGHT_MIN 0
#define LCD_BACKLIGHT_MAX 100

typedef struct
{
    vu16 LCD_REG;   // RS=0 命令
    vu16 LCD_RAM;   // RS=1 数据
} LCD_TypeDef;

#define LCD_BASE  ((uint32_t)(0x6C000000 | 0x0000007E))
#define LCD       ((LCD_TypeDef *) LCD_BASE)

/*================= 基础功能声明 =================*/
void LCD_Init(void);                // 初始化
void LCD_Backlight_Init(void);
void LCD_Backlight_Set(uint8_t percent);
uint8_t LCD_Backlight_Get(void);
void LCD_Clear(uint16_t Color);     // 全屏清指定颜色
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos);
void LCD_SetWindows(uint16_t xStar, uint16_t yStar, uint16_t xEnd, uint16_t yEnd);
void LCD_DrawPoint(uint16_t x, uint16_t y);        // 画点
uint16_t LCD_ReadPoint(uint16_t x, uint16_t y);    // 读点颜色
void Lcd_WriteData_16Bit(uint16_t Data);           // 写 16 位数据
uint16_t Lcd_ReadData_16Bit(void);                 // 读 16 位数据
void LCD_WR_REG(uint16_t data);     // 写寄存器
void LCD_WR_DATA(uint16_t data);    // 写数据
uint16_t LCD_RD_DATA(void);         // 读数据
void LCD_WriteReg(uint16_t LCD_Reg, uint16_t LCD_RegValue);
void LCD_ReadReg(uint16_t LCD_Reg, uint8_t *Rval, int n);
void LCD_direction(uint8_t direction);  // 旋转屏幕
uint16_t Color_To_565(uint8_t r, uint8_t g, uint8_t b);
uint16_t LCD_Read_ID(void);         // 读取驱动 IC ID

/*================= 高级封装 =================*/
uint32_t lcd_read_point(uint16_t x, uint16_t y);
void     lcd_draw_point(uint16_t x, uint16_t y, uint32_t color);
void     lcd_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint32_t color);
void     lcd_color_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t *color);
void     lcd_draw_hline(uint16_t x, uint16_t y, uint16_t len, uint16_t color);

#endif