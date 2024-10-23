#include "Int_Buzzer.h"

void Int_Buzzer_HzBuzzer(u8 number)
{
    u8 count = 100;
    while (count--)
    {
        P46 = ~P46;
        Delay10us(number);
    }
}