#include "Dri_Key.h"

void Driver_Key_init(void) {
    RCC->APB2ENR |= (RCC_APB2ENR_IOPFEN | RCC_APB2ENR_AFIOEN);

    // 12 �������� CNF10 MODE00  ODR1
    // 34 �������� CNF10 MODE00  ODR0
    GPIOF->CRH |= (GPIO_CRH_CNF8_1 | GPIO_CRH_CNF9_1 | GPIO_CRH_CNF10_1 | GPIO_CRH_CNF11_1);
    GPIOF->CRH &= ~(GPIO_CRH_CNF8_0 | GPIO_CRH_CNF9_0 | GPIO_CRH_CNF10_0 | GPIO_CRH_CNF11_0);
    GPIOF->ODR |= (KEY1 | KEY2);
    GPIOF->ODR &= ~(KEY3 | KEY4);

    GPIOF->CRH &= ~(GPIO_CRH_MODE8 | GPIO_CRH_MODE9 | GPIO_CRH_MODE10 | GPIO_CRH_MODE11);

    //�ⲿ�ж����üĴ���  0101��PF[x]����
    AFIO->EXTICR[2] |= (AFIO_EXTICR3_EXTI8_PF | AFIO_EXTICR3_EXTI9_PF | AFIO_EXTICR3_EXTI10_PF | AFIO_EXTICR3_EXTI11_PF);

    EXTI->IMR |= (EXTI_IMR_MR8 | EXTI_IMR_MR9 | EXTI_IMR_MR10 | EXTI_IMR_MR11);
    EXTI->FTSR |= (EXTI_FTSR_TR8 | EXTI_FTSR_TR9);
    EXTI->RTSR |= (EXTI_FTSR_TR10 | EXTI_FTSR_TR11);

    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(EXTI9_5_IRQn, 3);
    NVIC_SetPriority(EXTI15_10_IRQn, 3);
    NVIC_EnableIRQ(EXTI9_5_IRQn);
    NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void EXTI9_5_IRQHandler(void) {
    /* ���һ������Ҫ����жϱ�־λ */
    EXTI->PR |= (EXTI_PR_PR8 | EXTI_PR_PR9);
    // ����
    Delay_ms(10);
    if ((GPIOF->IDR & KEY1) == 0)  //&1����
    {
        Dri_LED_Toogle(LED1);
    }
    else if ((GPIOF->IDR & KEY2) == 0)
    {
        Dri_LED_Toogle(LED2);
    }
}


void EXTI15_10_IRQHandler(void) {
    /* ���һ������Ҫ����жϱ�־λ */
    EXTI->PR |= (EXTI_PR_PR10 | EXTI_PR_PR11);
    // ����
    Delay_ms(10);
    if ((GPIOF->IDR & KEY3) != 0)  //&1����
    {
        Dri_LED_Toogle(LED3);
    }
    else if ((GPIOF->IDR & KEY4) != 0)
    {
        Dri_LED_Toogle(LED1);
        Dri_LED_Toogle(LED2);
        Dri_LED_Toogle(LED3);
    }
}
