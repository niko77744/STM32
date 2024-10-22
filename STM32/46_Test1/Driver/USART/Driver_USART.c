#include "Driver_USART.h"
uint8_t USART1_R_Buffer[100] = { 0 };
uint8_t USART1_R_Len = 0;
uint8_t USART1_BRF = 0;
uint8_t USART2_R_Buffer[100] = { 0 };
uint8_t USART2_R_Len = 0;
uint8_t USART2_BRF = 0;

void Driver_USARTx_Init(USART_TypeDef* USARTx) {
    // UART1-TX PA9  ---------  UART1-RX PA10
    // UART2-TX PA2  ---------- UART2-RX PA3

    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    if (USARTx == USART1)
    {
        RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
        // TX PA9 输出 MODE=11  !!!复用推挽CNF=10
        // RX PA10 输入 MODE=00  浮空输入CNF=01
        Hal_GPIO_Mode_Selection(GPIOA, GPIO_pin_9, GPIO_Mode_AF_PP);
        Hal_GPIO_Mode_Selection(GPIOA, GPIO_pin_10, GPIO_Mode_IN_FLOATING);
    }
    else if (USARTx == USART2)
    {
        RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
        Hal_GPIO_Mode_Selection(GPIOA, GPIO_pin_2, GPIO_Mode_AF_PP);
        Hal_GPIO_Mode_Selection(GPIOA, GPIO_pin_3, GPIO_Mode_IN_FLOATING);
    }

    USARTx->BRR |= 0x0271;
    USARTx->CR1 &= ~USART_CR1_M;
    USARTx->CR1 &= ~USART_CR1_PCE;
    USARTx->CR2 &= ~USART_CR2_STOP;

    USARTx->CR1 |= USART_CR1_TE;
    USARTx->CR1 |= USART_CR1_RE;
    USARTx->CR1 |= USART_CR1_RXNEIE;
    USARTx->CR1 |= USART_CR1_IDLEIE;
    USARTx->CR1 |= USART_CR1_UE;

    NVIC_SetPriorityGrouping(3);
    if (USARTx == USART1)
    {
        NVIC_SetPriority(USART1_IRQn, 3);
        NVIC_EnableIRQ(USART1_IRQn);
    }
    else if (USARTx == USART2)
    {
        NVIC_SetPriority(USART2_IRQn, 3);
        NVIC_EnableIRQ(USART2_IRQn);
    }
}


uint8_t Driver_USARTx_SendByte(USART_TypeDef* USARTx, uint8_t byte) {
    uint16_t timeout = 0xffff;
    // 对USART_DR的写操作，将该位清零。
    while ((USARTx->SR & USART_SR_TXE) == 0 && timeout--);
    USARTx->DR = byte;
    return timeout ? Ok : Fail;
}

uint8_t Driver_USARTx_SendBytes(USART_TypeDef* USARTx, uint8_t* bytes, uint8_t len) {
    uint16_t timeout = 0xffff;
    for (uint8_t i = 0; i < len; i++)
    {
        Driver_USARTx_SendByte(USARTx, bytes[i]);
    }
    return timeout ? Ok : Fail;
}


void Driver_USARTx_ReceiveBytes(USART_TypeDef* USARTx, uint8_t* bytes, uint8_t* len) {
    if (USARTx == USART1)
    {
        strcpy((char*)bytes, (char*)USART1_R_Buffer);
        *len = USART1_R_Len;
        USART1_R_Len = 0;
        USART1_BRF = 0;
    }
    else if (USARTx == USART2)
    {
        strcpy((char*)bytes, (char*)USART2_R_Buffer);
        *len = USART2_R_Len;
        USART2_R_Len = 0;
        USART2_BRF = 0;
    }
}


void USART1_IRQHandler(void) {
    // 读USART_DR
    if ((USART1->SR & USART_SR_RXNE) != 0)
    {
        USART1_R_Buffer[USART1_R_Len++] = USART1->DR;
    }
    //先读USART_SR，然后读USART_DR
    else if ((USART1->SR & USART_SR_IDLE) != 0)
    {
        USART1->SR;
        USART1->DR;
        USART1_BRF = 1;
    }
}
void USART2_IRQHandler(void) {
    // 读USART_DR
    if ((USART2->SR & USART_SR_RXNE) != 0)
    {
        USART2_R_Buffer[USART2_R_Len++] = USART2->DR;
    }
    //先读USART_SR，然后读USART_DR
    else if ((USART2->SR & USART_SR_IDLE) != 0)
    {
        USART2->SR;
        USART2->DR;
        USART2_BRF = 1;
    }
}


int fputc(int ch, FILE* file)
{
    Driver_USARTx_SendByte(USART1, ch);
    return ch;
}
