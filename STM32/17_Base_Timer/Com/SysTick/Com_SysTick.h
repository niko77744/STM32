#ifndef __COM_SYSTICK_H__
#define __COM_SYSTICK_H__

#include "stm32f10x.h"
#include "Driver_LED.h"
#include "Driver_USART.h"

void Com_SysTick_Init(void);
void SysTick_Delay(uint32_t);


#endif /* __COM_SYSTICK_H__ */
