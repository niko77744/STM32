#include "Com_Util.h"
// #include "Int_SwLED.h"
// #include "Int_DigitalTube.h"
// #include "Int_MatrixSW.h"
// #include "Int_Buzzer.h"
// #include "Dri_Extern0Interrruput.h"
#include "Dri_Tmer0Interruput.h"
#include "Int_MatrixLED.h"



void main()
{
    u8 i = 0;

    Int_MatrixLED_Init();



    while (1)
    {
        Int_MatrixLED_SetPixel(picture[i]);
        i++;
        if (i ==4)
        {
            i=0;
        }
        Delay1ms(200);
    }
}
