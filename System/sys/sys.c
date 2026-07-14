#include "sys.h"


/**
 * @brief       设置中断向量表偏移地址
 * @param       baseaddr: 基址
 * @param       offset: 偏移量
 * @retval      无
 */
void sys_nvic_set_vector_table(uint32_t baseaddr, uint32_t offset)
{
    /* 设置NVIC的向量表偏移寄存器,VTOR低9位保留,即[8:0]保留 */
    SCB->VTOR = baseaddr | (offset & (uint32_t)0xFFFFFE00);
}

/**
 * @brief       执行: WFI指令(执行完该指令进入低功耗状态, 等待中断唤醒)
 * @param       无
 * @retval      无
 */
void sys_wfi_set(void)
{
    __ASM volatile("wfi");
}

/**
 * @brief       关闭所有中断(但是不包括fault和NMI中断)
 * @param       无
 * @retval      无
 */
void sys_intx_disable(void)
{
    __ASM volatile("cpsid i");
}

/**
 * @brief       开启所有中断
 * @param       无
 * @retval      无
 */
void sys_intx_enable(void)
{
    __ASM volatile("cpsie i");
}

/**
 * @brief       设置栈顶地址
 * @note        左侧若出现红X, 属于MDK误报, 实际是没问题的
 * @param       addr: 栈顶地址
 * @retval      无
 */
void sys_msr_msp(uint32_t addr)
{
    __set_MSP(addr);    /* 设置栈顶地址 */
}

/**
 * @brief       进入待机模式
 * @param       无
 * @retval      无
 */
void sys_standby(void)
{
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE); /* 使能电源时钟 */
    PWR_BackupAccessCmd(ENABLE);                        /* 使能后备寄存器访问 */
    PWR_EnterSTANDBYMode();                             /* 进入待机模式 */
}

/**
 * @brief       系统软复位
 * @param       无
 * @retval      无
 */
void sys_soft_reset(void)
{
    NVIC_SystemReset();
}

/**
 * @brief       时钟设置函数
 * @param       plln: PLL1倍频系数(PLL倍频), 取值范围: 64~432.
 * @param       pllm: PLL1预分频系数(进PLL之前的分频), 取值范围: 2~63.
 * @param       pllp: PLL1的p分频系数(PLL之后的分频), 分频后作为系统时钟, 取值范围: 2,4,6,8.(仅限这4个值!)
 * @param       pllq: PLL1的q分频系数(PLL之后的分频), 取值范围: 2~15.
 * @note
 *
 *              Fvco: VCO频率
 *              Fsys: 系统时钟频率, 也是PLL1的p分频输出时钟频率
 *              Fq:   PLL1的q分频输出时钟频率
 *              Fs:   PLL输入时钟频率, 可以是HSI, CSI, HSE等.
 *              Fvco = Fs * (plln / pllm);
 *              Fsys = Fvco / pllp = Fs * (plln / (pllm * pllp));
 *              Fq   = Fvco / pllq = Fs * (plln / (pllm * pllq));
 *
 *              外部晶振为25M的时候, 推荐值: plln = 336, pllm = 8, pllp = 2, pllq = 7.
 *              得到:Fvco = 8 * (336 / 8) = 336Mhz
 *                   Fsys = pll1_p_ck = 336 / 2 = 168Mhz
 *                   Fq   = pll1_q_ck = 336 / 7 = 48
 *
 * @retval      错误代码: 0, 成功; 1, 错误;
 */
uint8_t sys_stm32_clock_init(uint32_t plln, uint32_t pllm, uint32_t pllp, uint32_t pllq)
{
    RCC_DeInit();                                   /* 复位RCC配置 */
    
    RCC_HSEConfig(RCC_HSE_ON);                      /* 开启HSE */
    
    /* 等待HSE就绪 */
    if (RCC_WaitForHSEStartUp() != SUCCESS)
    {
        return 1;                                   /* HSE启动失败 */
    }
    
    /* 配置PLL */
    RCC_PLLConfig(RCC_PLLSource_HSE, pllm, plln, pllp, pllq);
    RCC_PLLCmd(ENABLE);                             /* 使能PLL */
    
    /* 等待PLL就绪 */
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
    
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);      /* 选择PLL作为系统时钟源 */
    
    /* 等待系统时钟源切换完成 */
    while (RCC_GetSYSCLKSource() != 0x08);
    
    RCC_HCLKConfig(RCC_SYSCLK_Div1);                /* AHB分频系数为1 */
    RCC_PCLK1Config(RCC_HCLK_Div4);                 /* APB1分频系数为4 */
    RCC_PCLK2Config(RCC_HCLK_Div2);                 /* APB2分频系数为2 */
    
    /* 使能Flash预取指和指令缓存 */
    FLASH_PrefetchBufferCmd(ENABLE);
    FLASH_InstructionCacheCmd(ENABLE);
    FLASH_DataCacheCmd(ENABLE);
    
    /* 设置Flash延时周期 */
    FLASH_SetLatency(FLASH_Latency_5);
    
    return 0;                                       /* 时钟配置成功 */
}


#ifdef  USE_FULL_ASSERT

/**
 * @brief       当编译提示出错的时候此函数用来报告错误的文件和所在行
 * @param       file：指向源文件
 *              line：指向在文件中的行数
 * @retval      无
 */
void assert_failed(uint8_t* file, uint32_t line)
{ 
    while (1)
    {
    }
}
#endif
