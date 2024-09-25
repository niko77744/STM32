#include "Driver_AdvancedTimer.h"

void Driver_AdvancedTimer1_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

    // 复用推挽
    GPIOA->CRH |= (GPIO_CRH_MODE8 | GPIO_CRH_CNF8_1);
    GPIOA->CRH &= ~GPIO_CRH_CNF8_0;


    /* 3. 时基单元的配置 ?频率是2Hz的PWM*/
    TIM1->ARR = 4999;
    TIM1->PSC = 7199;  // 1Mhz 
    TIM1->CR1 &= ~TIM_CR1_DIR;
    TIM1->RCR = 4; // Repetition counter   设置REP重复计数器的值  

    /* 4. 输出部分配置*/
    TIM1->CCMR1 &= ~TIM_CCMR1_CC1S;  // 00 输出  
    TIM1->CCR1 = 2500;  //  捕获/比较通道1的值 (Capture/Compare 1 value)    
    TIM1->CCER &= ~TIM_CCER_CC1P;  // 1：OC1低电平有效。  //!!!!!!!!!!!  重复计数器的值完后输出高电平
    TIM1->CCER |= TIM_CCER_CC1E;  // 输入/捕获1输出使能 (Capture/Compare 1 output enable)   

    TIM1->CCMR1 |= (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1); // CCXS  // IC: ICXPSC  ICXF(filter)     
    TIM1->CCMR1 &= ~TIM_CCMR1_OC1M_0;  // OC  OCXM(110：PWM模式1－ 在向上计数时)    

    TIM1->BDTR |= TIM_BDTR_MOE;  // brake dead   MOE: 主输出使能 (Main output enable) 

    /* 手动产生一个更新事件,并且设置不进入中断*/
    TIM1->CR1 |= TIM_CR1_URS;  // 更新请求源 (Update request source) 1只有溢出才会产生中断
    TIM1->EGR |= TIM_EGR_UG;  // 产生更新事件 (Update generation)  重新初始化计数器，并产生一个更新事件。

    TIM1->DIER |= TIM_DIER_UIE;  //UIE：允许更新中断 (Update interrupt enable) 
    TIM1->CR1 |= TIM_CR1_CEN;   //使能定时器


    // TIM1_UP_IRQn: 当 TIM1 的计数器达到设定的自动重载值时，会产生更新事件，进而触发这个中断。这个中断可以用于实现定时功能、测量时间间隔、生成周期性的信号等。
    // TIM1_CC_IRQn: 代表定时器 1 的捕获 / 比较中断。当 TIM1 的输入捕获通道检测到特定的输入信号边沿（如上升沿、下降沿或任意边沿），或者当定时器的计数器值与设定的比较值相等时，会产生捕获 / 比较事件，触发这个中断。这个中断可以用于测量输入信号的频率、占空比，实现脉冲宽度调制（PWM）输出的反馈控制等。
    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(TIM1_UP_IRQn, 3);
    NVIC_EnableIRQ(TIM1_UP_IRQn);
}


void TIM1_UP_IRQHandler(void) {
    // 开的是UIE
    TIM1->SR &= ~TIM_SR_UIF;
    TIM1->CR1 &= ~TIM_CR1_CEN;   //使能定时器
}
