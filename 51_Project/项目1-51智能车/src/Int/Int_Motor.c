/*
    电机原理：
        转动的控制：同一个电机产生电势差
        转动速度的控制：方波占空比, 控制一个电机的PWM高低，另一个0，形成电压降

    代码实现：
        四个变量：左轮方向，左轮速度，右轮方向，右轮速度
        初始化：
            注册Timer2的回调函数，实现控制占空比
        回调函数：
            通过速度函数拿到方向，通过调用执行次数控制占空比，执行代表高电平
            // 正向  A1高  A2低  flag = 1
            // 反向  A1低  A2高  flag = 0
        左轮速度：可以接受负数，代表反向
        右轮速度：可以接受负数，代表反向

        测试代码：
        Dri_Timer2_Init();
        Int_Motor_Init();

        Int_Motor_SetLeftSpeed(40);
        Delay_1ms(1000);
        Int_Motor_SetLeftSpeed(-40);
        Delay_1ms(1000);
        Int_Motor_SetLeftSpeed(0);
        Int_Motor_SetRightSpeed(40);
        Delay_1ms(1000);
        Int_Motor_SetRightSpeed(-40);
        Delay_1ms(1000);
        Int_Motor_SetRightSpeed(0);
*/

#include "Int_Motor.h"
#include "Dri_Timer2.h"
#include "MATH.H"

static u8 s_LeftWheelSpeed = 0;  // 设定40ms一个周期，值代表这40ms内高电平的时间
static u8 s_RightWheelSpeed = 0;

static bit s_LeftWheelDirection = 0;  // 1向前 0向后  利用差速转向
static bit s_RightWheelDirection = 0;

void Int_Timer2_MotorCallBack() {
    // 利用定时器2控制左轮占空比 
    static u8 count;
    if (count == 40)
    {
        count = 0;
    }
    count++;

    if (count < s_LeftWheelSpeed)
    {
        // 正向  A1高  A2低  flag = 1
        // 反向  A1低  A2高  flag = 0
        MOTOR_A1 = s_LeftWheelDirection;
        MOTOR_A2 = !s_LeftWheelDirection;
    }
    else {
        MOTOR_A1 = 0;
        MOTOR_A2 = 0;
    }

    if (count < s_RightWheelSpeed)
    {
        // 正向  A1高  A2低  flag = 1
        // 反向  A1低  A2高  flag = 0
        MOTOR_B1 = s_RightWheelDirection;
        MOTOR_B2 = !s_RightWheelDirection;
    }
    else {
        MOTOR_B1 = 0;
        MOTOR_B2 = 0;
    }
}

void Int_Motor_Init() {
    MOTOR_A1 = 0;
    MOTOR_A2 = 0;
    // 将MotorCallBack注册到定时器2，Timer2的初始化放在主函数统一初始化
    Dri_Timer2_RegisterCallback(Int_Timer2_MotorCallBack);
}

void Int_Motor_SetLeftSpeed(char speed) {
    // 可以接收负数，表示反向
    s_LeftWheelDirection = speed > 0 ? 1 : 0;
    speed = abs(speed);
    if (speed > 40)
    {
        speed = 40;
    }
    s_LeftWheelSpeed = speed;
}

void Int_Motor_SetRightSpeed(char speed) {
    // 可以接收负数，表示反向
    s_RightWheelDirection = speed > 0 ? 1 : 0;
    speed = abs(speed);
    if (speed > 40)
    {
        speed = 40;
    }
    s_RightWheelSpeed = speed;
}