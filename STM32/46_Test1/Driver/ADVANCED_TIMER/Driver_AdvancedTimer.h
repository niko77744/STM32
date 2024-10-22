#ifndef __DRIVER_ADVANCEDTIMER_H__
#define __DRIVER_ADVANCEDTIMER_H__

#include "stm32f10x.h"
#include "Driver_USART.h"

void AdvancedTimer_Count_Init(TIM_TypeDef* TIMx);
void AdvancedTimer_Start(TIM_TypeDef* TIMx);


#endif /* __DRIVER_ADVANCEDTIMER_H__ */
