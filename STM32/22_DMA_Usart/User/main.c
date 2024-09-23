#include <string.h>
#include "Driver_Key.h"
#include "Driver_LED.h"

#include "Driver_USART.h"
#include "Driver_IIC_Hard.h"
#include "Driver_IIC_Soft.h"

#include "Com_Delay.h"
#include "Com_SysTick.h"
#include "Driver_BaseTimer.h"
#include "Driver_GeneralTimer.h"
#include "Driver_AdvancedTimer.h"
#include "Driver_DMA.h"

#include "Inf_EEPROM.h"
uint8_t buffer[] = "abc\n";

int main(int argc, char const* argv[])
{
    Driver_USART_Init();
    Driver_DMA1_Init();

    Driver_DMA1_TransmitStart((uint32_t)buffer, (uint32_t)(&USART1->DR), (uint16_t)(strlen((char*)buffer)));
    while (1);
}


