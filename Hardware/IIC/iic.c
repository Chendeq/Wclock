#include "iic.h"
#include "delay.h"

// GPIO操作宏
#define IIC_SET_PIN(gpio_port, pin) (gpio_port)->BSRR = (pin)         // 置位1（SET）
#define IIC_RESET_PIN(gpio_port, pin) (gpio_port)->BSRR = (pin << 16) // 复位0（RESET）
#define IIC_READ_PIN(gpio_port, pin) ((gpio_port)->IDR & (pin))

// 总线引脚操作宏
#define IIC_SET_SCL(iic_dev) IIC_SET_PIN((iic_dev)->bus->scl.gpio_port, (iic_dev)->bus->scl.pin)
#define IIC_RESET_SCL(iic_dev) IIC_RESET_PIN((iic_dev)->bus->scl.gpio_port, (iic_dev)->bus->scl.pin)
#define IIC_SET_SDA(iic_dev) IIC_SET_PIN((iic_dev)->bus->sda.gpio_port, (iic_dev)->bus->sda.pin)
#define IIC_RESET_SDA(iic_dev) IIC_RESET_PIN((iic_dev)->bus->sda.gpio_port, (iic_dev)->bus->sda.pin)
#define IIC_READ_SDA(iic_dev) IIC_READ_PIN((iic_dev)->bus->sda.gpio_port, (iic_dev)->bus->sda.pin)

// 配置SDA为输出模式
static void iic_sda_output_mode(const iic_device_t *iic_dev)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = iic_dev->bus->sda.pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(iic_dev->bus->sda.gpio_port, &GPIO_InitStructure);
}

// 配置SDA为输入模式
static void iic_sda_input_mode(const iic_device_t *iic_dev)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    GPIO_InitStructure.GPIO_Pin = iic_dev->bus->sda.pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(iic_dev->bus->sda.gpio_port, &GPIO_InitStructure);
}

/**
 * @brief  初始化IIC总线
 * @param  bus: IIC总线结构体指针
 * @retval None
 */
void iic_bus_init(iic_bus_t *iic_bus)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    // 使能GPIO时钟
    if (iic_bus->scl.gpio_port == GPIOA)
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    else if (iic_bus->scl.gpio_port == GPIOB)
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
    else if (iic_bus->scl.gpio_port == GPIOC)   
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
    else if (iic_bus->scl.gpio_port == GPIOD)
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    else if (iic_bus->scl.gpio_port == GPIOE)
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
    else if (iic_bus->scl.gpio_port == GPIOF)
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
    else if (iic_bus->scl.gpio_port == GPIOG)
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
    else if (iic_bus->scl.gpio_port == GPIOH)   
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
    else if (iic_bus->scl.gpio_port == GPIOI)
        RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);

    if (iic_bus->sda.gpio_port != iic_bus->scl.gpio_port)
    { /* 不同端口才需要再开一次 */
        if (iic_bus->sda.gpio_port == GPIOA)            
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
        else if (iic_bus->sda.gpio_port == GPIOB)
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
        else if (iic_bus->sda.gpio_port == GPIOC)
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);
        else if (iic_bus->sda.gpio_port == GPIOD)
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
        else if (iic_bus->sda.gpio_port == GPIOE)
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE);
        else if (iic_bus->sda.gpio_port == GPIOF)
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);
        else if (iic_bus->sda.gpio_port == GPIOG)
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOG, ENABLE);
        else if (iic_bus->sda.gpio_port == GPIOH)
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOH, ENABLE);
        else if (iic_bus->sda.gpio_port == GPIOI)
            RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOI, ENABLE);
    }

    // 配置SCL引脚
    GPIO_InitStructure.GPIO_Pin = iic_bus->scl.pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_Speed = GPIO_Fast_Speed;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_Init(iic_bus->scl.gpio_port, &GPIO_InitStructure);

    // 配置SDA引脚
    GPIO_InitStructure.GPIO_Pin = iic_bus->sda.pin;
    GPIO_Init(iic_bus->sda.gpio_port, &GPIO_InitStructure);

    // 初始化为高电平
    IIC_SET_PIN(iic_bus->scl.gpio_port, iic_bus->scl.pin);
    IIC_SET_PIN(iic_bus->sda.gpio_port, iic_bus->sda.pin);
}

/**
 * @brief  初始化IIC设备
 * @param  dev: IIC设备结构体指针
 * @param  bus: IIC总线结构体指针
 * @param  addr: IIC设备地址
 * @retval None
 */
void iic_device_init(iic_device_t *iic_dev, const iic_bus_t *iic_bus, uint8_t dev_addr)
{
    iic_dev->bus = iic_bus;
    iic_dev->addr = dev_addr; // 已左移一位
}

/**
 * @brief  IIC起始信号
 * @param  dev: IIC设备结构体指针
 * @retval None
 */
void iic_start(const iic_device_t *iic_dev)
{
    iic_sda_output_mode(iic_dev); // SDA为输出模式
    IIC_SET_SDA(iic_dev);
    IIC_SET_SCL(iic_dev);
    delay_us(4);
    IIC_RESET_SDA(iic_dev);
    delay_us(4);
    IIC_RESET_SCL(iic_dev);
}

/**
 * @brief  IIC停止信号
 * @param  dev: IIC设备结构体指针
 * @retval None
 */
void iic_stop(const iic_device_t *iic_dev)
{
    iic_sda_output_mode(iic_dev); // SDA为输出模式
	IIC_RESET_SCL(iic_dev);
    IIC_RESET_SDA(iic_dev);
    delay_us(2);
    IIC_SET_SCL(iic_dev);
    delay_us(4);
    IIC_SET_SDA(iic_dev);
    delay_us(4);
}

/**
 * @brief  等待ACK应答
 * @param  dev: IIC设备结构体指针
 * @retval 0:成功  1:失败
 */
uint8_t iic_wait_ack(const iic_device_t *iic_dev)
{
    uint8_t timeout = 0; // 超时退出时间

	IIC_RESET_SCL(iic_dev);
    iic_sda_input_mode(iic_dev); // SDA为输入模式
    delay_us(2);

    IIC_SET_SCL(iic_dev);
    delay_us(2);

    while (IIC_READ_SDA(iic_dev))
    { // 从机未应答，返回了1
        timeout++;
        if (timeout > 250)
        {
            iic_stop(iic_dev);
            return IIC_STATUS_FAILED;
        }
    }

    IIC_RESET_SCL(iic_dev);
	delay_us(2);
    return IIC_STATUS_OK;
}

/**
 * @brief  发送ACK应答
 * @param  dev: IIC设备结构体指针
 * @param  ack: 0-发送ACK  1-发送NACK
 * @retval None
 */
void iic_send_ack(const iic_device_t *iic_dev, uint8_t ack)
{
IIC_RESET_SCL(iic_dev);
    iic_sda_output_mode(iic_dev); // SDA为输出模式

    if (ack)
        IIC_SET_SDA(iic_dev); // NACK
    else
        IIC_RESET_SDA(iic_dev); // ACK

    delay_us(2);
    IIC_SET_SCL(iic_dev);
    delay_us(2);
    IIC_RESET_SCL(iic_dev);
    delay_us(1);
}

/**
 * @brief  发送一个字节
 * @param  dev: IIC设备结构体指针
 * @param  data: 要发送的数据
 * @retval None
 */
void iic_send_byte(const iic_device_t *iic_dev, uint8_t data)
{
    uint8_t i = 0;

    iic_sda_output_mode(iic_dev); // SDA为输出模式
    IIC_RESET_SCL(iic_dev);

    for (i = 0; i < 8; i++)
    {
        if (data & 0x80)
            IIC_SET_SDA(iic_dev);
        else
            IIC_RESET_SDA(iic_dev);
        data <<= 1;
		delay_us(2);
		
        IIC_SET_SCL(iic_dev);
        delay_us(2);
        IIC_RESET_SCL(iic_dev);
        delay_us(2);
    }
}

/**
 * @brief  读取一个字节
 * @param  dev: IIC设备结构体指针
 * @param  ack: 读取后是否发送ACK
 * @retval 读取到的数据
 */
uint8_t iic_read_byte(const iic_device_t *iic_dev, uint8_t ack)
{
    uint8_t i = 0, data = 0;

    iic_sda_input_mode(iic_dev); // SDA为输入模式
	IIC_RESET_SCL(iic_dev);
	
    for (i = 0; i < 8; i++)
    {
        
        delay_us(2);
        IIC_SET_SCL(iic_dev);
		delay_us(2);
		
        data <<= 1;
        if (IIC_READ_SDA(iic_dev))
            data |= 0x01;

        delay_us(2);
		IIC_RESET_SCL(iic_dev);
		delay_us(2);
    }

    iic_send_ack(iic_dev, ack);
    return data;
}
