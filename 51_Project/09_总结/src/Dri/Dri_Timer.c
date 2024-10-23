#include "Dri_Timer.h"


// 结构体包含 1.函数指针，作为参数的回调函数 2.作为参数的触发频率 参数ms一次 3，作为TriggerFrequency的临时变量
typedef struct {
    Timer0_Callback callback;
    u16 TriggerFrequency;
    u16 temp;
}My_Timer0;

// 定义结构体数组，长度为4，类型是My_Timer0结构体
static My_Timer0 s_timer0_callbacks[MAX_CALLBACK_COUNT];

// 初始化定时器0
void Dri_Timer0_Init() {
    u8 i;

    EA = 1;     // 总开关
    ET0 = 1;    // Timer0开关
    TL0 = 0x66; // 两个寄存器里存储的值，溢出则触发中断
    TH0 = 0xFC;
    // TL0 = 64614;
    // TH0 = 64614 >> 8;
    TMOD &= 0xF0;  // 11110000    TMOD8位，高4位是定时器1的，低4位是定时器0的  这里将低4位置为0
    TMOD |= 0x01;  // 0000 0001   低4位 GATE是打开定时器(0)/计数器  C/T是选择定时器(0)/计数器  M0和M1控制计数模式
    TR0 = 1;       // TR允许开始计数

    for (i = 0; i < MAX_CALLBACK_COUNT; i++)
    {
        // 将结构体数组的每一个元素的.callback和.TriggerFrequency置为0，初始化
        s_timer0_callbacks[i].callback = NULL;
        s_timer0_callbacks[i].TriggerFrequency = 0;
    }
}

// 给定时器0 注册回调函数 参数1：回调函数  参数2：频率TriggerFrequency 参数ms一次
bit Dri_Timer0_setInterval(Timer0_Callback callback, u16 TriggerFrequency) {
    u8 i;
    for (i = 0; i < MAX_CALLBACK_COUNT; i++)
    {
        // 避免同一个回调函数重复注册
        if (callback == s_timer0_callbacks[i].callback)
        {
            return 1;
        }

        // 如果当前位置是空，将callback和触发频率添加到此处
        if (s_timer0_callbacks[i].callback == NULL)
        {
            s_timer0_callbacks[i].callback = callback;
            s_timer0_callbacks[i].TriggerFrequency = TriggerFrequency;
            return 1;
        }
    }
    return 0;
}



//  注销定时器0的回调函数
bit Dri_Timer0_clearInterval(Timer0_Callback callback) {
    u8 i;
    for (i = 0; i < MAX_CALLBACK_COUNT; i++)
    {
        if (callback == s_timer0_callbacks[i].callback)
        {
            s_timer0_callbacks[i].callback = NULL;
            return 1;
        }
    }
    return 0;
}

// 1ms触发一次中断
void Dri_Timer0_Handler() interrupt 1
{
    u8 i = 0;
    for (i = 0; i < MAX_CALLBACK_COUNT; i++)
    {
        // 执行数组不为空的元素
        if (s_timer0_callbacks[i].callback != NULL)
        {
            // TriggerFrequency ms执行一次回调函数
            if (s_timer0_callbacks[i].temp-- == 0)
            {
                s_timer0_callbacks[i].temp = s_timer0_callbacks[i].TriggerFrequency;
                s_timer0_callbacks[i].callback();
            }
        }
    }

    // 重新初始化寄存器的初始值  到溢出需要1ms 溢出触发中断
    TL0 = 0x66;
    TH0 = 0xFC;
}
