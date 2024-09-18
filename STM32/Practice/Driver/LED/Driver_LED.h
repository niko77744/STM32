#ifndef __DRIVER_LED_H__
#define __DRIVER_LED_H__

#include "stm32f10x.h"
#include "Com_Delay.h"
#define LED1 GPIO_ODR_ODR0
#define LED2 GPIO_ODR_ODR1
#define LED3 GPIO_ODR_ODR8
#define size 3

void Driver_LED_Init(void);

void Driver_LED_On(uint16_t led);
void Driver_LED_Off(uint16_t led);

void Driver_LED_Toogle(uint16_t led);
void Driver_LED_OnAll(uint16_t leds[], uint8_t len);
void Driver_LED_OffAll(uint16_t leds[], uint8_t len);


#endif /* __DRIVER_LED_H__ */
