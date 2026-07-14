#include "led.h"

void LED_Init(void)
{

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;
	
	GPIO_Init(GPIOE,&GPIO_InitStructure);
	
	GPIO_SetBits(GPIOE,GPIO_Pin_4);
	
}

void LED_Control(uint8_t state)
{
    if (state) 
	{
		GPIO_ResetBits(GPIOE, GPIO_Pin_4);
    } 
	else 
	{
        GPIO_SetBits(GPIOE, GPIO_Pin_4);
    }
}


