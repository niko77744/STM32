// /**
//  * *********************************************
//  * 8051 project
//  * *********************************************
//  */
// #include <STDIO.H>
// #include "Com_Util.h"
// #include "Int_DS1302.h"
// #include "Int_OLED.h"
// #include "Int_18B20.h"

// static char* s_week[] = {
//     "Mon",
//     "Tue",
//     "Wed",
//     "Thu",
//     "Fri",
//     "Sat",
//     "Sun" };

// void main()
// {
//     u8 tmp;
//     char str[17];
//     // ���� Struct_Date �������ݣ���¼��ʼ�����ں�ʱ��
//     Struct_Date st_date = { 24, 9, 1, 7, 15, 45, 55 };

//     // ��ʼ��OLED
//     Int_OLED_Init();
//     Int_OLED_Clear();

//     // ��ʼ��1302
//     Int_DS1302_Init();

//     // ������ʼ����ʱ��
//     Int_DS1302_SetDate(&st_date);

//     while (1)
//     {
//         // ��ȡ����ʱ��
//         st_date = Int_DS1302_GetDate();
//         // ��ȡ�¶�
//         tmp = Int_18B20_GetTemperature();

//         // 2024/11/03 Fri
//         // ��Ҫ����ǿ������ת����ǿ�������ݵ����ͣ�����51��ѷ�������˳��Ū��
//         // week��Ҫ-1����Ϊ����ֵ��1-7
//         sprintf(str, "20%d/%.2d/%.2d %s", (int)st_date.year, (int)st_date.month, (int)st_date.day_of_month, s_week[st_date.day_of_week - 1]);
//         Int_OLED_DisplayStr(0, 0, str);

//         // 12:05:30 Tmp:26
//         sprintf(str, "%.2d:%.2d:%.2d Tmp:%d", (int)st_date.hour, (int)st_date.minute, (int)st_date.second, (int)tmp);
//         Int_OLED_DisplayStr(0, 1, str);


//         Delay_1ms(50);
//     }
// }


/**
 * *********************************************
 * 8051 project
 * *********************************************
*/
#include "Com_Util.h"
#include "Dri/UART.h"


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