#include "stm32f4xx.h"
#include "spi.h"

void spi1_init(void)
{
	SPI_InitTypeDef g_spi1_init_struct; 
    GPIO_InitTypeDef GPIO_InitStructure;
    
    SPI1_SCK_GPIO_CLK_ENABLE();
    SPI1_MISO_GPIO_CLK_ENABLE();
    SPI1_MOSI_GPIO_CLK_ENABLE();
    SPI1_CS_GPIO_CLK_ENABLE();
    SPI1_SPI_CLK_ENABLE();

    GPIO_InitStructure.GPIO_Pin = SPI1_SCK_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(SPI1_SCK_GPIO_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(SPI1_SCK_GPIO_PORT, GPIO_PinSource3, GPIO_AF_SPI1);

    GPIO_InitStructure.GPIO_Pin = SPI1_MISO_GPIO_PIN;
    GPIO_Init(SPI1_MISO_GPIO_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(SPI1_MISO_GPIO_PORT, GPIO_PinSource4, GPIO_AF_SPI1);

    GPIO_InitStructure.GPIO_Pin = SPI1_MOSI_GPIO_PIN;
    GPIO_Init(SPI1_MOSI_GPIO_PORT, &GPIO_InitStructure);
    GPIO_PinAFConfig(SPI1_MOSI_GPIO_PORT, GPIO_PinSource5, GPIO_AF_SPI1);

    GPIO_InitStructure.GPIO_Pin = SPI1_CS_GPIO_PIN;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_Init(SPI1_CS_GPIO_PORT, &GPIO_InitStructure);

    SPI1_CS(1);

    g_spi1_init_struct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    g_spi1_init_struct.SPI_Mode = SPI_Mode_Master;
    g_spi1_init_struct.SPI_DataSize = SPI_DataSize_8b;
    g_spi1_init_struct.SPI_CPOL = SPI_CPOL_High;
    g_spi1_init_struct.SPI_CPHA = SPI_CPHA_2Edge;
    g_spi1_init_struct.SPI_NSS = SPI_NSS_Soft;
    g_spi1_init_struct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_256;
    g_spi1_init_struct.SPI_FirstBit = SPI_FirstBit_MSB;
    g_spi1_init_struct.SPI_CRCPolynomial = 7;
    SPI_Init(SPI1_SPI, &g_spi1_init_struct);

    SPI_Cmd(SPI1_SPI, ENABLE);

    spi1_read_write_byte(0Xff);
}

/**
 * @brief       SPI1速度设置函数
 *   @note      SPI1时钟频率为APB2, 为 84MHz
 *              SPI速度 = PCLK2 / 2^(speed + 1)
 * @param       speed   : SPI1时钟分频系数
 * @retval      无
 */
void spi1_set_speed(uint8_t speed)
{
    assert_param(IS_SPI_BAUDRATE_PRESCALER(speed)); /* 参数合法性检查 */
    
    SPI_Cmd(SPI1_SPI, DISABLE); /* 关闭SPI */
    
    /* 清除分频系数值 */
    SPI1_SPI->CR1 &= 0XFFC7;         /* 位3-5清零，用于设置分频系数 */
    SPI1_SPI->CR1 |= speed << 3;     /* 设置SPI速度 */
    
    SPI_Cmd(SPI1_SPI, ENABLE); /* 使能SPI */
}

/**
 * @brief       SPI1读写一个字节数据
 * @param       txdata  : 要发送的数据(1字节)
 * @retval      接收到的数据(1字节)
 */
uint8_t spi1_read_write_byte(uint8_t txdata)
{
    /* 等待发送缓冲区空 */
    while (SPI_I2S_GetFlagStatus(SPI1_SPI, SPI_I2S_FLAG_TXE) == RESET);
    
    /* 发送数据 */
    SPI_I2S_SendData(SPI1_SPI, txdata);
    
    /* 等待接收缓冲区非空 */
    while (SPI_I2S_GetFlagStatus(SPI1_SPI, SPI_I2S_FLAG_RXNE) == RESET);
    
    /* 返回接收到的数据 */
    return SPI_I2S_ReceiveData(SPI1_SPI);
}