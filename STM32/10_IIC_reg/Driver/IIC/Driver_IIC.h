#ifndef __DRIVER_IIC_H__
#define __DRIVER_IIC_H__

#include "stm32f10x.h"
#include "Delay.h"


#define SCL_Up (GPIOB->BSRR |= GPIO_BSRR_BS10)
#define SCL_Down (GPIOB->BRR |= GPIO_BRR_BR10)
#define SDA_Up (GPIOB->BSRR |= GPIO_BSRR_BS11)
#define SDA_Down (GPIOB->BRR |= GPIO_BRR_BR11)
#define Read_SDA (GPIOB->IDR & GPIO_IDR_IDR11)
#define ACK 0
#define NACK 1
#define Delay_I2C2 Delay_us(10)

void Driver_I2C_Init(void);

void Driver_I2C_Start(void);
void Driver_I2C_Stop(void);

uint8_t Driver_I2C_ReceiveAck(void);

void Driver_I2C_SendAck(void);
void Driver_I2C_SendNAck(void);

void Driver_I2C_Sendbyte(uint8_t);
uint8_t Driver_I2C_Receivebyte(void);


#endif /* __DRIVER_IIC_H__ */
