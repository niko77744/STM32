#ifndef __COM_SYSTICK_H__
#define __COM_SYSTICK_H__

#include <time.h>
#include <stdlib.h>
#include "stm32f10x.h"
#include "Driver_LED.h"
#include "Driver_USART.h"


void Com_SysTick_Init(void);
void SysTick_Delay(uint32_t);
uint32_t SysTick_GetTick(void);

/*
    通过SysTick生成随机数
    uint32_t timer_ms = 0;
    timer_ms = SysTick_GetTick();
    srand(timer_ms);
    uint32_t randomNumber = rand() % 2;
 */


#endif /* __COM_SYSTICK_H__ */
