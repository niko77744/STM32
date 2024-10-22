#ifndef __DRIVER_USART_H__
#define __DRIVER_USART_H__

#include "stm32f10x.h"
#include <string.h>
#include <stdio.h>
#include "gpio.h"

#define Ok 1
#define Fail 0

void Driver_USARTx_Init(USART_TypeDef* USARTx);

uint8_t Driver_USARTx_SendByte(USART_TypeDef* USARTx, uint8_t byte);
uint8_t Driver_USARTx_SendBytes(USART_TypeDef* USARTx, uint8_t* bytes, uint8_t len);

// void Driver_USARTx_ReceiveByte(uint8_t* byte);
void Driver_USARTx_ReceiveBytes(USART_TypeDef* USARTx, uint8_t* bytes, uint8_t* len);


#endif /* __DRIVER_USART_H__ */
