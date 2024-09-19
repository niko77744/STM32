#include "Com_SysTick.h"
uint32_t SysTick_Now = 0;



/**
 * @brief 配置并启用系统滴答定时器(SysTick)
 *
 * 本函数配置SysTick定时器，以产生定时中断，支持系统滴答和时间延迟功能。
 * SysTick定时器配置为使用AHB时钟源，设置滴答周期为1ms，并启用了定时器。
*/
void Com_SysTick_Init() {
    // 1.配置时钟源为AHB 72MHz
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE;

    // 2.配置重装载值  72MHz = 72 000 000Hz  LoAD最大为24M，所以不能直接配1s触发
    // 配置1ms触发一次  72MHz/1000 - 1(溢出左移一位)   0 到 71999，总共 72000 个计数值
    SysTick->LOAD = 72000 - 1;

    // 3.开启中断 优先级默认15
    SysTick->CTRL |= SysTick_CTRL_TICKINT;

    // 4.打开使能
    SysTick->CTRL |= SysTick_CTRL_ENABLE;
}


/**
 * @brief 获取当前系统滴答数
 *
 * 此函数用于获取当前系统的滴答数，以便跟踪自系统启动以来的时间（以滴答为单位）。
 *
 * @return uint32_t 返回当前的系统滴答数
*/
static uint32_t SysTick_GetTick(void) {
    return SysTick_Now;
}


/**
 * @brief 延时函数，使用SysTick定时器实现延时
 *
 * 该函数主要用于在程序中实现一段时间的延时，与时间相关的操作中非常有用
 *
 * @param Delay 延时的单位是滴答数（ticks），延时的精确时间取决于系统的时钟频率
*/
void SysTick_Delay(uint32_t Delay)
{
    // 获取当前的滴答数作为开始计时的参考点
    uint32_t tickstart = SysTick_GetTick();
    // 将传入的Delay赋给wait，表示需要延时的滴答数
    uint32_t wait = Delay;
    // 因为延时的计算方式是从0开始累加，所以需要额外增加一个滴答数来确保延时的准确性
    wait += 1;

    // 循环直到经过的时间达到或超过所需的延时时间
    while ((SysTick_GetTick() - tickstart) < wait);
}





/**
 * @brief SysTick中断服务例程
 *
 * 每当SysTick定时器产生中断时，此函数会被调用。
 * 它的主要作用是递增SysTick_Now变量，用于系统时间的计数。
*/
void SysTick_Handler(void)
{
    // 递增SysTick_Now变量，表示时间有进展
    SysTick_Now++;
}
