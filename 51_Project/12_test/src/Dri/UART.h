#ifndef __UART_H__
#define __UART_H__
#include "Com_Util.h"

void Dri_UART_Init();

bit Dri_UART_ReceiveStr(char* bytes);
void Dri_UART_TransmitStr(char* send_str);

#endif /* __UART_H__ */