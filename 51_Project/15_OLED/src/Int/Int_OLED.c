#include "Int_OLED.h"

// ����
#define OLED_ADDR 0x78
#define OLED_Command 0x00
#define OLED_Data 0x40

#define SetDisplayOn 0xAF
#define SetDisplayOff 0xAE

#define SetDisplayPumpEnable 0x8D
#define ChargePumpModel 0x14

#define SetSegmentRemap 0xA1
#define SetComOutputScanDirection 0xC8


#define SetMemoryAddressingMode 0x20
#define PageAddressingMode 0x02
#define HorizontalAddressingMode 0x00

static u8 ClearOLEDArr[16] = { 0x00 };

/**
 * @brief ��OLEDд�������� ��Ϊ���������
 *
 * @param bytes Ҫд�������/�����
 * @param len  Ҫд�볤��
 * @param bit is_data 1��ʾ���� 0��ʾ����
 */
static void Int_OLED_WriteBytes(u8* bytes, u8 len, bit is_data) {
    u8 i;
    // ���������ź�
    Dri_IIC_Start();
    // ����OLED��ַ��д��־��������Ӧ������
    Dri_IIC_SendByte(OLED_ADDR);
    Dri_IIC_ReceiveAck();

    // ���Ϳ����ֽڣ�ȷ�����������ݻ�������; ������Ϊ��������
    if (is_data)
    {
        // �����ֽ�ָ�������������ݣ� 0100 0000
        Dri_IIC_SendByte(OLED_Data);
    }
    else {
        // �����ֽ�ָ�������������0000 0000
        Dri_IIC_SendByte(OLED_Command);
    }
    Dri_IIC_ReceiveAck();

    // ���η��� ���������
    for (i = 0; i < len; i++)
    {
        Dri_IIC_SendByte(bytes[i]);
        Dri_IIC_ReceiveAck();
    }

    // ���ͽ����ź�
    Dri_IIC_Stop();
}

// ��������
static void Int_OLED_WriteCommand(u8* bytes, u8 len)
{
    Int_OLED_WriteBytes(bytes, len, 0);
}

// ��������
static void Int_OLED_WriteData(u8* bytes, u8 len)
{
    Int_OLED_WriteBytes(bytes, len, 1);
}

// ����ҳ��ַ���е�ַ ����������; ���������ֱ��� ҳ��ַ���е�ַ

static void Int_OLED_SetAddress(u8 page, u8 column) {
    // ��������
    u8 address_cmds[3];
    // pageҪ���ó� 1011 0xxx
    address_cmds[0] = page | 0xB0;
    // colҪ���óɣ���4λ 0000 xxxx    ��3λ 0001 0xxx
    address_cmds[1] = column & 0x0F;
    address_cmds[2] = (column >> 4) | 0x10;   // 0000 0xxx    0001 0000     0001 0xxx
    Int_OLED_WriteCommand(address_cmds, 3);
}

/**
 * @brief OLED ��ʼ��
 *
 */
void Int_OLED_Init() {
    u8 cmds[6] = { SetDisplayOff,SetDisplayPumpEnable,ChargePumpModel,SetSegmentRemap,SetComOutputScanDirection,SetDisplayOn };
    Int_OLED_WriteCommand(cmds, 6);
}


/**
 * @brief OLED ����
 *
 */
void Int_OLED_Clear() {
    u8 i;
    // ������ˮƽѰַ��ʽ
    u8 cmds[2] = { SetMemoryAddressingMode,HorizontalAddressingMode };
    // ��������
    Int_OLED_WriteCommand(cmds, 2);

    //ÿ��page��Ҫ8�Σ�һ��8��page  ÿ������ 16x8  4��x16��
    //һ���ִ泤16��8  ��Ҫ����page
    //  ��GDDRAMд�����ݣ�ѭ�� 64 �Σ�ÿ��д�� 16 ���ֽڣ�����д������ GDDRAM
    for (i = 0; i < 64; i++)
    {
        Int_OLED_WriteData(ClearOLEDArr, 16);
    }
}

void Int_OLED_ClearSpot(u8 x, u8 y) {
    // ������ˮƽѰַ��ʽ
    u8 i = 0;
    u8 cmds[8];
    cmds[0] = SetMemoryAddressingMode;
    // ˮƽѰַ
    cmds[1] = HorizontalAddressingMode;
    // ���ͱ�ʶ����������
    cmds[2] = 0x21;
    // ����ʼλ��
    cmds[3] = x * 8;
    // �н���λ��
    cmds[4] = x * 8 + 8;
    // ���ͱ�ʶ����������
    cmds[5] = 0x22;
    // ����ʼλ��
    cmds[6] = y * 2;
    // �н���λ��
    cmds[7] = y * 2 + 1;
    Int_OLED_WriteCommand(cmds, 8);

    for (i = 0; i < 1; i++)
    {
        Int_OLED_WriteData(ClearOLEDArr, 16);
    }
}

void Int_OLED_ClearSpotLine(u8 y) {
    u8 i;
    u8 cmds[5];
    // ������Ѱַ��ʽ
    cmds[0] = SetMemoryAddressingMode;
    cmds[1] = PageAddressingMode;
    // ����pageλ�� B0~B7
    cmds[2] = (y * 2) | 0xB0;
    // ��������ʼλ�� 0x00~0x0F
    cmds[3] = 0x00;
    // �����н���λ�� 0x10~0x17
    cmds[4] = 0x10;

    // ��GDDRAMд������
    // ѭ�� 8 �Σ�ÿ��д�� 16 ���ֽڣ�����д��һ����
    Int_OLED_WriteCommand(cmds, 5);
    for (i = 0; i < 8; i++)
    {
        Int_OLED_WriteData(ClearOLEDArr, 16);
    }


    cmds[2] = (y * 2 + 1) | 0xB0;
    Int_OLED_WriteCommand(cmds, 5);
    for (i = 0; i < 8; i++)
    {
        Int_OLED_WriteData(ClearOLEDArr, 16);
    }
}


/**
 * @brief OLED ��ʾ�ַ���
 *
 * @param x X����
 * @param y Y����
 * @param str Ҫд����ַ���
 */
void Int_OLED_DisplayStr(u8 x, u8 y, u8* str) {

    u8 i = 0;
    // һ���ִ泤16��8  ��Ҫ����page
    u8 cmds[2] = { SetMemoryAddressingMode,PageAddressingMode };
    Int_OLED_WriteCommand(cmds, 2);

    Int_OLED_SetAddress(y * 2, x * 8);  //page�ж�Ӧy  col�ж�Ӧx
    while ((str[i] != 0) && (x + i < 16)) {
        Int_OLED_WriteData(s_fonts[str[i] - 32], 8);
        i++;
    };

    Int_OLED_SetAddress(y * 2 + 1, x * 8);
    for (i = 0; (str[i] != 0) && (x + i < 16); i++)
    {
        // д������
        Int_OLED_WriteData(s_fonts[str[i] - 32] + 8, 8);
    }
}


/**
 * @brief OLED ��ʾ����
 *
 * @param x X����
 * @param y Y����
 * @param num Ҫд�������
 */
void Int_OLED_DisplayNum(u8 x, u8 y, long num)
{
    // �����ַ��� 
    u8 str[12];
    // �� num תΪ�ַ������� str
    sprintf(str, "%ld", num);
    // ��ʾstr
    Int_OLED_DisplayStr(x, y, str);
}