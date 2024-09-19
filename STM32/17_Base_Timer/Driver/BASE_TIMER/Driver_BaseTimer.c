#include "Driver_BaseTimer.h"

void Driver_BaseTimer6_Init(void) {
    RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;

    TIM6->PSC = 7199;  // Prescaler value Ԥ��Ƶ  ��ÿһ�θ����¼�ʱ��PSC����ֵ�����䵽ʵ�ʵ�Ԥ��Ƶ�Ĵ�����
    TIM6->ARR = 9999;  // ReLoad value  ��ʼֵ��0xFFFF������|=��|�껹��0xFFFF
    // TIM6->PSC = 7200 - 1;
    // TIM6->ARR = 10000 - 1;
    // �����ж�ʹ��
    TIM6->DIER |= TIM_DIER_UIE;


    // ��������Դ (Update request source)   Ĭ��0  
    TIM6->CR1 |= TIM_CR1_URS;
    // UG�����������¼� (Update generation)  �ֶ�����һ�������¼�����PSC ARR�Ĵ���ˢд��Ӱ�ӼĴ���
    TIM6->EGR |= TIM_EGR_UG;   // ����URSΪ1�����Ե�һ�β�������ж�

    // ��һ�λ���72MHz��PSC�����жϣ�Ȼ��Ž�7199ˢ��Ӱ�ӼĴ�����������Ҫ�ֶ�����һ�������¼�ȥ����Ӱ�ӼĴ�������һ��������UG�ֶ�����һ�������¼�����������¼����ǻ�����жϣ��ڶ�����UG֮ǰǰ����URS��������Դ�� Ĭ��URS=0��������UG=1���ǻ�����ж�  URS����Ϊ1��ֻ��������Ż�����ж�

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
