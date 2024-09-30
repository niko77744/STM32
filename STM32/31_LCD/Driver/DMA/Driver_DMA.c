#include "Driver_DMA.h"
uint8_t DMA_IS_BRF = 0;

// Channel 4 ���ڵķ���
void Driver_DMA1_Channel4_Init(void) { // USART TX
    /* 1.����ʱ��*/
    RCC->AHBENR |= RCC_AHBENR_DMA1EN;

    //!!!!! ������������GPIOģʽ

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
    DMA1_Channel4->CCR |= DMA_CCR4_TCIE;

    /* 3. ����USART��DMAT */
    USART1->CR3 |= USART_CR3_DMAT;

    /* 4. NVIC */
    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(DMA1_Channel4_IRQn, 3);
    NVIC_EnableIRQ(DMA1_Channel4_IRQn);
}


// Channel 5 ���ڵĽ���
void Driver_DMA1_Channel5_Init(void) { // USART RX
    /* 1.����ʱ��*/
    RCC->AHBENR |= RCC_AHBENR_DMA1EN;

    /* 2.DMA������� */
    // 2.1 ѡ���ڴ������
    DMA1_Channel5->CCR &= ~DMA_CCR5_MEM2MEM;  //0���Ǵ洢�����洢��ģʽ��
    DMA1_Channel5->CCR &= ~DMA_CCR5_DIR;  //0 ���赽�洢  1�洢������  !!!Ψһ����

    // 2.2 DMA���ȼ�
    DMA1_Channel5->CCR &= ~DMA_CCR5_PL;

    // 2.3 �����ֳ�
    /* 00:8λ 01:16λ 10:32λ 11:���� */
    DMA1_Channel5->CCR &= ~DMA_CCR5_MSIZE;
    DMA1_Channel5->CCR &= ~DMA_CCR5_PSIZE;

    // 2.4 ��ַ�Ƿ�����
    DMA1_Channel5->CCR &= ~DMA_CCR5_PINC;  /* ���������ַUSART1->DR�������� */
    DMA1_Channel5->CCR |= DMA_CCR5_MINC;  /* �洢����ַ���� ��Ȼ�ظ����͵�һ���ַ� */

    // 2.5 ѭ��ģʽ
    DMA1_Channel5->CCR &= ~DMA_CCR5_CIRC;
    // DMA1_Channel4->CCR |= DMA_CCR4_CIRC; //��ע���ж�DMA1_Channel4->CCR &= ~DMA_CCR4_EN;


    // 2.6 �����ж�
    DMA1_Channel5->CCR |= DMA_CCR5_TCIE;

    /* 3. ����USART��DMAT */
    USART1->CR3 |= USART_CR3_DMAR;

    /* 4. NVIC */
    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(DMA1_Channel5_IRQn, 3);
    NVIC_EnableIRQ(DMA1_Channel5_IRQn);
}

// ��ֻ���洢��ROM(const�ȳ��� Flash)����̬��ȡ�洢��SRAM(����)
void Driver_DMA1_Channel1_Init(void) { // Mem2Mem   
    /* 1.����ʱ�� */
    RCC->AHBENR |= RCC_AHBENR_DMA1EN;

    /* 2.DMA������� */
    // 2.1 a.ѡ��洢����洢��  b.���ڴ��
    DMA1_Channel1->CCR |= DMA_CCR1_MEM2MEM;
    DMA1_Channel1->CCR &= ~DMA_CCR1_DIR;  //???����ѡ���SRAM��������

    // 2.2 ����DMA���ȼ�
    DMA1_Channel1->CCR &= ~DMA_CCR1_PL;

    // 2.3 ���������ֳ�
    DMA1_Channel1->CCR &= ~DMA_CCR1_MSIZE;
    DMA1_Channel1->CCR &= ~DMA_CCR1_PSIZE;

    // 2.4 ��ַ�Ƿ����� �ڴ��ַ����,�����ַ����
    DMA1_Channel1->CCR |= DMA_CCR1_MINC;
    DMA1_Channel1->CCR |= DMA_CCR1_PINC;

    // 2.5 �ر�ѭ��ģʽ
    DMA1_Channel1->CCR &= ~DMA_CCR1_CIRC;

    // 2.6 �����ж�
    DMA1_Channel1->CCR |= DMA_CCR1_TCIE;

    /* 4.NVIC���� */
    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(DMA1_Channel1_IRQn, 3);
    NVIC_EnableIRQ(DMA1_Channel1_IRQn);
}
void Driver_DMA1_Channel4_TransmitStart(uint32_t SrcAddr, uint32_t TargetAddr, uint16_t DateLen) {
    DMA1_Channel4->CMAR = SrcAddr;      //���͵�ʱ�����ݵĵ�ַbuffer��ΪԴ��ַ
    DMA1_Channel4->CPAR = TargetAddr;   //���͵�ʱ��USART->DR��Ϊ�����ַ
    DMA1_Channel4->CNDTR = DateLen;     //Channel Number of Data to Transfer Register

    DMA1_Channel4->CCR |= DMA_CCR4_EN;
}

void Driver_DMA1_Channel5_ReceiveStart(uint32_t SrcAddr, uint32_t TargetAddr, uint16_t DateLen) {
    DMA1_Channel5->CMAR = TargetAddr;   //���յ�ʱ��USART->DR��ΪԴ��ַ
    DMA1_Channel5->CPAR = SrcAddr;      //���յ�ʱ�����ݵĵ�ַbuffer��Ϊ�����ַ
    DMA1_Channel5->CNDTR = DateLen;     //Channel Number of Data to Transfer Register

    DMA1_Channel5->CCR |= DMA_CCR5_EN;
}

void Driver_DMA1_Channel1_TransmitStart(uint32_t srcAddr, uint32_t destAddr, uint16_t dataLen) {
    DMA1_Channel1->CMAR = destAddr;     //����������Ŀ���ַ
    DMA1_Channel1->CPAR = srcAddr;      //��Rom��������Դ��ַ
    DMA1_Channel1->CNDTR = dataLen;

    DMA1_Channel1->CCR |= DMA_CCR1_EN;
}

void DMA1_Channel4_IRQHandler(void) {
    if (DMA1->ISR & DMA_ISR_TCIF4)
    {
        // DMA1->IFCR |= DMA_IFCR_CTCIF4;  //CTEIF:Error   CGIF:global  CHTIF:half
        DMA1->IFCR |= DMA_IFCR_CGIF4;
        DMA1_Channel4->CCR &= ~DMA_CCR4_EN;
    }
}

void DMA1_Channel5_IRQHandler(void) {
    if (DMA1->ISR & DMA_ISR_TCIF5)
    {
        // DMA1->IFCR |= DMA_IFCR_CTCIF4;  //CTEIF:Error   CGIF:global  CHTIF:half
        DMA1->IFCR |= DMA_IFCR_CGIF5;
        DMA1_Channel5->CCR &= ~DMA_CCR5_EN;
        DMA_IS_BRF = 1;
    }
}


void DMA1_Channel1_IRQHandler(void) {
    if (DMA1->ISR & DMA_ISR_TCIF1)
    {
        // 1.����жϱ�־λ
        DMA1->IFCR |= DMA_IFCR_CGIF1;
        // 2.�ر�DMAģ��
        DMA1_Channel1->CCR &= ~DMA_CCR1_EN;
    }
}
