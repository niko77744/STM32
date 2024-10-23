/**
 * *********************************************
 * 8051 project
 * *********************************************
*/
#include "Com_Util.h"
#include "Dri/Dri_Timer0.h"
#include "Dri/Dri_INT0.h"
#include "Dri/Dri_IIC.h"

#include "Int/Flow_LED.h"
#include "Int/Int_EEPROM.h"
#include "Int/Int_MatrixLED.h"

void main()
{
    // char str[40] = "hello word! build successfully";
    // Int_EEPROM_WriteBytes(6, str, strlen(str));


    //1.д�����
    // u8 picture[26] = { 0xF8, 0x0A, 0xEC, 0xAF, 0xEC, 0x8A, 0xF8, 0x00,0x10, 0xF9, 0x97, 0xF1, 0x88, 0xAA, 0xFF, 0xAA,
    //                             0x88, 0x00, 0x14, 0x0A, 0xF5, 0x92, 0x92, 0xF5,0x0A, 0x14 };
    // Int_EEPROM_WriteBytes(0, picture, 26);
    // while (1);

    // 2.��ȡ����
    u8 i;
    u8 picture[26];

    // ��EEPROM�ж�ȡ
    Int_EEPROM_ReadBytes(0, picture, 26);

    // ����LED��ʼ��
    Int_MatrixLED_Init();
    LED_SwitchH = 0;

    // ��ѭ��
    while (1)
    {
        // ����ʾ��Ϣ����
        if (i < 26)
        {
            // ����ͼ����ӵ���ʾ������
            Int_MatrixLED_ShiftPixels(picture[i]);
        }
        else
        {
            // ��ʾ����
            Int_MatrixLED_ShiftPixels(0);
        }

        // ��ʱ200ms
        Delay_1ms(200);

        i++;

        if (i == 34)
        {
            i = 0;
        }
    }
}

