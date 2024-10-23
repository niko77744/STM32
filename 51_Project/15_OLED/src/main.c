/**
 * *********************************************
 * 8051 project
 * *********************************************
*/
#include "Com_Util.h"
#include "Dri/Dri_Timer0.h"
#include "Dri/Dri_INT0.h"
#include "Dri/Dri_IIC.h"

#include "Int/Int_EEPROM.h"
#include "Int/Int_MatrixLED.h"
#include "Int/Int_OLED.h"
#include "Int/Int_Key.h"
void main()
{
    // ³õÊ¼»¯ OLED
    Int_OLED_Init();
    // ÇåÆÁ
    Int_OLED_Clear();

    // ÏÔÊ¾×Ö·û´®
    Int_OLED_DisplayStr(2, 0, "option one!");
    Int_OLED_DisplayStr(2, 1, "option two!");
    Int_OLED_DisplayNum(2, 2, 123);
    Int_OLED_DisplayNum(2, 3, -321);



    // ËÀÑ­»·
    while (1) {
        static u8 i = 1;

        if (Int_Key_IsSw1Pressed() == 1)
        {
            if (i == 4) {
                i = 0;
            }
            Int_OLED_ClearSpot(1, i - 1);
            Int_OLED_DisplayStr(1, i, ">");
            i++;
        }
    }
}
