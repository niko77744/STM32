#include "Com_Delay.h"


void Delay_us(uint16_t us) {
    volatile uint32_t temp = 0;
    // ��ʱ�� SysTick ģ��ÿ�� 1/72MHz �뼴  1/72 ΢���һ����
    SysTick->CTRL = 5;
    SysTick->LOAD = us * 72;
    SysTick->VAL = 0;
    do
    {
        // systick ����0��Ϊ1 ��ȡ���
        temp = SysTick->CTRL & SysTick_CTRL_COUNTFLAG;
    } while (temp == 0);

    SysTick->CTRL &= ~SysTick_CTRL_ENABLE;
}


void Delay_ms(uint16_t ms) {
    while (ms--)
    {
        Delay_us(1000);
    }
}
void Delay_s(uint16_t s) {
    while (s--)
    {
        Delay_ms(1000);
    }
}
