#include "stm32f4xx.h"
#include "Lis2dh12tr.h"
#include "delay.h"
#include "iic.h"
#include "FreeRTOS.h" 
#include "semphr.h"   

static iic_bus_t lis2dh12tr_bus = {
    .scl = {.gpio_port = GPIOB, .pin = GPIO_Pin_6},
    .sda = {.gpio_port = GPIOB, .pin = GPIO_Pin_7},
    .mutex = NULL // 在 init 里创建
};

static iic_device_t lis2dh12tr_dev;


/* LIS2DH12TR 初始化 */
uint8_t LIS2DH12TR_Init(void)
{
    /* 1. 初始化 GPIO 时钟 */
    iic_bus_init(&lis2dh12tr_bus);
    iic_device_init(&lis2dh12tr_dev, &lis2dh12tr_bus, LIS2DH12TR_WrADDRESS); // 7 位地址 0x18 -> 0x30/0x31

    delay_ms(10);
    if (LIS2DH12TR_CheckID() != 0x33) return 0; // ID 不对，初始化失败

    /* 100 Hz, XYZ enable */
    LIS2DH12TR_WriteRegister(LIS2DH12TR_CTRL_REG1, 0x57);   //0x57 -> ODR3=0,ODR2=1,ODR1=0,ODR0=1, LPen=0, Zen=1, Yen=1, Xen=1
    /* ±2 g, High-Resolution ,BDU=1*/
    LIS2DH12TR_WriteRegister(LIS2DH12TR_CTRL_REG4, LIS2DH12TR_RANGE_2G | 0x88);

    delay_ms(10);
    return 1;
}

uint8_t LIS2DH12TR_CheckID(void)
{
    return LIS2DH12TR_ReadRegister(LIS2DH12TR_WHO_AM_I);
}

/**
 * @brief   读取LIS2DH12TR加速度传感器的指定寄存器数据
 * @param   reg: 要读取的寄存器地址
 * @retval  寄存器的数据字节
 * @note    
 */
uint8_t LIS2DH12TR_ReadRegister(uint8_t reg)
{
    uint8_t val = 0xFF;
    iic_start(&lis2dh12tr_dev);
    iic_send_byte(&lis2dh12tr_dev, LIS2DH12TR_WrADDRESS); // 写地址
    if (iic_wait_ack(&lis2dh12tr_dev) != IIC_STATUS_OK)
        goto err;

    iic_send_byte(&lis2dh12tr_dev, reg); // 寄存器地址
    if (iic_wait_ack(&lis2dh12tr_dev) != IIC_STATUS_OK)
        goto err;

    iic_start(&lis2dh12tr_dev);                           // 重启总线
    iic_send_byte(&lis2dh12tr_dev, LIS2DH12TR_RdADDRESS); // 读地址
    if (iic_wait_ack(&lis2dh12tr_dev) != IIC_STATUS_OK)
        goto err;

    val = iic_read_byte(&lis2dh12tr_dev, 1); // 读 1 字节 + NACK
err:
    iic_stop(&lis2dh12tr_dev);
    return val;
}

/**
 * @brief   向LIS2DH12TR加速度传感器的寄存器写入一个字节数据
 * @param   reg: 要写入的寄存器地址
 * @param   value: 要写入的数据字节
 * @retval  无
 * @note    
 */
void LIS2DH12TR_WriteRegister(uint8_t reg, uint8_t value)
{
    iic_start(&lis2dh12tr_dev);
    iic_send_byte(&lis2dh12tr_dev, LIS2DH12TR_WrADDRESS); // 写地址
    if (iic_wait_ack(&lis2dh12tr_dev) != IIC_STATUS_OK)
        goto err;

    iic_send_byte(&lis2dh12tr_dev, reg); // 寄存器地址
    if (iic_wait_ack(&lis2dh12tr_dev) != IIC_STATUS_OK)
        goto err;

    iic_send_byte(&lis2dh12tr_dev, value); // 数据
    if (iic_wait_ack(&lis2dh12tr_dev) != IIC_STATUS_OK)
        goto err;

err:
    iic_stop(&lis2dh12tr_dev);
}

/**
 * @brief   设置LIS2DH12TR加速度传感器的测量量程
 * @param   range: 要设置的量程值，必须是以下宏之一：
 *            - LIS2DH12TR_RANGE_2G  (0x00): ±2g 量程
 *            - LIS2DH12TR_RANGE_4G  (0x10): ±4g 量程
 *            - LIS2DH12TR_RANGE_8G  (0x20): ±8g 量程
 *            - LIS2DH12TR_RANGE_16G (0x30): ±16g 量程
 * @retval  无
 * @note    量程设置影响传感器的灵敏度和测量范围，量程越大，灵敏度越低
 *          该函数通过修改CTRL_REG4寄存器的第4-5位来设置量程
 */
void LIS2DH12TR_SetRange(uint8_t range)
{
    uint8_t ctrl4 = LIS2DH12TR_ReadRegister(LIS2DH12TR_CTRL_REG4);
    ctrl4 = (ctrl4 & 0xCF) | (range & 0x30);
    LIS2DH12TR_WriteRegister(LIS2DH12TR_CTRL_REG4, ctrl4);
}

/**
 * @brief   设置LIS2DH12TR加速度传感器的输出数据率
 * @param   datarate: 要设置的数据率值，必须是以下宏之一：
 *            - LIS2DH12TR_ODR_POWERDOWN (0x00): 关闭传感器
 *            - LIS2DH12TR_ODR_1HZ       (0x10): 1 Hz 输出数据率
 *            - LIS2DH12TR_ODR_10HZ      (0x20): 10 Hz 输出数据率
 *            - LIS2DH12TR_ODR_25HZ      (0x30): 25 Hz 输出数据率
 *            - LIS2DH12TR_ODR_50HZ      (0x40): 50 Hz 输出数据率
 *            - LIS2DH12TR_ODR_100HZ     (0x50): 100 Hz 输出数据率
 *            - LIS2DH12TR_ODR_200HZ     (0x60): 200 Hz 输出数据率
 *            - LIS2DH12TR_ODR_400HZ     (0x70): 400 Hz 输出数据率
 * @retval  无
 * @note    数据率设置影响传感器的响应速度和功耗，数据率越高，响应越快但功耗也越大
 *          该函数通过修改CTRL_REG1寄存器的第4-7位来设置输出数据率
 */
void LIS2DH12TR_SetDataRate(uint8_t datarate)
{
    uint8_t ctrl1 = LIS2DH12TR_ReadRegister(LIS2DH12TR_CTRL_REG1);
    ctrl1 = (ctrl1 & 0x0F) | (datarate & 0xF0);
    LIS2DH12TR_WriteRegister(LIS2DH12TR_CTRL_REG1, ctrl1);
}

/**
 * @brief   读取LIS2DH12TR加速度传感器的XYZ轴原始数据
 * @param   x: 指向存储X轴原始数据的16位整数指针
 * @param   y: 指向存储Y轴原始数据的16位整数指针
 * @param   z: 指向存储Z轴原始数据的16位整数指针
 * @retval  无
 * @note    
 */
void LIS2DH12TR_ReadAcceleration(int16_t *x, int16_t *y, int16_t *z)
{
    uint8_t buf[6] = {0};

    iic_start(&lis2dh12tr_dev);
    iic_send_byte(&lis2dh12tr_dev, LIS2DH12TR_WrADDRESS); // 写地址
    if (iic_wait_ack(&lis2dh12tr_dev) != IIC_STATUS_OK)
        goto err;

    iic_send_byte(&lis2dh12tr_dev, LIS2DH12TR_OUT_X_L | 0x80); // 寄存器地址,使用自动地址增量：寄存器地址最高位置 1
    if (iic_wait_ack(&lis2dh12tr_dev) != IIC_STATUS_OK)
        goto err;

    iic_start(&lis2dh12tr_dev);                           // 重启
    iic_send_byte(&lis2dh12tr_dev, LIS2DH12TR_RdADDRESS); // 读地址
    if (iic_wait_ack(&lis2dh12tr_dev) != IIC_STATUS_OK)
        goto err;

    for (int i = 0; i < 5; i++)
    {
        buf[i] = iic_read_byte(&lis2dh12tr_dev, 0); // ACK
    }
    buf[5] = iic_read_byte(&lis2dh12tr_dev, 1); // 最后一字节 NACK
err:
    iic_stop(&lis2dh12tr_dev);

    *x = (int16_t)((buf[1] << 8) | buf[0]);
    *y = (int16_t)((buf[3] << 8) | buf[2]);
    *z = (int16_t)((buf[5] << 8) | buf[4]);
}

/**
 * @brief   将LIS2DH12TR加速度传感器的原始数据转换为g单位
 * @param   raw: 原始数据（16位有符号整数）
 * @param   range: 当前设置的量程值，必须是以下宏之一：
 *            - LIS2DH12TR_RANGE_2G  (0x00): ±2g 量程
 *            - LIS2DH12TR_RANGE_4G  (0x10): ±4g 量程
 *            - LIS2DH12TR_RANGE_8G  (0x20): ±8g 量程
 *            - LIS2DH12TR_RANGE_16G (0x30): ±16g 量程
 * @retval  转换后的加速度值，单位为g（浮点数）
 * @note    
 */
float LIS2DH12TR_ConvertToG(int16_t raw, uint8_t range)
{
    switch (range) 
    {
        case LIS2DH12TR_RANGE_2G:  
            return raw * (1.0f / 16384.0f);
        case LIS2DH12TR_RANGE_4G:  
            return raw * (1.0f / 8192.0f);
        case LIS2DH12TR_RANGE_8G:  
            return raw * (1.0f / 4096.0f);
        case LIS2DH12TR_RANGE_16G: 
            return raw * (1.0f / 1365.33f);
        default:                   
            return raw * (1.0f / 16384.0f);
    }
}

/**
 * @brief  启用或禁用LIS2DH12TR传感器的FIFO功能
 * @param  enable: FIFO使能控制 (0: 禁用FIFO, 非0: 启用FIFO)
 * @param  mode: FIFO工作模式 (取值范围如下):
 *              - LIS2DH12TR_FIFO_BYPASS (0x00): 旁路模式，FIFO不工作
 *              - LIS2DH12TR_FIFO_MODE (0x40): FIFO模式，填充到阈值后停止
 *              - LIS2DH12TR_FIFO_STREAM (0x80): 流模式，持续更新FIFO
 *              - LIS2DH12TR_FIFO_STREAM_FIFO (0xC0): 流到FIFO模式
 * @param  watermark: FIFO水印阈值 (0x00~0x1F, 表示FIFO中数据量达到该值时产生中断)
 * @retval 无
 * @note   
 */
void LIS2DH12TR_EnableFIFO(uint8_t enable, uint8_t mode, uint8_t watermark)
{
    if (enable) 
    {
        LIS2DH12TR_WriteRegister(LIS2DH12TR_FIFO_CTRL_REG, mode | (watermark & 0x1F));
        uint8_t ctrl5 = LIS2DH12TR_ReadRegister(LIS2DH12TR_CTRL_REG5);
        LIS2DH12TR_WriteRegister(LIS2DH12TR_CTRL_REG5, ctrl5 | 0x40); /* FIFO_EN=1 */
    } 
    else 
    {
        uint8_t ctrl5 = LIS2DH12TR_ReadRegister(LIS2DH12TR_CTRL_REG5);
        LIS2DH12TR_WriteRegister(LIS2DH12TR_CTRL_REG5, ctrl5 & ~0x40);
        LIS2DH12TR_WriteRegister(LIS2DH12TR_FIFO_CTRL_REG, 0x00);  /* Bypass模式 */
    }
}

/**
 * @brief  获取LIS2DH12TR传感器FIFO当前数据量
 * @param  无
 * @retval FIFO当前数据量（0~31）
 * @note   
 */
uint8_t LIS2DH12TR_GetFIFOLevel(void)
{
    return LIS2DH12TR_ReadRegister(LIS2DH12TR_FIFO_SRC_REG) & 0x1F;
}

/**
 * @brief  重置LIS2DH12TR传感器FIFO
 * @param  无
 * @retval 无
 * @note   
 */
void LIS2DH12TR_FIFOReset(void)
{
    uint8_t ctrl5 = LIS2DH12TR_ReadRegister(LIS2DH12TR_CTRL_REG5);
    LIS2DH12TR_WriteRegister(LIS2DH12TR_CTRL_REG5, ctrl5 & ~0x40); /* 先禁用 */
    LIS2DH12TR_WriteRegister(LIS2DH12TR_FIFO_CTRL_REG, 0x00);      /* Bypass模式清空 */
    LIS2DH12TR_WriteRegister(LIS2DH12TR_CTRL_REG5, ctrl5 | 0x40);  /* 重新使能 */
}


//int16_t accel_x, accel_y, accel_z;
//float accel_x_g, accel_y_g, accel_z_g;
//uint8_t range = LIS2DH12TR_RANGE_2G;
//char buf[16];

//		/* 读取原始数据并转换为 g */
//        LIS2DH12TR_ReadAcceleration(&accel_x, &accel_y, &accel_z);
//        accel_x_g = LIS2DH12TR_ConvertToG(accel_x, range);
//        accel_y_g = LIS2DH12TR_ConvertToG(accel_y, range);
//        accel_z_g = LIS2DH12TR_ConvertToG(accel_z, range);

//        /* 标题 */
//        LCD_ShowString(10, 10, 16, (uint8_t *)"LIS2DH12TR  (g)", 0);

//        /* X 轴 */
//        sprintf(buf, "%.2f", accel_x_g);
//        LCD_ShowString(10, 30, 16, (uint8_t *)"X:", 0);
//        LCD_ShowString(30, 30, 16, (uint8_t *)buf, 0);

//        /* Y 轴 */
//        sprintf(buf, "%.2f", accel_y_g);
//        LCD_ShowString(10, 50, 16, (uint8_t *)"Y:", 0);
//        LCD_ShowString(30, 50, 16, (uint8_t *)buf, 0);

//        /* Z 轴 */
//        sprintf(buf, "%.2f", accel_z_g);
//        LCD_ShowString(10, 70, 16, (uint8_t *)"Z:", 0);
//        LCD_ShowString(30, 70, 16, (uint8_t *)buf, 0);

//		delay_ms(1000);
