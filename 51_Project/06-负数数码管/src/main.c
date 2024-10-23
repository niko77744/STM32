/**
 * *********************************************
 * 8051 project
 * *********************************************
*/
#include "Com_Util.h"

// 1.����0-9 - . ��Ĭ������
u8 Digital_Number_codes[21] = { 0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,
                                0xBF,0x86,0xDB,0xC7,0xE6,0xED,0xFD,0x87,0xFF,0xEF,
                                0x40 };

// 2.����һ��Ҫ��ʾ��Digital������ ֻ��8��������������Ϊ8���洢��Ҳ�Ƕ�ѡ
u8 Digital_Buffer_codes[8];

// 3. ����λѡ�Ͷ�ѡ ��������뵽CU ��������ʾ����
void Int_DigitalTube_Single(u8, u8);

// 4.��Digital_Buffer����д������ ��ʮ���Ƶ�����ÿһλ�������ŵ� ��ѡ ��buffer�������
void Int_DigitalTube_SetBuffer(u32, u8);

// 5.��Buffer����ȡ������3.Int_DigitalTube_Single(i, Digital_Buffer_codes[i])  ��ʾ��Digital
void Int_DigitalTube_Refresh();

void main()
{
    // �ر�LED���������
    P34 = 0;
    P36 = 0;

    Int_DigitalTube_SetBuffer(12678, 2);  //!!! ע���д��while������

    while (1)
    {
        Int_DigitalTube_Refresh();
    }
}

void Int_DigitalTube_Single(u8 location, u8 dat) {
    // 1. ����location
    // P1�˿ڵ�P15,P14,P13����38������������͵�ƽ����������
    // location 1-7 == 000 , 001...

    location <<= 3;    //������λ��P1�˿ڶ���
    P1 &= 0xC7;        //!!!!��1���ı�ԭֵ����0��P13-P15��Ϊ0  0b11000111
    P1 |= location;     //!!!!��0���ı�ԭֵ
    // 0b00xxx000 location
    // 0buu000uuu P1
    // 0buuxxxuuu P1|=  //xȷ��,u��ȷ������P15-P13���뵽��P1���в���û�иı�P1��������


    // 2. ������Ǹ����Ķ�ѡ������ֱ�Ӹ�P0����
    // Int_DigitalTube_Single(5, Digital_Number_codes[1]);
    //  !!!!!ע���д����dat = P0; ?????
    P0 = dat;
}

void Int_DigitalTube_SetBuffer(u32 number, u8 Point_postion) {
    u8 i, len = 0;
    u32 temp;
    temp = number;
    for (i = 0; i < 8; i++)
    {
        temp /= 10;
        len++;
        if (0 == temp)
        {
            break;
        }
    }

    // !!�Ƚ���ʾ���������е���Ϣ����
    for (i = 0; i < 8; i++)
    {
        Digital_Buffer_codes[i] = 0x00;
    }
    for (i = 7; i >= 0; i--)  //!!!!ע��������7����8
    {
        if (7 + Point_postion - len == i) {  //p2  4  //p3  5  ����=6  i=8  i+1-p   //Point_postion+7-len
            Digital_Buffer_codes[7 + Point_postion - len] = Digital_Number_codes[number % 10 + 10];
        }
        else
        {
            Digital_Buffer_codes[i] = Digital_Number_codes[number % 10];  // �������numberȡ��λ�Ķ�ѡ���뵽����ĩβ
        }

        number /= 10;

        // �ǳ���Ҫ!!!!!
        if (0 == number)
        {
            Digital_Buffer_codes[i - 1] = Digital_Number_codes[20];
            break;
        }
    }
}

void Int_DigitalTube_Refresh() {
    u8 i;
    // ����buffer���鼴��,ֻҪ����(ˢ��)�Ĺ��죬�Ϳ�������������ֻ��һ��
    for (i = 0; i < 8; i++)  //time��ִ��һ����ҪԼ8ms
    {
        Int_DigitalTube_Single(i, Digital_Buffer_codes[i]);
        Delay_1ms(1);
    }
}