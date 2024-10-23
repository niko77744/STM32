#include "Int_Buzzer.h"

/**
 * @brief ���������� 500Hz ������, �� 0.1s
 */
void Int_Buzzer_Buzz()
{
    u8 count = 100;
    while (count > 0)
    {
        P46 = ~P46;
        Delay_1ms(1);       // ��ʱ 1ms 
        count--;
    }
}

void Int_Buzzer_frequency(u8 type, u16 Buzzer_MsTime) {
    // ����������� ÿ��ѭ����ʱ ���ٸ� 10us
    u16 t;
    // �����������ѭ������
    u16 count;

    // �������ַ������;���Ƶ�ʽ������� t ��ֵ
    switch (type)
    {
    case 1: t = 100000 / (400 * 2); break;
    case 2: t = 100000 / (450 * 2); break;
    case 3: t = 100000 / (506 * 2); break;
    case 4: t = 100000 / (541 * 2); break;
    case 5: t = 100000 / (600 * 2); break;
    case 6: t = 100000 / (675 * 2); break;
    case 7: t = 100000 / (759 * 2); break;
    default: t = 100000 / (500 * 2);
    }

    // ����t��ֵ������ѭ������
    count = Buzzer_MsTime * 100 / t;

    // ѭ��
    while (count > 0)
    {
        P46 = ~P46;
        Delay_10us(t);
        count--;
    }
}
