#include "Int_MatrixSW.h"

// 定义逐行查找数组
static Int_MatrixSW_rows[4] = {0xFE, 0xFD, 0xFB, 0xF7};

u8 Int_MatrixSW_IsSWPressed()
{
    u8 i;
    // 逐行查找按键
    for (i = 0; i < 4; i++)
    {
        P2 = Int_MatrixSW_rows[i];
        // 逐列查找按键是否被按下
        if (P24 == 0)
        {
            Delay1ms(10); // 消除抖动
            while (P24 == 0)
                ; // 等待按键抬起
            return 5 + 4 * i;
        }
        if (P25 == 0)
        {
            Delay1ms(10); // 消除抖动
            while (P25 == 0)
                ; // 等待按键抬起
            return 6 + 4 * i;
        }
        if (P26 == 0)
        {
            Delay1ms(10); // 消除抖动
            while (P26 == 0)
                ; // 等待按键抬起
            return 7 + 4 * i;
        }
        if (P27 == 0)
        {
            Delay1ms(10); // 消除抖动
            while (P27 == 0)
                ; // 等待按键抬起
            return 8 + 4 * i;
        }
    }
    return 0;
}