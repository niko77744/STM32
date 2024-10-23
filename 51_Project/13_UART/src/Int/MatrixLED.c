#include "MatrixLED.h"

static u8 Int_MatrixLED_bufferArray[8];
void Int_MatrixLED_Init() {
    u8 i;
    MatrixLED_SwitchL = 0;
    Dri_Timer0_Init();
    Dri_Timer0_setInterval(Int_MatrixLED_Refresh);
    for (i = 0; i < 8; i++)
    {
        Int_MatrixLED_bufferArray[i] = 0x00;
    }
}


void Int_MatrixLED_ShiftPixels(u8 new_line) {
    u8 i;
    for (i = 7; i > 0; i--)
    {
        Int_MatrixLED_bufferArray[i] = Int_MatrixLED_bufferArray[i - 1];
    }
    Int_MatrixLED_bufferArray[0] = new_line;
}

void Int_MatrixLED_SetPixels(u8 pixels[8]) {
    u8 i;
    for (i = 0; i < 8; i++)
    {
        Int_MatrixLED_bufferArray[i] = pixels[i];
    }
}

void Int_MatrixLED_Refresh() {
    static u8 i;
    if (i == 0)
    {
        SER = 1;
    }
    else
    {
        SER = 0;
    }
    RCK = 0;
    SCK = 0;

    SCK = 1;
    RCK = 1;

    P0 = ~Int_MatrixLED_bufferArray[i];

    i++;
    if (i == 8)
    {
        i = 0;
    }
}
