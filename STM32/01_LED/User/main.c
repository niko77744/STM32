#include <stdint.h>

int main() {
    // 一、LED1 PA0 二、LED2 PA1  LED3 PA8
    // 1.设置时钟
    *(uint32_t*)(0x40021000 + 0x18) = 0x04;
    // 2.设置工作模式 推挽和最大输出50MHZ
    *(uint32_t*)(0x40010800 + 0x00) = 0x77;  // 33 77
		*(uint32_t*)(0x40010800 + 0x04) = 0x03;  // 03 07
    // 3.让PA0输出低电平有效
    *(uint32_t*)(0x40010800 + 0x0C) = 0xFEFC;


    while (1){}
}

