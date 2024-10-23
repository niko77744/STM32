#include "Com_Util.h"
#include "Int_DigitalTube.h"

// 函数的定义 指定位置指定段选信息
void DigitalTube_Single(u8 pos, u8 cod)
{
    // 实现位选 ---------------------------------
    // 处理 pos，让 pos 的有效数字与 p1 的 P15~P13 三个位对齐
    pos <<= 3;
    // 处理 P1， 将P15~P13 三个位置0，其他位不变
    P1 &= 0xC7;
    // 将 pos 的有效数字赋值到 P15~P13 三个位
    P1 |= pos;


    // 段选 ------------------------------------------
    P0 = cod;

}


// 定义函数  设置显示缓存
void DigitalTube_SetBuffer(u32 number)
{
    u8 i;

    // 先将显示缓存数组中的信息重置
    for (i = 0; i < 8; i++)
    {
        digital_buffer[i] = 0x00;
    }

    // 将 number 每个位的数取出，找到对应的段选信息，存入缓存数组
    /*
        2784

        %10 = 4, /10=278
        %10 = 8, /10=27
        %10 = 7, /10=2
        %10 = 2, /10=0
    */
    for (i = 7; i >= 0; i--)
    {
        digital_buffer[i] = number_codes[number % 10];
        number /= 10;
        if (number == 0)
        {
            break;
        }
    }
}

// 定义函数 将显示缓存中的数据显示到数码管
void DigitalTube_Refresh()
{
    u8 i;
    // 遍历缓存数组
    for (i = 0; i <= 7; i++)
    {
        // 调用函数 指定位置 指定段选信息
        DigitalTube_Single(i, digital_buffer[i]);
        // 添加占空比 时间延时
        Delay_1ms(1);
    }
}
