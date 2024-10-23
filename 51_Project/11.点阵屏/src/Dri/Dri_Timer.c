#include "Dri_Timer.h"


// �ṹ����� 1.����ָ�룬��Ϊ�����Ļص����� 2.��Ϊ�����Ĵ���Ƶ�� ����msһ�� 3����ΪTriggerFrequency����ʱ����
typedef struct {
    Timer0_Callback callback;
    u16 TriggerFrequency;
    u16 temp;
}My_Timer0;

// ����ṹ�����飬����Ϊ4��������My_Timer0�ṹ��
static My_Timer0 s_timer0_callbacks[MAX_CALLBACK_COUNT];

// ��ʼ����ʱ��0
void Dri_Timer0_Init() {
    u8 i;

    EA = 1;     // �ܿ���
    ET0 = 1;    // Timer0����
    TL0 = 0x66; // �����Ĵ�����洢��ֵ������򴥷��ж�
    TH0 = 0xFC;
    // TL0 = 64614;
    // TH0 = 64614 >> 8;
    TMOD &= 0xF0;  // 11110000    TMOD8λ����4λ�Ƕ�ʱ��1�ģ���4λ�Ƕ�ʱ��0��  ���ｫ��4λ��Ϊ0
    TMOD |= 0x01;  // 0000 0001   ��4λ GATE�Ǵ򿪶�ʱ��(0)/������  C/T��ѡ��ʱ��(0)/������  M0��M1���Ƽ���ģʽ
    TR0 = 1;       // TR����ʼ����

    for (i = 0; i < MAX_CALLBACK_COUNT; i++)
    {
        // ���ṹ�������ÿһ��Ԫ�ص�.callback��.TriggerFrequency��Ϊ0����ʼ��
        s_timer0_callbacks[i].callback = NULL;
        s_timer0_callbacks[i].TriggerFrequency = 0;
    }
}

// ����ʱ��0 ע��ص����� ����1���ص�����  ����2��Ƶ��TriggerFrequency ����msһ��
bit Dri_Timer0_setInterval(Timer0_Callback callback, u16 TriggerFrequency) {
    u8 i;
    for (i = 0; i < MAX_CALLBACK_COUNT; i++)
    {
        // ����ͬһ���ص������ظ�ע��
        if (callback == s_timer0_callbacks[i].callback)
        {
            return 1;
        }

        // �����ǰλ���ǿգ���callback�ʹ���Ƶ����ӵ��˴�
        if (s_timer0_callbacks[i].callback == NULL)
        {
            s_timer0_callbacks[i].callback = callback;
            s_timer0_callbacks[i].TriggerFrequency = TriggerFrequency;
            return 1;
        }
    }
    return 0;
}



//  ע����ʱ��0�Ļص�����
bit Dri_Timer0_clearInterval(Timer0_Callback callback) {
    u8 i;
    for (i = 0; i < MAX_CALLBACK_COUNT; i++)
    {
        if (callback == s_timer0_callbacks[i].callback)
        {
            s_timer0_callbacks[i].callback = NULL;
            return 1;
        }
    }
    return 0;
}

// 1ms����һ���ж�
void Dri_Timer0_Handler() interrupt 1
{
    u8 i = 0;
    for (i = 0; i < MAX_CALLBACK_COUNT; i++)
    {
        // ִ�����鲻Ϊ�յ�Ԫ��
        if (s_timer0_callbacks[i].callback != NULL)
        {
            // TriggerFrequency msִ��һ�λص�����
            if (s_timer0_callbacks[i].temp-- == 0)
            {
                s_timer0_callbacks[i].temp = s_timer0_callbacks[i].TriggerFrequency;
                s_timer0_callbacks[i].callback();
            }
        }
    }

    // ���³�ʼ���Ĵ����ĳ�ʼֵ  �������Ҫ1ms ��������ж�
    TL0 = 0x66;
    TH0 = 0xFC;
}
