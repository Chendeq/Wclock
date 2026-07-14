#include "key.h"
#include "delay.h"

/**
 * 函    数：按键初始化
 * 参    数：无
 * 返 回 值：无
 */
void Key_Init(void)
{
  /*开启时钟*/
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE); // 开启GPIOB的时钟

  /*GPIO初始化*/
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;       // 普通输出模式
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz; // 100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;       // 无上拉
  GPIO_Init(GPIOE, &GPIO_InitStructure);             // 初始化
}

/**
 * 函    数：按键获取键码
 * 参    数：无
 * 返 回 值：按下按键的键码值，范围：0~2，返回0代表没有按键按下
 * 注意事项：此函数是阻塞式操作，当按键按住不放时，函数会卡住，直到按键松手
 */
uint8_t Key_GetNum(void)
{
  uint8_t KeyNum = 0; // 定义变量，默认键码值为0

  if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3) == 0) // 读PB1输入寄存器的状态，如果为0，则代表按键1按下
  {
    delay_ms(20); // 延时消抖

    while (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3) == 0)
      ;           // 等待按键松手
    delay_ms(20); // 延时消抖
    KeyNum = 1;   // 置键码为1
  }

  return KeyNum; // 返回键码值，如果没有按键按下，所有if都不成立，则键码为默认值0
}

/* 自定义按键扫描函数，支持非阻塞扫描 */
uint8_t key_scan(uint8_t mode)
{
  static uint8_t key_up = 1; /* 按键松开标志 */
  uint8_t keyval = 0;

  if (mode)
    key_up = 1; /* 支持连按 */

  if (key_up && (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3) == 0))
  {
    // 消抖
    delay_ms(10); // 延时消抖
    key_up = 0;
    if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3) == 0)
      keyval = 1; /* 按键按下 */
  }
  else if (GPIO_ReadInputDataBit(GPIOE, GPIO_Pin_3) == 1)
  {
    key_up = 1;
  }

  return keyval;
}
