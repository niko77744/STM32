#include "UART.h"

// 定义变量 标记是否正在发送数据  1表示正在发送
static bit Send_data_state = 0;
// 定义变量 标记是否正在接收数据  1表示接收完成，正在处理
static bit Receiving_data_state = 0;
// 记录接收字符的长度
static u8 Receiving_data_len = 0;
// 记录接收字符的长度
// 定义数组保存接收到一帧数据
static char s_buffers[15];

void Dri_UART_Init() {
    EA = 1;

    SM0 = 0;
    SM1 = 1;
    SM2 = 0;
    REN = 1;
    ES = 1;
    PCON &= 0x7f;
    TI = 0;
    RI = 0;

    TR1 = 1;
    TMOD &= 0x0f;
    TMOD |= 0x20;
    TH1 = 0xFD;
    TL1 = 0xFD;
}


bit Dri_UART_ReceiveStr(char* bytes) {
    // static u8 i;
    if (Receiving_data_state)
    {
        u8 i;
        for (i = 0; i < Receiving_data_len; i++)
        {
            bytes[i] = s_buffers[i];
        }
        bytes[i] = '\0';
        Receiving_data_len = 0;
        Receiving_data_state = 0;  //表示接收数据处理完毕
        return 1;
    }
    return 0;
}

// void Dri_UART_TransmitStr(char* send_str) {
//     u8 i = 0;
//     while (send_str[i] != '\0')  // while (*send_str != '\0')
//     {
//         while (Send_data_state);
//         SBUF = send_str[i++];
//         // SBUF = *(send_str++);
//         Send_data_state = 1;
//     }
// }


void Dri_UART_Handler() interrupt 4 {
    if (TI == 1)
    {
        Send_data_state = 0;  //表示发送完成
        TI = 0;
    }
    else if (RI == 1)
    {
        if (SBUF == '\n')
        {
            Receiving_data_state = 1;
        }
        else {
            Receiving_data_state = 0;  //表示正在接收
            s_buffers[Receiving_data_len++] = SBUF;
        }
        RI = 0;
    }
}