#include "UART.h"

static char buffer[15];
bit Receive_state;  //0��ʾ���ڴ���1��ʾ�������
bit Send_state;     //0��ʾ���ڴ���1��ʾ�������

// ��¼�����ַ��ĳ���
static u8 Receiving_data_len = 0;



void Dri_UART_Init(void) {
    SM0 = 0;
    SM1 = 1;
    SM2 = 0;

    // ��ʱ���Ͳ�����
    TR1 = 1;
    PCON &= 0x7f; //0111 1111 ��λ����Ϊ0

    TMOD &= 0x0f;  //0010 xxxx
    TMOD |= 0x20;

    TH1 = 253;
    TL1 = 253;
    TI = 0;
    RI = 0;

    // ���ڿ���
    REN = 1;
    EA = 1;
    ES = 1;
}


bit Dri_UART_ReceiveStr(char* command)
{
    if (Receive_state == 1)  // ���������� 
    {
        strcpy(command, buffer);
        Receiving_data_len = 0;
        Receive_state = 0;
        return 1;
    }
    return 0;
}


void Dri_UART_TransmitStr(char* command) {
    u8 i = 0;   // i=0 ��Ȼ�����
    //while (*(command++) != '\0')
    while (command[i] != '\0')
    {
        while (Send_state); //�����1�Ῠ����ֱ��Ϊ0  д��while����
        SBUF = command[i++];
        Send_state = 1;  //��ʾ�������  д��while����
    }
}


void Dri_UART_Handler() interrupt 4 {
    if (TI == 1)
    {
        Send_state = 0;  //��ʾ���ڴ���
        TI = 0;
    }
    else if (RI == 1)
    {
        if (SBUF == '\n')  //  if (SBUF != '\n') 
        {
            Receive_state = 1;  // ��ʾ������ϣ��������ǹ涨��'\n'��ʾ�ַ����������
            // buffer[Receiving_data_len] = '\0';   ����Ҫ
        }
        else {
            buffer[Receiving_data_len++] = SBUF;
            Receive_state = 0;  // ����Ҫ ��ʾ���ڴ���
        }
        //�жϱ�־λ
        RI = 0;
    }
}