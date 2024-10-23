#include "Int/Int_DigitalTube.h"


void Int_DigitalTube_Single(u8 bit_Sel, u8 segment_Sel) {
    bit_Sel <<= 3;
    P1 &= 0xC7;    //0b11000111
    P1 |= bit_Sel;

    P0 = segment_Sel;
}

void Int_DigitalTube_SetBuffer(u32 ObjNumber) {
    u8 i;
    for (i = 0; i <= 7; i++)
    {
        buffer[i] = 0;
    }

    for (i = 7; i >= 0; i--)
    {
        buffer[i] = DigitalTube_codes[ObjNumber % 10];
        ObjNumber /= 10;
        if (0 == ObjNumber)
        {
            break;
        }
    }
}


void Int_DigitalTube_Refresh() {
    u8 i;
    for (i = 0; i <= 7;i++)
    {
        Int_DigitalTube_Single(i, buffer[i]);
        Delay_1ms(100);
    }
    for (i = 8; i >= 1; i--)
    {
        Int_DigitalTube_Single(i - 1, buffer[i - 1]);
        Delay_1ms(100);
    }
}
