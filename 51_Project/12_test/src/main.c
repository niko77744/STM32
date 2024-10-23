/**
 * *********************************************
 * 8051 project
 * *********************************************
*/

#include "Com_Util.h"
#include "Dri/Dri_Timer0.h"
#include "Dri/Dri_INT0.h"
#include "Dri/UART.h"
#include "Int/Flow_LED.h"
// #include "Int/MatrixLED.h"

void main()
{
    static char serial_data[15];
    Dri_UART_Init();

    while (1) {
        // 如果接收到的数据不为空  并将SBUF的值传给serial_data
        if (Dri_UART_ReceiveStr(serial_data))
        {
            // strcmp
            if (strcmp(serial_data, "on") == 0)
            {
                P00 = 0;
                // 向上位机返回字符串turn on LED
                Dri_UART_TransmitStr("LED is open");
            }
            else if (strcmp(serial_data, "off") == 0)
            {
                P00 = 0x01;
                // 向上位机返回字符串turn off LED
                Dri_UART_TransmitStr("LED is close");
            }
            else
            {
                // 向上位机返回字符串ERROR
                Dri_UART_TransmitStr("ERROR");
            }
        }
    }
}

