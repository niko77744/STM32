#include "Com_Util.h"

// ��ʱ�����Ķ���
void Delay_1ms(u16 ms)
{
    unsigned char data i, j;

    // ѭ�� ms ��
    for (; ms > 0; ms--)
    {

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


void Delay_10us(u16 us)	//@11.0592MHz
{
    unsigned char data i;

    // ѭ�� ms ��
    for (; us > 0; us--)
    {
        i = 2;
        while (--i);
    }
}