#include "Driver_usart .h"
uint8_t ReceiveBuffer[100] = { 0 };
uint8_t ReceiveLen = 0;
uint8_t is_Over = 0;


void Dri_USART1_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    // 配置模式  发送：PA9  输出MDOE11  复用推挽CNF 10  
    GPIOA->CRH |= GPIO_CRH_MODE9;
    GPIOA->CRH |= GPIO_CRH_CNF9_1;
    GPIOA->CRH &= ~GPIO_CRH_CNF9_0;

    // 配置模式  接收：PA10  输入MDOE00  浮空CNF 01
    GPIOA->CRH &= ~GPIO_CRH_MODE10;
    GPIOA->CRH &= ~GPIO_CRH_CNF10_1;
    GPIOA->CRH |= GPIO_CRH_CNF10_0;

    USART1->BRR = 0x271;
    USART1->CR1 |= USART_CR1_RE;
    USART1->CR1 |= USART_CR1_TE;
    USART1->CR1 |= USART_CR1_RXNEIE;
    USART1->CR1 |= USART_CR1_IDLEIE;
    USART1->CR1 &= ~USART_CR1_M;
    USART1->CR1 &= ~USART_CR1_PCE;
    USART1->CR2 &= ~USART_CR2_STOP;

    USART1->CR1 |= USART_CR1_UE;
    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(USART1_IRQn, 3);
    NVIC_EnableIRQ(USART1_IRQn);
}
void Driver_USART1_SendChar(uint8_t byte) {
    while ((USART1->SR & USART_SR_TXE) == 0);  //发送数据寄存器空 1：数据已经被转移到移位寄存器
    USART1->DR = byte;
}
void Driver_USART1_SendData(uint8_t* bytes, uint8_t len) {
    for (uint8_t i = 0; i < len; i++)
    {
        Driver_USART1_SendChar(bytes[i]);
    }
}
void Driver_USART1_ReceiveChar(uint8_t* byte) {
    while ((USART1->SR & USART_SR_RXNE) == 0);  //读数据寄存器非空  1收到数据可以读出
    *byte = USART1->DR;
    // return USART1->DR;
}

// 打开RXNEIE和IDLEIE失效
void Driver_USART1_ReceiveData(uint8_t* bytes, uint8_t* len) {
    uint8_t i = 0;
    while (1) {
        while ((USART1->SR & USART_SR_RXNE) == 0)
        {
            if (USART1->SR & USART_SR_IDLE) {
                *len = i;
                return;
            }
        }
        bytes[i++] = USART1->DR;
    }
}

void USART1_IRQHandler(void) {
    if ((USART1->SR & USART_SR_RXNE) != 0)
    {
        USART1->DR;
        ReceiveBuffer[ReceiveLen++] = USART1->DR;
    }
    else if (USART1->SR & USART_SR_IDLE)
    {
        USART1->SR;
        USART1->DR;
        is_Over = 1;
    }
}

int fputc(int c, FILE* file)
{
    Driver_USART1_SendChar(c);
    return c;
}
