#include "Dri_Key.h"
int8_t flag = -1;

/**
 * Driver_Key1_init�������ڳ�ʼ������1��������
 * �ú���������GPIO��AFIO��EXTI��NVIC����ؼĴ�������ȷ������1�ܹ����������������ܹ��ڰ�������ʱ�����жϡ�
 */
void Driver_Key1_init(void) {
    // 1.����ʱ�� GPIOF AFIO��������IOʱ��ʹ�� 1����
    RCC->APB2ENR |= RCC_APB2ENR_IOPFEN;  //69�н�ע��
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

    // 2.����PF8����ģʽ  ��������  MDOE��00; CNF��10;  ODR��1
    GPIOF->CRH &= ~GPIO_CRH_MODE8;
    GPIOF->CRH |= GPIO_CRH_CNF8_1;
    GPIOF->CRH &= ~GPIO_CRH_CNF8_0;
    GPIOF->BSRR |= GPIO_BRR_BR8;

    // 3.AFIO(�ⲿ�ж����üĴ���)ѡ��EXTI8  ����EXTICR3�������±��2   ����Ϊ0101��ʾ��GPIOPF
    AFIO->EXTICR[2] |= AFIO_EXTICR3_EXTI8_PF;

    // 4.EXTI  
    // 4.1���μĴ���  EXTI_IMR��MR8
    EXTI->IMR |= EXTI_IMR_MR8;
    // 4.2�����ش���  EXTI_RTSR(Rising trigger event configuration)�����ش���ѡ��Ĵ�����TR8
    EXTI->FTSR |= EXTI_FTSR_TR8;

    // 5.NVIC���ȼ�  
    // 5.1�������ȼ��� (3-7) ����3��ʾ4��������λȫ�����ڱ�ʾ��ռ���ȼ�
    NVIC_SetPriorityGrouping(3);
    // 5.2�������ȼ�(0-15) ����1:�жϺ�
    NVIC_SetPriority(EXTI9_5_IRQn, 2); //IRQnҪ�������ȼ����ж��� �ⲿ��·[9:5]�ж�
    // 5.3ʹ��Line8
    NVIC_EnableIRQ(EXTI9_5_IRQn);
}


void Driver_Key2_init(void) {
    // 1.����ʱ�� GPIOF AFIO��������IOʱ��ʹ�� 1����
    RCC->APB2ENR |= RCC_APB2ENR_IOPFEN;  //69�н�ע��
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

    // 2.����PF8����ģʽ  ��������  MDOE��00; CNF��10;  ODR��1
    GPIOF->CRH &= ~GPIO_CRH_MODE9;
    GPIOF->CRH |= GPIO_CRH_CNF9_1;
    GPIOF->CRH &= ~GPIO_CRH_CNF9_0;
    GPIOF->BSRR |= GPIO_BRR_BR9;

    // 3.AFIO(�ⲿ�ж����üĴ���)ѡ��EXTI8  ����EXTICR3�������±��2   ����Ϊ0101��ʾ��GPIOPF
    AFIO->EXTICR[2] |= AFIO_EXTICR3_EXTI9_PF;

    // 4.EXTI  
    // 4.1���μĴ���  EXTI_IMR��MR8
    EXTI->IMR |= EXTI_IMR_MR9;
    // 4.2�����ش���  EXTI_RTSR(Rising trigger event configuration)�����ش���ѡ��Ĵ�����TR8
    EXTI->FTSR |= EXTI_FTSR_TR9;

    // 5.NVIC���ȼ�  
    // 5.1�������ȼ��� (3-7) ����3��ʾ4��������λȫ�����ڱ�ʾ��ռ���ȼ�
    NVIC_SetPriorityGrouping(3);
    // 5.2�������ȼ�(0-15) ����1:�жϺ�
    NVIC_SetPriority(EXTI9_5_IRQn, 2); //IRQnҪ�������ȼ����ж��� �ⲿ��·[9:5]�ж�
    // 5.3ʹ��Line8
    NVIC_EnableIRQ(EXTI9_5_IRQn);
}

/**
 * Driver_Key3_init�������ڳ�ʼ������3��������
 * �ú���������GPIO��AFIO��EXTI��NVIC����ؼĴ�������ȷ������3�ܹ����������������ܹ��ڰ�������ʱ�����жϡ�
 */
void Driver_Key3_init(void) {
    // 1.����ʱ�� GPIOF AFIO��������IOʱ��ʹ�� 1����
    RCC->APB2ENR |= RCC_APB2ENR_IOPFEN;  //69�н�ע��
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

    // 2.����PF10����ģʽ  ��������  MDOE��00; CNF��10;  ODR��0
    GPIOF->CRH &= ~GPIO_CRH_MODE10;
    GPIOF->CRH |= GPIO_CRH_CNF10_1;
    GPIOF->CRH &= ~GPIO_CRH_CNF10_0;
    GPIOF->BRR |= GPIO_BRR_BR10;

    // 3.AFIO(�ⲿ�ж����üĴ���)ѡ��EXTI10  ����EXTICR3�������±��2   ����Ϊ0101��ʾ��GPIOPF
    AFIO->EXTICR[2] |= AFIO_EXTICR3_EXTI10_PF;

    // 4.EXTI  
    // 4.1���μĴ���  EXTI_IMR��MR10
    EXTI->IMR |= EXTI_IMR_MR10;
    // 4.2�����ش���  EXTI_RTSR(Rising trigger event configuration)�����ش���ѡ��Ĵ�����TR10
    EXTI->RTSR |= EXTI_RTSR_TR10;

    // 5.NVIC���ȼ�  
    // 5.1�������ȼ��� (3-7) ����3��ʾ4��������λȫ�����ڱ�ʾ��ռ���ȼ�
    NVIC_SetPriorityGrouping(3);
    // 5.2�������ȼ�(0-15) ����1:�жϺ�
    NVIC_SetPriority(EXTI15_10_IRQn, 2); //IRQnҪ�������ȼ����ж��� �ⲿ��·[15:10]�ж�
    // 5.3ʹ��Line10
    NVIC_EnableIRQ(EXTI15_10_IRQn);
}


void Driver_Key4_init(void) {
    // 1.����ʱ�� GPIOF AFIO��������IOʱ��ʹ�� 1����
    RCC->APB2ENR |= RCC_APB2ENR_IOPFEN;  //69�н�ע��
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

    // 2.����PF11����ģʽ  ��������  MDOE��00; CNF��10;  ODR��0
    GPIOF->CRH &= ~GPIO_CRH_MODE11;
    GPIOF->CRH |= GPIO_CRH_CNF11_1;
    GPIOF->CRH &= ~GPIO_CRH_CNF11_0;
    GPIOF->BRR |= GPIO_BRR_BR11;

    // 3.AFIO(�ⲿ�ж����üĴ���)ѡ��EXTI11  ����EXTICR3�������±��2   ����Ϊ0101��ʾ��GPIOPF
    AFIO->EXTICR[2] |= AFIO_EXTICR3_EXTI11_PF;

    // 4.EXTI  
    // 4.1���μĴ���  EXTI_IMR��MR11
    EXTI->IMR |= EXTI_IMR_MR11;
    // 4.2�����ش���  EXTI_RTSR(Rising trigger event configuration)�����ش���ѡ��Ĵ�����TR11
    EXTI->RTSR |= EXTI_RTSR_TR11;

    // 5.NVIC���ȼ�  
    // 5.1�������ȼ��� (3-7) ����3��ʾ4��������λȫ�����ڱ�ʾ��ռ���ȼ�
    NVIC_SetPriorityGrouping(3);
    // 5.2�������ȼ�(0-15) ����1:�жϺ�
    NVIC_SetPriority(EXTI15_10_IRQn, 2); //IRQnҪ�������ȼ����ж��� �ⲿ��·[15:10]�ж�
    // 5.3ʹ��Line11
    NVIC_EnableIRQ(EXTI15_10_IRQn);
}


/**
 * @brief GPIO�ⲿ�жϻص�����
 * @param GPIO_Pin �����ⲿ�жϵ�GPIO���ź�
 * @note �����������ض�GPIO���ŵ��ⲿ�ж��߼����������ź�����жϱ�־����������Ӧ����
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
    // ����ж������Ƿ�ΪGPIO 10
    if (GPIO_Pin == GPIO_IDR_IDR10) {
        // ����жϱ�־λ��д1�����Ӧλ��EXIT��PR(����Ĵ��� Pending Register)
        EXTI->PR |= EXTI_PR_PR10;

        // ��ʱ���������������
        Delay_ms(10);

        // ���GPIOF������10�����ָߵ�ƽ����תLED1��״̬
        if ((GPIOF->IDR & GPIO_IDR_IDR10) != 0) {
            Driver_LED_Toggle(LED1);
        }
    }
    // ����ж������Ƿ�ΪGPIO 11
    else if (GPIO_Pin == GPIO_IDR_IDR11) {
        // ����жϱ�־λ��д1�����Ӧλ��EXIT��PR(����Ĵ��� Pending Register)
        EXTI->PR |= EXTI_PR_PR11;

        // ��ʱ���������������
        Delay_ms(10);

        // ���GPIOF������11�����ָߵ�ƽ����תLED2��״̬
        if ((GPIOF->IDR & GPIO_IDR_IDR11) != 0) {
            Driver_LED_Toggle(LED2);
        }
    }
    else if (GPIO_Pin == GPIO_IDR_IDR8) {
        // ����жϱ�־λ д1���  EXIT��PR(����Ĵ��� Pending Register)
        EXTI->PR |= EXTI_PR_PR8;

        // ��ʱ���������
        Delay_ms(10);

        // ���PF8�����ֵ͵�ƽ����ת
        if ((GPIOF->IDR & GPIO_IDR_IDR8) == 0)
        {
            Driver_LED_Toggle(LED3);
        }
    }
    else if (GPIO_Pin == GPIO_IDR_IDR9) {
        // ����жϱ�־λ д1���  EXIT��PR(����Ĵ��� Pending Register)
        EXTI->PR |= EXTI_PR_PR9;

        // ��ʱ���������
        Delay_ms(10);

        // ���PF9�����ֵ͵�ƽ����ת
        if ((GPIOF->IDR & GPIO_IDR_IDR9) == 0)
        {
            flag = (flag + 1) % 3;
        }
    }
}


//  line 9-5���жϷ�����  �ڻ���ļ����ҵ�
void EXTI9_5_IRQHandler(void) {
    // ����GPIO 10���жϷ�������
    HAL_GPIO_EXTI_Callback(GPIO_IDR_IDR8);
    // ����GPIO 11���жϷ�������
    HAL_GPIO_EXTI_Callback(GPIO_IDR_IDR9);
}



//  line 15-10���жϷ�����  �ڻ���ļ����ҵ�
/**
 * EXTI15_10_IRQHandler�������ڴ���GPIO�ж�����10��15��
 * ��������Ҫ���������Ӧ��GPIO�жϷ������̡�
 */
void EXTI15_10_IRQHandler(void) {
    // ����GPIO 10���жϷ�������
    HAL_GPIO_EXTI_Callback(GPIO_IDR_IDR10);
    // ����GPIO 11���жϷ�������
    HAL_GPIO_EXTI_Callback(GPIO_IDR_IDR11);
}
