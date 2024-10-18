#include "Driver_ADC.h"

// ����ͨ�����Ϊ16ͨ��(IN0-In15)�����ݼĴ���ֻ��һ��
// ע��ͨ�����Ϊ4ͨ�����������ݼĴ�����4��


// ADC1��ͨ�� IN10 Ҳ����PC0���ӿɱ����   PC1����ͨ�� IN11
void Driver_ADC1_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    // 10��PCLK2 6��Ƶ����ΪADCʱ��  2 4 6 8  00-11
    RCC->CFGR |= RCC_CFGR_ADCPRE_1;
    RCC->CFGR &= ~RCC_CFGR_ADCPRE_0;

    // ����GPIO  ģ������ MODE=CNF=00  PC0
    GPIOC->CRL &= ~(GPIO_CRL_MODE0 | GPIO_CRL_CNF0);
    GPIOC->CRL &= ~(GPIO_CRL_MODE1 | GPIO_CRL_CNF1);

    ADC1->CR1 |= ADC_CR1_SCAN; //�ر�ɨ��(ֻת��ͨ����ĵ�һ��ͨ��)  ��ͨ��˳��ɨ�谤��ת��
    ADC1->CR2 |= ADC_CR2_CONT; // �������� 
    ADC1->CR2 &= ~ADC_CR2_ALIGN; //0�Ҷ���

    //���ò���ʱ�� 001 7.5������  һ��18��ͨ�� 0 - 17
    ADC1->SMPR1 |= ADC_SMPR1_SMP10_0; //001 7.5���� ÿ��ͨ���Ĳ���ʱ��
    ADC1->SMPR1 &= ~(ADC_SMPR1_SMP10_1 | ADC_SMPR1_SMP10_2);
    ADC1->SMPR1 |= ADC_SMPR1_SMP11_0;
    ADC1->SMPR1 &= ~(ADC_SMPR1_SMP11_1 | ADC_SMPR1_SMP11_2);


    // ADC1->SQR1 &= ~ADC_SQR1_L; // 0000 1��ת�� �����ڹ���ͨ��ת�������е�ͨ����Ŀ
    // 0001 2��ת�� �����ڹ���ͨ��ת�������е�ͨ����Ŀ
    ADC1->SQR1 &= ~ADC_SQR1_L;
    ADC1->SQR1 |= ADC_SQR1_L_0;


    ADC1->SQR3 &= ~ADC_SQR3_SQ1; //����ո�λ������Ĭ��ֵ������1���´���
    // ��Щλ���������ת�������еĵ�16��ת��ͨ���ı��(0~17) 5λ
    ADC1->SQR3 |= (10 << 0);  // ��10��ͨ�����������5λ,��ʾ���е�һ��ͨ��Ϊ10��ͨ��

    ADC1->SQR3 &= ~ADC_SQR3_SQ2;
    ADC1->SQR3 |= (11 << 5);  // ��11��ͨ�������ڵ���5λ,��ʾ���еڶ���ͨ��Ϊ11��ͨ��

    // ADC1->CR2 |= ADC_CR2_EXTSEL; //ѡ����������ͨ����ת�����ⲿ�¼�  111���
    // ADC1->CR2 |= ADC_CR2_EXTTRIG; //1��ʹ���ⲿ�¼�����ת����
}
void Driver_ADC1_Start(void) {
    // �ϵ绽�� д1���� ��д1����ת��  0����ϵ�ģʽ���ر�ADת����У׼
    ADC1->CR2 |= ADC_CR2_ADON;

    //RSTCAL �����ڸ�λУ׼״̬��Ϊ�µ�У׼��׼������ CAL ����ֱ������ ADC ��У׼���̣��Ի�ȡ׼ȷ��ת���������ֵ����� ADC ��ת�����ȡ�
    ADC1->CR2 |= ADC_CR2_RSTCAL;
    while (ADC1->CR2 & ADC_CR2_RSTCAL); //�ȵ�rstcal=0���У׼
    // A/DУ׼ �൱��У׼��ƽ
    ADC1->CR2 |= ADC_CR2_CAL;
    while (ADC1->CR2 & ADC_CR2_CAL); //�ȵ�cal=0���У׼

    // �ӳ�һ��ʱ�����д1 ���ADC_CR2_EXTSEL��ADC_CR2_EXTTRIG��ADC_CR2_SWSTART
    ADC1->CR2 |= ADC_CR2_ADON;
    // ADC1->CR2 |= ADC_CR2_SWSTART; //1����ʼת������ͨ���������EXTSEL[2:0]λ��ѡ����SWSTARTΪ�����¼�����λ��������һ�����ͨ����ת����
    while (!(ADC1->SR & ADC_SR_EOC));
}

// ʹ��DMA1��CH1��ӦADC1ģ��
void Driver_ADC1_DMA1_Init(void) {
    RCC->AHBENR |= RCC_AHBENR_DMA1EN;

    DMA1_Channel1->CCR |= DMA_CCR1_CIRC;
    DMA1_Channel1->CCR &= ~DMA_CCR1_DIR;  // 0�������
    DMA1_Channel1->CCR &= ~DMA_CCR1_MEM2MEM;

    DMA1_Channel1->CCR &= ~DMA_CCR1_PINC;
    DMA1_Channel1->CCR |= DMA_CCR1_MINC;

    DMA1_Channel1->CCR &= ~DMA_CCR1_MSIZE_1;
    DMA1_Channel1->CCR |= DMA_CCR1_MSIZE_0;
    DMA1_Channel1->CCR &= ~DMA_CCR1_PSIZE_1;
    DMA1_Channel1->CCR |= DMA_CCR1_PSIZE_0;

    DMA1_Channel1->CCR &= ~DMA_CCR1_PL;

    // ����Ҫ�ж�

    ADC1->CR2 |= ADC_CR2_DMA;  //!!!!
}

void Driver_ADC1_DMA1_Start(uint32_t SrcAddr, uint32_t TargetAddr, uint16_t DataLen) {
    /* 1. DMAģ������ */
    DMA1_Channel1->CPAR = SrcAddr;
    DMA1_Channel1->CMAR = TargetAddr;
    DMA1_Channel1->CNDTR = DataLen;
    DMA1_Channel1->CCR |= DMA_CCR1_EN;

    /* ADCģ������ */
    ADC1->CR2 |= ADC_CR2_ADON;

    ADC1->CR2 |= ADC_CR2_RSTCAL;
    while (ADC1->CR2 & ADC_CR2_RSTCAL);
    ADC1->CR2 |= ADC_CR2_CAL;
    while (ADC1->CR2 & ADC_CR2_CAL);

    ADC1->CR2 |= ADC_CR2_ADON;
    while ((ADC1->SR & ADC_SR_EOC) == 0);  //1ת�����
}


double Driver_ADC1_GetValue(void) {
    return (ADC1->DR * 3.3) / 4095;  //ADC�ֱ���Ϊ12λ��4096-1
}

