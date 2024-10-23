#include "Int_Matrix.h"
#include "./Com/Com_Util.h"

/**
 * @brief 检测矩阵按键中哪个按键被按下
 *
 * @return u8 按键编号
 */
u8 Int_Matrix_CheckKey(void) {
    u8 i;

    // 定义数组，保存每一行 P2寄存器的值
    /*
    第一行： 1111 1110
    第二行： 1111 1101
    第三行： 1111 1011
    第四行： 1111 0111
    */
    u8 lines[4] = {
        0xFE,
        0xFD,
        0xFB,
        0xF7 };
    for (i = 0; i < 4; i++)
    {
        P2 = lines[i];

        // 检测P24引脚 第一列
        if (P24 == 0)
        {
            // 消抖
            Delay_1ms(10);
            // 再次判断
            if (P24 == 0)
            {
                // 按键抬起结束循环
                while (P24 == 0)
                    ;
                // 此时按键抬起 返回按键编号
                return 5 + i * 4;
            }
        }

        // 检测P25引脚 第二列
        if (P25 == 0)
        {
            // 消抖
            Delay_1ms(10);
            // 再次判断
            if (P25 == 0)
            {
                // 按键抬起结束循环
                while (P25 == 0)
                    ;
                // 此时按键抬起 返回按键编号
                return 6 + i * 4;
            }
        }

        // 检测P26引脚 第三列
        if (P26 == 0)
        {
            // 消抖
            Delay_1ms(10);
            // 再次判断
            if (P26 == 0)
            {
                // 按键抬起结束循环
                while (P26 == 0)
                    ;
                // 此时按键抬起 返回按键编号
                return 7 + i * 4;
            }
        }

        // 检测P27引脚 第四列
        if (P27 == 0)
        {
            // 消抖
            Delay_1ms(10);
            // 再次判断
            if (P27 == 0)
            {
                // 按键抬起结束循环
                while (P27 == 0)
                    ;
                // 此时按键抬起 返回按键编号
                return 8 + i * 4;
            }
        }
    }
    // 没有按下任何按键
    return 0;
}
