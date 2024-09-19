#include "Com_Delay.h"
#include "Com_SysTick.h"
#include "Driver_IIC_Hard.h"
#include "Driver_IIC_Soft.h"
#include "Driver_Key.h"
#include "Driver_LED.h"
#include "Driver_USART.h"
#include "Driver_BaseTimer.h"
#include "Inf_EEPROM.h"

uint8_t buffer[100] = { 0 };
uint8_t len = 0;
extern uint8_t USART_BRF;
int main(int argc, char const* argv[])
{
    Com_SysTick_Init();
    Driver_BaseTimer6_Init();
    Driver_LED_Init();
    Driver_USART_Init();
    // Driver_KEY_Init();
    // Inf_EEPROM_Hard_Init();

    while (1) {
    }
}

