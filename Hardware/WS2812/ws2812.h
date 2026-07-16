#ifndef __WS2812_H__
#define __WS2812_H__

#include "stm32f4xx.h"

#ifndef WS2812_LED_NUM
#define WS2812_LED_NUM 5
#endif

#define WS2812_COLOR_BLACK 0x000000U
#define WS2812_COLOR_RED 0xFF0000U
#define WS2812_COLOR_GREEN 0x00FF00U
#define WS2812_COLOR_BLUE 0x0000FFU
#define WS2812_COLOR_WHITE 0xFFFFFFU

void WS2812_Init(void);
void WS2812_SetPixelRGB(uint16_t index, uint8_t red, uint8_t green, uint8_t blue);
void WS2812_SetPixelGRB(uint16_t index, uint8_t green, uint8_t red, uint8_t blue);
void WS2812_SetPixelColor(uint16_t index, uint32_t rgb);
void WS2812_FillRGB(uint8_t red, uint8_t green, uint8_t blue);
void WS2812_Clear(void);
void WS2812_Refresh(void);
uint8_t WS2812_IsBusy(void);

#endif
