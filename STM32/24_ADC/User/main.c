#include "Com_Delay.h"
#include "Com_SysTick.h"
#include "Driver_Key.h"
#include "Driver_LED.h"
#include "Driver_USART.h"
#include "Driver_IIC_Hard.h"
#include "Driver_IIC_Soft.h"
#include "Driver_BaseTimer.h"
#include "Driver_GeneralTimer.h"
#include "Driver_AdvancedTimer.h"
#include "Driver_DMA.h"
#include "Driver_ADC.h"
#include "GPIO.h"
#include "Inf_EEPROM.h"

// DMA_USART
uint8_t buffer[5] = "1234";

// DMA M2M
const uint8_t src[5] = { 'a','b','c','d','e' };
uint8_t target[20] = {};

extern uint8_t DMA_IS_BRF;
extern uint8_t USART_BRF;
extern uint8_t USART_R_Len;

int main(int argc, char const* argv[])
{
    Driver_USART_Init();
    Driver_ADC1_Init();
    Driver_ADC1_Start();

    while (1) {
        printf("V = %.2lf\n", Driver_ADC1_GetValue());
        Delay_s(1);
    }
}


