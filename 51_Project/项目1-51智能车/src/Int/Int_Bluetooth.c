/*
    ʹ��UART������ģ�����ͨ��
    �������AT���������ģ��ᴦ������ֱ�ӽ���Ϣת������λ��
    ����AT����ظ�OK ������AT+NAME=username��������
*/

#include "Int_Bluetooth.h"
#include "Dri_UART.h"
#include "Int_OLED.h"

static bit SendFlag = 1;
static char ATReceive[17];

bit Int_Bluetooth_Init() {

    Dri_UART_TransmitStr("AT");

    while (1) {
        Dri_UART_ReceiveStr(ATReceive);  //���յ����ݷ���1 

        SendFlag = (ATReceive[0] == 'O' && ATReceive[1] == 'K');
        if (SendFlag)
        {
            Int_OLED_DisplayStr(1, 1, ATReceive);
            break;
        }

    }
    return SendFlag;

    // Dri_UART_TransmitStr("AT");
    // Dri_UART_ReceiveStr(ATReceive)�����������գ���ΪSBUFҲ��Ҫʱ��
    // while(! Dri_UART_ReceiveStr(ATReceive));
    // while(! Dri_UART_ReceiveStr(ATReceive));
    // return (ATReceive[0] == 'O' && ATReceive[1] == 'K');
}

void Int_Bluetooth_SetName()
{
    Dri_UART_TransmitStr("AT+NAME=username");
}