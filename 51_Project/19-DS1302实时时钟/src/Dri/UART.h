#ifndef __UART_H__
#define __UART_H__
#include "Com_Util.h"
#include "string.h"

void Dri_UART_Init(void);
bit Dri_UART_ReceiveStr(char* bytes);
void Dri_UART_TransmitStr(char* send_str);

// Dri_UART_ReceiveChar
// Dri_UART_ReceiveStr
// Dri_UART_TransmitChar
// Dri_UART_TransmitStr

#endif /* __UART_H__ */
