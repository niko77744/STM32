/**
 * *********************************************
 * 8051 project
 * *********************************************
*/
#include "Com_Util.h"

// 1.设置0-9 - . 的默认数组
u8 Digital_Number_codes[21] = { 0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F,
                                0xBF,0x86,0xDB,0xC7,0xE6,0xED,0xFD,0x87,0xFF,0xEF,
                                0x40 };

// 2.设置一个要显示到Digital的数组 只有8个数，所以设置为8，存储的也是段选
u8 Digital_Buffer_codes[8];

// 3. 控制位选和段选 将结果输入到CU 真正的显示函数
void Int_DigitalTube_Single(u8, u8);

// 4.向Digital_Buffer数组写入数据 将十进制的数字每一位拆下来放的 段选 在buffer数组最后
void Int_DigitalTube_SetBuffer(u32, u8);

// 5.从Buffer数组取数调用3.Int_DigitalTube_Single(i, Digital_Buffer_codes[i])  显示到Digital
void Int_DigitalTube_Refresh();

void main()
{
    // 关闭LED，打开数码管
    P34 = 0;
    P36 = 0;

    Int_DigitalTube_SetBuffer(12678, 2);  //!!! 注意别写在while里面了

    while (1)
    {
        Int_DigitalTube_Refresh();
    }
}

void Int_DigitalTube_Single(u8 location, u8 dat) {
    // 1. 处理location
    // P1端口的P15,P14,P13连接38译码器（输出低电平）控制阴极
    // location 1-7 == 000 , 001...

    location <<= 3;    //左移三位与P1端口对齐
    P1 &= 0xC7;        //!!!!与1不改变原值，与0将P13-P15置为0  0b11000111
    P1 |= location;     //!!!!或0不改变原值
    // 0b00xxx000 location
    // 0buu000uuu P1
    // 0buuxxxuuu P1|=  //x确定,u不确定，将P15-P13插入到了P1当中并且没有改变P1的其他数


    // 2. 传入的是该数的段选，所以直接给P0即可
    // Int_DigitalTube_Single(5, Digital_Number_codes[1]);
    //  !!!!!注意别写反了dat = P0; ?????
    P0 = dat;
}

void Int_DigitalTube_SetBuffer(u32 number, u8 Point_postion) {
    u8 i, len = 0;
    u32 temp;
    temp = number;
    for (i = 0; i < 8; i++)
    {
        temp /= 10;
        len++;
        if (0 == temp)
        {
            break;
        }
    }

    // !!先将显示缓存数组中的信息重置
    for (i = 0; i < 8; i++)
    {
        Digital_Buffer_codes[i] = 0x00;
    }
    for (i = 7; i >= 0; i--)  //!!!!注意这里是7不是8
    {
        if (7 + Point_postion - len == i) {  //p2  4  //p3  5  长度=6  i=8  i+1-p   //Point_postion+7-len
            Digital_Buffer_codes[7 + Point_postion - len] = Digital_Number_codes[number % 10 + 10];
        }
        else
        {
            Digital_Buffer_codes[i] = Digital_Number_codes[number % 10];  // 将传入的number取低位的段选存入到数组末尾
        }

        number /= 10;

        // 非常重要!!!!!
        if (0 == number)
        {
            Digital_Buffer_codes[i - 1] = Digital_Number_codes[20];
            break;
        }
    }
}

void Int_DigitalTube_Refresh() {
    u8 i;
    // 遍历buffer数组即可,只要遍历(刷新)的够快，就看不出来是依次只亮一个
    for (i = 0; i < 8; i++)  //time：执行一轮需要约8ms
    {
        Int_DigitalTube_Single(i, Digital_Buffer_codes[i]);
        Delay_1ms(1);
    }
}