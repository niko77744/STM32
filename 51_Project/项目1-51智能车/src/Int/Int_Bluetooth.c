/*
    使用UART与蓝牙模块进行通信
    如果发送AT命令，则蓝牙模块会处理，否则直接将消息转发给上位机
    向发送AT，会回复OK ，发送AT+NAME=username，重命名
*/

#include "Int_Bluetooth.h"
#include "Dri_UART.h"
#include "Int_OLED.h"

static bit SendFlag = 1;
static char ATReceive[17];

bit Int_Bluetooth_Init() {

    Dri_UART_TransmitStr("AT");

    while (1) {
        Dri_UART_ReceiveStr(ATReceive);  //接收到数据返回1 

        SendFlag = (ATReceive[0] == 'O' && ATReceive[1] == 'K');
        if (SendFlag)
        {
            Int_OLED_DisplayStr(1, 1, ATReceive);
            break;
        }

    }
    return SendFlag;

    // Dri_UART_TransmitStr("AT");
    // Dri_UART_ReceiveStr(ATReceive)不能连续接收，因为SBUF也需要时间
    // while(! Dri_UART_ReceiveStr(ATReceive));
    // while(! Dri_UART_ReceiveStr(ATReceive));
    // return (ATReceive[0] == 'O' && ATReceive[1] == 'K');
}

void Int_Bluetooth_SetName()
{
    Dri_UART_TransmitStr("AT+NAME=username");
}