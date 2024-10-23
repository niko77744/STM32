/**
 * *********************************************
 * 8051 project
 * *********************************************
*/
#include "Com_Util.h"
#include "Int/Int_LED.h"
#include "Int/Int_DigitalTube.h"
#include "Int/Int_Key.h"
#include "Int_Matrix.h"
#include "Int/Int_Buzzer.h"
#include "Int/Int_MatrixLED.h"
#include "Dri/Dri_Timer.h"

u8 tab[] = { 0x1,0x2,0x4,0x8,0x10,0x20,0x40,0x80,  //正向流水灯
            0x40,0x20,0x10,0x8,0x4,0x2,0x1,0x0 };//反向流水灯
void main()
{
    MatrixLED_SwitchL = 1;
    DigitalTube_SwitchL = 1;
    LED_SwitchH = 0;

    // 死循环
    while (1) {
        if (Int_Key_IsSw1Pressed() == 1) {  //判断按键按下  按下函数返回1
            u8 i;
            MatrixLED_SwitchL = 1;
            DigitalTube_SwitchL = 1;
            LED_SwitchH = 1;
            Int_Buzzer_Buzz();
            for (i = 0; i < 16; i++)
            {
                P0 = tab[i];
                Delay_1ms(100);
            }
        }
        if (Int_Key_IsSw2Pressed() == 1) {  //判断按键按下  按下函数返回1
            u8 bit_Sel = 6;
            MatrixLED_SwitchL = 1;
            DigitalTube_SwitchL = 0;
            LED_SwitchH = 0;
            Int_Buzzer_Buzz();
            bit_Sel <<= 3;  // P17... P10   00xxx000  连接P15-P13
            P1 &= 0xC7;  // 0b11000111 与1不变，与0变0，将P15-P13置为0
            P1 |= bit_Sel;
            P0 = 0x3F;
        }
        if (Int_Key_IsSw3Pressed() == 1) {  //判断按键按下  按下函数返回1
            u8 i;
            MatrixLED_SwitchL = 0;
            DigitalTube_SwitchL = 1;
            LED_SwitchH = 0;
            Int_Buzzer_Buzz();
            for (i = 0; i < 26; i++)
            {
                P0 = tab[i];
                Delay_1ms(100);
            }
        }
        if (Int_Key_IsSw4Pressed() == 1) {
            MatrixLED_SwitchL = 1;
            DigitalTube_SwitchL = 1;
            LED_SwitchH = 0;
            Int_Buzzer_Buzz();
        }
    }
}
/**
 * *********************************************
 * 8051 project
 * *********************************************
*/
// #include "Com_Util.h"
// #include "Int/Int_LED.h"
// #include "Int/Int_DigitalTube.h"
// #include "Int/Int_Key.h"
// #include "Int_Matrix.h"
// #include "Int/Int_Buzzer.h"
// #include "Int/Int_MatrixLED.h"
// #include "Dri/Dri_Timer.h"

// void main()
// {
//     u8 i = 0;
//     // 定义数组 要显示的文字信息
//     u8 picture[26] = { 0xF8, 0x0A, 0xEC, 0xAF, 0xEC, 0x8A, 0xF8, 0x00,
//                         0x10, 0xF9, 0x97, 0xF1, 0x88, 0xAA, 0xFF, 0xAA,0x88, 0x00,
//                         0x14, 0x0A, 0xF5, 0x92, 0x92, 0xF5,0x0A, 0x14 };

//     Int_MatrixLED_Init();

//     // 死循环
//     while (1)
//     {
//         // 让显示信息滚动
//         if (i < 26)
//         {
//             // 正常图案添加到显示数组中
//             Int_MatrixLED_ShiftPixels(picture[i]);
//         }
//         else
//         {
//             // 显示空行
//             Int_MatrixLED_ShiftPixels(0x00);
//         }

//         // 延时200ms
//         Delay_1ms(500);

//         i++;

//         if (i == 34)
//         {
//             i = 0;
//         }
//     }
// }