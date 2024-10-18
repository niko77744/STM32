#include "Driver_Key.h"


void Driver_KEY_Init(void) {
    RCC->APB2ENR |= (RCC_APB2ENR_IOPFEN | RCC_APB2ENR_AFIOEN);

    // 12 上拉输入 CNF10 MODE00  ODR1 (另一侧接地，不能配置为输出，因为无法检测到下降沿)
    // 34 下拉输入 CNF10 MODE00  ODR0
    GPIOF->CRH |= (GPIO_CRH_CNF8_1 | GPIO_CRH_CNF9_1 | GPIO_CRH_CNF10_1 | GPIO_CRH_CNF11_1);
    GPIOF->CRH &= ~(GPIO_CRH_CNF8_0 | GPIO_CRH_CNF9_0 | GPIO_CRH_CNF10_0 | GPIO_CRH_CNF11_0);
    GPIOF->ODR |= (GPIO_ODR_ODR8 | GPIO_ODR_ODR9);
    GPIOF->ODR &= ~(GPIO_ODR_ODR10 | GPIO_ODR_ODR11);

    GPIOF->CRH &= ~(GPIO_CRH_MODE8 | GPIO_CRH_MODE9 | GPIO_CRH_MODE10 | GPIO_CRH_MODE11);

    //外部中断配置寄存器  0101：PF[x]引脚
    AFIO->EXTICR[2] |= (AFIO_EXTICR3_EXTI8_PF | AFIO_EXTICR3_EXTI9_PF | AFIO_EXTICR3_EXTI10_PF | AFIO_EXTICR3_EXTI11_PF);

    //1：开放来自线x上的中断请求
    EXTI->IMR |= (EXTI_IMR_MR8 | EXTI_IMR_MR9 | EXTI_IMR_MR10 | EXTI_IMR_MR11);
    // 下降沿
    EXTI->FTSR |= (EXTI_FTSR_TR8 | EXTI_FTSR_TR9);
    // 上升沿
    EXTI->RTSR |= (EXTI_FTSR_TR10 | EXTI_FTSR_TR11);

    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(EXTI9_5_IRQn, 3);
    NVIC_SetPriority(EXTI15_10_IRQn, 3);
    NVIC_EnableIRQ(EXTI9_5_IRQn);
    NVIC_EnableIRQ(EXTI15_10_IRQn);
}

void EXTI9_5_IRQHandler(void) {
    if ((EXTI->PR & EXTI_PR_PR8) != 0)
    {
        /* 务必一定必须要清除中断标志位 在该位中写入1可以清除它 */
        EXTI->PR |= EXTI_PR_PR8;
        // 防抖
        Delay_ms(10);
        if ((GPIOF->IDR & GPIO_IDR_IDR8) == 0) {
            printf("KEY1 press\n");
        }
    }
    else if ((EXTI->PR & EXTI_PR_PR9) != 0)
    {
        /* 务必一定必须要清除中断标志位 在该位中写入1可以清除它 */
        EXTI->PR |= EXTI_PR_PR9;
        // 防抖
        Delay_ms(10);
        if ((GPIOF->IDR & GPIO_IDR_IDR9) == 0) {
            printf("KEY2 press\n");
        }
    }
}


void EXTI15_10_IRQHandler(void) {
    if ((EXTI->PR & EXTI_PR_PR10) != 0)
    {
        /* 务必一定必须要清除中断标志位 在该位中写入1可以清除它 */
        EXTI->PR |= EXTI_PR_PR10;  //Pending Register 的缩写，即挂起寄存器

        // 防抖
        Delay_ms(10);
        if ((GPIOF->IDR & GPIO_IDR_IDR10) != 0)  //&1不变
        {
            printf("KEY3 press\n");
        }
    }
    else if ((EXTI->PR & EXTI_PR_PR11) != 0)
    {
        /* 务必一定必须要清除中断标志位 在该位中写入1可以清除它 */
        EXTI->PR |= EXTI_PR_PR11;  //Pending Register 的缩写，即挂起寄存器

        // 防抖
        Delay_ms(10);
        if ((GPIOF->IDR & GPIO_IDR_IDR11) != 0)
        {
            printf("KEY4 press\n");
        }
    }
}
