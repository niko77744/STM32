#include "stm32f10x.h"
#include "driver_led.h"
#include "Driver_usart .h"
#include "Dri_Key.h"
extern uint16_t leds[];

// uint8_t temp[100] = { 0 };
// uint8_t len;
extern uint8_t is_Over;
extern uint8_t ReceiveBuffer[100];
extern uint8_t ReceiveLen;


int main(int argc, char const* argv[])
{
    Dri_LED_Init();
    Driver_Key_init();
    Dri_USART1_Init();


    Driver_USART1_SendChar('a');
    Driver_USART1_SendChar('\n');
    Driver_USART1_SendData("hello\n", 6);
    Driver_USART1_SendData("world\n", 6);
    int a = 10;
    printf("nihao %d\n", a);

    while (1) {
        // Driver_USART1_ReceiveData(temp, &len);
        // Driver_USART1_SendData(temp, len);
        if (is_Over)
        {
            Driver_USART1_SendData(ReceiveBuffer, ReceiveLen);
            is_Over = 0;
            ReceiveLen = 0;
        }
    }
}

