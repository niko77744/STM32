#ifndef __DRI_KEY_H__
#define __DRI_KEY_H__

#include "stm32f10x.h"
#include "driver_led.h"
#include "Driver_usart .h"
#include <stdio.h>
#include "Delay.h"

#define KEY1 GPIO_ODR_ODR8
#define KEY2 GPIO_ODR_ODR9
#define KEY3 GPIO_ODR_ODR10
#define KEY4 GPIO_ODR_ODR11

void Driver_Key_init(void);

#endif /* __DRI_KEY_H__ */
