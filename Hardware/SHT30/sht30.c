#include "sht30.h"
#include "delay.h"
#include <math.h>
#include "iic2_bus.h"

iic_device_t sht30_dev;

/**
 * @brief   初始化 SHT30 传感器
 */
void SHT30_Init(void)
{
    iic_device_init(&sht30_dev, &g_iic2_bus, SHT30_ADDRESS);
}

/**
 * @brief   使用默认命令读取 SHT30 数据
 * @param   data: 指向存储测量结果的结构体指针
 * @retval  0:成功 1:失败
 */
uint8_t SHT30_Read_Data(sht30_data_t* data)
{
    return SHT30_Read_Data_With_Cmd(SHT30_DEFAULT_CMD, data);
}

/**
 * @brief   使用指定命令读取 SHT30 数据
 * @param   cmd: 测量命令
 * @param   data: 指向存储测量结果的结构体指针
 * @retval  0:成功 1:失败
 */
uint8_t SHT30_Read_Data_With_Cmd(uint16_t cmd, sht30_data_t* data)
{
    uint8_t buf[6];
    uint16_t raw_temp, raw_humi;
    
    if (!data) return 1;
    if (IIC2_Bus_Lock(pdMS_TO_TICKS(100)) != pdTRUE) return 1;
    
    data->status = 1;  // 默认状态为失败
    
    /* 1. 发送测量命令 */
    iic_start(&sht30_dev);
    iic_send_byte(&sht30_dev, SHT30_WrADDRESS);
    if (iic_wait_ack(&sht30_dev)) 
        goto error;
    
    iic_send_byte(&sht30_dev, cmd >> 8);
    if (iic_wait_ack(&sht30_dev)) 
        goto error;
    
    iic_send_byte(&sht30_dev, cmd & 0xFF);
    if (iic_wait_ack(&sht30_dev)) 
        goto error;
    
    iic_stop(&sht30_dev);
    
    /* 2. 等待测量完成，根据重复精度选择等待时间 */
    if (cmd == SHT30_MEAS_HIGHREP)
        delay_ms(18);    // 高重复精度最长约 15ms
    else if (cmd == SHT30_MEAS_MEDREP)
        delay_ms(8);     // 中重复精度最长约 6ms
    else
        delay_ms(6);     // 低重复精度最长约 4ms
    
    /* 3. 读取 6 字节数据 */
    iic_start(&sht30_dev);
    iic_send_byte(&sht30_dev, SHT30_RdADDRESS);
    if (iic_wait_ack(&sht30_dev)) 
        goto error;
    
    for (int i = 0; i < 6; i++) {
        buf[i] = iic_read_byte(&sht30_dev, (i == 5) ? 1 : 0);   // 最后一个字节 NACK
    }
    iic_stop(&sht30_dev);
    
    /* 4. CRC 校验 */
    if (SHT30_Check_CRC8(buf[0], buf[1], buf[2]) != 0) {
        // CRC 校验失败
        data->status = 2;  // CRC 错误
        IIC2_Bus_Unlock();
        return 1;
    }
    
    if (SHT30_Check_CRC8(buf[3], buf[4], buf[5]) != 0) {
        data->status = 2;  // CRC 错误
        IIC2_Bus_Unlock();
        return 1;
    }
    
    /* 5. 组合原始数据并转换 */
    raw_temp = ((uint16_t)buf[0] << 8) | buf[1];
    raw_humi = ((uint16_t)buf[3] << 8) | buf[4];
    
    data->temp = SHT30_Convert_Temperature(raw_temp);
    data->humi = SHT30_Convert_Humidity(raw_humi);
    data->status = 0;  // 成功
    IIC2_Bus_Unlock();
    
    return 0;
    
error:
    iic_stop(&sht30_dev);
    IIC2_Bus_Unlock();
    return 1;
}

/**
 * @brief   将原始温度值转换为摄氏度
 * @param   raw_temp: 原始温度值（16 位）
 * @retval  转换后的温度值（℃）
 */
float SHT30_Convert_Temperature(uint16_t raw_temp)
{
    // 公式：T = -45 + 175 * (raw_temp / 65535)
    return -45.0f + 175.0f * ((float)raw_temp / 65535.0f);
}

/**
 * @brief   将原始湿度值转换为百分比
 * @param   raw_humi: 原始湿度值（16 位）
 * @retval  转换后的湿度值（%RH）
 */
float SHT30_Convert_Humidity(uint16_t raw_humi)
{
    // 公式：RH = 100 * (raw_humi / 65535)
    return 100.0f * ((float)raw_humi / 65535.0f);
}

/**
 * @brief   检查 SHT30 是否在线
 * @retval  0:在线 1:不在线
 */
uint8_t SHT30_Check(void)
{
    uint8_t ret;
    if (IIC2_Bus_Lock(pdMS_TO_TICKS(50)) != pdTRUE) return 1;
    iic_start(&sht30_dev);
    iic_send_byte(&sht30_dev, SHT30_WrADDRESS);
    ret = iic_wait_ack(&sht30_dev);
    iic_stop(&sht30_dev);
    IIC2_Bus_Unlock();
    return ret;
}

/**
 * @brief   CRC8 校验计算
 * @param   msb: 数据高字节
 * @param   lsb: 数据低字节
 * @param   crc: 接收到的 CRC 值
 * @retval  0:校验通过 1:校验失败
 */
uint8_t SHT30_Check_CRC8(uint8_t msb, uint8_t lsb, uint8_t crc)
{
    uint8_t data[2] = {msb, lsb};
    uint8_t crc_calc = 0xFF;
    const uint8_t poly = 0x31;  // x^8 + x^5 + x^4 + 1
    
    for (int i = 0; i < 2; i++) {
        crc_calc ^= data[i];
        for (int bit = 0; bit < 8; bit++) {
            if (crc_calc & 0x80)
                crc_calc = (crc_calc << 1) ^ poly;
            else
                crc_calc <<= 1;
        }
    }
    
    return (crc_calc == crc) ? 0 : 1;
}

