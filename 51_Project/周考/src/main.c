/**
 * *********************************************
 * 8051 project
 * *********************************************
*/
#include "Com_Util.h"
#include "Int/Int_Digital.h"

void main()
{
    SW_LED = 0;
    SW_Digital = 0;
    while (1) {
        Int_Digital_StaticDisplay(2, number_codes[0]);
    }
}

