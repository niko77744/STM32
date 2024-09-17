#ifndef __DRIVER_USART_H__
#define __DRIVER_USART_H__

#include "stm32f10x.h"
#include <string.h>
#include <stdio.h>

#define Ok 1
#define Fail 0

void Driver_USART_Init(void);

uint8_t Driver_USART_SendByte(uint8_t byte);
uint8_t Driver_USART_SendBytes(uint8_t* bytes, uint8_t len);

void Driver_USART_ReceiveByte(uint8_t* byte);
void Driver_USART_ReceiveBytes(uint8_t* bytes, uint8_t* len);


#endif /* __DRIVER_USART_H__ */
