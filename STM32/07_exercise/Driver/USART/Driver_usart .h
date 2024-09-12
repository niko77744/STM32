#ifndef __DRIVER_USART _H__
#define __DRIVER_USART _H__

#include "stm32f10x.h"

void Dri_USART1_Init(void);
void Driver_USART1_SendData(uint8_t bytes[]);
void Driver_USART1_ReceiveData(uint8_t bytes[]);

#endif /* __DRIVER_USART _H__ */
