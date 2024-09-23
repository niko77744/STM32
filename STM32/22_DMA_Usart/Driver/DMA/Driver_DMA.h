#ifndef __DRIVER_DMA_H__
#define __DRIVER_DMA_H__

#include "stm32f10x.h"

void Driver_DMA1_Init(void);
void Driver_DMA1_TransmitStart(uint32_t SrcAddr, uint32_t TargetAddr, uint16_t DateLen);

#endif /* __DRIVER_DMA_H__ */
