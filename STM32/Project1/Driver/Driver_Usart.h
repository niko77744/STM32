#ifndef __DRIVER_USART_H__
#define __DRIVER_USART_H__

#include "stm32f10x.h"
#include <stdio.h>
#include <string.h>
#include "Com_Gpio.h"

void Driver_USARTx_Init(USART_TypeDef* USARTx);
void Driver_USARTx_Start(USART_TypeDef* USARTx);
void Driver_USARTx_Stop(USART_TypeDef* USARTx);
void Driver_USARTx_SendChar(USART_TypeDef* USARTx, uint8_t ch);
void Driver_USARTx_SendString(USART_TypeDef* USARTx, uint8_t* str, uint16_t datalen);
void Driver_USARTx_ReceiveString(USART_TypeDef* USARTx, uint8_t* str, uint16_t* datalen);



#endif /* __DRIVER_USART_H__ */
