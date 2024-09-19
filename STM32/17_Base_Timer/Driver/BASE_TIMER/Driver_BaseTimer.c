#include "Driver_BaseTimer.h"

void Driver_BaseTimer6_Init(void) {
    RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;

    TIM6->PSC = 7199;  // Prescaler value 预分频  在每一次更新事件时，PSC的数值被传输到实际的预分频寄存器中
    TIM6->ARR = 9999;  // ReLoad value  初始值是0xFFFF，不能|=，|完还是0xFFFF
    // TIM6->PSC = 7200 - 1;
    // TIM6->ARR = 10000 - 1;
    // 开启中断使能
    TIM6->DIER |= TIM_DIER_UIE;


    // 更新请求源 (Update request source)   默认0  
    TIM6->CR1 |= TIM_CR1_URS;
    // UG：产生更新事件 (Update generation)  手动产生一个更新事件，将PSC ARR寄存器刷写到影子寄存器
    TIM6->EGR |= TIM_EGR_UG;   // 由于URS为1，所以第一次不会进入中断

    // 第一次会以72MHz的PSC进入中断，然后才将7199刷到影子寄存器，所以需要手动产生一个更新事件去更新影子寄存器，第一步设置了UG手动产生一个更新事件，但是这个事件还是会进入中断，第二步在UG之前前设置URS更新请求源， 默认URS=0，设置了UG=1还是会产生中断  URS设置为1，只有上溢出才会产生中断

    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(TIM6_IRQn, 15);
    NVIC_EnableIRQ(TIM6_IRQn);

    TIM6->CR1 |= TIM_CR1_CEN;
}


void TIM6_IRQHandler(void) {
    if ((TIM6->SR & TIM_SR_UIF) != 0)
    {
        TIM6->SR &= ~TIM_SR_UIF;
        printf("Timer6 Start\n");
        Driver_LED_Toggle(LED2);
    }
}
