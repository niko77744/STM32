/**
 * *********************************************
 * 8051 project
 * *********************************************
*/
#include "Com_Util.h"

// 1.����1-9��Ĭ������
u8 Digital_Number_codes[10] = { 0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F };
// 00111111  00000110  01011011  01000111  01100110  01101101  01111101  00000111  01111111  01101111

// 2.����һ��Ҫ��ʾ��Digital������
u8 Digital_Buffer_codes[8];

// 3. ����λѡ�Ͷ�ѡ ��������뵽CU
void Int_DigitalTube_Single(u8, u8);

// 4.��Digital_Buffer����д������
void Int_DigitalTube_SetBuffer(u32);

// 5.��Buffer����ȡ������3.Int_DigitalTube_Single()��ʾ��Digital
void Int_DigitalTube_Refresh();

void main()
{
    // ע������Ķ���һ��Ҫдզ��ǰ��
    u8 n = 0, time = 125;  //timeѭ��125��(������Refresh(),һ����8ms,һ��Լ1s)����n+1
    // �ر�LED���������
    P34 = 0;
    P36 = 0;


    while (1)
    {
        if (0 == time)
        {
            Int_DigitalTube_SetBuffer(n++);
            time = 125;
            // if (60 == n)
            // {
            //     n = 0;
            // }
        }

        Int_DigitalTube_Refresh();
        time--;
    }
}

void Int_DigitalTube_Single(u8 location, u8 dat) {
    // 1. ����location
    // P1�˿ڵ�P15,P14,P13����38������������͵�ƽ����������
    // location 1-7 == 000 , 001...

    location <<= 3;    //������λ��P1�˿ڶ���
    P1 &= 0xC7;        //��1���ı�ԭֵ����0��P13-P15��Ϊ0  0b11000111
    P1 |= location;     //��0���ı�ԭֵ
    // 0b00xxx000 location
    // 0buu000uuu P1
    // 0buuxxxuuu P1|=  //xȷ��,u��ȷ������P15-P13���뵽��P1���в���û�иı�P1��������


    // 2. ������Ǹ����Ķ�ѡ������ֱ�Ӹ�P0����
    // Int_DigitalTube_Single(5, Digital_Number_codes[1]);
    //  dat = P0; ?????
    P0 = dat;
}

void Int_DigitalTube_SetBuffer(u32 number) {
    u8 i;

    // �Ƚ���ʾ���������е���Ϣ����
    for (i = 0; i < 8; i++)
    {
        Digital_Buffer_codes[i] = 0x00;
    }

    for (i = 7; i >= 0; i--)  //������7����8
    {
        Digital_Buffer_codes[i] = Digital_Number_codes[number % 10];  // �������numberȡ��λ�Ķ�ѡ���뵽����ĩβ
        number /= 10;

        // ��Ҫ
        if (0 == number)
        {
            break;
        }
    }
}


void Int_DigitalTube_Refresh() {
    u8 i, j; //i���Ƶڼ������֣�j������ʾʲô
    // ����buffer���鼴��,ֻҪˢ�µĹ��죬����һֱ��ʾ
    for (i = 0; i < 8; i++)  //time��ִ��һ����ҪԼ8msj
    {
        for (j = 0; j < 8; j++)
        {
            Int_DigitalTube_Single(i, Digital_Buffer_codes[j]);
        }
        Delay_1ms(1);
    }
}

