/**
 * *********************************************
 * 8051 project
 * *********************************************
*/
#include "Com_Util.h"
#include "Int/Int_MatrixLED.h"

void main()
{
    u8 line_pixels[16] = { 0x1, 0x2, 0x4, 0x8, 0x10, 0x20, 0x40, 0x80 };

    Int_MatrixLED_Init();
    Int_MatrixLED_SetPixels(line_pixels);

    while (1);
}

