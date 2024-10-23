#include "Dri_Tmer0Interruput.h"
#include <STDIO.H>

void Dri_Timer0Interrupt_Init()
{
    // 打开中断开关
    EA = 1;
    // 打开定时器中断
    ET0 = 1;
    // 定义中断触发方式

    TMOD &= 0xF0;
    TMOD |= 0x01; // 设置定时器模式
    TL0 = 0x66;   // 设置定时初始值
    TH0 = 0xFC;   // 设置定时初始值
    TF0 = 0;      // 清除TF0标志
    TR0 = 1;      // 定时器0开始计时
}

// 定义注册功能函数
bit Dri_Timer0Interrupt_RegisiterFunction(CallbackFunction Function)
{
    u8 i;
    // 检查功能是否注册过
    for (i = 0; i < MaxFunctionCount; i++)
    {
        if (FunctionArray[i] == Function)
            return 1;
    }

    // 如果函数没有注册过，注册该函数
    for (i = 0; i < MaxFunctionCount; i++)
    {
        if (FunctionArray[i] == NULL)
        {
            FunctionArray[i] = Function;
            return 1;
        }
    }
    // 如果功能数组已满，且不存在该函数
    return 0;
}

// 定义注销功能函数
bit Dri_Timer0Interrupt_DeregisiterFunction(CallbackFunction Function)
{
    u8 i;
    // 遍历数组内是否有该函数
    for (i = 0; i < MaxFunctionCount; i++)
    {
        if (FunctionArray[i] == Function)
        {
            FunctionArray[i] = NULL;
            return 1;
        }
    }
    return 0;
}

void Timer0Interrupt_Handler() interrupt 1
{
    u8 i;

    // 重置定时器装载值,每隔1ms对进行1次中断
    TL0 = 64614;
    TH0 = 64614 >> 8;
    // 遍历调用功能数组内的功能
    for (i = 0; i < MaxFunctionCount; i++)
    {
        if (FunctionArray[i] != NULL)
        {
            FunctionArray[i]();
        }
    }
}

void toggle_LED1()
{
    static u16 count = 500;
    count--;
    if (count == 0)
    {

        if (!P0)
            P0 = 0x01;
        P0 = ~P0;
        P0 <<= 1;
        P0 = ~P0;
        count = 500;
    }
}