#include "Driver_AdvancedTimer.h"

void Driver_AdvancedTimer1_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

    // ��������
    GPIOA->CRH |= (GPIO_CRH_MODE8 | GPIO_CRH_CNF8_1);
    GPIOA->CRH &= ~GPIO_CRH_CNF8_0;


    /* 3. ʱ����Ԫ������ ?Ƶ����2Hz��PWM*/
    TIM1->ARR = 4999;
    TIM1->PSC = 7199;  // 1Mhz 
    TIM1->CR1 &= ~TIM_CR1_DIR;
    TIM1->RCR = 4; // Repetition counter   ����REP�ظ���������ֵ  

    /* 4. �����������*/
    TIM1->CCMR1 &= ~TIM_CCMR1_CC1S;  // 00 ���  
    TIM1->CCR1 = 2500;  //  ����/�Ƚ�ͨ��1��ֵ (Capture/Compare 1 value)    
    TIM1->CCER &= ~TIM_CCER_CC1P;  // 1��OC1�͵�ƽ��Ч��  //!!!!!!!!!!!  �ظ���������ֵ�������ߵ�ƽ
    TIM1->CCER |= TIM_CCER_CC1E;  // ����/����1���ʹ�� (Capture/Compare 1 output enable)   

    TIM1->CCMR1 |= (TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1); // CCXS  // IC: ICXPSC  ICXF(filter)     
    TIM1->CCMR1 &= ~TIM_CCMR1_OC1M_0;  // OC  OCXM(110��PWMģʽ1�� �����ϼ���ʱ)    

    TIM1->BDTR |= TIM_BDTR_MOE;  // brake dead   MOE: �����ʹ�� (Main output enable) 

    /* �ֶ�����һ�������¼�,�������ò������ж�*/
    TIM1->CR1 |= TIM_CR1_URS;  // ��������Դ (Update request source) 1ֻ������Ż�����ж�
    TIM1->EGR |= TIM_EGR_UG;  // ���������¼� (Update generation)  ���³�ʼ����������������һ�������¼���

    TIM1->DIER |= TIM_DIER_UIE;  //UIE����������ж� (Update interrupt enable) 
    TIM1->CR1 |= TIM_CR1_CEN;   //ʹ�ܶ�ʱ��


    // TIM1_UP_IRQn: �� TIM1 �ļ������ﵽ�趨���Զ�����ֵʱ������������¼���������������жϡ�����жϿ�������ʵ�ֶ�ʱ���ܡ�����ʱ���������������Ե��źŵȡ�
    // TIM1_CC_IRQn: ����ʱ�� 1 �Ĳ��� / �Ƚ��жϡ��� TIM1 �����벶��ͨ����⵽�ض��������źű��أ��������ء��½��ػ�������أ������ߵ���ʱ���ļ�����ֵ���趨�ıȽ�ֵ���ʱ����������� / �Ƚ��¼�����������жϡ�����жϿ������ڲ��������źŵ�Ƶ�ʡ�ռ�ձȣ�ʵ�������ȵ��ƣ�PWM������ķ������Ƶȡ�
    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(TIM1_UP_IRQn, 3);
    NVIC_EnableIRQ(TIM1_UP_IRQn);
}


void TIM1_UP_IRQHandler(void) {
    // ������UIE
    TIM1->SR &= ~TIM_SR_UIF;
    TIM1->CR1 &= ~TIM_CR1_CEN;   //ʹ�ܶ�ʱ��
}
