#include "Dri_Key.h"


/**
 * Driver_Key3_init函数用于初始化按键3的驱动。
 * 该函数配置了GPIO、AFIO、EXTI和NVIC的相关寄存器，以确保按键3能够正常工作，并且能够在按键按下时产生中断。
 */
void Driver_Key3_init(void) {
    // 1.开启时钟 GPIOF AFIO辅助功能IO时钟使能 1开启
    RCC->APB2ENR |= RCC_APB2ENR_IOPFEN;  //69行解注释
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

    // 2.配置PF10工作模式  下拉输入  MDOE：00; CNF：10;  ODR：0
    GPIOF->CRH &= ~GPIO_CRH_MODE10;
    GPIOF->CRH |= GPIO_CRH_CNF10_1;
    GPIOF->CRH &= ~GPIO_CRH_CNF10_0;
    GPIOF->BRR |= GPIO_BRR_BR10;

    // 3.AFIO(外部中断配置寄存器)选择EXTI10  设置EXTICR3在数组下标的2   配置为0101表示打开GPIOPF
    AFIO->EXTICR[2] |= AFIO_EXTICR3_EXTI10_PF;

    // 4.EXTI  
    // 4.1屏蔽寄存器  EXTI_IMR的MR10
    EXTI->IMR |= EXTI_IMR_MR10;
    // 4.2上升沿触发  EXTI_RTSR(Rising trigger event configuration)上升沿触发选择寄存器的TR10
    EXTI->RTSR |= EXTI_RTSR_TR10;

    // 5.NVIC优先级
    // 5.1配置优先级组 (3-7) 配置3表示4个二进制位全部用于表示抢占优先级
    NVIC_SetPriorityGrouping(3);
    // 5.2配置优先级(0-15) 参数1:中断号
    NVIC_SetPriority(EXTI15_10_IRQn, 2); //IRQn要设置优先级的中断数 外部线路[10:15]中断
    // 5.3使能Line10
    NVIC_EnableIRQ(EXTI15_10_IRQn);
}


//  line 15-10的中断服务函数.
void EXTI15_10_IRQHandler(void) {
    // 清除中断标志位 写1清除  EXIT的PR(挂起寄存器 Pending Register)
    EXTI->PR |= EXTI_PR_PR10;

    // 延时，软件防抖
    Delay_ms(10);

    // 如果PF10还保持高电平，翻转
    if ((GPIOF->IDR & GPIO_IDR_IDR10) != 0)
    {
        Driver_LED_Toggle(LED1);
    }
}

