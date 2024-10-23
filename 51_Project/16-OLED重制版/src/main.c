/**
 * *********************************************
 * 8051 project
 * *********************************************
    IIC��ע�⣺�����ֽ�����λ����ÿ��ֻ�ƶ�1λ
    EEPROM������������Ԫ������len  len <= page_remain
        Dri_IIC_SendAck(i == (len - 1) ? 1 : 0);
    OLED��ע�⣺�궨�岻Ҫд����  ע�⣺D/C#
        #define OLED_Data 0x40
        #define OLED_Command 0x00
        #define SetDisplayOn 0xAF
        #define SetDisplayOff 0xAE
        #define SetPumpLevel 0x14
        ע������������ˣ�λ����
        ��ʾ����while ѭ������i��ʼֵ������i=0
 *
*/
#include "Com_Util.h"
#include "Dri/Dri_IIC.h"
#include "Int/Int_EEPROM.h"
#include "Int_OLED.h"


void main()
{
    char str[17];
    // д��EEPROM
    u8 s_EEPROMfonts[] = "ni hao";
    Int_EEPROM_WriteBytes(0, s_EEPROMfonts, strlen(s_EEPROMfonts));

    // ��ʼ��OLED
    Int_OLED_Init();
    Int_OLED_Clear();
    // ��ȡEEPROM
    Int_EEPROM_ReadBytes(0, str, strlen(s_EEPROMfonts));
    // ��ʾEEPROM
    Int_OLED_DisplayStr(1, 0, str);
    Int_OLED_DisplayNum(1, 1, 123);
    while (1);
}

