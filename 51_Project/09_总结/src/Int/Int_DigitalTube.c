#include <STDIO.H>
#include <STRING.H>
#include <MATH.H>
#include "Int_DigitalTube.h"
#include "Com_Util.h"

static u8 DigitalTube_SegmentSel_Codes[10] = { 0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F };
static u8 DigitalTube_Buffer_Codes[8];

void Int_DigitalTube_Init(void)
{
    // �ر���ˮ��
    LED_SwitchH = 0;
    // ���������
    DigitalTube_SwitchL = 0;
}

//��̬��ʾ
void Int_DigitalTube_StaticDisplay(u8 display_number) {
    Int_DigitalTube_Single(display_number, DigitalTube_SegmentSel_Codes[display_number]);
}



// ��������ʾ���� ����λѡ�Ͷ�ѡ ��������뵽CU  ͨ������P1����38����������ѡ��
void Int_DigitalTube_Single(u8 bit_Sel, u8 segment_Sel) {
    bit_Sel <<= 3;  // P17... P10   00xxx000  ����P15-P13
    P1 &= 0xC7;  // 0b11000111 ��1���䣬��0��0����P15-P13��Ϊ0
    P1 |= bit_Sel;

    P0 = segment_Sel; 
}

// ����������ݴ���buffer����
void Int_DigitalTube_SetBuffer(u32 ObjNumber) {
    u8 i;
    for (i = 0; i < 8; i++)
    {
        DigitalTube_Buffer_Codes[i] = 0x00;
    }

    for (i = 7; i >= 0; i--)
    {
        DigitalTube_Buffer_Codes[i] = DigitalTube_SegmentSel_Codes[ObjNumber % 10];
        ObjNumber /= 10;
        if (0 == ObjNumber)
        {
            break;
        }
    }
}

// ��������buffer
void Int_DigitalTube_SetNegativeBuffer(float number) {

    char i;	  // ѭ������
    char index; // ���һ����Ч�ַ��±�
    u8 str[15];
    bit has_signed = 0; // �з��ű��
    bit has_dot = 0;	// ��С������

    if (number < 0)
    {
        has_signed = 1;
    }

    // �Ƚ���ʾ���������е���Ϣ����
    for (i = 0; i < 8; i++)
    {
        DigitalTube_Buffer_Codes[i] = 0x00;
    }

    // �� number ����ֵ����Ϊ�ַ���
    sprintf(str, "%f", fabs(number));

    // �������һ����Ч�ַ��±�
    index = strlen(str) - 1;

    // ȥ��С������� 0
    for (i = index; i >= 0; i--)
    {
        if (str[i] == 48)  //ASCII�� 48��0
        {
            str[i] = 0;
            index--;
        }
        else
        {
            break;
        }
    }

    // �Ӻ���ǰ�����ַ���, ������ buffer ����
    for (i = 7; i >= 0 && index >= 0; i--, index--)
    {
        // �����С����
        if (str[index] == 46)  //ASCII�� 46��С����
        {
            has_dot = 1;
            i++;
            continue;
        }

        DigitalTube_Buffer_Codes[i] = DigitalTube_SegmentSel_Codes[str[index] - 48];
        //break;

        //�����С����
        if (has_dot)
        {
            DigitalTube_Buffer_Codes[i] += 0x80;
            has_dot = 0;
        }
    }
    // ����и���
    if (has_signed && i >= 0)
    {
        DigitalTube_Buffer_Codes[i] = 0x40;
    }
}

// ����buffer���� ˢ��Int_DigitalTube_Single��������ʾ
void Int_DigitalTube_Refresh(void) {
    u8 i;
    for (i = 0; i <= 7; i++)
    {
        Int_DigitalTube_Single(i, DigitalTube_Buffer_Codes[i]);
        Delay_1ms(1);
    }
    // for (i = 8; i >= 1; i--)
    // {
    //     Int_DigitalTube_Single(i - 1, buffer[i - 1]);
    //     Delay_1ms(1);
    // }
}