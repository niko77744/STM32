#ifndef __DRIVER_IIC_H__
#define __DRIVER_IIC_H__

#include "stm32f10x.h"
#include "Delay.h"


// #define SCL_HIGH (GPIOB->BSRR |= GPIO_BSRR_BS10)
// #define SCL_LOW  (GPIOB->BRR |= GPIO_BRR_BR10)

// #define SDA_HIGH (GPIOB->BSRR |= GPIO_BSRR_BS11)
// #define SDA_LOW (GPIOB->BRR |= GPIO_BRR_BR11)

// #define READ_SDA (GPIOB->IDR & GPIO_IDR_IDR11)

#define SCL_LOW (GPIOB->ODR &= ~GPIO_ODR_ODR10)
#define SCL_HIGH (GPIOB->ODR |= GPIO_ODR_ODR10)

#define SDA_LOW (GPIOB->ODR &= ~GPIO_ODR_ODR11)
#define SDA_HIGH (GPIOB->ODR |= GPIO_ODR_ODR11)

#define READ_SDA (GPIOB->IDR & GPIO_IDR_IDR11)

#define ACK 0
#define NACK 1
#define Ok 1
#define Error 0
#define Delay_I2C2 Delay_us(10)

void Driver_I2C_Init(void);

uint8_t Driver_I2C_Start(void);
void Driver_I2C_Stop(void);

// uint8_t Driver_I2C_ReceiveAck(void);
uint8_t Driver_I2C_SendAddr(uint8_t);
void Driver_I2C_SendAck(void);
void Driver_I2C_SendNAck(void);

uint8_t Driver_I2C_Sendbyte(uint8_t);
uint8_t Driver_I2C_Receivebyte(void);


#endif /* __DRIVER_IIC_H__ */
