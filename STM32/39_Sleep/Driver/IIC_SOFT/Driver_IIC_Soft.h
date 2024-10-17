#ifndef __DRIVER_IIC_SOFT_H__
#define __DRIVER_IIC_SOFT_H__

#include "stm32f10x.h"
#include "Com_Delay.h"

// I2C2-SDA PB10
// I2C2-SCL PB11

#define SCL_LOW (GPIOB->BRR |= GPIO_BRR_BR10)
#define SCL_HIGH (GPIOB->BSRR |= GPIO_BSRR_BS10)

#define SDA_LOW (GPIOB->BRR |= GPIO_BRR_BR11)
#define SDA_HIGH (GPIOB->BSRR |= GPIO_BSRR_BS11)

#define READ_SDA (GPIOB->IDR & GPIO_IDR_IDR11)


#define Delay_I2C_Soft Delay_us(10)

void Driver_I2C_Soft_Init(void);
void Driver_I2C_Soft_Start(void);
void Driver_I2C_Soft_Stop(void);
void Driver_I2C_Soft_SendAddr(uint8_t addr);
void Driver_I2C_Soft_SendAck(void);
void Driver_I2C_Soft_SendNAck(void);
uint8_t Driver_I2C_Soft_ReceivAck(void);
void Driver_I2C_Soft_Sendbyte(uint8_t byte);
uint8_t Driver_I2C_Soft_Receivebyte(void);


#endif /* __DRIVER_IIC_SOFT_H__ */
