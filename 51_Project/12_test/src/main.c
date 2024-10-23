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
        // ������յ������ݲ�Ϊ��  ����SBUF��ֵ����serial_data
        if (Dri_UART_ReceiveStr(serial_data))
        {
            // strcmp
            if (strcmp(serial_data, "on") == 0)
            {
                P00 = 0;
                // ����λ�������ַ���turn on LED
                Dri_UART_TransmitStr("LED is open");
            }
            else if (strcmp(serial_data, "off") == 0)
            {
                P00 = 0x01;
                // ����λ�������ַ���turn off LED
                Dri_UART_TransmitStr("LED is close");
            }
            else
            {
                // ����λ�������ַ���ERROR
                Dri_UART_TransmitStr("ERROR");
            }
        }
    }
}

