#include "Driver_ADC.h"

// ����ͨ�����Ϊ16ͨ��(IN0-IN15)�����ݼĴ���ֻ��һ��
// ע��ͨ�����Ϊ4ͨ�����������ݼĴ�����4��


// ADC1��ͨ�� IN10 Ҳ����PC0���ӿɱ����   

void ADCx_Init(ADC_TypeDef* ADCx) {
    if (ADCx == ADC1)
    {
        RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
        // 10��PCLK2 6��Ƶ����ΪADCʱ��  2 4 6 8  00-11
        RCC->CFGR |= RCC_CFGR_ADCPRE_1;
        RCC->CFGR &= ~RCC_CFGR_ADCPRE_0;
        Hal_GPIO_Mode_Selection(GPIOC, GPIO_pin_0, GPIO_Mode_AIN);
    }
    else return;

    ADCx->CR2 |= ADC_CR2_EXTSEL;
    ADCx->CR2 &= ~ADC_CR2_ALIGN;
    ADCx->CR2 |= ADC_CR2_CONT;
    ADCx->CR1 &= ~ADC_CR1_SCAN;

    ADCx->SMPR1 &= ~(ADC_SMPR1_SMP10_2 | ADC_SMPR1_SMP10_1);
    ADCx->SMPR1 |= ADC_SMPR1_SMP10_0;

    ADCx->SQR1 &= ~ADC_SQR1_L;
    ADCx->SQR3 &= ~ADC_SQR3_SQ1;
    ADCx->SQR3 |= 10 << 0;
}


void ADCx_Start(ADC_TypeDef* ADCx, uint32_t sourceAdd, uint16_t count) {
    RCC->AHBENR |= RCC_AHBENR_DMA1EN;
    DMA1_Channel1->CCR &= ~DMA_CCR1_MEM2MEM;
    DMA1_Channel1->CCR &= ~DMA_CCR1_PL;

    DMA1_Channel1->CCR |= (DMA_CCR1_MSIZE_0 | DMA_CCR1_PSIZE_0);
    DMA1_Channel1->CCR &= ~(DMA_CCR1_MSIZE_1 | DMA_CCR1_PSIZE_1);
    DMA1_Channel1->CCR |= DMA_CCR1_MINC;
    DMA1_Channel1->CCR &= ~DMA_CCR1_PINC;
    DMA1_Channel1->CCR |= DMA_CCR1_CIRC;
    DMA1_Channel1->CCR &= ~DMA_CCR1_DIR;
    ADCx->CR2 |= ADC_CR2_DMA;

    DMA1_Channel1->CMAR = sourceAdd;
    DMA1_Channel1->CNDTR = count;
    DMA1_Channel1->CPAR = (uint32_t)(&ADCx->DR);
    DMA1_Channel1->CCR |= DMA_CCR1_EN;

    ADCx->CR2 |= ADC_CR2_ADON;
    ADCx->CR2 |= ADC_CR2_RSTCAL;
    while ((ADCx->CR2 & ADC_CR2_RSTCAL));
    ADCx->CR2 |= ADC_CR2_CAL;
    while ((ADCx->CR2 & ADC_CR2_CAL));

    ADCx->CR2 |= ADC_CR2_ADON;
    while ((ADCx->SR & ADC_SR_EOC) == 0);  //1ת�����
}
