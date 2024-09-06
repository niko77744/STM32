#include <stdint>

int main() {
    // 1.设置时钟
    *(uint32_t*)(0x40021000 + 0x18) = 0x04;
    // 2.设置工作模式 推挽和最大输出50MHZ
    *(uint32_t*)(0x40010800 + 0x00) = 0x03;
    // 3.让PA0输出低电平有效
    *(uint32_t)(0x40010800 + 0x0C) = 0xFFFE;

    while (1);
}
