#ifndef __IIC2_BUS_H
#define __IIC2_BUS_H

#include "iic.h"

extern iic_bus_t g_iic2_bus;

void IIC2_Bus_Init(void);
BaseType_t IIC2_Bus_Lock(TickType_t timeout);
void IIC2_Bus_Unlock(void);

#endif
