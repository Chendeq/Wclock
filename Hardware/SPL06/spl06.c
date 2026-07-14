#include "spl06.h"
#include "delay.h"
#include <math.h>
#include "iic2_bus.h"

static iic_device_t spl06_dev;// I2C设备句柄

// 校准系数
int32_t Pressure_Para[7];  // c00, c10, c01, c11, c20, c21, c30
int32_t Temperature_Para[2]; // c0, c1

/**
 * @brief  读取字节
 * @param  addr: 寄存器地址
 * @retval 寄存器值，0xFF表示失败
 */
uint8_t SPL06_Read_Byte(uint8_t addr)
{
    uint8_t value = 0;
    
    iic_start(&spl06_dev);
    iic_send_byte(&spl06_dev, SPL06_WRADDRESS);
    if (iic_wait_ack(&spl06_dev) != IIC_STATUS_OK) {
        iic_stop(&spl06_dev);
        return 0xFF;
    }
    
    iic_send_byte(&spl06_dev, addr);
    if (iic_wait_ack(&spl06_dev) != IIC_STATUS_OK) {
        iic_stop(&spl06_dev);
        return 0xFF;
    }
    
    iic_start(&spl06_dev);
    iic_send_byte(&spl06_dev, SPL06_RDADDRESS);
    if (iic_wait_ack(&spl06_dev) != IIC_STATUS_OK) {
        iic_stop(&spl06_dev);
        return 0xFF;
    }
    
    value = iic_read_byte(&spl06_dev, 1); // NACK
    iic_stop(&spl06_dev);
    
    return value;
}

/**
 * @brief  写入字节
 * @param  addr: 寄存器地址
 * @param  data: 要写入的数据
 */
void SPL06_Write_Byte(uint8_t addr, uint8_t data)
{
    iic_start(&spl06_dev);
    iic_send_byte(&spl06_dev, SPL06_WRADDRESS);
    if (iic_wait_ack(&spl06_dev) != IIC_STATUS_OK) {
        iic_stop(&spl06_dev);
        return;
    }
    
    iic_send_byte(&spl06_dev, addr);
    if (iic_wait_ack(&spl06_dev) != IIC_STATUS_OK) {
        iic_stop(&spl06_dev);
        return;
    }
    
    iic_send_byte(&spl06_dev, data);
    if (iic_wait_ack(&spl06_dev) != IIC_STATUS_OK) {
        iic_stop(&spl06_dev);
        return;
    }
    
    iic_stop(&spl06_dev);
}

/**
 * @brief  初始化SPL06
 * @retval SPL06 ID，0xFF表示失败
 */
uint8_t SPL06_Init(void)
{   
    iic_device_init(&spl06_dev, &g_iic2_bus, SPL06_WRADDRESS);
    
    delay_ms(10);
    
    // 软复位
    SPL06_Write_Byte(RESET_Addr, 0x89);
    delay_ms(100);
    
    // 读取设备ID
    uint8_t spl06_id = SPL06_Read_Byte(ID_Addr);
    
    if (spl06_id != 0x10)
        return 0xFF;
        
    // 配置测量模式
    SPL06_Write_Byte(MEAS_CFG_Addr, 0x07); // 连续压力和温度测量
    SPL06_Write_Byte(PRS_CFG_Addr, 0x27);  // 压力: 8倍过采样，连续测量
    SPL06_Write_Byte(TMP_CFG_Addr, 0xA0);  // 温度: 8倍过采样，外部传感器
    SPL06_Write_Byte(CFG_REG_Addr, 0x04);  // 使能压力和温度移位

    // 读取校准参数
    Parameter_Reading(Pressure_Para, Temperature_Para);
    
    
    delay_ms(50);
    return spl06_id;
}

/**
 * @brief  读取参数
 * @param  Pressure_Para_Out: 压力校准参数输出
 * @param  Temperature_Para_Out: 温度校准参数输出
 */
void Parameter_Reading(int32_t *Pressure_Para_Out, int32_t *Temperature_Para_Out)
{
    uint8_t coef_buffer[18];
    
    // 读取校准系数
    coef_buffer[0] = SPL06_Read_Byte(Temp_c0_Addr);
    coef_buffer[1] = SPL06_Read_Byte(Temp_c1_Addr);
    coef_buffer[2] = SPL06_Read_Byte(Temp_c2_Addr);
    coef_buffer[3] = SPL06_Read_Byte(Press_c0_Addr);
    coef_buffer[4] = SPL06_Read_Byte(Press_c1_Addr);
    coef_buffer[5] = SPL06_Read_Byte(Press_c2_Addr);
    coef_buffer[6] = SPL06_Read_Byte(Press_c3_Addr);
    coef_buffer[7] = SPL06_Read_Byte(Press_c4_Addr);
    coef_buffer[8] = SPL06_Read_Byte(Press_c5_Addr);
    coef_buffer[9] = SPL06_Read_Byte(Press_c6_Addr);
    coef_buffer[10] = SPL06_Read_Byte(Press_c7_Addr);
    coef_buffer[11] = SPL06_Read_Byte(Press_c8_Addr);
    coef_buffer[12] = SPL06_Read_Byte(Press_c9_Addr);
    coef_buffer[13] = SPL06_Read_Byte(Press_c10_Addr);
    coef_buffer[14] = SPL06_Read_Byte(Press_c11_Addr);
    coef_buffer[15] = SPL06_Read_Byte(Press_c12_Addr);
    coef_buffer[16] = SPL06_Read_Byte(Press_c13_Addr);
    coef_buffer[17] = SPL06_Read_Byte(Press_c14_Addr);
    
    // 解析温度系数 (12位补码)
    Temperature_Para_Out[0] = (coef_buffer[0] << 4) + ((coef_buffer[1] & 0xF0) >> 4); 
    if(Temperature_Para_Out[0] & 0x0800)
        Temperature_Para_Out[0] = Temperature_Para_Out[0] - Total_Number_12;

    Temperature_Para_Out[1] = ((coef_buffer[1] & 0x0F) << 8) + coef_buffer[2];
    if(Temperature_Para_Out[1] & 0x0800)
        Temperature_Para_Out[1] = Temperature_Para_Out[1] - Total_Number_12;

    // 解析压力系数 (24位补码)
    Pressure_Para_Out[0] = (coef_buffer[3] << 12) + (coef_buffer[4] << 4) + ((coef_buffer[5] & 0xF0) >> 4); // c00
    if(Pressure_Para_Out[0] & 0x80000) 
        Pressure_Para_Out[0] = Pressure_Para_Out[0] - Total_Number_20;

    Pressure_Para_Out[1] = ((coef_buffer[5] & 0x0F) << 16) + (coef_buffer[6] << 8) + coef_buffer[7]; // c10
    if(Pressure_Para_Out[1] & 0x80000) 
        Pressure_Para_Out[1] = Pressure_Para_Out[1] - Total_Number_20;

    Pressure_Para_Out[2] = (coef_buffer[8] << 8) + coef_buffer[9]; // c01
    if(Pressure_Para_Out[2] & 0x8000) 
        Pressure_Para_Out[2] = Pressure_Para_Out[2] - Total_Number_16;

    Pressure_Para_Out[3] = (coef_buffer[10] << 8) + coef_buffer[11]; // c11
    if(Pressure_Para_Out[3] & 0x8000) 
        Pressure_Para_Out[3] = Pressure_Para_Out[3] - Total_Number_16;

    Pressure_Para_Out[4] = (coef_buffer[12] << 8) + coef_buffer[13]; // c20
    if(Pressure_Para_Out[4] & 0x8000) 
        Pressure_Para_Out[4] = Pressure_Para_Out[4] - Total_Number_16;

    Pressure_Para_Out[5] = (coef_buffer[14] << 8) + coef_buffer[15]; // c21
    if(Pressure_Para_Out[5] & 0x8000) 
        Pressure_Para_Out[5] = Pressure_Para_Out[5] - Total_Number_16;

    Pressure_Para_Out[6] = (coef_buffer[16] << 8) + coef_buffer[17]; // c30
    if(Pressure_Para_Out[6] & 0x8000)
        Pressure_Para_Out[6] = Pressure_Para_Out[6] - Total_Number_16;
}

/**
 * @brief  温度转换
 * @param  Temp_Data: 原始温度数据
 * @param  k: 缩放因子
 * @retval 转换后的温度
 */
float Temperature_conversion(uint32_t Temp_Data, float k)
{
    float Temperature;
    int32_t Temp;
    
    if(Temp_Data & 0x800000) {
        Temp = Temp_Data - Total_Number_24;
    } else {
        Temp = Temp_Data;
    }
    
    Temperature = Temp / k;
    return Temperature;

}

/**
 * @brief  压力转换
 * @param  Pressure_Data: 原始压力数据
 * @param  k: 缩放因子
 * @retval 转换后的压力
 */
float Pressure_conversion(uint32_t Pressure_Data, float k)
{
    float Pressure;
    int32_t Press;
    
    if(Pressure_Data & 0x800000) {
        Press = Pressure_Data - Total_Number_24;
    } else {
        Press = Pressure_Data;
    }
    
    Pressure = Press / k;
    return Pressure;
}

/**
 * @brief  缩放因子
 * @param  Config_k: 配置值
 * @retval 缩放因子
 */
float Scale_factor(uint8_t Config_k)
{
    float k;
    switch(Config_k & 0x07) {
        case 0: k = k_SPS1; break;
        case 1: k = k_SPS2; break;
        case 2: k = k_SPS4; break;
        case 3: k = k_SPS8; break;
        case 4: k = k_SPS16; break;
        case 5: k = k_SPS32; break;
        case 6: k = k_SPS64; break;
        case 7: k = k_SPS128; break;
        default: k = k_SPS8; break;
    }
    return k;
}

/**
 * @brief  压力补偿
 * @param  Pressure_Para_In: 压力校准参数
 * @param  Pressure: 压力值
 * @param  Temperature: 温度值
 * @retval 补偿后的压力
 */
float Correcting_Pressure(int32_t *Pressure_Para_In, float Pressure, float Temperature)
{
    return Pressure_Para_In[0] + 
           Pressure * (Pressure_Para_In[1] + Pressure * 
           (Pressure_Para_In[4] + Pressure * Pressure_Para_In[6])) +
           Temperature * Pressure_Para_In[2] + 
           Temperature * Pressure * 
           (Pressure_Para_In[3] + Pressure * Pressure_Para_In[5]);
}

/**
 * @brief  温度补偿
 * @param  Temperature_Para_In: 温度校准参数
 * @param  Temperature: 温度值
 * @retval 补偿后的温度
 */
float Correcting_Temperature(int32_t *Temperature_Para_In, float Temperature)
{
    return Temperature_Para_In[0] * 0.5f + Temperature_Para_In[1] * Temperature;
}

/**
 * @brief  读取原始温度数据
 * @retval 原始温度数据
 */
uint32_t SPL06_ReadTemperatureRaw(void)
{
    uint8_t buf[3];

    buf[0] = SPL06_Read_Byte(TMP_B2_Addr);
    buf[1] = SPL06_Read_Byte(TMP_B1_Addr);
    buf[2] = SPL06_Read_Byte(TMP_B0_Addr);

    return ((uint32_t)buf[0] << 16) | ((uint32_t)buf[1] << 8) | buf[2];
}

/**
 * @brief  读取原始压力数据
 * @retval 原始压力数据
 */
uint32_t SPL06_ReadPressureRaw(void)
{
    uint8_t buf[3];

    buf[0] = SPL06_Read_Byte(PSR_B2_Addr);
    buf[1] = SPL06_Read_Byte(PSR_B1_Addr);
    buf[2] = SPL06_Read_Byte(PSR_B0_Addr);

    return ((uint32_t)buf[0] << 16) | ((uint32_t)buf[1] << 8) | buf[2];
}

/**
 * @brief  读取温度值（℃）
 * @retval 温度值
 */
float SPL06_ReadTemperature(void)
{
    uint32_t temp_raw;
    float temp_scaled, temp_corrected;
    uint8_t tmp_cfg;
    
    // 读取温度配置
    tmp_cfg = SPL06_Read_Byte(TMP_CFG_Addr);
    
    // 读取原始温度数据
    temp_raw = SPL06_ReadTemperatureRaw();
    
    // 转换为缩放后的温度
    temp_scaled = Temperature_conversion(temp_raw, Scale_factor(tmp_cfg & 0x07));
    
    // 应用温度补偿
    temp_corrected = Correcting_Temperature(Temperature_Para, temp_scaled);
    
    return temp_corrected;

}

/**
 * @brief  读取压力值（Pa）
 * @retval 压力值
 */
float SPL06_ReadPressure(void)
{
    uint32_t press_raw, temp_raw;
    float press_scaled, temp_scaled, press_corrected;
    uint8_t prs_cfg, tmp_cfg;
    
    // 读取配置
    prs_cfg = SPL06_Read_Byte(PRS_CFG_Addr);
    tmp_cfg = SPL06_Read_Byte(TMP_CFG_Addr);
    
    // 读取原始数据
    press_raw = SPL06_ReadPressureRaw();
    temp_raw = SPL06_ReadTemperatureRaw();
    
    // 转换为缩放后的值
    press_scaled = Pressure_conversion(press_raw, Scale_factor(prs_cfg & 0x07));
    temp_scaled = Temperature_conversion(temp_raw, Scale_factor(tmp_cfg & 0x07));
    
    // 应用压力补偿
    press_corrected = Correcting_Pressure(Pressure_Para, press_scaled, temp_scaled);
    
    return press_corrected / 100.0f; // 转换为hPa

}
