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
    u8 i;
    // 关闭流水灯,1开
    P34 = 0;
    // 关闭数码管，0开
    P36 = 1;
    // 打开点阵屏，0开
    P35 = 0;
    for (i = 0; i < 8; i++)
    {
        s_matrix_line_pixels[i] = 0x00;
    }

    Dri_Timer0_Init();
    Dri_Timer0_setInterval(Int_MatrixLED_Refresh, 1);
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

    // for (int i = 0; i < 2; i++)
    // {
    //     for (int j = 0; j < 8; j++)
    //     {
    //         s_matrix_line_pixels[j] = pixels[j + 8 * i];
    //     }
    // }
}

/**
 * @brief 让数组中的元素整体后移，0位置添加新元素
 *
 * @param new_line
 */
void Int_MatrixLED_ShiftPixels(u8 new_line)
{

    u8 i;
    // 原数组整体后移 将前面元素的值赋值给后面  从后向前遍历
    for (i = 7; i > 0; i--)
    {
        s_matrix_line_pixels[i] = s_matrix_line_pixels[i - 1];
    }

    // 给0位置设置新的值
    s_matrix_line_pixels[0] = new_line;
}

/**
 * @brief 刷新显示信息 结合定时器中断，作为定时器中断的回调函数
 *
 */
void Int_MatrixLED_Refresh()
{
    static u8 i = 0;

    // 第一行的时候，向595移位器输入1，以后的输入0
    if (i == 0)
    {
        SER = 1;
    }
    else
    {
        SER = 0;
    }

    // 先熄灭当前行的LED
    P0 = 0XFF;

    // 将 SER 信息存入移位寄存器  SCK 上升沿
    SCK = 0;
    SCK = 1;

    // 将移位寄存器的信息放入存储寄存器 RCK 上升沿
    RCK = 0;
    RCK = 1;

    // 设置当前行的显示信息
    P0 = ~s_matrix_line_pixels[i];

    // i 自增
    i++;
    // 刷到最后一行，从头再来
    if (i == 8)
    {
        i = 0;
    }
}
