#include "stm32f10x.h"
#include "driver_led.h"
#include "Driver_usart .h"
#include "Dri_Key.h"
#include "Delay.h"
#include <stdbool.h>
// uint8_t message[100] = { 0 };
// uint8_t size = 0;
extern uint8_t buffer[100];
extern uint8_t len;
extern uint8_t is_over;

int main() {
    Driver_USART1_Init();

    Driver_USART1_SendString("hello", 5);
    Driver_USART1_SendChar('\n');


    while (1) {
        // û���Ļ��Ῠ������
        // uint8_t ch = Driver_USART1_ReceiveChar();
        // Driver_USART1_SendChar(ch);
        // Driver_USART1_ReceiveString(message, &size);  //size�ᱻ������ size��++
        // Driver_USART1_SendString(message, size);
        if (is_over) {
            // ��ʾ���ձ䳤�������, ����PC
            Driver_USART1_SendString(buffer, len);
            len = 0;
            is_over = 0;
        }
    }
}

