/**
 * *********************************************
 * 8051 project
 * *********************************************
*/
#include "./Com/Com_Util.h"
#include "./Int/Int_Key.h"

void main()
{
    while (1)
    {
        if (Int_Key_IsSw1Pressed())
        {
            P00 = ~P00;
        }
        if (Int_Key_IsSw2Pressed())
        {
            P01 = ~P01;
        }
        if (Int_Key_IsSw3Pressed())
        {
            P02 = ~P02;
        }
        if (Int_Key_IsSw4Pressed())
        {
            P03 = ~P03;
        }
    }
}

