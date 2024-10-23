#include "Int_MatrixLED.h"
#include "Dri_Timer.h"
#include "Com_Util.h"

// 定义数组，存储点阵屏每行的显示信息
static s_matrix_line_pixels[8];

/**
 * @brief 点阵LED初始化
 *
 */
void Int_MatrixLED_Init(void)
{
    // 关闭流水灯,1开
    P34 = 0;
    // 关闭数码管，0开
    P36 = 1;
    // 打开点阵屏，0开
    P35 = 0;

    Dri_Timer0_Init();
    Dri_Timer0_setInterval(Int_MatrixLED_Refresh, 1000);
}

/**
 * @brief 设置点阵屏要显示的信息 给 存储点阵屏每行的显示信息 的数组赋值
 *
 * @param pixels 点阵屏信息，长度必须是8，每个元素必须是8bit整数
 */
void Int_MatrixLED_SetPixels(u8 pixels[8])
{
    u8 i;
    // 给 s_matrix_line_pixels 赋值
    for (i = 0; i < 8; i++)
    {
        s_matrix_line_pixels[i] = pixels[i];
    }
}

/**
 * @brief 刷新显示信息 结合定时器中断，作为定时器中断的回调函数
 *
 */
void Int_MatrixLED_Refresh()
{
    static u8 i = 0;


    // 先熄灭当前行的LED
    // P0 = 0XFF;
    // 设置当前行的显示信息
    P0 = ~s_matrix_line_pixels[i];

    // 第一行的时候，向595移位器输入1，以后的输入0
    if (i == 0)
    {
        SER = 1;
    }
    else
    {
        SER = 0;
    }

    // 将 SER 信息存入移位寄存器  SCK 上升沿
    SCK = 0;
    SCK = 1;
    SCK = 0;

    // 将移位寄存器的信息放入存储寄存器 RCK 上升沿
    RCK = 0;
    RCK = 1;
    RCK = 0;

    // i 自增
    i++;
    // 刷到最后一行，从头再来
    if (i == 8)
    {
        i = 0;
    }
}