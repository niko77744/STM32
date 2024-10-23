#include <STC89C5xRC.H>
#include <INTRINS.H>

// 类型别名
typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;

// 定义数组，保存每个数字对应的段选信息
u8 number_codes[10] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F  // 9
};

// 定义数组，显示缓存，保存数码管每个位置要显示的数字的段选信息
u8 digital_buffer[9];

// 延时函数的定义
void Delay_1ms(u16 ms)
{
    unsigned char data i, j;

    // 循环 ms 次
    for (; ms > 0; ms--) {
        _nop_();
        i = 2;
        j = 199;
        do
        {
            while (--j)
                ;
        } while (--i);
    }
}

/**
 * @brief 给数码管指定位置指定段选信息
 *
 * @param pos 位置， 从左向右依次 0 ~ 7
 * @param code 段选信息
 */
void DigitalTube_Single(u8, u8);

/**
 * @brief 设置显示缓存
 *
 * @param number 要显示的完整的数字（十进制表示）
 */
void DigitalTube_SetBuffer(u32);

/**
 * @brief 将显示缓存中的数据显示到数码管
 */
void DigitalTube_Refresh();


void main()
{
    // 关闭流水灯
    P34 = 0;

    // 打开数码管
    P36 = 0;

    // 设置要显示的数字
    DigitalTube_SetBuffer(123456789);


    // 死循环 不停刷新
    while (1)
    {
        DigitalTube_Refresh();

    }

}


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
    for (i = 0; i < 9; i++)
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
    for (i = 8; i >= 0; i--)
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
    u8 i, j;
    // 遍历缓存数组
    for (i = 0; i < 2; i++)
    {
        DigitalTube_Single(i, digital_buffer[i]);
        for (j = 0; j < 9; j++)
        {
            // 调用函数 指定位置 指定段选信息
            DigitalTube_Single(1, digital_buffer[j]);
            Delay_1ms(1000);
        }
    }
}