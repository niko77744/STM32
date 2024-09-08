#ifndef __DRIVER_LED_H__
#define __DRIVER_LED_H__


#include "stm32f10x.h"

/* 宏定义三个LED灯输出数据寄存器 */
// 定义的偏移量，对于A、B...都是同一个偏移量   ((uint16_t)0x0001)  所以不是GPIOA
// 要想定位到GPIOA
#define LED1 GPIO_ODR_ODR0    //((uint16_t)0x0001) 
#define LED2 GPIO_ODR_ODR1    //((uint16_t)0x0002) 
#define LED3 GPIO_ODR_ODR8    //((uint16_t)0x0100) 


void Driver_LED_Init(void);

void Driver_LED_On(uint16_t led);

void Driver_LED_Off(uint16_t led);

void Driver_LED_Toggle(uint16_t led);

void Driver_LED_OnAll(uint16_t leds[], uint8_t len);

void Driver_LED_OffAll(uint16_t leds[], uint8_t len);

#endif /* __DRIVER_LED_H__ */
