#include "Dri_Timer2.h"

// 定义变量记录已注册的回调函数数量
static u8 s_timer2_callback_count = 0;
// 定义数组保存 Timer2 的回调函数
static Timer2_Callback s_Timer2_callbacks[MAX_CALLBACK_COUNT];

/**
 * @brief 定时器2 初始化
 *
 */
void Dri_Timer2_Init()
{
    u8 i;
    // 第一步 打开定时器开关 ------------------------------------------------------------
    // 打开中断总开关
    EA = 1;
    ET2 = 1;


    // 第二步 选择定时器工作模式 --------------------------------------------------------
    // 设置为16位自动重装载
    // TF2 = 0; //溢出标志 需要手动置为0
    // C_T2 = 0; //内部定时器
    RCLK = 0;
    TCLK = 0;
    CP_RL2 = 0;


    // 第三步 设置脉冲计数器的初始值   Timer2 对应 TH2 TL2  ------------------------------
    // ① 计算每个计数脉冲(机器周期)需要多长时间        12 / 11059200 s
    // ② 计算 1 毫秒需要计数多少次                    0.001 / (12 / 11059200)
    // ③ 计算脉冲计数器的起始值                       65536 - 0.001 / (12 / 11059200) = 64614
    RCAP2L = 64614;
    RCAP2H = 64614 >> 8;  //这里不要写反了
    TH2 = RCAP2H;
    TL2 = RCAP2L;

    // 第四步 设置开始计数（启动定时器）---------------------------------------------------
    TR2 = 1;

    // 初始化 回调函数数组 --------------------------------------------------------------------------
    for (i = 0; i < s_timer2_callback_count; i++)
    {
        s_Timer2_callbacks[i] = NULL;
    }
}

/**
 * @brief 给定时器2 注册回调函数
 *
 * @param callback 要注册回调函数
 * @return bit 1表示注册成功 0表示注册失败
 */
bit Dri_Timer2_RegisterCallback(Timer2_Callback callback)
{
    u8 i;
    // 避免同一个回调函数重复注册
    for (i = 0; i < s_timer2_callback_count; i++)
    {
        // 如果该回调函数在数组中已经存在
        if (s_Timer2_callbacks[i] == callback)
        {
            return 1;
        }
    }

    if (s_timer2_callback_count < MAX_CALLBACK_COUNT)
    {
        s_Timer2_callbacks[s_timer2_callback_count++] = callback;
        // s_timer2_callback_count++;
        return 1;
    }


    return 0;
}

/**
 * @brief 注销定时器2的回调函数
 *
 * @param callback 要注销的回调函数
 * @return bit 1表示注销成功 0表示注销失败
 */
bit Dri_Timer2_DeregisterCallback(Timer2_Callback callback)
{
    u8 i;
    bit flag = 0; // 标记是否注册过该回调函数
    // 遍历数组，找到 callback
    for (i = 0; i < s_timer2_callback_count; i++)
    {

        if (flag)
        {
            // 第一次不执行这里，执行else，然后执行s_timer2_callback_count-1次这里，刚好也移位这么多次
            // 后面元素前移  标记后到这里这里i会先+1
            s_Timer2_callbacks[i - 1] = s_Timer2_callbacks[i];
        }
        else
        {
            if (s_Timer2_callbacks[i] == callback)
            {
                flag = 1;
            }
        }
    }

    if (flag == 1)
    {
        s_timer2_callback_count--;
    }

    return flag;
}

// 定义 Timer2 的中断服务程序， 调用数组 s_Timer2_callbacks 中的回调函数
void Dri_Timer2_Handler() interrupt 5
{
    u8 i;
    // 遍历数组
    for (i = 0; i < s_timer2_callback_count; i++)
    {
        s_Timer2_callbacks[i](); // 调用
    }

    // 定时器2的中断标志位复位
    TF2 = 0;
}
