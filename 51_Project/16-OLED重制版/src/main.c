/**
 * *********************************************
 * 8051 project
 * *********************************************
    IIC：注意：接收字节像移位器，每次只移动1位
    EEPROM：两个错误：三元和重置len  len <= page_remain
        Dri_IIC_SendAck(i == (len - 1) ? 1 : 0);
    OLED：注意：宏定义不要写错了  注意：D/C#
        #define OLED_Data 0x40
        #define OLED_Command 0x00
        #define SetDisplayOn 0xAF
        #define SetDisplayOff 0xAE
        #define SetPumpLevel 0x14
        注意计算器别点错了，位运算
        显示函数while 循环变量i初始值和重置i=0
 *
*/
#include "Com_Util.h"
#include "Dri/Dri_IIC.h"
#include "Int/Int_EEPROM.h"
#include "Int_OLED.h"


void main()
{
    char str[17];
    // 写入EEPROM
    u8 s_EEPROMfonts[] = "ni hao";
    Int_EEPROM_WriteBytes(0, s_EEPROMfonts, strlen(s_EEPROMfonts));

    // 初始化OLED
    Int_OLED_Init();
    Int_OLED_Clear();
    // 读取EEPROM
    Int_EEPROM_ReadBytes(0, str, strlen(s_EEPROMfonts));
    // 显示EEPROM
    Int_OLED_DisplayStr(1, 0, str);
    Int_OLED_DisplayNum(1, 1, 123);
    while (1);
}

