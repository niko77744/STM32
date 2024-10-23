#include "Com_Util.h"
#include "Int_DigitalTube.h"

// �����Ķ��� ָ��λ��ָ����ѡ��Ϣ
void DigitalTube_Single(u8 pos, u8 cod)
{
    // ʵ��λѡ ---------------------------------
    // ���� pos���� pos ����Ч������ p1 �� P15~P13 ����λ����
    pos <<= 3;
    // ���� P1�� ��P15~P13 ����λ��0������λ����
    P1 &= 0xC7;
    // �� pos ����Ч���ָ�ֵ�� P15~P13 ����λ
    P1 |= pos;


    // ��ѡ ------------------------------------------
    P0 = cod;

}


// ���庯��  ������ʾ����
void DigitalTube_SetBuffer(u32 number)
{
    u8 i;

    // �Ƚ���ʾ���������е���Ϣ����
    for (i = 0; i < 8; i++)
    {
        digital_buffer[i] = 0x00;
    }

    // �� number ÿ��λ����ȡ�����ҵ���Ӧ�Ķ�ѡ��Ϣ�����뻺������
    /*
        2784

        %10 = 4, /10=278
        %10 = 8, /10=27
        %10 = 7, /10=2
        %10 = 2, /10=0
    */
    for (i = 7; i >= 0; i--)
    {
        digital_buffer[i] = number_codes[number % 10];
        number /= 10;
        if (number == 0)
        {
            break;
        }
    }
}

// ���庯�� ����ʾ�����е�������ʾ�������
void DigitalTube_Refresh()
{
    u8 i;
    // ������������
    for (i = 0; i <= 7; i++)
    {
        // ���ú��� ָ��λ�� ָ����ѡ��Ϣ
        DigitalTube_Single(i, digital_buffer[i]);
        // ���ռ�ձ� ʱ����ʱ
        Delay_1ms(1);
    }
}
