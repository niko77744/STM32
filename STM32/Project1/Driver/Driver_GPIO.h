#ifndef __DRIVER_GPIO_H__
#define __DRIVER_GPIO_H__

#include "stm32f10x.h"
#include "Com_Gpio.h"
#include "Com_Delay.h"
#include "Com_Debug.h"

void Driver_GPIO_TM7711_Init(void);
uint8_t Driver_GPIO_IsKey3Pressed(void);

#endif /* __DRIVER_GPIO_H__ */
