#include "Driver_LED.h"


uint16_t leds[size] = { LED1, LED2, LED3 };

void Driver_LED_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    // MODE11  CNF00  通用推挽输出
    GPIOA->CRL |= GPIO_CRL_MODE0;
    GPIOA->CRL |= GPIO_CRL_MODE1;
    GPIOA->CRH |= GPIO_CRH_MODE8;

    GPIOA->CRL &= ~GPIO_CRL_CNF0;
    GPIOA->CRL &= ~GPIO_CRL_CNF1;
    GPIOA->CRH &= ~GPIO_CRH_CNF8;

    Driver_LED_OffAll(leds, size);
}

void Driver_LED_On(uint16_t led) {
    GPIOA->BRR |= led;
}
void Driver_LED_Off(uint16_t led) {
    GPIOA->BSRR |= led;
}

void Driver_LED_Toogle(uint16_t led) {
    if ((GPIOA->IDR & led) == 0)
    {
        Driver_LED_Off(led);
    }
    else {
        Driver_LED_On(led);
    }

}
void Driver_LED_OnAll(uint16_t leds[], uint8_t len) {
    for (uint8_t i = 0; i < len; i++)
    {
        Driver_LED_On(leds[i]);
    }
}
void Driver_LED_OffAll(uint16_t leds[], uint8_t len) {
    for (uint8_t i = 0; i < len; i++)
    {
        Driver_LED_Off(leds[i]);
    }
}
