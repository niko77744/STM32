#include "stm32f10x.h"
#include "driver_led.h"
#include "Driver_usart .h"
#include "Dri_Key.h"
extern uint16_t leds[];

uint8_t temp[100] = { 0 };

int main(int argc, char const* argv[])
{
    Dri_LED_Init();
    Driver_Key_init();
    Dri_USART1_Init();

    Driver_USART1_SendData("hello");

    while (1);
}

