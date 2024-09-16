#ifndef __DRIVER_USART_H__
#define __DRIVER_USART_H__

#include "stm32f10x.h"
#include <stdio.h>

void Dri_USART1_Init(void);
void Driver_USART1_SendChar(uint8_t byte);
void Driver_USART1_SendData(uint8_t* bytes, uint8_t len);
void Driver_USART1_ReceiveChar(uint8_t* byte);
void Driver_USART1_ReceiveData(uint8_t* bytes, uint8_t* len);

#endif
