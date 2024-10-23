#include "Inf_TM7711.h"


void Inf_TM7711_Init(void) {
    Driver_GPIO_TM7711_Init();
}


/**
 * @brief ��ȡˮλ��������ֵ ����24λ�����λ�Ƿ���λ ��������
 *  ʱ�� ��С0.2us  ���50us  ��λ�ȷ� ǰ24λΪ��Ч���� 25λΪ��Ч����
 *
 * ���������ŵ����� ��Χ        DATA����������ò�����  ->  ת��Ϊ�����洢
 * 0x800000 - 0x7fffff
 *      ��
 * ���0x800000   ͬ0��1
 *      ��
 * ������������
 * 0x000000 - 0xffffff
 * 
 * @return uint32_t
 */
uint32_t Inf_TM7711_ReadV(void) {
    uint32_t data = 0;
    TM7711_SCK_L;
    while ((TM7711_SDA_R) != 0); //�ȴ�����������

    for (uint8_t i = 0; i < 24; i++)
    {
        TM7711_SCK_H;
        Delay_us(5);

        TM7711_SCK_L;
        // ���½���ʱ��ȡ����

        data <<= 1;
        if (TM7711_SDA_R)
        {
            data |= 0x01;
        }

        Delay_us(5);
    }

    // ʹ�õ�25����ʱ���ź�
    TM7711_SCK_H;
    Delay_us(5);
    TM7711_SCK_L;
    Delay_us(5);

    // ע��: ����DATA����������ò�����  ->  ת��Ϊ�����洢
    return data ^ 0x800000;
}
