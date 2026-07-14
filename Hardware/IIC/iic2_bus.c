#include "iic2_bus.h"

iic_bus_t g_iic2_bus = {
    .scl = {GPIOB, GPIO_Pin_10},
    .sda = {GPIOB, GPIO_Pin_11},
    .mutex = NULL
};

void IIC2_Bus_Init(void)
{
    if (g_iic2_bus.mutex == NULL)
    {
        g_iic2_bus.mutex = xSemaphoreCreateMutex();
    }

    iic_bus_init(&g_iic2_bus);
}

BaseType_t IIC2_Bus_Lock(TickType_t timeout)
{
    if (g_iic2_bus.mutex == NULL)
    {
        return pdFALSE;
    }

    return xSemaphoreTake(g_iic2_bus.mutex, timeout);
}

void IIC2_Bus_Unlock(void)
{
    if (g_iic2_bus.mutex != NULL)
    {
        xSemaphoreGive(g_iic2_bus.mutex);
    }
}
