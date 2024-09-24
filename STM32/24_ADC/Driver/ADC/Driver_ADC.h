#ifndef __DRIVER_ADC_H__
#define __DRIVER_ADC_H__

#include "stm32f10x.h"

void Driver_ADC1_Init(void);
void Driver_ADC1_Start(void);
double Driver_ADC1_GetValue(void);

#endif /* __DRIVER_ADC_H__ */
