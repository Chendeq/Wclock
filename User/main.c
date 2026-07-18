#include "stm32f4xx.h"
#include "lcd.h"
#include "gui.h"
#include "touch.h"
#include "fonts.h"
#include "key.h"
#include "delay.h"
#include "tf.h"
#include "ff.h"
#include "exfuns.h"
#include "24c02.h"
#include "w25q128.h"
#include "sram.h"
#include "malloc.h"
#include "rtos_task.h"
#include "usart1.h"
#include "beep.h"

#include "lvgl.h"
#include "lv_port_disp.h"
#include "lv_port_indev.h"


int main(void)
{	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//中断分组
	delay_init(168);     //延时初始化
	
	Key_Init();
	USART1_Init();
	Beep_Init();
	AT24CXX_Init();
	my_mem_init(SRAMIN);
	norflash_init();

	fonts_init();

	SD_Init();
	exfuns_init();
	f_mount(fs[0],"0:",1);

	lv_init();
	lv_port_disp_init();
	lv_port_indev_init();

	task_init();
	

	while(1)
	{

	}
}
