#include "Int_OLED.h"

// ע��궨�岻Ҫд���ˣ������Ų�
#define OLEDAddrWrite 0x78

// ע�⣺D/C#
#define OLED_Data 0x40
#define OLED_Command 0x00

#define SetAddMode 0x20
#define SetAdd_Horizontal 0x00
#define SetAdd_Page 0x02

#define SetColRemap 0xA1
#define SetRowRemap 0xC8

// ע�⣺д����
#define SetDisplayOn 0xAF
#define SetDisplayOff 0xAE

#define SetPump 0x8D
#define SetPumpLevel 0x14

/**
 * ��OLED��ʾ�������ֽ�����
 *
 * @param bytes Ҫ���͵������ֽ�����
 * @param is_data ����������ͣ�1��ʾ���ݣ�0��ʾ����
 * @param len Ҫ���͵��ֽ���
 *
 * ������ͨ��IICͨ��Э����OLED��ʾ���������ݻ������ֽ�
 * ��������IICͨ�ţ�����OLED�豸��д��ַ��������Ӧ��
 * ����is_data�������������ݻ������ʶ����������Ӧ��
 * Ȼ�����ֽڷ������������е��ֽڣ�����ÿ���ֽں����Ӧ��
 * ���ֹͣIICͨ��
 */
static void Int_OLED_SendBytes(u8* bytes, bit is_data, u8 len) {
    u8 i;
    Dri_IIC_Start();

    Dri_IIC_SendByte(OLEDAddrWrite);
    Dri_IIC_ReceiveAck();

    if (is_data)
    {
        Dri_IIC_SendByte(OLED_Data);
    }
    else {
        Dri_IIC_SendByte(OLED_Command);
    }
    Dri_IIC_ReceiveAck();


    for (i = 0; i < len; i++)
    {
        Dri_IIC_SendByte(bytes[i]);
        Dri_IIC_ReceiveAck();
    }

    Dri_IIC_Stop();
}

static void Int_OLED_SendData(u8* bytes, u8 len) {
    Int_OLED_SendBytes(bytes, 1, len);
}

static void Int_OLED_SendCommand(u8* bytes, u8 len) {
    Int_OLED_SendBytes(bytes, 0, len);
}


void Int_OLED_Init() {
    u8 cmds[6] = { SetDisplayOff, SetColRemap,SetRowRemap,SetPump,SetPumpLevel,SetDisplayOn };
    Int_OLED_SendCommand(cmds, 6);
}


void Int_OLED_Clear() {
    u8 i;
    u8 ClearArr[16] = { 0x00 };
    u8 cmds[2] = { SetAddMode,SetAdd_Horizontal };
    Int_OLED_SendCommand(cmds, 2);

    for (i = 0; i < 64; i++)
    {
        Int_OLED_SendData(ClearArr, 16);
    }
}


/**
 * ��OLED��ʾ������ʾ�ַ���
 *
 * �˺������𽫸������ַ�������ʾ��OLED��ʾ���ϵ�ָ��λ��
 * ��ͨ��������������ݵ�OLED��������ʵ����ʾ����
 *
 * ����:
 * x - �ַ�����ʾ����ʼ��λ�ã�0-15��
 * y - �ַ�����ʾ����ʼҳλ�ã�0-7��
 * bytes - ָ��Ҫ��ʾ���ַ������ָ��
 *
 * ע��:
 * 1. �ú�������OLED��ʾ��Ϊ128x64���أ�ʹ��I2Cͨ��
 * 2. �ַ�����Ӧ�����ɴ�ӡ��ASCII�ַ���32-127��
 */
void Int_OLED_DisplayStr(u8 x, u8 y, u8* bytes) {
    u8 i = 0; // ���ڱ����ַ����������
    u8 cmds[5]; // �������飬���ڴ洢���͵�OLED������������

    // ��ʼ���������飬���õ�ַģʽ��ҳ��ģʽ
    cmds[0] = SetAddMode;
    cmds[1] = SetAdd_Page;
    cmds[2] = (y * 2) | 0xB0; // ����ҳ���ַ
    cmds[3] = (x * 8) & 0x0F; // �����е�ַ�ĵ�4λ
    cmds[4] = ((x * 8) >> 4) | 0x10; // �����е�ַ�ĸ�4λ

    // ���ͳ�ʼ�����OLED������
    Int_OLED_SendCommand(cmds, 5);

    // �����ַ����飬�����ַ����ݵ�OLED������
    while ((bytes[i] != '\0') && (x + i < 16)) {
        Int_OLED_SendData(s_fonts[bytes[i] - 32], 8);
        i++;
    }

    // ׼��������һ��ҳ�������
    cmds[2] = (y * 2 + 1) | 0xB0; // ����ҳ���ַ
    Int_OLED_SendCommand(cmds, 5); // ��������

    // ���������ַ����ݵ�OLED������
    while ((bytes[i] != '\0') && (x + i < 16)) {
        Int_OLED_SendData(s_fonts[bytes[i] - 32] + 8, 8);
        i++;
    }
}


void Int_OLED_DisplayNum(u8 x, u8 y, long num) {
    char str[17];
    sprintf(str, "%ld", num);
    Int_OLED_DisplayStr(x, y, str);
}

