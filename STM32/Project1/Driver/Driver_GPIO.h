#ifndef __DRIVER_GPIO_H__
#define __DRIVER_GPIO_H__

#include "stm32f10x.h"
#include "Com_Gpio.h"
#include "Com_Delay.h"
#include "Com_Debug.h"

#define TM7711_SCK_H (HAL_GPIO_WritePin(GPIOB,GPIO_pin_12,GPIO_PIN_SET))
#define TM7711_SCK_L (HAL_GPIO_WritePin(GPIOB,GPIO_pin_12,GPIO_PIN_RESET))
#define TM7711_SDA_R (HAL_GPIO_ReadPin(GPIOB,GPIO_pin_13))


void Driver_GPIO_TM7711_Init(void);
uint8_t Driver_GPIO_IsKey3Pressed(void);

#endif /* __DRIVER_GPIO_H__ */
