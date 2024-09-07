#include "stm32f10x.h"

// д�ɺ꣬������ֲ
// #define setbit(x,y) x|=(1<<y) //��X�ĵ�Yλ��1
// #define clrbit(x,y) x&=~(1<<y) //��X�ĵ�Yλ��0
// ��&�ĳ�0����Ҫȡ��   |�ĳ�1

int main() {

    // 1.��ʱ��  ��IOPAEN����Ϊ1
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    // 2.1 ����LED1�Ĺ���ģʽ  Port x configuration  CNF  00ͨ������  11ͨ�ÿ�©
    GPIOA->CRL &= ~GPIO_CRL_CNF0;  // ����Ϊ00
    // ����Ϊ���ģʽ11(������50MHZ)   00Ϊ����ģʽ
    GPIOA->CRL |= GPIO_CRL_MODE0;  // ����Ϊ11

    // 2.2 ����LED2�Ĺ���ģʽ
    GPIOA->CRL &= ~GPIO_CRL_CNF1;  // ����Ϊ00
    GPIOA->CRL |= GPIO_CRL_MODE1;  // ����Ϊ11

    // 2.3 ����LED3�Ĺ���ģʽ
    GPIOA->CRH &= ~GPIO_CRH_CNF8;  // ����Ϊ00
    GPIOA->CRH |= GPIO_CRH_MODE8;  // ����Ϊ11

    // 3.��PA0��PA1��PA8����͵�ƽ��Ч
    GPIOA->ODR &= ~GPIO_ODR_ODR0;  // ����Ϊ0 ����͵�ƽ����
    GPIOA->ODR &= ~GPIO_ODR_ODR1;
    GPIOA->ODR &= ~GPIO_ODR_ODR8;

    while (1);
}

