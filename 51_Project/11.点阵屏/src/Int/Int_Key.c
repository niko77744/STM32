#include "./Int/Int_Key.h"

bit Int_Key_IsSw1Pressed() {

    // 判断sw1是否被按下
    if (0 == SW1)
    {
        // 消抖 延时10ms
        Delay_1ms(10);
        // 延时之后还是按下的状态
        if (0 == SW1)
        {
            // 等待按键抬起，循环结束
            while (0 == SW1);
            return 1;
        }
    }
    return 0;
}

bit Int_Key_IsSw2Pressed() {

    // 判断sw1是否被按下
    if (0 == SW2)
    {
        // 消抖 延时10ms
        Delay_1ms(10);
        // 延时之后还是按下的状态
        if (0 == SW2)
        {
            // 等待按键抬起，循环结束
            while (0 == SW2);
            return 1;
        }
    }
    return 0;
}

bit Int_Key_IsSw3Pressed() {

    // 判断sw1是否被按下
    if (0 == SW3)
    {
        // 消抖 延时10ms
        Delay_1ms(10);
        // 延时之后还是按下的状态
        if (0 == SW3)
        {
            // 等待按键抬起，循环结束
            while (0 == SW3);
            return 1;
        }
    }
    return 0;
}


bit Int_Key_IsSw4Pressed() {

    // 判断sw1是否被按下
    if (0 == SW4)
    {
        // 消抖 延时10ms
        Delay_1ms(10);
        // 延时之后还是按下的状态
        if (0 == SW4)
        {
            // 等待按键抬起，循环结束
            while (0 == SW4);
            return 1;
        }
    }
    return 0;
}