#include "24c02.h"
#include "iic.h"
#include "delay.h"
#include "FreeRTOS.h"
#include "semphr.h" 

/* IIC总线对象 */
static iic_bus_t at24c02_bus = {
    .scl = {.gpio_port = GPIOB, .pin = GPIO_Pin_6}, // PB6/SCL  PB7/SDA
    .sda = {.gpio_port = GPIOB, .pin = GPIO_Pin_7},
    .mutex = NULL // 在 AT24CXX_Init() 创建
};

static iic_device_t at24c02_dev; // IIC设备对象

/* 初始化总线 + 设备对象 */
void AT24CXX_Init(void)
{
    /* 初始化 GPIO */
    iic_bus_init(&at24c02_bus);

    /* 设备地址 0x50（7 位）← 左移 1 位后 = 0xA0写 / 0xA1读 */
    iic_device_init(&at24c02_dev, &at24c02_bus, AT24C02_WrADDRESS);
}

uint8_t AT24CXX_ReadOneByte(uint16_t ReadAddr)
{
    uint8_t data = 0xFF;

    iic_start(&at24c02_dev);
    iic_send_byte(&at24c02_dev, AT24C02_WrADDRESS); // 写器件地址
    if (iic_wait_ack(&at24c02_dev) != IIC_STATUS_OK)
        goto err;

    iic_send_byte(&at24c02_dev, ReadAddr); // 写寄存器地址
    if (iic_wait_ack(&at24c02_dev) != IIC_STATUS_OK)
        goto err;

    iic_start(&at24c02_dev);                        // 重启总线
    iic_send_byte(&at24c02_dev, AT24C02_RdADDRESS); // 读器件地址
    if (iic_wait_ack(&at24c02_dev) != IIC_STATUS_OK)
        goto err;

    data = iic_read_byte(&at24c02_dev, 1); // 读 1 字节 + NACK

err:
    iic_stop(&at24c02_dev);
    return data;
}

void AT24CXX_WriteOneByte(uint16_t WriteAddr, uint8_t DataToWrite)
{
    iic_start(&at24c02_dev);
    iic_send_byte(&at24c02_dev, AT24C02_WrADDRESS); // 写器件地址
    if (iic_wait_ack(&at24c02_dev) != IIC_STATUS_OK)
        goto err;

    iic_send_byte(&at24c02_dev, WriteAddr); // 写寄存器地址
    if (iic_wait_ack(&at24c02_dev) != IIC_STATUS_OK)
        goto err;

    iic_send_byte(&at24c02_dev, DataToWrite); // 写数据
    if (iic_wait_ack(&at24c02_dev) != IIC_STATUS_OK)
        goto err;

    delay_ms(5); // AT24C02 内部写周期 < 5 ms

err:
    iic_stop(&at24c02_dev);
}

void AT24CXX_WriteLenByte(uint16_t WriteAddr, uint32_t DataToWrite, uint8_t Len)
{
    for (uint8_t i = 0; i < Len; i++)
        AT24CXX_WriteOneByte(WriteAddr + i, (DataToWrite >> (8 * i)) & 0xFF);
}

uint32_t AT24CXX_ReadLenByte(uint16_t ReadAddr, uint8_t Len)
{
    uint32_t temp = 0;
    for (uint8_t i = 0; i < Len; i++)
        temp = (temp << 8) | AT24CXX_ReadOneByte(ReadAddr + Len - 1 - i);
    return temp;
}

uint8_t AT24CXX_Check(void)
{
    uint8_t temp = AT24CXX_ReadOneByte(255);
    if (temp == 0x55)
        return 0;

    AT24CXX_WriteOneByte(255, 0x55);
    temp = AT24CXX_ReadOneByte(255);
    return (temp == 0x55) ? 0 : 1;
}

void AT24CXX_Read(uint16_t ReadAddr, uint8_t *pBuffer, uint16_t NumToRead)
{
    while (NumToRead--)
        *pBuffer++ = AT24CXX_ReadOneByte(ReadAddr++);
}

void AT24CXX_Write(uint16_t WriteAddr, uint8_t *pBuffer, uint16_t NumToWrite)
{
    while (NumToWrite--)
    {
        AT24CXX_WriteOneByte(WriteAddr++, *pBuffer++);
    }
}
