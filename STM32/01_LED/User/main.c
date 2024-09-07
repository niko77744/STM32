#include "stm32f10x.h"

// 写成宏，方便移植
// #define setbit(x,y) x|=(1<<y) //将X的第Y位置1
// #define clrbit(x,y) x&=~(1<<y) //将X的第Y位清0
// 与&改成0，需要取反   |改成1

int main() {

    // 1.打开时钟  将IOPAEN设置为1
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    // 2.1 设置LED1的工作模式  Port x configuration  CNF  00通用推挽  11通用开漏
    GPIOA->CRL &= ~GPIO_CRL_CNF0;  // 设置为00
    // 配置为输出模式11(最大输出50MHZ)   00为输入模式
    GPIOA->CRL |= GPIO_CRL_MODE0;  // 设置为11

    // 2.2 设置LED2的工作模式
    GPIOA->CRL &= ~GPIO_CRL_CNF1;  // 设置为00
    GPIOA->CRL |= GPIO_CRL_MODE1;  // 设置为11

    // 2.3 设置LED3的工作模式
    GPIOA->CRH &= ~GPIO_CRH_CNF8;  // 设置为00
    GPIOA->CRH |= GPIO_CRH_MODE8;  // 设置为11

    // 3.让PA0，PA1和PA8输出低电平有效
    GPIOA->ODR &= ~GPIO_ODR_ODR0;  // 设置为0 输出低电平点亮
    GPIOA->ODR &= ~GPIO_ODR_ODR1;
    GPIOA->ODR &= ~GPIO_ODR_ODR8;

    while (1);
}

