#include "./Int/Int_Key.h"

bit Int_Key_IsSw1Pressed() {

    // �ж�sw1�Ƿ񱻰���
    if (0 == SW1)
    {
        // ���� ��ʱ10ms
        Delay_1ms(10);
        // ��ʱ֮���ǰ��µ�״̬
        if (0 == SW1)
        {
            // �ȴ�����̧��ѭ������
            while (0 == SW1);
            return 1;
        }
    }
    return 0;
}

bit Int_Key_IsSw2Pressed() {

    // �ж�sw1�Ƿ񱻰���
    if (0 == SW2)
    {
        // ���� ��ʱ10ms
        Delay_1ms(10);
        // ��ʱ֮���ǰ��µ�״̬
        if (0 == SW2)
        {
            // �ȴ�����̧��ѭ������
            while (0 == SW2);
            return 1;
        }
    }
    return 0;
}

bit Int_Key_IsSw3Pressed() {

    // �ж�sw1�Ƿ񱻰���
    if (0 == SW3)
    {
        // ���� ��ʱ10ms
        Delay_1ms(10);
        // ��ʱ֮���ǰ��µ�״̬
        if (0 == SW3)
        {
            // �ȴ�����̧��ѭ������
            while (0 == SW3);
            return 1;
        }
    }
    return 0;
}


bit Int_Key_IsSw4Pressed() {

    // �ж�sw1�Ƿ񱻰���
    if (0 == SW4)
    {
        // ���� ��ʱ10ms
        Delay_1ms(10);
        // ��ʱ֮���ǰ��µ�״̬
        if (0 == SW4)
        {
            // �ȴ�����̧��ѭ������
            while (0 == SW4);
            return 1;
        }
    }
    return 0;
}