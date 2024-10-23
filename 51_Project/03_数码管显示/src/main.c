/**
 * *********************************************
 * 8051 project
 * *********************************************
*/
#include "Com_Util.h"

// 1.设置1-9的默认数组
u8 Digital_Number_codes[10] = { 0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F };
// 00111111  00000110  01011011  01000111  01100110  01101101  01111101  00000111  01111111  01101111

// 2.设置一个要显示到Digital的数组
u8 Digital_Buffer_codes[8];

// 3. 控制位选和段选 将结果输入到CU
void Int_DigitalTube_Single(u8, u8);

// 4.向Digital_Buffer数组写入数据
void Int_DigitalTube_SetBuffer(u32);

// 5.从Buffer数组取数调用3.Int_DigitalTube_Single()显示到Digital
void Int_DigitalTube_Refresh();

void main()
{
    // 注意变量的定义一定要写咋最前面
    u8 n = 0, time = 125;  //time循环125次(里面有Refresh(),一次是8ms,一共约1s)再让n+1
    // 关闭LED，打开数码管
    P34 = 0;
    P36 = 0;


    while (1)
    {
        if (0 == time)
        {
            Int_DigitalTube_SetBuffer(n++);
            time = 125;
            // if (60 == n)
            // {
            //     n = 0;
            // }
        }

        Int_DigitalTube_Refresh();
        time--;
    }
}

void Int_DigitalTube_Single(u8 location, u8 dat) {
    // 1. 处理location
    // P1端口的P15,P14,P13连接38译码器（输出低电平）控制阴极
    // location 1-7 == 000 , 001...

    location <<= 3;    //左移三位与P1端口对齐
    P1 &= 0xC7;        //与1不改变原值，与0将P13-P15置为0  0b11000111
    P1 |= location;     //或0不改变原值
    // 0b00xxx000 location
    // 0buu000uuu P1
    // 0buuxxxuuu P1|=  //x确定,u不确定，将P15-P13插入到了P1当中并且没有改变P1的其他数


    // 2. 传入的是该数的段选，所以直接给P0即可
    // Int_DigitalTube_Single(5, Digital_Number_codes[1]);
    //  dat = P0; ?????
    P0 = dat;
}

void Int_DigitalTube_SetBuffer(u32 number) {
    u8 i;

    // 先将显示缓存数组中的信息重置
    for (i = 0; i < 8; i++)
    {
        Digital_Buffer_codes[i] = 0x00;
    }

    for (i = 7; i >= 0; i--)  //这里是7不是8
    {
        Digital_Buffer_codes[i] = Digital_Number_codes[number % 10];  // 将传入的number取低位的段选存入到数组末尾
        number /= 10;

        // 重要
        if (0 == number)
        {
            break;
        }
    }
}


void Int_DigitalTube_Refresh() {
    u8 i, j; //i控制第几个数字，j控制显示什么
    // 遍历buffer数组即可,只要刷新的够快，就能一直显示
    for (i = 0; i < 8; i++)  //time：执行一轮需要约8msj
    {
        for (j = 0; j < 8; j++)
        {
            Int_DigitalTube_Single(i, Digital_Buffer_codes[j]);
        }
        Delay_1ms(1);
    }
}

