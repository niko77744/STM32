#include "Driver_GeneralTimer.h"

// ����LED1��LED2�ĺ�����  CH1����LED1  CH2����LED2
void Driver_GeneralTimer5_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;

    // ����������� MODE=11  CNF=10
    GPIOA->CRL |= (GPIO_CRL_MODE0 | GPIO_CRL_MODE1 | GPIO_CRL_CNF0_1 | GPIO_CRL_CNF1_1);
    GPIOA->CRL &= ~(GPIO_CRL_CNF0_0 | GPIO_CRL_CNF1_0);

    TIM5->CR1 &= ~TIM_CR1_DIR;  // 0:���������ϼ�����
    // TIM5->CR1 |= TIM_CR1_URS;  // ��������Դ
    // TIM5->EGR |= TIM_EGR_UG;  // Update generation

    // capture/compare Mode register  ����/�Ƚ�2ѡ�� (Capture/Compare 2 selection) 
    TIM5->CCMR1 &= ~(TIM_CCMR1_CC2S | TIM_CCMR1_CC1S);  // 00 ���   01��CC1ͨ��������Ϊ���룬IC1ӳ����TI1��

    // Output compare 2 enable  110��PWMģʽ1�� �����ϼ���ʱ��һ��TIMx_CNT<TIMx_CCR1ʱͨ��1Ϊ��Ч��ƽ������Ϊ��Ч��ƽ
    TIM5->CCMR1 |= (TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC1M_2);
    TIM5->CCMR1 |= (TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC1M_1);
    TIM5->CCMR1 &= ~(TIM_CCMR1_OC2M_0 | TIM_CCMR1_OC1M_0);

    // ����/����2������� (Capture/Compare 2 output polarity) 
    TIM5->CCER &= ~(TIM_CCER_CC2P | TIM_CCER_CC1P);  //CC1ͨ������Ϊ���ʱ 0��OC1�ߵ�ƽ��Ч

    // ����/����1���ʹ�� (Capture/Compare 1 output enable)
    TIM5->CCER |= (TIM_CCER_CC2E | TIM_CCER_CC1E); //CC1ͨ������Ϊ���ʱ  1������OC1,�ź��������Ӧ��������š�

    // Ԥ��Ƶ�� Prescaler  7199��Ƶ��Ϊ1MHz, 1000ns=0.001msһ������
    TIM5->PSC = 7199;

    // �Զ���װ�ؼĴ��� auto reload register  99��Ϊ�˺���ռ�ձ� ֱ��/100
    TIM5->ARR = 99;

    // �ȽϼĴ�����ֵ  ����/�Ƚ�1��ֵ (Capture/Compare 1 value) 
    TIM5->CCR1 = 50;  //С��CCR1����Ч��ƽ
    TIM5->CCR2 = 77;

    TIM5->CR1 |= TIM_CR1_CEN;  // ʹ�ܼ�����
}

//��Time4����Tim5������PWM��Ƶ�� / ���ں�ռ�ձ�  ��Ҫ�öŰ��߽�B6��A1��������  TIM4 - CH1   ������CH2������ռ�ձ�(�½���)
void Driver_GeneralTimer4_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;

    // PB6Ϊ��������  MODE=00 CNF=01
    GPIOB->CRL &= ~(GPIO_CRL_MODE6 | GPIO_CRL_CNF6_1);
    GPIOB->CRL |= GPIO_CRL_CNF6_0;

    // ���ü�����������  0
    TIM4->CR1 &= ~TIM_CR1_DIR;


    /* 4.����TIM4�����벶�񲿷� */
    // 4.1 ����ͨ��1����ֱ��TI1
    TIM4->CR2 &= ~TIM_CR2_TI1S; //-------------


    //!!!!!!!!!!!!!!!!!! DMA/�ж�ʹ�ܼĴ���  DIER
    // TIM4->DIER |= TIM_DIER_CC1IE; //������/�Ƚ��ж�(Capture / Compare 4 interrupt enable)  1����

    // SMS[2:0]����ģʽѡ�� (Slave mode selection)   100 ��λģʽ
    TIM4->SMCR |= TIM_SMCR_SMS_2;
    TIM4->SMCR &= ~(TIM_SMCR_SMS_1 | TIM_SMCR_SMS_0);
    // TS[2:0]������ѡ�� (Trigger selection)  101���˲���Ķ�ʱ������1(TI1FP1) 
    TIM4->SMCR |= (TIM_SMCR_TS_2 | TIM_SMCR_TS_0);
    TIM4->SMCR &= ~TIM_SMCR_TS_1;


    // CC1S[1:0]������/�Ƚ�1 ѡ�� (Capture/Compare 1 selection)  
    TIM4->CCMR1 |= TIM_CCMR1_CC1S_0; // ����Ϊ01��CC1ͨ��������Ϊ���룬IC1ӳ����TI1�ϣ�
    TIM4->CCMR1 &= ~TIM_CCMR1_CC1S_1;

    // !!!!IC2ӳ����TI1��  10
    TIM4->CCMR1 &= ~TIM_CCMR1_CC2S_0;
    TIM4->CCMR1 |= TIM_CCMR1_CC2S_1;

    //Ԥ��Ƶ�� IC1PSC[1:0]������/����1Ԥ��Ƶ�� (Input capture 1 prescaler) 00����Ƶ
    TIM4->CCMR1 &= ~(TIM_CCMR1_IC1PSC | TIM_CCMR1_IC2PSC);

    // IC1F[3:0]�����벶��1�˲��� (Input capture 1 filter)   00���˲�
    TIM4->CCMR1 &= ~(TIM_CCMR1_IC1F | TIM_CCMR1_IC2F);

    // ����/�Ƚ�ʹ�ܼĴ���CCER  
    // CC1P������/����1������� (Capture/Compare 1 output polarity) 
    // ��Ϊ����ʱ�� 0�������ࣺ��������IC1��������
    TIM4->CCER &= ~TIM_CCER_CC1P;
    TIM4->CCER |= TIM_CCER_CC2P;  //cc2p�½���

    // CC1E������/����1���ʹ�� (Capture/Compare 1 output enable)  ��Ϊ����
    TIM4->CCER |= (TIM_CCER_CC1E | TIM_CCER_CC2E);

    // !!!!!3.1 Ԥ��Ƶϵ�� 72��Ƶ,ʱ��Ƶ��Ϊ1MHz,һ�μ�����ʾ1us
    TIM4->PSC = 71;

    // �Զ���װ��
    TIM4->ARR = 65535;  //����Ϊ���

    // ʹ�ܼ���
    TIM4->CR1 |= TIM_CR1_CEN;

    // NVIC_SetPriorityGrouping(3);
    // NVIC_SetPriority(TIM4_IRQn, 3);
    // NVIC_EnableIRQ(TIM4_IRQn);
}


void Driver_GeneralTimer5_LED1_SetDutyCycle(uint8_t DutyCycle) {
    TIM5->CCR1 = DutyCycle;
}
void Driver_GeneralTimer5_LED2_SetDutyCycle(uint8_t DutyCycle) {
    TIM5->CCR2 = DutyCycle;
}

// uint8_t PWM_count = 0;
// uint16_t PWM_cycle_time = 0;  //��λ��us

// ����PWM������ ms
double Driver_GeneralTimer4_GetCycle(void) {
    return TIM4->CCR1 / 1000.0;  // �������� ���磬5000 ��s = 5000��1000 = 5 ms�� 5msҲ��tim5��100��Ƶ��
}
double Driver_GeneralTimer4_GetFrequency(void) {
    return 1000000.0 / TIM4->CCR1; // ����Ƶ��= 1/���� = 1/(PWM_cycle_time/1000000)
}

double Driver_GeneralTimer4_GetDutyCycle(void) {
    return (TIM4->CCR2 * 1.0) / TIM4->CCR1; // ����ռ�ձ�= �ߵ�ƽ������ʱ��/���� 
}

// ���ô�ģʽ����ж϶�CNF��0
// void TIM4_IRQHandler(void) {
//     TIM4->SR &= ~TIM_SR_CC1IF;
//     TIM4->CNT = 0;
// }
