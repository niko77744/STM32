/*
    目标：把超声测距和电机驱动结合
    思路：
        1.能在main函数调用
        2.将测距结果返回，如果小于300mm，开始转向，测距需要一直调用，电机还需要一直接收距离
            Int_Range_Init已经将测距注册给定时器2
            判断 < 300mm 转向
            否则 直行
*/
#include "App_Avoidance.h"
#include "Int_Motor.h"
#include "Int_Range.h"

static u16 range;
/**
 * @brief 避障控制函数
 */
void APP_AvoidanceControl() {
    range = Int_Range_GetRange();
#ifdef DEBUG
    Int_OLED_DisplayNum(1, 0, range);
#endif

    if (range > 300)
    {
#ifdef DEBUG
        Int_OLED_DisplayStr(1, 1, "Go Straight!");
#endif
        Int_Motor_SetLeftSpeed(40);
        Int_Motor_SetRightSpeed(40);

    }
    else {
#ifdef DEBUG
        Int_OLED_DisplayStr(1, 2, "Turn Right!");
#endif
        Int_Motor_SetLeftSpeed(10);
        Int_Motor_SetRightSpeed(-10);
    }
}