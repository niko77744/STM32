#include <STDIO.H>
#include <STRING.H>
#include <MATH.H>
#include "Int_DigitalTube.h"
#include "Com_Util.h"

static u8 DigitalTube_SegmentSel_Codes[10] = { 0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F };
static u8 DigitalTube_Buffer_Codes[8];

void Int_DigitalTube_Init(void)
{
    // 关闭流水灯
    LED_SwitchH = 0;
    // 开启数码管
    DigitalTube_SwitchL = 0;
}

//静态显示
void Int_DigitalTube_StaticDisplay(u8 display_number) {
    Int_DigitalTube_Single(display_number, DigitalTube_SegmentSel_Codes[display_number]);
}



// 真正的显示函数 控制位选和段选 将结果输入到CU  通过控制P1控制38译码器重新选择
void Int_DigitalTube_Single(u8 bit_Sel, u8 segment_Sel) {
    bit_Sel <<= 3;  // P17... P10   00xxx000  连接P15-P13
    P1 &= 0xC7;  // 0b11000111 与1不变，与0变0，将P15-P13置为0
    P1 |= bit_Sel;

    P0 = segment_Sel; 
}

// 将输入的内容存入buffer数组
void Int_DigitalTube_SetBuffer(u32 ObjNumber) {
    u8 i;
    for (i = 0; i < 8; i++)
    {
        DigitalTube_Buffer_Codes[i] = 0x00;
    }

    for (i = 7; i >= 0; i--)
    {
        DigitalTube_Buffer_Codes[i] = DigitalTube_SegmentSel_Codes[ObjNumber % 10];
        ObjNumber /= 10;
        if (0 == ObjNumber)
        {
            break;
        }
    }
}

// 负数存入buffer
void Int_DigitalTube_SetNegativeBuffer(float number) {

    char i;	  // 循环变量
    char index; // 最后一个有效字符下标
    u8 str[15];
    bit has_signed = 0; // 有符号标记
    bit has_dot = 0;	// 有小数点标记

    if (number < 0)
    {
        has_signed = 1;
    }

    // 先将显示缓存数组中的信息重置
    for (i = 0; i < 8; i++)
    {
        DigitalTube_Buffer_Codes[i] = 0x00;
    }

    // 将 number 绝对值处理为字符串
    sprintf(str, "%f", fabs(number));

    // 计算最后一个有效字符下标
    index = strlen(str) - 1;

    // 去掉小数后面的 0
    for (i = index; i >= 0; i--)
    {
        if (str[i] == 48)  //ASCII码 48是0
        {
            str[i] = 0;
            index--;
        }
        else
        {
            break;
        }
    }

    // 从后先前遍历字符串, 并存入 buffer 数组
    for (i = 7; i >= 0 && index >= 0; i--, index--)
    {
        // 如果有小数点
        if (str[index] == 46)  //ASCII码 46是小数点
        {
            has_dot = 1;
            i++;
            continue;
        }

        DigitalTube_Buffer_Codes[i] = DigitalTube_SegmentSel_Codes[str[index] - 48];
        //break;

        //如果有小数点
        if (has_dot)
        {
            DigitalTube_Buffer_Codes[i] += 0x80;
            has_dot = 0;
        }
    }
    // 如果有负号
    if (has_signed && i >= 0)
    {
        DigitalTube_Buffer_Codes[i] = 0x40;
    }
}

// 遍历buffer数组 刷新Int_DigitalTube_Single函数的显示
void Int_DigitalTube_Refresh(void) {
    u8 i;
    for (i = 0; i <= 7; i++)
    {
        Int_DigitalTube_Single(i, DigitalTube_Buffer_Codes[i]);
        Delay_1ms(1);
    }
    // for (i = 8; i >= 1; i--)
    // {
    //     Int_DigitalTube_Single(i - 1, buffer[i - 1]);
    //     Delay_1ms(1);
    // }
}