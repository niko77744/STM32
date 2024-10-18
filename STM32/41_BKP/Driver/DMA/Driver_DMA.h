#ifndef __DRIVER_DMA_H__
#define __DRIVER_DMA_H__

#include "stm32f10x.h"

void Driver_DMA1_Channel1_Init(void); // Mem2Mem   
void Driver_DMA1_Channel4_Init(void); // USART TX
void Driver_DMA1_Channel5_Init(void); // USART RX

void Driver_DMA1_Channel1_TransmitStart(uint32_t srcAddr, uint32_t destAddr, uint16_t dataLen);
void Driver_DMA1_Channel4_TransmitStart(uint32_t SrcAddr, uint32_t TargetAddr, uint16_t DateLen);
void Driver_DMA1_Channel5_ReceiveStart(uint32_t SrcAddr, uint32_t TargetAddr, uint16_t DateLen);

#endif /* __DRIVER_DMA_H__ */
