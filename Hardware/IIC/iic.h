#ifndef __IIC_H
#define __IIC_H

#include "stm32f4xx.h"
#include "FreeRTOS.h"
#include "semphr.h"

// 状态定义
#define IIC_STATUS_OK      0
#define IIC_STATUS_FAILED  1

// GPIO引脚结构体
typedef struct {
    GPIO_TypeDef* gpio_port;
    uint16_t pin;
} iic_gpio_pin_t;

// IIC总线结构体
typedef struct {
    iic_gpio_pin_t scl;       // SCL引脚
    iic_gpio_pin_t sda;       // SDA引脚
    SemaphoreHandle_t mutex;   // FreeRTOS互斥锁
} iic_bus_t;

// IIC设备结构体
typedef struct {
    const iic_bus_t* bus;     // IIC设备使用的总线
    uint8_t addr;             // IIC设备地址（已左移一位）
} iic_device_t;

// 函数声明
void iic_bus_init(iic_bus_t* iic_bus);
void iic_device_init(iic_device_t* iic_dev, const iic_bus_t* iic_bus, uint8_t dev_addr);

void iic_start(const iic_device_t* iic_dev);
void iic_stop(const iic_device_t* iic_dev);
uint8_t iic_wait_ack(const iic_device_t* iic_dev);
void iic_send_ack(const iic_device_t* iic_dev, uint8_t ack);
void iic_send_byte(const iic_device_t* iic_dev, uint8_t data);
uint8_t iic_read_byte(const iic_device_t* iic_dev, uint8_t ack);


#endif
