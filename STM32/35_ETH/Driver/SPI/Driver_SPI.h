#ifndef __DRIVER_SPI_H__
#define __DRIVER_SPI_H__

#include "stm32f10x.h"
#include "GPIO.h"
#include "Com_Delay.h"

// #define SPI1  ((SPI_TypeDef *) SPI1_BASE)
// #define SPI2  ((SPI_TypeDef *) SPI2_BASE)

// 宏定义输出引脚  SCK：PA5  MOSI：PA7  SC：PC13
#define CS_HIGH     (HAL_GPIO_WritePin(GPIOC,GPIO_pin_13,GPIO_PIN_SET))
#define CS_LOW      (HAL_GPIO_WritePin(GPIOC,GPIO_pin_13,GPIO_PIN_RESET))

#define CS2_HIGH     (HAL_GPIO_WritePin(GPIOD,GPIO_pin_3,GPIO_PIN_SET))
#define CS2_LOW      (HAL_GPIO_WritePin(GPIOD,GPIO_pin_3,GPIO_PIN_RESET))

#define SCK_HIGH    (HAL_GPIO_WritePin(GPIOA,GPIO_pin_5,GPIO_PIN_SET))
#define SCK_LOW     (HAL_GPIO_WritePin(GPIOA,GPIO_pin_5,GPIO_PIN_RESET))

#define MOSI_HIGH   (HAL_GPIO_WritePin(GPIOA,GPIO_pin_7,GPIO_PIN_SET))
#define MOSI_LOW    (HAL_GPIO_WritePin(GPIOA,GPIO_pin_7,GPIO_PIN_RESET))


// 宏定义读数据引脚 MISO PA6
#define MISO_READ   (HAL_GPIO_ReadPin(GPIOA,GPIO_pin_6))

// 宏定义延时函数
#define SPI_DELAY   (Delay_us(5))

void Driver_SPI_Init(void);
void Driver_SPI_Start(void);
void Driver_SPI_Stop(void);
uint8_t Driver_SPI_SwapByte(uint8_t);

void Driver_SPIx_Init(SPI_TypeDef* SPIx);
void Driver_SPI2_Start(void);
void Driver_SPI2_Stop(void);

void Driver_SPI_Soft_Init(void);
void Driver_SPI_Soft_Start(void);
void Driver_SPI_Soft_Stop(void);
uint8_t Driver_SPI_Soft_SwapByte(uint8_t);

#endif /* __DRIVER_SPI_H__ */

