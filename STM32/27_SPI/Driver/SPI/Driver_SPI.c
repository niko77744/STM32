#include "Driver_SPI.h"

void Driver_SPI_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

    GPIOC->CRH &= ~GPIO_CRH_CNF13;
    GPIOC->CRH |= GPIO_CRH_CNF13;

    GPIOC->CRL &= ~GPIO_CRL_CNF5;
    GPIOC->CRL |= GPIO_CRL_CNF5;

    GPIOC->CRL &= ~GPIO_CRL_CNF7;
    GPIOC->CRL |= GPIO_CRL_CNF7;

    GPIOC->CRL &= ~(GPIO_CRL_CNF6_1 | GPIO_CRL_MODE6);
    GPIOC->CRL |= GPIO_CRL_MODE6_0;

    
}


void Driver_SPI_Start(void);
void Driver_SPI_Stop(void);
uint8_t Driver_SPI_SwapByte(uint8_t byte);
