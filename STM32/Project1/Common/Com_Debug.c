#include "Com_Debug.h"


void Debug_Init(void)
{
    Driver_USARTx_Init(USART1);
    Driver_USARTx_Start(USART1);
}
