#include "UART.h"

static char buffer[15];
bit Receive_state;  //0表示正在处理，1表示处理完成
bit Send_state;     //0表示正在处理，1表示处理完成

// 记录接收字符的长度
static u8 Receiving_data_len = 0;



void Dri_UART_Init(void) {
    SM0 = 0;
    SM1 = 1;
    SM2 = 0;

    // 定时器和波特率
    TR1 = 1;
    PCON &= 0x7f; //0111 1111 高位设置为0

    TMOD &= 0x0f;  //0010 xxxx
    TMOD |= 0x20;

    TH1 = 253;
    TL1 = 253;
    TI = 0;
    RI = 0;

    // 串口开关
    REN = 1;
    EA = 1;
    ES = 1;
}


bit Dri_UART_ReceiveStr(char* command)
{
    if (Receive_state == 1)  // 如果接收完毕 
    {
        strcpy(command, buffer);
        Receiving_data_len = 0;
        Receive_state = 0;
        return 1;
    }
    return 0;
}


void Dri_UART_TransmitStr(char* command) {
    u8 i = 0;   // i=0 不然会出错
    //while (*(command++) != '\0')
    while (command[i] != '\0')
    {
        while (Send_state); //如果是1会卡死，直到为0  写在while里面
        SBUF = command[i++];
        Send_state = 1;  //表示发送完成  写在while里面
    }
}


void Dri_UART_Handler() interrupt 4 {
    if (TI == 1)
    {
        Send_state = 0;  //表示正在处理
        TI = 0;
    }
    else if (RI == 1)
    {
        if (SBUF == '\n')  //  if (SBUF != '\n') 
        {
            Receive_state = 1;  // 表示接收完毕，读到我们规定的'\n'表示字符串发送完毕
            // buffer[Receiving_data_len] = '\0';   不需要
        }
        else {
            buffer[Receiving_data_len++] = SBUF;
            Receive_state = 0;  // 不需要 表示正在处理
        }
        //中断标志位
        RI = 0;
    }
}