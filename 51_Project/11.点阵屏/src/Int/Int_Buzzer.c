#include "Int_Buzzer.h"

/**
 * @brief 蜂鸣器发出 500Hz 的声音, 响 0.1s
 */
void Int_Buzzer_Buzz()
{
    u8 count = 100;
    while (count > 0)
    {
        P46 = ~P46;
        Delay_1ms(1);       // 延时 1ms 
        count--;
    }
}

void Int_Buzzer_frequency(u8 type, u16 Buzzer_MsTime) {
    // 定义变量保存 每次循环延时 多少个 10us
    u16 t;
    // 定义变量保存循环次数
    u16 count;

    // 根据音乐发音类型决定频率进而决定 t 的值
    switch (type)
    {
    case 1: t = 100000 / (400 * 2); break;
    case 2: t = 100000 / (450 * 2); break;
    case 3: t = 100000 / (506 * 2); break;
    case 4: t = 100000 / (541 * 2); break;
    case 5: t = 100000 / (600 * 2); break;
    case 6: t = 100000 / (675 * 2); break;
    case 7: t = 100000 / (759 * 2); break;
    default: t = 100000 / (500 * 2);
    }

    // 根据t的值，计算循环次数
    count = Buzzer_MsTime * 100 / t;

    // 循环
    while (count > 0)
    {
        P46 = ~P46;
        Delay_10us(t);
        count--;
    }
}
