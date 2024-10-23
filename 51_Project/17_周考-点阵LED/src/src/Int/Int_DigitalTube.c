#include "Int_DigitalTube.h"


//�����������ڻ�������
static Int_DigitalTube_SetBuffer[8];

void Int_DigitalTube_single (u8 dig ,u8 num)
{

    P0 =0;

    //ѡ��λѡ
    P1 &= 0xC7;
    dig <<= 3;
    P1 |= dig;

    //Ƭѡ����
    P0 = num;

}

void Int_DigitalTube_DisplayNum(u32 number)
{
    //��ջ�������
    u8 i;
    for ( i = 0; i < 8; i++)
    {
        Int_DigitalTube_SetBuffer[i]=0;
    }


    //���number��0��ֱ��������ܵ�7λ��ʾ
    if (!number)
    {
        Int_DigitalTube_SetBuffer[7] = DigitalTube_codes[0];
        return;
    }
    
    //number����0��������������鸳ֵ����ע��������ϴ�������������Ϊ�����0~7Ԫ��
   i=7;
    while (number)
    {

            Int_DigitalTube_SetBuffer[i] = DigitalTube_codes[(number % 10)]; 
            i--;
            number /= 10;
        
    }   
}


void Int_DigitalTube_Refresh()
{
    u8 i;
    for ( i = 0; i < 8; i++)
    {
        Int_DigitalTube_single(i,Int_DigitalTube_SetBuffer[i]);
        Delay1ms(1);
    }
    return;
    
}

void Int_DigitalTube_Init()
{
    //������ܿ���
    P34 = 0;
    P36 = 0;
    Int_DigitalTube_DisplayNum(0);
}