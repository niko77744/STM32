#ifndef __DRIVER_IIC_HARD_H__
#define __DRIVER_IIC_HARD_H__

#include "stm32f10x.h"
#define Ok 1
#define Fail 0
#define Error 0

void Driver_I2C_Hard_Init(void);
uint8_t Driver_I2C_Hard_Start(void);
void Driver_I2C_Hard_Stop(void);
uint8_t Driver_I2C_Hard_SendAddr(uint8_t addr);
void Driver_I2C_Hard_SendAck(void);
void Driver_I2C_Hard_SendNAck(void);
uint8_t Driver_I2C_Hard_Sendbyte(uint8_t byte);
uint8_t Driver_I2C_Hard_Receivebyte(void);

#endif /* __DRIVER_IIC_HARD_H__ */
