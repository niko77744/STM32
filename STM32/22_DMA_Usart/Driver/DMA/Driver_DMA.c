#include "Driver_DMA.h"

void Driver_DMA1_Init(void) {
    /* 1.����ʱ��*/
    RCC->AHBENR |= RCC_AHBENR_DMA1EN;

    /* 2.DMA������� */
    // 2.1 ѡ���ڴ������
    DMA1_Channel4->CCR &= ~DMA_CCR4_MEM2MEM;  //0���Ǵ洢�����洢��ģʽ��
    DMA1_Channel4->CCR |= DMA_CCR4_DIR;  //0 ���赽�洢  1�洢������

    // 2.2 DMA���ȼ�
    DMA1_Channel4->CCR &= ~DMA_CCR4_PL;

    // 2.3 �����ֳ�
    /* 00:8λ 01:16λ 10:32λ 11:���� */
    DMA1_Channel4->CCR &= ~DMA_CCR4_MSIZE;
    DMA1_Channel4->CCR &= ~DMA_CCR4_PSIZE;

    // 2.4 ��ַ�Ƿ�����
    DMA1_Channel4->CCR &= ~DMA_CCR4_PINC;  /* ���������ַUSART1->DR�������� */
    DMA1_Channel4->CCR |= DMA_CCR4_MINC;  /* �洢����ַ���� ��Ȼ�ظ����͵�һ���ַ� */

    // 2.5 ѭ��ģʽ
    DMA1_Channel4->CCR &= ~DMA_CCR4_CIRC;
    // DMA1_Channel4->CCR |= DMA_CCR4_CIRC; //��ע���ж�DMA1_Channel4->CCR &= ~DMA_CCR4_EN;


    // 2.6 �����ж�
    // DMA1_Channel4->CCR |= DMA_CCR4_TCIE;

    /* 3. ����USART��DMAT */
    USART1->CR3 |= USART_CR3_DMAT;

    /* 4. NVIC */
    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(DMA1_Channel4_IRQn, 3);
    NVIC_EnableIRQ(DMA1_Channel4_IRQn);
}

void Driver_DMA1_TransmitStart(uint32_t SrcAddr, uint32_t TargetAddr, uint16_t DateLen) {
    DMA1_Channel4->CMAR = SrcAddr;
    DMA1_Channel4->CPAR = TargetAddr;
    DMA1_Channel4->CNDTR = DateLen;  //Channel Number of Data to Transfer Register

    DMA1_Channel4->CCR |= DMA_CCR4_EN;
}

void DMA1_Channel4_IRQHandler(void) {
    if (DMA1->ISR & DMA_ISR_TCIF4)
    {
        // DMA1->IFCR |= DMA_IFCR_CTCIF4;  //CTEIF:Error   CGIF:global  CHTIF:half
        DMA1->IFCR |= DMA_IFCR_CGIF4;
        DMA1_Channel4->CCR &= ~DMA_CCR4_EN;
    }
}
