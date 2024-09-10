#include "Dri_Key.h"


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
    NVIC_SetPriority(EXTI15_10_IRQn, 2); //IRQnҪ�������ȼ����ж��� �ⲿ��·[10:15]�ж�
    // 5.3ʹ��Line10
    NVIC_EnableIRQ(EXTI15_10_IRQn);
}


//  line 15-10���жϷ�����.
void EXTI15_10_IRQHandler(void) {
    // ����жϱ�־λ д1���  EXIT��PR(����Ĵ��� Pending Register)
    EXTI->PR |= EXTI_PR_PR10;

    // ��ʱ���������
    Delay_ms(10);

    // ���PF10�����ָߵ�ƽ����ת
    if ((GPIOF->IDR & GPIO_IDR_IDR10) != 0)
    {
        Driver_LED_Toggle(LED1);
    }
}

