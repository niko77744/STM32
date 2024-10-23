/*
    按键思路：按键初始状态是1，将检测函数注册到定时器2(将不断检测按键对应引脚的状态，也就是将 1bit的状态不断填充到status的低位，如果status=0表示连续8个状态都是0，表示被按下。)
    消抖：如果上一次是未被按下，本次状态是按下，则可以表明按下，同时完成消抖，下降沿
*/


#include "Int_Key.h"
#include "Dri_Timer2.h"


// 记录每个按键采样到的信号
u8 key1_status = 0xff;
u8 key2_status = 0xff;


// 记录每个按键上一次的状态，1表示抬起，0表示按下
bit sw1_last_status = 1;
bit sw2_last_status = 1;

// 初始化函数
void Int_KeyDetection_Timer2Callback() {
    key1_status <<= 1;
    key1_status |= KEY_SW1;


    key2_status <<= 1;
    key2_status |= KEY_SW2;
}


/**
 * @brief 按键初始化, 将检测的回调函数注册到定时器2中
 */
void Int_Key_Init() {
    Dri_Timer2_RegisterCallback(Int_KeyDetection_Timer2Callback);
}

/**
 * @brief 判断按键1的状态
 *
 * @return 0:按键无变化 1:按键正在被按下（下降沿） 2:按键正在抬起（上升沿）
 *
 */
u8 Int_Key_GetSw1Status() {

    // 按键未被按下
    if (sw1_last_status == 1 && key1_status == 1)
    {
        return 0;
    }

    // 按键按下 下降沿
    if (sw1_last_status == 1 && key1_status == 0)
    {
        sw1_last_status = 0;  //上次状态，0表示按下，1表示抬起
        return 1;
    }

    // 按键抬起 上升沿
    if (sw1_last_status == 0 && key1_status == 1)
    {
        sw1_last_status = 1;
        return 2;
    }
    return 0;

}

/**
 * @brief 判断按键2的状态
 *
 * @return 0:按键无变化 1:按键正在被按下（下降沿） 2:按键正在抬起（上升沿）
 *
 */
u8 Int_Key_GetSw2Status() {

    // 按键未被按下
    if (sw2_last_status == 1 && key2_status == 1)
    {
        return 0;
    }

    // 按键按下 下降沿
    if (sw2_last_status == 1 && key2_status == 0)
    {
        sw2_last_status = 0;
        return 1;
    }

    // 按键抬起 上升沿
    if (sw2_last_status == 0 && key2_status == 1)
    {
        sw2_last_status = 1;
        return 2;
    }
    return 0;

}

