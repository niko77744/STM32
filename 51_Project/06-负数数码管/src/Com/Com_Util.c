#include "Com_Util.h"

// 延时函数的定义
void Delay_1ms(u16 ms)
{
    unsigned char data i, j;

    // 循环 ms 次
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