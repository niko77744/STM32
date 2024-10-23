#include <STC89C5xRC.H>
#include <INTRINS.H>

// ���ͱ���
typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;

// �������飬����ÿ�����ֶ�Ӧ�Ķ�ѡ��Ϣ
u8 number_codes[10] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F  // 9
};

// �������飬��ʾ���棬���������ÿ��λ��Ҫ��ʾ�����ֵĶ�ѡ��Ϣ
u8 digital_buffer[9];

// ��ʱ�����Ķ���
void Delay_1ms(u16 ms)
{
    unsigned char data i, j;

    // ѭ�� ms ��
    for (; ms > 0; ms--) {
        _nop_();
        i = 2;
        j = 199;
        do
        {
            while (--j)
                ;
        } while (--i);
    }
}

/**
 * @brief �������ָ��λ��ָ����ѡ��Ϣ
 *
 * @param pos λ�ã� ������������ 0 ~ 7
 * @param code ��ѡ��Ϣ
 */
void DigitalTube_Single(u8, u8);

/**
 * @brief ������ʾ����
 *
 * @param number Ҫ��ʾ�����������֣�ʮ���Ʊ�ʾ��
 */
void DigitalTube_SetBuffer(u32);

/**
 * @brief ����ʾ�����е�������ʾ�������
 */
void DigitalTube_Refresh();


void main()
{
    // �ر���ˮ��
    P34 = 0;

    // �������
    P36 = 0;

    // ����Ҫ��ʾ������
    DigitalTube_SetBuffer(123456789);


    // ��ѭ�� ��ͣˢ��
    while (1)
    {
        DigitalTube_Refresh();

    }

}


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
    for (i = 0; i < 9; i++)
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
    for (i = 8; i >= 0; i--)
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
    u8 i, j;
    // ������������
    for (i = 0; i < 2; i++)
    {
        DigitalTube_Single(i, digital_buffer[i]);
        for (j = 0; j < 9; j++)
        {
            // ���ú��� ָ��λ�� ָ����ѡ��Ϣ
            DigitalTube_Single(1, digital_buffer[j]);
            Delay_1ms(1000);
        }
    }
}