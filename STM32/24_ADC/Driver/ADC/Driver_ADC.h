#ifndef __DRIVER_ADC_H__
#define __DRIVER_ADC_H__

#include "stm32f10x.h"

void Driver_ADC1_Init(void);
void Driver_ADC1_Start(void);
double Driver_ADC1_GetValue(void);

void Driver_ADC1_DMA1_Init(void);
void Driver_ADC1_DMA1_Start(uint32_t SrcAddr, uint32_t TargetAddr, uint16_t DataLen);

#endif /* __DRIVER_ADC_H__ */
