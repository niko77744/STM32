#ifndef __DRIVER_GENERALTIMER_H__
#define __DRIVER_GENERALTIMER_H__

#include "stm32f10x.h"
#include "Driver_USART.h"

void Driver_GeneralTimer4_Init(void);
double Driver_GeneralTimer4_GetCycle(void);
double Driver_GeneralTimer4_GetFrequency(void);
double Driver_GeneralTimer4_GetDutyCycle(void);

void Driver_GeneralTimer5_Init(void);
void Driver_GeneralTimer5_LED1_SetDutyCycle(uint8_t);
void Driver_GeneralTimer5_LED2_SetDutyCycle(uint8_t);


#endif /* __DRIVER_GENERALTIMER_H__ */
