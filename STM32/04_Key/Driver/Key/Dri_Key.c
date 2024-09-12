#include "Dri_Key.h"
int8_t flag = -1;

/**
 * Driver_Key1_init函数用于初始化按键1的驱动。
 * 该函数配置了GPIO、AFIO、EXTI和NVIC的相关寄存器，以确保按键1能够正常工作，并且能够在按键按下时产生中断。
 */
void Driver_Key1_init(void) {
    // 1.开启时钟 GPIOF AFIO辅助功能IO时钟使能 1开启
    RCC->APB2ENR |= RCC_APB2ENR_IOPFEN;  //69行解注释
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

    // 2.配置PF8工作模式  上拉输入  MDOE：00; CNF：10;  ODR：1
    GPIOF->CRH &= ~GPIO_CRH_MODE8;
    GPIOF->CRH |= GPIO_CRH_CNF8_1;
    GPIOF->CRH &= ~GPIO_CRH_CNF8_0;
    GPIOF->BSRR |= GPIO_BRR_BR8;

    // 3.AFIO(外部中断配置寄存器)选择EXTI8  设置EXTICR3在数组下标的2   配置为0101表示打开GPIOPF
    AFIO->EXTICR[2] |= AFIO_EXTICR3_EXTI8_PF;

    // 4.EXTI  
    // 4.1屏蔽寄存器  EXTI_IMR的MR8
    EXTI->IMR |= EXTI_IMR_MR8;
    // 4.2上升沿触发  EXTI_RTSR(Rising trigger event configuration)上升沿触发选择寄存器的TR8
    EXTI->FTSR |= EXTI_FTSR_TR8;

    // 5.NVIC优先级  
    // 5.1配置优先级组 (3-7) 配置3表示4个二进制位全部用于表示抢占优先级
    NVIC_SetPriorityGrouping(3);
    // 5.2配置优先级(0-15) 参数1:中断号
    NVIC_SetPriority(EXTI9_5_IRQn, 2); //IRQn要设置优先级的中断数 外部线路[9:5]中断
    // 5.3使能Line8
    NVIC_EnableIRQ(EXTI9_5_IRQn);
}


void Driver_Key2_init(void) {
    // 1.开启时钟 GPIOF AFIO辅助功能IO时钟使能 1开启
    RCC->APB2ENR |= RCC_APB2ENR_IOPFEN;  //69行解注释
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

    // 2.配置PF8工作模式  上拉输入  MDOE：00; CNF：10;  ODR：1
    GPIOF->CRH &= ~GPIO_CRH_MODE9;
    GPIOF->CRH |= GPIO_CRH_CNF9_1;
    GPIOF->CRH &= ~GPIO_CRH_CNF9_0;
    GPIOF->BSRR |= GPIO_BRR_BR9;

    // 3.AFIO(外部中断配置寄存器)选择EXTI8  设置EXTICR3在数组下标的2   配置为0101表示打开GPIOPF
    AFIO->EXTICR[2] |= AFIO_EXTICR3_EXTI9_PF;

    // 4.EXTI  
    // 4.1屏蔽寄存器  EXTI_IMR的MR8
    EXTI->IMR |= EXTI_IMR_MR9;
    // 4.2上升沿触发  EXTI_RTSR(Rising trigger event configuration)上升沿触发选择寄存器的TR8
    EXTI->FTSR |= EXTI_FTSR_TR9;

    // 5.NVIC优先级  
    // 5.1配置优先级组 (3-7) 配置3表示4个二进制位全部用于表示抢占优先级
    NVIC_SetPriorityGrouping(3);
    // 5.2配置优先级(0-15) 参数1:中断号
    NVIC_SetPriority(EXTI9_5_IRQn, 2); //IRQn要设置优先级的中断数 外部线路[9:5]中断
    // 5.3使能Line8
    NVIC_EnableIRQ(EXTI9_5_IRQn);
}

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
    NVIC_SetPriority(EXTI15_10_IRQn, 2); //IRQn要设置优先级的中断数 外部线路[15:10]中断
    // 5.3使能Line10
    NVIC_EnableIRQ(EXTI15_10_IRQn);
}


void Driver_Key4_init(void) {
    // 1.开启时钟 GPIOF AFIO辅助功能IO时钟使能 1开启
    RCC->APB2ENR |= RCC_APB2ENR_IOPFEN;  //69行解注释
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

    // 2.配置PF11工作模式  下拉输入  MDOE：00; CNF：10;  ODR：0
    GPIOF->CRH &= ~GPIO_CRH_MODE11;
    GPIOF->CRH |= GPIO_CRH_CNF11_1;
    GPIOF->CRH &= ~GPIO_CRH_CNF11_0;
    GPIOF->BRR |= GPIO_BRR_BR11;

    // 3.AFIO(外部中断配置寄存器)选择EXTI11  设置EXTICR3在数组下标的2   配置为0101表示打开GPIOPF
    AFIO->EXTICR[2] |= AFIO_EXTICR3_EXTI11_PF;

    // 4.EXTI  
    // 4.1屏蔽寄存器  EXTI_IMR的MR11
    EXTI->IMR |= EXTI_IMR_MR11;
    // 4.2上升沿触发  EXTI_RTSR(Rising trigger event configuration)上升沿触发选择寄存器的TR11
    EXTI->RTSR |= EXTI_RTSR_TR11;

    // 5.NVIC优先级  
    // 5.1配置优先级组 (3-7) 配置3表示4个二进制位全部用于表示抢占优先级
    NVIC_SetPriorityGrouping(3);
    // 5.2配置优先级(0-15) 参数1:中断号
    NVIC_SetPriority(EXTI15_10_IRQn, 2); //IRQn要设置优先级的中断数 外部线路[15:10]中断
    // 5.3使能Line11
    NVIC_EnableIRQ(EXTI15_10_IRQn);
}


/**
 * @brief GPIO外部中断回调函数
 * @param GPIO_Pin 触发外部中断的GPIO引脚号
 * @note 本函数处理特定GPIO引脚的外部中断逻辑，根据引脚号清除中断标志，并进行相应操作
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    // 检查中断引脚是否为GPIO 10
    if (GPIO_Pin == GPIO_IDR_IDR10) {
        // 清除中断标志位，写1清除对应位的EXIT的PR(挂起寄存器 Pending Register)
        EXTI->PR |= EXTI_PR_PR10;

        // 延时，用于软件防抖动
        Delay_ms(10);

        // 如果GPIOF的引脚10还保持高电平，则翻转LED1的状态
        if ((GPIOF->IDR & GPIO_IDR_IDR10) != 0) {
            Driver_LED_Toggle(LED1);
        }
    }
    // 检查中断引脚是否为GPIO 11
    else if (GPIO_Pin == GPIO_IDR_IDR11) {
        // 清除中断标志位，写1清除对应位的EXIT的PR(挂起寄存器 Pending Register)
        EXTI->PR |= EXTI_PR_PR11;

        // 延时，用于软件防抖动
        Delay_ms(10);

        // 如果GPIOF的引脚11还保持高电平，则翻转LED2的状态
        if ((GPIOF->IDR & GPIO_IDR_IDR11) != 0) {
            Driver_LED_Toggle(LED2);
        }
    }
    else if (GPIO_Pin == GPIO_IDR_IDR8) {
        // 清除中断标志位 写1清除  EXIT的PR(挂起寄存器 Pending Register)
        EXTI->PR |= EXTI_PR_PR8;

        // 延时，软件防抖
        Delay_ms(10);

        // 如果PF8还保持低电平，翻转
        if ((GPIOF->IDR & GPIO_IDR_IDR8) == 0)
        {
            Driver_LED_Toggle(LED3);
        }
    }
    else if (GPIO_Pin == GPIO_IDR_IDR9) {
        // 清除中断标志位 写1清除  EXIT的PR(挂起寄存器 Pending Register)
        EXTI->PR |= EXTI_PR_PR9;

        // 延时，软件防抖
        Delay_ms(10);

        // 如果PF9还保持低电平，翻转
        if ((GPIOF->IDR & GPIO_IDR_IDR9) == 0)
        {
            flag = (flag + 1) % 3;
        }
    }
}


//  line 9-5的中断服务函数  在汇编文件中找到
void EXTI9_5_IRQHandler(void) {
    // 调用GPIO 10的中断服务例程
    HAL_GPIO_EXTI_Callback(GPIO_IDR_IDR8);
    // 调用GPIO 11的中断服务例程
    HAL_GPIO_EXTI_Callback(GPIO_IDR_IDR9);
}



//  line 15-10的中断服务函数  在汇编文件中找到
/**
 * EXTI15_10_IRQHandler函数用于处理GPIO中断请求10至15。
 * 本函数主要负责调用相应的GPIO中断服务例程。
 */
void EXTI15_10_IRQHandler(void) {
    // 调用GPIO 10的中断服务例程
    HAL_GPIO_EXTI_Callback(GPIO_IDR_IDR10);
    // 调用GPIO 11的中断服务例程
    HAL_GPIO_EXTI_Callback(GPIO_IDR_IDR11);
}
