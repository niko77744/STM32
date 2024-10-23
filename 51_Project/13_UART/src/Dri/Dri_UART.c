#include "Dri_UART.h"

// ������� ����Ƿ����ڷ�������  1��ʾ���ڷ���
static bit Send_data_state = 0;
// ������� ����Ƿ����ڽ�������  1��ʾ������ɣ����ڴ���
static bit Receiving_data_state = 0;
// ��¼�����ַ��ĳ���
static u8 Receiving_data_len = 0;
// ��¼�����ַ��ĳ���
// �������鱣����յ�һ֡����
static char s_buffers[15];
static char s_buffer;


/**
 * @brief UART ��ʼ��
 *
 */
void Dri_UART_Init() {
    // �ܿ���
    EA = 1;

    //����Timer1�Ͳ�����
    PCON &= 0x7F;
    TMOD &= 0x0F; // 0b 0000 1111
    TMOD |= 0x20;      // 0b 0010 0000
    TR1 = 1;
    TH1 = 253;
    TL1 = 253;

    // ���ô��ڹ���ģʽ
    SM0 = 0;
    SM1 = 1;
    SM2 = 0;  // �����ֹͣλ

    // ������
    REN = 1;  //���ݽ���ʹ��
    ES = 1;   //���ڿ���
    // �������жϱ�־λ��0
    TI = 0;
    RI = 0;
}



/**
 * @brief ��ȡ���յ����ַ�
 * @param char * �����յ��ַ����浽�õ�ַ��
 * @return bit 1���յ����� 0δ���յ�����
 */
bit Dri_UART_ReceiveChar(char* receive_char) {
    if (s_buffer != '\0')
    {
        // s_buffer = SBUF;  ���жϺ����Ѿ�д����
        *receive_char = s_buffer;  //��s_buffer,Ҳ����SBUF��ֵ��receive_charָ��
        s_buffer = 0; // ��s_buffer��Ϊ0
        return 1;
    }
    return 0;
}


/**
  * @brief ��ȡ���յ����ַ��������ֽ�ָ�
  *
  * @param char * �����յ��ַ������浽�õ�ַ��
  * @return bit 1���յ����� 0δ���յ�����
  */
bit Dri_UART_ReceiveStr(char* bytes) {
    if (Receiving_data_state)
    {
        u8 i;
        for (i = 0; i < Receiving_data_len; i++)
        {
            bytes[i] = s_buffers[i];
        }
        bytes[i] = '\0';
        Receiving_data_len = 0;
        Receiving_data_state = 0;
        return 1;
    }
    return 0;
}


/**
 * @brief ���͵��ֽ�����
 * @param char ch
 */
static void Dri_UART_TransmitChar(char ch)
{
    //һֱ�ȵ����������ݣ�ǰ������ݷ�����ɣ�
    // ��������һ���ֽڣ������жϽ� Send_data_state ��Ϊ 0���Ϳ��Է�����һ���ֽ�
    while (Send_data_state);
    SBUF = ch;  //��������
    // ������ڷ�������
    Send_data_state = 1;
}


/**
 * @brief ���Ͷ��ֽ�����
 * @param char *str
 */
void Dri_UART_TransmitStr(char* send_str) {
    while (*send_str != '\0') {
        Dri_UART_TransmitChar(*(send_str++));  // ����ָ����Ʊ����ַ�������
    };
}


/**
  * @brief ���崮���жϷ������
  *
  */
void Dri_UART_Handler() interrupt 4 {

    // ����������ݴ������ж�
    if (RI == 1)
    {
        if (SBUF == '\n')
        {
            Receiving_data_state = 1;
        }
        else {
            s_buffers[Receiving_data_len++] = SBUF;
        }
        RI = 0; // ��λ�жϱ��λ
    }
    // �������������
    else if (TI == 1)
    {
        Send_data_state = 0;
        TI = 0; // ��λ�жϱ��λ
    }
}