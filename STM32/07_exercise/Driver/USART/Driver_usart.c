#include "Driver_usart .h"
#include "stdbool.h"
#include "string.h"
uint8_t SendBuffer[100] = { 0 };
uint8_t ReceiveBuffer[100] = { 0 };
uint8_t is_send_next = 0;
bool is_receive_next = 0;
bool is_receive_complete = 0;
uint8_t receive_len = 0;

void Dri_USART1_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    // PA9 TX输出MODE11 复用推挽 CNF10     P10 RX 输入MODE00   浮空CNF01
    GPIOA->CRH |= GPIO_CRH_MODE9;
    GPIOA->CRH |= GPIO_CRH_CNF9_1;
    GPIOA->CRH &= ~GPIO_CRH_CNF9_0;

    GPIOA->CRH &= ~GPIO_CRH_MODE10;
    GPIOA->CRH &= ~GPIO_CRH_CNF10_1;
    GPIOA->CRH |= GPIO_CRH_CNF10_0;

    USART1->BRR = 0x271;
    USART1->CR1 &= ~USART_CR1_M;
    USART1->CR1 &= ~USART_CR1_PCE;
    USART1->CR2 &= ~USART_CR2_STOP;
    // 接收和发送数据的使能
    USART1->CR1 |= USART_CR1_TE;
    USART1->CR1 |= USART_CR1_RE;

    // 接收中断使能
    USART1->CR1 |= USART_CR1_RXNEIE;
    USART1->CR1 |= USART_CR1_IDLEIE;

    // 发送中断使能
    USART1->CR1 |= USART_CR1_TXEIE;
    USART1->CR1 |= USART_CR1_TCIE;

    // USART使能
    USART1->CR1 |= USART_CR1_UE;

    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(USART1_IRQn, 3);
    NVIC_EnableIRQ(USART1_IRQn);
}

void Driver_USART1_SendData(uint8_t bytes[]) {
    uint8_t i = 0;
    strcpy(SendBuffer, bytes);
    while (bytes[i] != '\0')
    {
        while (~is_send_next);
        USART1->DR = SendBuffer[i++];
        is_send_next = 0;
    }
}


void Driver_USART1_ReceiveData(uint8_t bytes[]) {
    while (1) {
        while (!is_receive_next);
        ReceiveBuffer[receive_len++] = USART1->DR;
        is_receive_next = 0;
        if (is_receive_complete == 1)
        {
            ReceiveBuffer[receive_len] = '\0';
            strcpy(bytes, ReceiveBuffer);
            return;
        }
    }
}


void USART1_IRQHandler(void) {
    // 判断是谁产生的中断S
    // 发送  产生中断表示数据已经被转移到移位寄存器，可以写下一个数据了
    if ((USART1->SR & USART_SR_TXE) != 0)
    {
        USART1->DR = 1;
        is_send_next = 1;
        // if ((USART1->SR & USART_SR_TC) != 0)
        // {
        //     USART1->SR;
        //     USART1->DR = 1;
        // }
    }
    // 接收   1收到数据可以读出
    else if ((USART1->SR & USART_SR_RXNE) != 0)
    {
        USART1->DR;
        is_receive_next = 1;

        if ((USART1->SR & USART_SR_IDLE) != 0)
        {
            USART1->SR;
            USART1->DR;
            is_receive_complete = 1;
        }
    }
}
