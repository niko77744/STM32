#include "Driver_USART.h"
uint8_t USART_R_Buffer[100] = { 0 };
uint8_t USART_R_Len = 0;
uint8_t USART_BRF = 0;

void Driver_USART_Init(void) {
    // UART1-TX PA9  ---------  UART1-RX PA10
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    // TX PA9 输出 MODE=11  !!!复用推挽CNF=10
    // RX PA10 输入 MODE=00  浮空输入CNF=01
    GPIOA->CRH |= GPIO_CRH_MODE9;
    GPIOA->CRH |= GPIO_CRH_CNF9_1;
    GPIOA->CRH &= ~GPIO_CRH_CNF9_0;

    GPIOA->CRH &= ~GPIO_CRH_MODE10;
    GPIOA->CRH &= ~GPIO_CRH_CNF10_1;
    GPIOA->CRH |= GPIO_CRH_CNF10_0;

    USART1->BRR |= 0x0271;
    USART1->CR1 &= ~USART_CR1_M;
    USART1->CR1 &= ~USART_CR1_PCE;
    USART1->CR2 &= ~USART_CR2_STOP;

    USART1->CR1 |= USART_CR1_TE;
    USART1->CR1 |= USART_CR1_RE;
    USART1->CR1 |= USART_CR1_RXNEIE;
    USART1->CR1 |= USART_CR1_IDLEIE;

    USART1->CR1 |= USART_CR1_UE;
    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(USART1_IRQn, 3);
    NVIC_EnableIRQ(USART1_IRQn);
}

uint8_t Driver_USART_SendByte(uint8_t byte) {
    uint16_t timeout = 0xffff;
    // 对USART_DR的写操作，将该位清零。
    while ((USART1->SR & USART_SR_TXE) == 0 && timeout--);
    USART1->DR = byte;
    return timeout ? Ok : Fail;
}
uint8_t Driver_USART_SendBytes(uint8_t* bytes, uint8_t len) {
    uint16_t timeout = 0xffff;
    for (uint8_t i = 0; i < len; i++)
    {
        Driver_USART_SendByte(bytes[i]);
        // if (!Driver_USART_SendByte(bytes[i])) {
        //     return Fail; // 发送失败
        // }
    }
    return timeout ? Ok : Fail;
}

void Driver_USART_ReceiveByte(uint8_t* byte) {
    *byte = USART_R_Buffer[0];
    USART_R_Len = 0;
    USART_BRF = 0;
}
void Driver_USART_ReceiveBytes(uint8_t* bytes, uint8_t* len) {
    strcpy((char*)bytes, (char*)USART_R_Buffer);
    // memcpy(bytes, USART_R_Buffer, USART_R_Len);
    *len = USART_R_Len;
    USART_R_Len = 0;
    USART_BRF = 0;
}


void USART1_IRQHandler(void) {
    // 读USART_DR
    if ((USART1->SR & USART_SR_RXNE) != 0)
    {
        USART_R_Buffer[USART_R_Len++] = USART1->DR;
    }
    //先读USART_SR，然后读USART_DR
    else if ((USART1->SR & USART_SR_IDLE) != 0)
    {
        USART1->SR;
        USART1->DR;
        USART_BRF = 1;
    }
}


int fputc(int ch, FILE* file)
{
    Driver_USART_SendByte(ch);
    // HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 1, HAL_MAX_DELAY);
    return ch;
}
