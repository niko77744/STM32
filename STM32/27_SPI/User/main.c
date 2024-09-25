#include "Com_Delay.h"
#include "Com_SysTick.h"
#include "Driver_Key.h"
#include "Driver_LED.h"
#include "Driver_USART.h"
#include "Driver_IIC_Hard.h"
#include "Driver_IIC_Soft.h"
#include "Driver_SPI.h"
#include "Driver_BaseTimer.h"
#include "Driver_GeneralTimer.h"
#include "Driver_AdvancedTimer.h"
#include "Driver_DMA.h"
#include "Driver_ADC.h"
#include "GPIO.h"
#include "Inf_EEPROM.h"
#include "Inf_w25q32.h"

int main(int argc, char const* argv[])
{
    Driver_USART_Init();
    Inf_W25Q32_Init();
    uint8_t mid = 0;
    uint16_t did = 0;
    Inf_W25Q32_ReadId(&mid, &did);

    // mid = 0xef       did = 0x4016
    printf("mid = %#x \t did = %#x\n", mid, did);

    while (1) {
    }
}


