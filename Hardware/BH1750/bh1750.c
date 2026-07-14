#include "delay.h"
#include "bh1750.h"
#include "iic2_bus.h"


// 定义BH1750设备结构体
iic_device_t bh1750_dev;

/**
  * @brief  BH1750初始化
  * @retval None
  */
void BH1750_Init(void)
{
    iic_device_init(&bh1750_dev, &g_iic2_bus, BH1750_WrAddress);
    
    // 发送上电指令
    BH1750_Write_Cmd(BH1750_POWER_ON);
    delay_ms(10);
    
    // 发送重置指令
    BH1750_Write_Cmd(BH1750_RESET);
    delay_ms(10);
    
    // 设置为连续高分辨率模式
    BH1750_Write_Cmd(BH1750_CONT_H_RES_MODE);
    delay_ms(180); // 等待测量完成
}

/**
  * @brief  向BH1750写入命令
  * @param  cmd: 指令
  * @retval None
  */
void BH1750_Write_Cmd(uint8_t cmd)
{
    if (IIC2_Bus_Lock(pdMS_TO_TICKS(50)) != pdTRUE)
    {
        return;
    }

    iic_start(&bh1750_dev);
    
    // 发送设备地址+写位
    iic_send_byte(&bh1750_dev, BH1750_WrAddress);
    if (iic_wait_ack(&bh1750_dev) != IIC_STATUS_OK)
    {
        iic_stop(&bh1750_dev);
        IIC2_Bus_Unlock();
        return;
    }
    
    // 发送指令
    iic_send_byte(&bh1750_dev, cmd);
    if (iic_wait_ack(&bh1750_dev) != IIC_STATUS_OK)
    {
        iic_stop(&bh1750_dev);
        IIC2_Bus_Unlock();
        return;
    }
    
    iic_stop(&bh1750_dev);
    IIC2_Bus_Unlock();
}

/**
  * @brief  读取BH1750光照强度原始值
  * @retval 原始光照强度值
  */
uint16_t BH1750_Read_Light(void)
{
    uint8_t data_h = 0, data_l = 0;
    uint16_t light_value = 0;

    if (IIC2_Bus_Lock(pdMS_TO_TICKS(50)) != pdTRUE)
    {
        return 0;
    }
    
    iic_start(&bh1750_dev);
    
    // 发送设备地址+读位
    iic_send_byte(&bh1750_dev, BH1750_RdAddress);
    if (iic_wait_ack(&bh1750_dev) != IIC_STATUS_OK)
    {
        iic_stop(&bh1750_dev);
        IIC2_Bus_Unlock();
        return 0;
    }
    
    // 读取高字节
    data_h = iic_read_byte(&bh1750_dev, 0); // 发送ACK
    
    // 读取低字节
    data_l = iic_read_byte(&bh1750_dev, 1); // 发送NACK
    
    iic_stop(&bh1750_dev);
    IIC2_Bus_Unlock();
    
    // 计算光照强度
    light_value = (data_h << 8) | data_l;
    
    return light_value;
}

/**
  * @brief  获取光照强度（lux）
  * @retval 光照强度值（单位：lux）
  */
float BH1750_Get_Lux(void)
{
    uint16_t light_raw = BH1750_Read_Light();
    float lux = light_raw / 1.2f; // 分辨率转换
    
    return lux;
}
