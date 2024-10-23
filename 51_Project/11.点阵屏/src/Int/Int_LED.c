#include "Int_LED.h"

u8 led_code = 0X01;
bit led_flag;  //控制方向
u8 led_init = 0xFF;  //0b 1111 1111 默认code码
u8 led_time_flag, led_time = 1000;  //控制流动时间

// 普通流水灯  0亮1灭
void Int_Waterfall_Light() {
    // P0 = ~led_code;
    P0 = led_init ^ led_code;
    led_code <<= 1;  //0b 0000 0001 -> 0b 0000 0010 第二颗就亮了
    if (0 == led_code)
    {
        led_code = 0X01;
    }
    Delay_1ms(500);
}

// 来回流水灯
void Int_GoBackWaterfall_Light() {

    P0 = led_init ^ led_code;        // 1111 1111 ^ 0000 0001 异或(同0异1) == 1111 1110
    Delay_1ms(500);
    if (0x80 == led_code) {     // 1000 0000
        led_flag = 0;           //  右位移
    }
    else if (0x01 == led_code) { // 0000 0001
        led_flag = 1;           //  左位移
    }
    led_flag ? (led_code <<= 1) : (led_code >>= 1); //flag==1左移，flag==0右移
}


// 来回加减速流水灯
void Int_TimeGoBackWaterfall_Light() {
    Delay_1ms(led_time);

    P0 = led_init ^ led_code;        // 1111 1111 ^ 0000 0001 异或(同0异1) == 1111 1110
    if (0x80 == led_code) {     // 1000 0000
        led_flag = 0;           //  右位移
    }
    else if (0x01 == led_code) { // 0000 0001
        led_flag = 1;           //  左位移
    }

    if (led_time > 100) {
        led_time = 100;
        led_time_flag = 0;
    }
    else if (led_time < 10) {
        led_time = 100;
        led_time_flag = 1;
    }

    led_flag ? (led_code <<= 1) : (led_code >>= 1); //flag==1左移，flag==0右移
    led_time_flag ? (led_time += 10) : (led_time -= 10);
}

花式流水灯
void Int_FancyWaterfall_Light() {
    u8 i;
    u8 tab[] = { 0x1,0x2,0x4,0x8,0x10,0x20,0x40,0x80,  //正向流水灯
        0x40,0x20,0x10,0x8,0x4,0x2,0x1,0x0,  //反向流水灯
        0x55,0xaa,0x55,0xaa,0x55,0xaa,0x0, //隔灯闪烁
        0x0f,0xf0,0x0f,0xf0,0x0,  //高四盏 底四盏闪烁
        0xcc,0x33,0xcc,0x33,0xcc,0x33,0x0 };  //隔两盏闪烁
    for (i = 0;i < 35;i++) {
        P0 = tab[i];
        Delay_1ms(100);
    }
}

