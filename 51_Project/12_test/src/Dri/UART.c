#include "UART.h"

// ������� ����Ƿ����ڷ�������  1��ʾ���ڷ���
static bit Send_data_state = 0;
// ������� ����Ƿ����ڽ�������  1��ʾ������ɣ����ڴ���
static bit Receiving_data_state = 0;
// ��¼�����ַ��ĳ���
static u8 Receiving_data_len = 0;
// ��¼�����ַ��ĳ���
// �������鱣����յ�һ֡����
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
        Receiving_data_state = 0;  //��ʾ�������ݴ������
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
        Send_data_state = 0;  //��ʾ�������
        TI = 0;
    }
    else if (RI == 1)
    {
        if (SBUF == '\n')
        {
            Receiving_data_state = 1;
        }
        else {
            Receiving_data_state = 0;  //��ʾ���ڽ���
            s_buffers[Receiving_data_len++] = SBUF;
        }
        RI = 0;
    }
}