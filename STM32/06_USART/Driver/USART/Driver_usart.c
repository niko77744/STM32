#include "Driver_usart .h"

void Driver_USART1_Init(void) {
    // 1.����ʱ��  1.GPIOA PA9��PA10   2.USART�Լ�
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    // 2.����GPIO����ģʽ
    // 2.1 PA9 TX ��� ����������� MODE��11  CNF��10
    GPIOA->CRH |= GPIO_CRH_MODE9;
    GPIOA->CRH &= ~GPIO_CRH_CNF9_0;
    GPIOA->CRH |= GPIO_CRH_CNF9_1;
    // 2.2 PA10 RX ���� �������� MDOE��00 CNF��01
    GPIOA->CRH &= ~GPIO_CRH_MODE10;
    GPIOA->CRH |= GPIO_CRH_CNF10_0;
    GPIOA->CRH &= ~GPIO_CRH_CNF10_1;

    // 3.USARTģ������
    // 3.1 USART_BRR������  115200  0x0271
    USART1->BRR = 0x271;
    // 3.2 USART_CR1 ���շ���ʹ��  RE,TE
    USART1->CR1 |= USART_CR1_TE;
    USART1->CR1 |= USART_CR1_RE;
    // 3.3 USART_CR1 �ֳ� M Ĭ��0��ʾ���ݳ���8
    USART1->CR1 &= ~USART_CR1_M;
    // 3.4 USART_CR1 ����ҪУ��λ PCE  Ĭ��0������У��
    USART1->CR1 &= ~USART_CR1_PCE;
    // 3.5 USART_CR2����ֹͣλ Ĭ��00��ʾֹͣλSTOPΪ1λ
    USART1->CR2 &= ~USART_CR2_STOP;
    // 3.6 �����ж� RXENIE��IDLEIE
    USART1->CR1 |= USART_CR1_RXNEIE;
    USART1->CR1 |= USART_CR1_IDLEIE;

    // 3.7 USART_CR1 USART����ģ��ʹ�� (ģ��ʹ�ܷ��������Щ����ʹ�ܿ������ܸ�������) UE 
    USART1->CR1 |= USART_CR1_UE;

    // // 4.����NVIC���ȼ�
    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(USART1_IRQn, 3);
    NVIC_EnableIRQ(USART1_IRQn);
}

void Driver_USART1_SendChar(uint8_t byte) {
    // �ȵ��������ݼĴ���Ϊ�գ��ŵ���λ�Ĵ���  SR��TXE==1
    while ((USART1->SR & USART_SR_TXE) == 0);  //�������ݼĴ�����
    USART1->DR = byte;
}
void Driver_USART1_SendString(uint8_t* str, uint8_t len) {
    // ����Ҫ�ж���û�з����꣬��Ϊ����֪���������ݵĳ���
    for (uint8_t i = 0; i < len; i++)
    {
        Driver_USART1_SendChar(str[i]);
    }
}

uint8_t Driver_USART1_ReceiveChar(void) {
    while ((USART1->SR & USART_SR_RXNE) == 0); // RXNE��ȡ���ݼĴ����ǿ�  û�����ݵ�ʱ��ס
    return USART1->DR;
}
void Driver_USART1_ReceiveString(uint8_t* buff, uint8_t* len) {
    // uint8_t i = 0;
    // while (1)
    // {
    //     while ((USART1->SR & USART_SR_RXNE) == 0) {  // ��ȡ���ݼĴ���Ϊ��
    //         if (USART1->SR & USART_SR_IDLE) { // ���Ҽ�⵽����֡  ���ܽ���ֻ�п���֡��������������ݾ��ǽ���һ���ֽ�
    //             // �ƶ����ݷ������
    //             *len = i;
    //             return;
    //         }
    //     };
    //     buff[i] = USART1->DR;
    //     i++;
    // }
}
uint8_t buffer[100] = { 0 };
uint8_t len = 0;
uint8_t is_over = 0;
void USART1_IRQHandler(void) {
    // ��RDR��λ�Ĵ����е����ݱ�ת�Ƶ�USART_DR�Ĵ����У���λ��Ӳ����λ�����USART_CR1�Ĵ����е�RXNEIEΪ1��������жϡ���USART_DR�Ķ��������Խ���λ���㡣
    if (USART1->SR & USART_SR_RXNE)  // �����ݼĴ����ǿ� 1�յ����ݿ��Զ���
    {
        // 1���ֽڽ������cc
        buffer[len++] = USART1->DR;  //��ȡDR�Ĵ���������Ĵ��� 
    }
    //��⵽���߿���  1��⵽���� ����⵽���߿���ʱ����λ��Ӳ����λ�����USART_CR1�е�IDLEIEΪ��1����������жϡ���������������λ(�ȶ�USART_SR��Ȼ���USART_DR)��
    else if (USART1->SR & USART_SR_IDLE)
    {
        // ����жϱ�־λ
        USART1->SR;
        USART1->DR;
        is_over = 1;

        // ��ʾ���ձ䳤�������,����PC
        // Driver_USART1_SendString(buffer, len);
        // len = 0;
    }
}
