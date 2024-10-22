#include "Driver_Usart.h"
volatile uint8_t USART1_R_Buffer[128] = { 0 };
volatile uint16_t USART1_R_Len = 0;
volatile uint8_t USART1_BRF = 0;

void Driver_USARTx_Init(USART_TypeDef* USARTx) {
    // UART1-TX PA9  ---------  UART1-RX PA10
    // UART2-TX PA2  ---------- UART2-RX PA3
    if (USARTx == USART1)
    {
        RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
        RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
        Hal_GPIO_Mode_Selection(GPIOA, GPIO_pin_9, GPIO_Mode_AF_PP);
        Hal_GPIO_Mode_Selection(GPIOA, GPIO_pin_10, GPIO_Mode_IN_FLOATING);
    }
    else return;

    USARTx->BRR = 0x271;
    USARTx->CR1 &= ~(USART_CR1_M | USART_CR1_PCE);
    USARTx->CR2 &= ~(USART_CR2_STOP);
    USARTx->CR1 |= USART_CR1_RXNEIE;
    USARTx->CR1 |= USART_CR1_IDLEIE;
    USARTx->CR1 |= (USART_CR1_TE | USART_CR1_RE);

    NVIC_SetPriorityGrouping(3);
    if (USARTx == USART1)
    {
        NVIC_SetPriority(USART1_IRQn, 4);
        NVIC_EnableIRQ(USART1_IRQn);

    }
    else return;
}

void Driver_USARTx_Start(USART_TypeDef* USARTx) {
    USARTx->CR1 |= USART_CR1_UE;
}
void Driver_USARTx_Stop(USART_TypeDef* USARTx) {
    USARTx->CR1 &= ~USART_CR1_UE;
}
void Driver_USARTx_SendChar(USART_TypeDef* USARTx, uint8_t ch) {
    while ((USARTx->SR & USART_SR_TXE) == 0);
    USARTx->DR = ch;
}
void Driver_USARTx_SendString(USART_TypeDef* USARTx, uint8_t* str, uint16_t datalen) {
    for (uint16_t i = 0; i < datalen; i++)
    {
        Driver_USARTx_SendChar(USARTx, str[i]);
    }
}


void Driver_USARTx_ReceiveString(USART_TypeDef* USARTx, uint8_t* str, uint16_t* datalen) {
    if (USARTx == USART1)
    {
        strcpy((char*)str, (char*)USART1_R_Buffer);
        *datalen = USART1_R_Len;
        USART1_R_Len = 0;
        memset((uint8_t*)USART1_R_Buffer, 0, sizeof(USART1_R_Buffer));
        USART1_BRF = 0;
    }
}

void USART1_IRQHandler(void) {
    if ((USART1->SR & USART_SR_RXNE) != 0)
    {
        USART1_R_Buffer[USART1_R_Len++] = USART1->DR;
    }
    else if ((USART1->SR & USART_SR_IDLE) != 0)
    {
        USART1->SR;
        USART1->DR;
        USART1_BRF = 1;
    }
}


int fputc(int ch, FILE* file)
{
    Driver_USARTx_SendChar(USART1, ch);
    return ch;
}
