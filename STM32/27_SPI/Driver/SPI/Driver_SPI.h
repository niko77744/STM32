#ifndef __DRIVER_SPI_H__
#define __DRIVER_SPI_H__

#include "stm32f10x.h"
#include "GPIO.h"
#include "Com_Delay.h"

// 宏定义输出引脚  SCK：PA5  MOSI：PA7  SC：PC13
#define CS_HIGH     (GPIOC->ODR |= GPIO_ODR_ODR13)
#define CS_LOW      (GPIOC->ODR &= ~GPIO_ODR_ODR13)

#define SCL_HIGH    (GPIOC->ODR |= GPIO_ODR_ODR5)
#define SCL_LOW     (GPIOC->ODR &= ~GPIO_ODR_ODR5)

#define MOSI_HIGH   (GPIOC->ODR |= GPIO_ODR_ODR7)
#define MOSI_LOW    (GPIOC->ODR &= ~GPIO_ODR_ODR7)


// 宏定义读数据引脚 MISO PA6
#define MISO_READ (GPIOA->IDR & GPIO_IDR_IDR6)

// 宏定义延时函数
#define __SPI_DELAY(T) (Delay_us(T))


void Driver_SPI_Init(void);
void Driver_SPI_Start(void);
void Driver_SPI_Stop(void);
uint8_t Driver_SPI_SwapByte(uint8_t byte);

#endif /* __DRIVER_SPI_H__ */
