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