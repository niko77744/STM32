#include "Dri_Timer0.h"


// ��ʱ��Timer0�ĳ�ʼ��
void Dri_Timer0_Init() {
    u8 i;
    EA = 1;
    ET0 = 1;
    TR0 = 1;

    TMOD &= 0xF0;
    TMOD |= 0x01;

    TL0 = 0x66;
    TH0 = 0xFC;

    for (i = 0; i < Max_Timer0CallbackFun_Count; i++)
    {
        s_Dri_Timer0CallbackFunArr[i] = 0x00;
    }
}

// ע�ᶨʱ��0�� �ص����� ����1���ص����� 
bit Dri_Timer0_setInterval(Timer0_Callback callback) {
    u8 i;
    for (i = 0; i < Max_Timer0CallbackFun_Count; i++)
    {
        if (s_Dri_Timer0CallbackFunArr[i] == callback)
        {
            return 1;
        }
    }
    for (i = 0; i < Max_Timer0CallbackFun_Count; i++)
    {
        if (s_Dri_Timer0CallbackFunArr[i] == NULL)
        {
            s_Dri_Timer0CallbackFunArr[i] = callback;
            return 1;
        }
    }
    return 0;
}

//  ע����ʱ��0�� �ص�����
bit Dri_Timer0_clearInterval(Timer0_Callback callback) {
    u8 i;
    for (i = 0; i < Max_Timer0CallbackFun_Count; i++)
    {
        if (s_Dri_Timer0CallbackFunArr[i] == callback)
        {
            s_Dri_Timer0CallbackFunArr[i] = NULL;
            return 1;
        }
    }
    return 0;
}

void Dri_Timer0_Handler() interrupt 1{
    u8 i;
    for (i = 0; i < Max_Timer0CallbackFun_Count; i++)
    {
        if (s_Dri_Timer0CallbackFunArr[i] != NULL)
        {
            s_Dri_Timer0CallbackFunArr[i]();
        }
    }
    TL0 = 0x66;
    TH0 = 0xFC;
}

