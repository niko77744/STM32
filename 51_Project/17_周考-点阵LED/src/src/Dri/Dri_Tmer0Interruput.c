#include "Dri_Tmer0Interruput.h"
#include <STDIO.H>

void Dri_Timer0Interrupt_Init()
{
    // ���жϿ���
    EA = 1;
    // �򿪶�ʱ���ж�
    ET0 = 1;
    // �����жϴ�����ʽ

    TMOD &= 0xF0;
    TMOD |= 0x01; // ���ö�ʱ��ģʽ
    TL0 = 0x66;   // ���ö�ʱ��ʼֵ
    TH0 = 0xFC;   // ���ö�ʱ��ʼֵ
    TF0 = 0;      // ���TF0��־
    TR0 = 1;      // ��ʱ��0��ʼ��ʱ
}

// ����ע�Ṧ�ܺ���
bit Dri_Timer0Interrupt_RegisiterFunction(CallbackFunction Function)
{
    u8 i;
    // ��鹦���Ƿ�ע���
    for (i = 0; i < MaxFunctionCount; i++)
    {
        if (FunctionArray[i] == Function)
            return 1;
    }

    // �������û��ע�����ע��ú���
    for (i = 0; i < MaxFunctionCount; i++)
    {
        if (FunctionArray[i] == NULL)
        {
            FunctionArray[i] = Function;
            return 1;
        }
    }
    // ������������������Ҳ����ڸú���
    return 0;
}

// ����ע�����ܺ���
bit Dri_Timer0Interrupt_DeregisiterFunction(CallbackFunction Function)
{
    u8 i;
    // �����������Ƿ��иú���
    for (i = 0; i < MaxFunctionCount; i++)
    {
        if (FunctionArray[i] == Function)
        {
            FunctionArray[i] = NULL;
            return 1;
        }
    }
    return 0;
}

void Timer0Interrupt_Handler() interrupt 1
{
    u8 i;

    // ���ö�ʱ��װ��ֵ,ÿ��1ms�Խ���1���ж�
    TL0 = 64614;
    TH0 = 64614 >> 8;
    // �������ù��������ڵĹ���
    for (i = 0; i < MaxFunctionCount; i++)
    {
        if (FunctionArray[i] != NULL)
        {
            FunctionArray[i]();
        }
    }
}

void toggle_LED1()
{
    static u16 count = 500;
    count--;
    if (count == 0)
    {

        if (!P0)
            P0 = 0x01;
        P0 = ~P0;
        P0 <<= 1;
        P0 = ~P0;
        count = 500;
    }
}