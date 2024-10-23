#include "Com_Util.h"

void Delay1ms(u16 times) //@11.0592MHz
{
    u8 i, j;

    for (; times > 0; times--)
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

void Delay10us(u16 times) //@11.0592MHz
{
    u8 i;
    for (; times > 0; times--)
    {
        i = 2;
        while (--i);
    }
}