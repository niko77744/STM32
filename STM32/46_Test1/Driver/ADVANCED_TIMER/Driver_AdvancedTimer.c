#include "Driver_AdvancedTimer.h"

void AdvancedTimer_Count_Init(TIM_TypeDef* TIMx) {
    if (TIMx == TIM1)
    {
        RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
    }
    else if (TIMx == TIM8)
    {
        RCC->APB2ENR |= RCC_APB2ENR_TIM8EN;
    }
    else {
        return;
    }
    TIMx->CR1 &= ~TIM_CR1_DIR;
    TIMx->DIER |= TIM_DIER_UIE;
    TIMx->PSC = 7199; // 0.1ms
    TIMx->ARR = 9999; // 1s

    TIMx->CR1 |= TIM_CR1_URS;
    TIMx->EGR |= TIM_EGR_UG;

    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(TIM1_UP_IRQn, 4);
    NVIC_EnableIRQ(TIM1_UP_IRQn);
}
void AdvancedTimer_Start(TIM_TypeDef* TIMx) {
    TIMx->CR1 |= TIM_CR1_CEN;
}



