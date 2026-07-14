#include "stm32f4xx.h"
#include "tim3.h"
#include "lvgl.h"
#include "sys.h"

void TIM3_Int_Init(uint16_t arr, uint16_t psc)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    TIM_TimeBaseStructure.TIM_Period = arr;              // 自动重装值
    TIM_TimeBaseStructure.TIM_Prescaler = psc;           // 预分频系数
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

    TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

    NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; // 高优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    TIM_Cmd(TIM3, ENABLE);
}

void TIM3_IRQHandler(void)
{
       /* 检测时间更新中断的标志位是否置位 */
    if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)
    {
#if SYS_SUPPORT_OS
		
#else
        lv_tick_inc(1); // 告诉LVGL：时间过了1ms
#endif
        /* 清空标志位 */
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
    }
}
