#ifndef __DRIVER_ADC_H__
#define __DRIVER_ADC_H__

#include "stm32f10x.h"
#include "gpio.h"
#include "Driver_USART.h"

void ADCx_Init(ADC_TypeDef* ADCx);
void ADCx_Start(ADC_TypeDef* ADCx, uint32_t sourceAdd, uint16_t count);


#endif /* __DRIVER_ADC_H__ */
