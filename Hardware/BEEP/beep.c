#include "beep.h"
#include "stm32f4xx.h"


void Beep_Init(void)
{
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);

    GPIO_InitTypeDef gpio_init;

    gpio_init.GPIO_Pin =GPIO_Pin_5;
    gpio_init.GPIO_Mode = GPIO_Mode_OUT;
    gpio_init.GPIO_OType = GPIO_OType_PP;
    gpio_init.GPIO_PuPd = GPIO_PuPd_NOPULL;
    gpio_init.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(GPIOE, &gpio_init);

    GPIO_ResetBits(GPIOE, GPIO_Pin_5);
}

void Beep_Control(uint8_t state)
{
    state ? GPIO_SetBits(GPIOE, GPIO_Pin_5) : GPIO_ResetBits(GPIOE, GPIO_Pin_5);
}


