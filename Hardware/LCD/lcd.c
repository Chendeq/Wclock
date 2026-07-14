#include "lcd.h"
#include "stdlib.h"
#include "delay.h"	 

	   
//管理LCD重要参数
//默认为竖屏
_lcd_dev lcddev;

//画笔颜色,背景颜色
uint16_t POINT_COLOR = 0x0000,BACK_COLOR = 0xFFFF;  
uint16_t DeviceCode;	 
static uint8_t lcd_backlight_percent = 50;	// 背光亮度默认50%

static uint8_t LCD_Backlight_Clamp(uint8_t percent)
{
	if(percent > LCD_BACKLIGHT_MAX)
	{
		return LCD_BACKLIGHT_MAX;
	}
	return percent;
}

void LCD_Backlight_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;	// 定时器基础结构体
	TIM_OCInitTypeDef TIM_OCInitStructure;			// 定时器通道结构体

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource15, GPIO_AF_TIM1);	// 配置PB15为TIM1通道3复用功能
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;				// 推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	TIM_TimeBaseStructure.TIM_Prescaler = 167;					// 预分频器值，168MHz/168=1MHz
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	// 向上计数模式
	TIM_TimeBaseStructure.TIM_Period = 99;						// 定时器周期值，99=100ms
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;		// 时钟分频器值，1分频
	TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;			// 重复计数器值，0表示不重复
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;					// PWM模式模式1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Disable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;			// 输出比较极性，高电平有效
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_High;			// 输出比较极性，高电平有效
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	TIM_OC3Init(TIM1, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM1, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM1, ENABLE);
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
	TIM_Cmd(TIM1, ENABLE);

	LCD_Backlight_Set(lcd_backlight_percent);								// 设置背光亮度
}

void LCD_Backlight_Set(uint8_t percent)
{
	lcd_backlight_percent = LCD_Backlight_Clamp(percent);
	TIM_SetCompare3(TIM1, lcd_backlight_percent);						// 设置定时器通道3的比较值，即背光亮度
}

uint8_t LCD_Backlight_Get(void)
{
	return lcd_backlight_percent;
}


uint16_t LCD_read(void)
{
	vu16 data;  //防止被优化
	data=LCD->LCD_RAM;	
#if LCD_USE8BIT_MODEL
	return (data>>8);  
#else
	return data;
#endif
}

/*****************************************************************************
 * @name       :void LCD_WR_REG(uint16_t data)
 * @date       :2018-08-09 
 * @function   :向LCD屏幕写入16位命令
 * @parameters :data:要写入的命令值
 * @retvalue   :无
******************************************************************************/
void LCD_WR_REG(uint16_t data)
{ 
	data=data;  //使用-O2优化的时候,必须插入的延时
#if LCD_USE8BIT_MODEL
	LCD->LCD_REG=(data<<8); //写入要写的寄存器序号
#else
	LCD->LCD_REG=data; //写入要写的寄存器序号
#endif	
}

/*****************************************************************************
 * @name       :void LCD_WR_DATA(uint16_t data)
 * @date       :2018-08-09 
 * @function   :向LCD屏幕写入16位数据
 * @parameters :data:要写入的数据值
 * @retvalue   :无
******************************************************************************/
void LCD_WR_DATA(uint16_t data)
{
	data=data;			//使用-O2优化的时候,必须插入的延时
#if LCD_USE8BIT_MODEL
	LCD->LCD_RAM=(data<<8);//写入要写的数据
#else
	LCD->LCD_RAM=data; //写入要写的数据
#endif
}

/*****************************************************************************
 * @name       :uint16_t LCD_RD_DATA(void)
 * @date       :2018-11-13 
 * @function   :从LCD屏幕读取16位值
 * @parameters :无
 * @retvalue   :读取的值
******************************************************************************/
uint16_t LCD_RD_DATA(void)
{
	return LCD_read();
}

/*****************************************************************************
 * @name       :void LCD_WriteReg(uint16_t LCD_Reg, uint16_t LCD_RegValue)
 * @date       :2018-08-09 
 * @function   :向寄存器写入数据
 * @parameters :LCD_Reg:寄存器地址
                LCD_RegValue:要写入的数据
 * @retvalue   :无
******************************************************************************/
void LCD_WriteReg(uint16_t LCD_Reg, uint16_t LCD_RegValue)
{
#if LCD_USE8BIT_MODEL	
	LCD->LCD_REG = (LCD_Reg<<8);		//写入要写的寄存器序号	 
	LCD->LCD_RAM = (LCD_RegValue<<8);//写入数据
#else
	LCD->LCD_REG = LCD_Reg;		//写入要写的寄存器序号	 
	LCD->LCD_RAM = LCD_RegValue;//写入数据	     		 
#endif
}	   

/*****************************************************************************
 * @name       :uint16_t LCD_ReadReg(uint16_t LCD_Reg)
 * @date       :2018-11-13 
 * @function   :从指定寄存器读取值
 * @parameters :LCD_Reg:寄存器地址
 * @retvalue   :读取的值
******************************************************************************/
void LCD_ReadReg(uint16_t LCD_Reg,uint8_t *Rval,int n)
{
	LCD_WR_REG(LCD_Reg); 
	while(n--)
	{		
		*(Rval++) = LCD_RD_DATA();
		delay_us(100);
	}
}

/*****************************************************************************
 * @name       :void LCD_WriteRAM_Prepare(void)
 * @date       :2018-08-09 
 * @function   :写GRAM
 * @parameters :无
 * @retvalue   :无
******************************************************************************/	 
void LCD_WriteRAM_Prepare(void)
{
	LCD_WR_REG(lcddev.wramcmd);
}	 

/*****************************************************************************
 * @name       :void LCD_ReadRAM_Prepare(void)
 * @date       :2018-11-13 
 * @function   :读GRAM
 * @parameters :无
 * @retvalue   :无
******************************************************************************/	 
void LCD_ReadRAM_Prepare(void)
{
	LCD_WR_REG(lcddev.rramcmd);
}

/*****************************************************************************
 * @name       :void Lcd_WriteData_16Bit(uint16_t Data)
 * @date       :2018-08-09 
 * @function   :向LCD屏幕写入16位命令
 * @parameters :Data:要写入的数据
 * @retvalue   :无
******************************************************************************/	 
void Lcd_WriteData_16Bit(uint16_t Data)
{
#if LCD_USE8BIT_MODEL	
	 LCD->LCD_RAM = Data;
	 LCD->LCD_RAM = Data<<8;    //写十六位颜色值
#else
	 LCD->LCD_RAM = Data;  //写十六位颜色值
#endif
}

uint16_t Color_To_565(uint8_t r, uint8_t g, uint8_t b)
{
	return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | ((b & 0xF8) >> 3);
}

/*****************************************************************************
 * @name       :uint16_t Lcd_ReadData_16Bit(void)
 * @date       :2018-11-13 
 * @function   :从LCD屏幕读取16位值
 * @parameters :无
 * @retvalue   :读取的值
******************************************************************************/	
uint16_t Lcd_ReadData_16Bit(void)
{
	uint16_t r,g,b;
	//虚拟数据
	r = LCD_RD_DATA();
	delay_us(1);//延时1us
	//8bit:红色数据	
	//16bit:红色和绿色数据
	r = LCD_RD_DATA();
	delay_us(1);//延时1us	
	//8bit:绿色数据
	//16bit:蓝色数据
	g = LCD_RD_DATA();
#if LCD_USE8BIT_MODEL
	delay_us(1);//延时1us	
	//8bit:蓝色数据
	b = LCD_RD_DATA();
#else
	b = g>>8;
	g = r&0xFF; 
	r = r>>8;
#endif
	return Color_To_565(r, g, b);
}

/*****************************************************************************
 * @name       :void LCD_DrawPoint(uint16_t x,uint16_t y)
 * @date       :2018-08-09 
 * @function   :在指定位置写入像素数据
 * @parameters :x:像素的x坐标
                y:像素的y坐标
 * @retvalue   :无
******************************************************************************/	
void LCD_DrawPoint(uint16_t x,uint16_t y)
{
	LCD_SetCursor(x,y);//设置光标位置 
	Lcd_WriteData_16Bit(POINT_COLOR); 
}

/*****************************************************************************
 * @name       :uint16_t LCD_ReadPoint(uint16_t x,uint16_t y)
 * @date       :2018-11-13 
 * @function   :在指定位置读取像素颜色值
 * @parameters :x:像素的x坐标
                y:像素的y坐标
 * @retvalue   :读取的颜色值
******************************************************************************/	
uint16_t LCD_ReadPoint(uint16_t x,uint16_t y)
{
	uint16_t color;
	if(x>=lcddev.width||y>=lcddev.height)
	{
		return 0;	//超过了范围,直接返回	
	}
	LCD_SetCursor(x,y);//设置光标位置 
	LCD_ReadRAM_Prepare();
	color = Lcd_ReadData_16Bit();
	return color;
}

/*****************************************************************************
 * @name       :void LCD_Clear(uint16_t Color)
 * @date       :2018-08-09 
 * @function   :全屏填充LCD屏幕
 * @parameters :color:填充颜色
 * @retvalue   :无
******************************************************************************/	
void LCD_Clear(uint16_t Color)
{
  unsigned int i;//,m;  
	u32 total_point=lcddev.width*lcddev.height;
	LCD_SetWindows(0,0,lcddev.width-1,lcddev.height-1);   
	for(i=0;i<total_point;i++)
	{ 
#if LCD_USE8BIT_MODEL	
		LCD->LCD_RAM = Color;
		LCD->LCD_RAM = Color<<8;
#else
		LCD->LCD_RAM = Color;
#endif
	}
} 

/*****************************************************************************
 * @name       :void LCD_GPIOInit(void)
 * @date       :2018-08-09 
 * @function   :初始化LCD屏幕GPIO
 * @parameters :无
 * @retvalue   :无
******************************************************************************/	
void LCD_GPIOInit(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	FSMC_NORSRAMInitTypeDef  FSMC_NORSRAMInitStructure;
    FSMC_NORSRAMTimingInitTypeDef  readWriteTiming; 
	FSMC_NORSRAMTimingInitTypeDef  writeTiming;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOD|RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOF|RCC_AHB1Periph_GPIOG, ENABLE);//使能PD,PE,PF,PG时钟  
    RCC_AHB3PeriphClockCmd(RCC_AHB3Periph_FSMC,ENABLE);//使能FSMC时钟  
	
 
	// GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;//PB15 推挽输出,控制背光
    // GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
    // GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
    // GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//100MHz
    // GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
    // GPIO_Init(GPIOB, &GPIO_InitStructure);//初始化 //PB15 推挽输出,控制背光
    
    GPIO_InitStructure.GPIO_Pin = (3<<0)|(3<<4)|(7<<8)|(3<<14);//PD0,1,4,5,8,9,10,14,15 AF OUT
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用输出
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
    GPIO_Init(GPIOD, &GPIO_InitStructure);//初始化  
    
    GPIO_InitStructure.GPIO_Pin = (0X1FF<<7);//PE7~15,AF OUT
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用输出
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
    GPIO_Init(GPIOE, &GPIO_InitStructure);//初始化  

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;//PF12,FSMC_A6
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用输出
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
    GPIO_Init(GPIOF, &GPIO_InitStructure);//初始化  

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;//PG12,FSMC_NE4
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;//复用输出
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
    GPIO_Init(GPIOG, &GPIO_InitStructure);//初始化 

    GPIO_PinAFConfig(GPIOD,GPIO_PinSource0,GPIO_AF_FSMC);//PD0,AF12
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource1,GPIO_AF_FSMC);//PD1,AF12
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource4,GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource5,GPIO_AF_FSMC); 
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource8,GPIO_AF_FSMC); 
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource9,GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource10,GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource14,GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOD,GPIO_PinSource15,GPIO_AF_FSMC);//PD15,AF12
 
    GPIO_PinAFConfig(GPIOE,GPIO_PinSource7,GPIO_AF_FSMC);//PE7,AF12
    GPIO_PinAFConfig(GPIOE,GPIO_PinSource8,GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOE,GPIO_PinSource9,GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOE,GPIO_PinSource10,GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOE,GPIO_PinSource11,GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOE,GPIO_PinSource12,GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOE,GPIO_PinSource13,GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOE,GPIO_PinSource14,GPIO_AF_FSMC);
    GPIO_PinAFConfig(GPIOE,GPIO_PinSource15,GPIO_AF_FSMC);//PE15,AF12
 
    GPIO_PinAFConfig(GPIOF,GPIO_PinSource12,GPIO_AF_FSMC);//PF12,AF12
    GPIO_PinAFConfig(GPIOG,GPIO_PinSource12,GPIO_AF_FSMC);


    readWriteTiming.FSMC_AddressSetupTime = 0XF;	 //地址建立时间(ADDSET)为16个HCLK 1/168M=6ns*16=96ns	
    readWriteTiming.FSMC_AddressHoldTime = 0x00;	 //地址保持时间(ADDHLD)模式A未用到	
    readWriteTiming.FSMC_DataSetupTime = 60;			//数据保存时间为60个HCLK	=6*60=360ns
    readWriteTiming.FSMC_BusTurnAroundDuration = 0x00;
    readWriteTiming.FSMC_CLKDivision = 0x00;
    readWriteTiming.FSMC_DataLatency = 0x00;
    readWriteTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 //模式A 
    

	writeTiming.FSMC_AddressSetupTime =9;	      //地址建立时间(ADDSET)为9个HCLK =54ns 
    writeTiming.FSMC_AddressHoldTime = 0x00;	 //地址保持时间(A		
    writeTiming.FSMC_DataSetupTime = 8;		 //数据保存时间为6ns*9个HCLK=54ns
    writeTiming.FSMC_BusTurnAroundDuration = 0x00;
    writeTiming.FSMC_CLKDivision = 0x00;
    writeTiming.FSMC_DataLatency = 0x00;
    writeTiming.FSMC_AccessMode = FSMC_AccessMode_A;	 //模式A 

 
    FSMC_NORSRAMInitStructure.FSMC_Bank = FSMC_Bank1_NORSRAM4;//  这里我们使用NE4 ，也就对应BTCR[6],[7]。
    FSMC_NORSRAMInitStructure.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable; // 不复用数据地址
    FSMC_NORSRAMInitStructure.FSMC_MemoryType =FSMC_MemoryType_SRAM;// FSMC_MemoryType_SRAM;  //SRAM   
    FSMC_NORSRAMInitStructure.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;//存储器数据宽度为16bit    
    FSMC_NORSRAMInitStructure.FSMC_BurstAccessMode =FSMC_BurstAccessMode_Disable;// FSMC_BurstAccessMode_Disable; 
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMInitStructure.FSMC_AsynchronousWait=FSMC_AsynchronousWait_Disable; 
    FSMC_NORSRAMInitStructure.FSMC_WrapMode = FSMC_WrapMode_Disable;   
    FSMC_NORSRAMInitStructure.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;  
    FSMC_NORSRAMInitStructure.FSMC_WriteOperation = FSMC_WriteOperation_Enable;	//  存储器写使能
    FSMC_NORSRAMInitStructure.FSMC_WaitSignal = FSMC_WaitSignal_Disable;   
    FSMC_NORSRAMInitStructure.FSMC_ExtendedMode = FSMC_ExtendedMode_Enable; // 读写使用不同的时序
    FSMC_NORSRAMInitStructure.FSMC_WriteBurst = FSMC_WriteBurst_Disable; 
    FSMC_NORSRAMInitStructure.FSMC_ReadWriteTimingStruct = &readWriteTiming; //读写时序
    FSMC_NORSRAMInitStructure.FSMC_WriteTimingStruct = &writeTiming;  //写时序

    FSMC_NORSRAMInit(&FSMC_NORSRAMInitStructure);  //初始化FSMC配置

    FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4, ENABLE);  // 使能BANK1 
	
	//重新配置写时序控制寄存器的时间使WR时间为最快   	 							    
	FSMC_Bank1E->BWTR[6]&=~(0XF<<0);//地址建立时间(ADDSET)清零 	 
	FSMC_Bank1E->BWTR[6]&=~(0XF<<8);//数据保存时间清零
	FSMC_Bank1E->BWTR[6]|=4<<0;		//地址建立时间(ADDSET)为4个HCLK =24ns  	 
	FSMC_Bank1E->BWTR[6]|=3<<8; 	//数据保存时间(DATAST)为6ns*3个HCLK=18ns
}

/*****************************************************************************
 * @name       :void LCD_Init(void)
 * @date       :2018-08-09 
 * @function   :初始化LCD屏幕
 * @parameters :无
 * @retvalue   :无
******************************************************************************/	 	 
void LCD_Init(void)
{  
	LCD_GPIOInit();//LCD GPIO初始化	
	LCD_Backlight_Init();//初始化背光
	delay_ms(100);
//*************2.8寸 ILI9341初始化**********//	
	LCD_WR_REG(0xCF);  
	LCD_WR_DATA(0x00); 
	LCD_WR_DATA(0xC9); //C1 
	LCD_WR_DATA(0X30); 
	LCD_WR_REG(0xED);  
	LCD_WR_DATA(0x64); 
	LCD_WR_DATA(0x03); 
	LCD_WR_DATA(0X12); 
	LCD_WR_DATA(0X81); 
	LCD_WR_REG(0xE8);  
	LCD_WR_DATA(0x85); 
	LCD_WR_DATA(0x10); 
	LCD_WR_DATA(0x7A); 
	LCD_WR_REG(0xCB);  
	LCD_WR_DATA(0x39); 
	LCD_WR_DATA(0x2C); 
	LCD_WR_DATA(0x00); 
	LCD_WR_DATA(0x34); 
	LCD_WR_DATA(0x02); 
	LCD_WR_REG(0xF7);  
	LCD_WR_DATA(0x20); 
	LCD_WR_REG(0xEA);  
	LCD_WR_DATA(0x00); 
	LCD_WR_DATA(0x00); 
	LCD_WR_REG(0xC0);    //Power control 
	LCD_WR_DATA(0x1B);   //VRH[5:0] 
	LCD_WR_REG(0xC1);    //Power control 
	LCD_WR_DATA(0x00);   //SAP[2:0];BT[3:0] 01 
	LCD_WR_REG(0xC5);    //VCM control 
	LCD_WR_DATA(0x30); 	 //3F
	LCD_WR_DATA(0x30); 	 //3C
	LCD_WR_REG(0xC7);    //VCM control2 
	LCD_WR_DATA(0XB7); 
	LCD_WR_REG(0x36);    // Memory Access Control 
	LCD_WR_DATA(0x08); 
	LCD_WR_REG(0x3A);   
	LCD_WR_DATA(0x55); 
	LCD_WR_REG(0xB1);   
	LCD_WR_DATA(0x00);   
	LCD_WR_DATA(0x1A); 
	LCD_WR_REG(0xB6);    // Display Function Control 
	LCD_WR_DATA(0x0A); 
	LCD_WR_DATA(0xA2); 
	LCD_WR_REG(0xF2);    // 3Gamma Function Disable 
	LCD_WR_DATA(0x00); 
	LCD_WR_REG(0x26);    //Gamma curve selected 
	LCD_WR_DATA(0x01); 
	LCD_WR_REG(0xE0);    //Set Gamma 
	LCD_WR_DATA(0x0F); 
	LCD_WR_DATA(0x2A); 
	LCD_WR_DATA(0x28); 
	LCD_WR_DATA(0x08); 
	LCD_WR_DATA(0x0E); 
	LCD_WR_DATA(0x08); 
	LCD_WR_DATA(0x54); 
	LCD_WR_DATA(0XA9); 
	LCD_WR_DATA(0x43); 
	LCD_WR_DATA(0x0A); 
	LCD_WR_DATA(0x0F); 
	LCD_WR_DATA(0x00); 
	LCD_WR_DATA(0x00); 
	LCD_WR_DATA(0x00); 
	LCD_WR_DATA(0x00); 		 
	LCD_WR_REG(0XE1);    //Set Gamma 
	LCD_WR_DATA(0x00); 
	LCD_WR_DATA(0x15); 
	LCD_WR_DATA(0x17); 
	LCD_WR_DATA(0x07); 
	LCD_WR_DATA(0x11); 
	LCD_WR_DATA(0x06); 
	LCD_WR_DATA(0x2B); 
	LCD_WR_DATA(0x56); 
	LCD_WR_DATA(0x3C); 
	LCD_WR_DATA(0x05); 
	LCD_WR_DATA(0x10); 
	LCD_WR_DATA(0x0F); 
	LCD_WR_DATA(0x3F); 
	LCD_WR_DATA(0x3F); 
	LCD_WR_DATA(0x0F); 
	LCD_WR_REG(0x2B); 
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x01);
	LCD_WR_DATA(0x3f);
	LCD_WR_REG(0x2A); 
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0x00);
	LCD_WR_DATA(0xef);	 
	LCD_WR_REG(0x11); //退出睡眠
	delay_ms(120);
	LCD_WR_REG(0x29); //显示开启		

    LCD_direction(USE_HORIZONTAL);//设置LCD显示方向
	// LCD_LED=1;//点亮背光	 
	// LCD_Clear(WHITE);//清除屏幕白色
}
 
/*****************************************************************************
 * @name       :void LCD_SetWindows(uint16_t xStar, uint16_t yStar,uint16_t xEnd,uint16_t yEnd)
 * @date       :2018-08-09 
 * @function   :设置LCD显示窗口
 * @parameters :xStar:LCD显示窗口起始x坐标
								yStar:LCD显示窗口起始y坐标
								xEnd:LCD显示窗口结束x坐标
								yEnd:LCD显示窗口结束y坐标
 * @retvalue   :无
******************************************************************************/ 
void LCD_SetWindows(uint16_t xStar, uint16_t yStar,uint16_t xEnd,uint16_t yEnd)
{	
	LCD_WR_REG(lcddev.setxcmd);	
	LCD_WR_DATA(xStar>>8);
	LCD_WR_DATA(0x00FF&xStar);		
	LCD_WR_DATA(xEnd>>8);
	LCD_WR_DATA(0x00FF&xEnd);

	LCD_WR_REG(lcddev.setycmd);	
	LCD_WR_DATA(yStar>>8);
	LCD_WR_DATA(0x00FF&yStar);		
	LCD_WR_DATA(yEnd>>8);
	LCD_WR_DATA(0x00FF&yEnd);

	LCD_WriteRAM_Prepare();	//开始写入GRAM			
}   

/*****************************************************************************
 * @name       :void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos)
 * @date       :2018-08-09 
 * @function   :设置坐标值
 * @parameters :Xpos:像素的x坐标
								Ypos:像素的y坐标
 * @retvalue   :无
******************************************************************************/ 
void LCD_SetCursor(uint16_t Xpos, uint16_t Ypos)
{	  	    			
	LCD_SetWindows(Xpos,Ypos,Xpos,Ypos);	
} 

/*****************************************************************************
 * @name       :void LCD_direction(uint8_t direction)
 * @date       :2018-08-09 
 * @function   :设置LCD屏幕的显示方向
 * @parameters :direction:0-0度
                          1-90度
													2-180度
													3-270度
 * @retvalue   :无
******************************************************************************/ 
void LCD_direction(uint8_t direction)
{ 
			lcddev.setxcmd=0x2A;
			lcddev.setycmd=0x2B;
			lcddev.wramcmd=0x2C;
			lcddev.rramcmd=0x2E;
	switch(direction){		  
		case 0:						 	 		
			lcddev.width=LCD_W;
			lcddev.height=LCD_H;		
			LCD_WriteReg(0x36,(1<<3));
		break;
		case 1:
			lcddev.width=LCD_H;
			lcddev.height=LCD_W;
			LCD_WriteReg(0x36,(1<<3)|(1<<5)|(1<<6));
		break;
		case 2:						 	 		
			lcddev.width=LCD_W;
			lcddev.height=LCD_H;	
			LCD_WriteReg(0x36,(1<<3)|(1<<7)|(1<<4)|(1<<6));
		break;
		case 3:
			lcddev.width=LCD_H;
			lcddev.height=LCD_W;
			LCD_WriteReg(0x36,(1<<3)|(1<<7)|(1<<5)|(1<<4));
		break;	
		default:break;
	}		
}	 

/*****************************************************************************
 * @name       :uint16_t LCD_Read_ID(void)
 * @date       :2018-11-13 
 * @function   :读取ID
 * @parameters :无
 * @retvalue   :ID值
******************************************************************************/ 
uint16_t LCD_Read_ID(void)
{
	uint8_t val[4] = {0};
	LCD_ReadReg(0xD3,val,4);
	return (val[2]<<8)|val[3];
}

/*------------------ 32-bit 颜色接口 ------------------*/

/**
 * @brief  读取指定像素颜色(32-bit 容量)
 * @param  x,y: 像素坐标
 * @retval 32-bit 颜色值(低 16 位为 565 格式，高 16 位保留为 0)
 */
uint32_t lcd_read_point(uint16_t x, uint16_t y)
{
    return (uint32_t)LCD_ReadPoint(x, y);   /* 底层还是 16-bit 565 */
}

/**
 * @brief  在指定位置画点(32-bit 颜色)
 * @param  x,y: 坐标
 * @param  color: 32-bit 颜色值(仅低 16 位有效，565 格式)
 */
void lcd_draw_point(uint16_t x, uint16_t y, uint32_t color)
{
    LCD_SetCursor(x, y);
    Lcd_WriteData_16Bit((uint16_t)color);   /* 取低 16 位写入 */
}

/**
 * @brief  纯色填充矩形(32-bit 颜色)
 * @param  sx,sy: 左上角
 * @param  ex,ey: 右下角
 * @param  color: 32-bit 颜色值(低 16 位有效)
 */
void lcd_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint32_t color)
{
    uint16_t c16 = (uint16_t)color;
    uint32_t total = (uint32_t)(ex - sx + 1) * (ey - sy + 1);

    LCD_SetWindows(sx, sy, ex, ey);
    while (total--)
    {
#if LCD_USE8BIT_MODEL
        LCD->LCD_RAM = c16;
        LCD->LCD_RAM = c16 << 8;
#else
        LCD->LCD_RAM = c16;
#endif
    }
    LCD_SetWindows(0, 0, lcddev.width - 1, lcddev.height - 1);
}

/**
 * @brief  彩色填充矩形(16-bit 数组)
 * @param  sx,sy: 左上角
 * @param  ex,ey: 右下角
 * @param  color: 指向 16-bit 颜色数组的指针，长度 >= (ex-sx+1)*(ey-sy+1)
 */
void lcd_color_fill(uint16_t sx, uint16_t sy, uint16_t ex, uint16_t ey, uint16_t *color)
{
    uint32_t total = (uint32_t)(ex - sx + 1) * (ey - sy + 1);

    LCD_SetWindows(sx, sy, ex, ey);
    while (total--)
    {
#if LCD_USE8BIT_MODEL
        LCD->LCD_RAM = *color;
        LCD->LCD_RAM = *color << 8;
#else
        LCD->LCD_RAM = *color;
#endif
        color++;
    }
    LCD_SetWindows(0, 0, lcddev.width - 1, lcddev.height - 1);
}

/**
 * @brief  画水平线(复用 lcd_fill，速度最快)
 * @param  x: 起始 X 坐标
 * @param  y:  Y 坐标
 * @param  len: 线长度(像素)
 * @param  color: 16-bit 颜色值
 */
void lcd_draw_hline(uint16_t x, uint16_t y, uint16_t len, uint16_t color)
{
	if ((len == 0) || (x > lcddev.width) || (y > lcddev.height))
    {
        return;
    }
	
    /* 右边沿保护 */
    if (x + len > lcddev.width) len = lcddev.width - x;
    lcd_fill(x, y, x + len - 1, y, color);   /* 单行矩形填充 */
}
