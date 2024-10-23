#include "App_Mode.h"
#include "Dri_Timer2.h"
#include "Int_OLED.h"
#include "Int_Key.h"
#include "Int_Motor.h"

// 定义变量保存已选择的模式 默认是遥控模式
static Enum_Mode s_mode = REMOTE;
// 定义倒计时的值
static u16 down_count = 0;
// 定义倒计时标志位
static bit is_down = 0;
// 定义屏幕清空标志位
static bit is_oled_clear = 0;

// 回调函数 定时器2，用于倒计时3s
void App_Mode_Timer2Callback()
{
    if (is_down)
    {
        down_count--;
    }
}

/**
 * @brief 模式选择初始化
 */
void App_Mode_Init()
{
    // 默认遥控模式
    s_mode = REMOTE;
    // 开始计时
    is_down = 1;
    down_count = 4000;
    // 重新显示屏幕信息
    is_oled_clear = 1;

    // 回调函数注册
    Dri_Timer2_RegisterCallback(App_Mode_Timer2Callback);
}

/**
 * @brief 返回按键按下后所选择的模式
 * @return 模式
 */
Enum_Mode App_Mode_GetMode()
{
    // 判断按键是否按下
    if (Int_Key_GetSw1Status() == 1)
    {
        // 停止电机
        Int_Motor_SetLeftSpeed(0);
        Int_Motor_SetRightSpeed(0);

        // 切换到下个模式
        s_mode++;
        if (s_mode > AVOIDANCE)
        {
            s_mode = REMOTE;
        }

        // 标记屏幕更新
        is_oled_clear = 1;

        // 设置倒计时的起始值
        is_down = 1;
        down_count = 4000;
    }


    // 屏幕显示模式
    if (is_oled_clear)
    {
        Int_OLED_Clear();

        switch (s_mode)
        {
        case REMOTE:
            Int_OLED_DisplayStr(0, 0, "Mode:REMOTE");
            break;
        case PATROL:
            Int_OLED_DisplayStr(0, 0, "Mode:PATROL");
            break;
        case AVOIDANCE:
            Int_OLED_DisplayStr(0, 0, "Mode:AVOIDANCE");
            break;
        }

        is_oled_clear = 0;
    }

    // 屏幕显示倒计时
    if (is_down)
    {
        Int_OLED_DisplayNum(0, 1, (down_count / 1000) + 1);
        if (down_count < 100)
        {
            Int_OLED_DisplayStr(0, 1, "GO!");
            is_down = 0;
        }

        return STOP;
    }


    // 按键没有按下，返回上次的模式
    return s_mode;
}