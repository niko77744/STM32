/*
    分析：
    两个标记 ：是否允许测距，是否完成测距
    两个定时器： 定时器0计数、定时器2间隔100ms
    一个外部中断：INT0，下降沿触发
    两条线：ECHO(P32,超声回应线，测得结果以高电平回应，距离*2=高电平的时间)和TRIG(P33，触发线，发送一个10us的高电平)

    原理：
    一、测距方式：TRIG拉高10us，然后拉低，表示开启测距，测完后ECHO就会返回一段时间的高电平，用定时器的计数0可以得到高电平的时间 （只计数，不触发中断）
    二、计算公式：1/11059200 * 12 计一个数的时间（机器周期 秒） * 340米每秒 / 2 * 1000(转换成mm) * 记的数 =2/11 * 记的数
    三、什么时候开始和停止计数：P32引脚,是外部中断0，也是定时器0的计数开关[有GATE和INTO以或门控制，再打开TR1]，ECHO接的就是P32，只要超声波返回高电平，那么定时器0就开始计数，只要ECHO回到低电平就会停止计数。
    四、什么时候去TH0和TL0取数：通过INT0中断，可以配置下降沿触发中断，只要触发我们就可以确定TH0和TL0已经完成数据的存储
    五、注意：超声波每次测距需要间隔至少60ms，否则会影响上一次的返回声波，所以需要定时器2来定时100ms，100ms后允许测距，定时器2是选择16位重装载

    代码：
    初始化函数：
        注册回调函数（回调函数用于100ms计数）
        定时器0基本配置（用于计数，不会触发中断仅仅用作计数，GAME置1，ECHO一拉过就开始计数）
        外部中断0配置（下降沿触发，ECHO信号一拉就触发，标志着测距结果已经传递给单片机）
        信号线初始化（默认都处于低电平）

    测距函数
        判断是否允许测距（计数记到100）
            TRIG信号触发，开始测距
        判断是否完成测距
            读取脉冲计数器并处理
            修改保存距离的变量
            重置脉冲计数器
        返回测距结果

 */


#include "Int_Range.h"
static u8 Allowable_Range;
static bit isFinishRange = 0;
static u16 RangeResult = 0;

void Int_Range_Timer2Callback() {
    if (Allowable_Range < 100)
    {
        Allowable_Range++;
    }
}
void Int_Range_Init() {
    // 将Int_Range_Timer2Callback注册到定时器2 100ms
    Dri_Timer2_RegisterCallback(Int_Range_Timer2Callback);

    // 初始化定时器0 计数
    EA = 1;
    ET0 = 0; //因为不需要中断，只需要计数
    TR0 = 1;
    TMOD &= 0xF0;   // 第四位 GATE，C/T，M1，M2设置为 10 01 16位定时器
    TMOD |= 0x09;
    TH0 = 0;
    TL0 = 0;

    //初始化外部中断0
    IT0 = 1; //下降沿触发
    EX0 = 1; //开关
    PX0 = 1; //设置优先级

    // 初始化第一次允许直接测距
    Allowable_Range = 100;

    // 重置超声模块的控制引脚
    RANGE_TRIG = 0;
    RANGE_ECHO = 0;
}


// 允许测距 100ms 返回上一次测距的结果
u16 Int_Range_GetRange() {
    if (100 == Allowable_Range)
    {
        Allowable_Range = 0;

        // 向超声模块发送触发信号，开始测距，维持10us以上的高电平
        RANGE_TRIG = 1;
        Delay_10us();
        RANGE_TRIG = 0;
    }

    if (isFinishRange == 1)
    {
        isFinishRange = 0;
        // 从TH0和TH0取数
        // RangeResult = TL0 + (TH0 << 8);  //错误
        RangeResult = TL0;
        RangeResult += TH0 << 8;

        // 计算距离 mm
        RangeResult *= 2;
        RangeResult /= 11;
        // RangeResult *= 0.182F;

        // 复位
        TL0 = 0;
        TH0 = 0;
    }

    return RangeResult;
}


void Dri_INT0_Handler() interrupt 0
{
    // if (IE0 == 1) { //错误，不会像串口一样判断TI和RI
    isFinishRange = 1;
}


