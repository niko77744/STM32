#ifndef __DRIVER_IIC_H__
#define __DRIVER_IIC_H__

#include "stm32f10x.h"
#include "Com_Delay.h"
#include "Com_Gpio.h"

void Driver_IIC_Init(void);
void Driver_IIC_Start(void);
void Driver_IIC_Stop(void);
void Driver_IIC_SendACK(void);
void Driver_IIC_SendAddr(void);
void Driver_IIC_SendNACK(void);
void Driver_IIC_SendData(uint8_t* data);
void Driver_IIC_ReceiveData(uint8_t* data);

#endif /* __DRIVER_IIC_H__ */

