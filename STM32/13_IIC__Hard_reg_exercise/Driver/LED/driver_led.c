#include "driver_led.h"
uint16_t leds[size] = { LED1, LED2, LED3 };

void Dri_LED_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    // MODE11  CNF00
    GPIOA->CRL |= GPIO_CRL_MODE0;
    GPIOA->CRL |= GPIO_CRL_MODE1;
    GPIOA->CRH |= GPIO_CRH_MODE8;

    GPIOA->CRL &= ~GPIO_CRL_CNF0;
    GPIOA->CRL &= ~GPIO_CRL_CNF1;
    GPIOA->CRH &= ~GPIO_CRH_CNF8;

    Dri_LED_OffAll(leds, size);
}

void Dri_LED_On(uint16_t led) {
    GPIOA->BRR |= led;
}
void Dri_LED_Off(uint16_t led) {
    GPIOA->BSRR |= led;
}

void Dri_LED_Toogle(uint16_t led) {
    if ((GPIOA->IDR & led) == 0)
    {
        Dri_LED_Off(led);
    }
    else {
        Dri_LED_On(led);
    }

}
void Dri_LED_OnAll(uint16_t leds[], uint8_t len) {
    for (uint8_t i = 0; i < len; i++)
    {
        Dri_LED_On(leds[i]);
    }
}
void Dri_LED_OffAll(uint16_t leds[], uint8_t len) {
    for (uint8_t i = 0; i < len; i++)
    {
        Dri_LED_Off(leds[i]);
    }
}

void Dri_LED_FlowLight1(uint16_t leds[], uint8_t len) {
    for (uint8_t i = 0; i < len; i++)
    {
        Dri_LED_On(leds[i]);
        Delay_ms(300);
        Dri_LED_On(leds[i]);
    }
}
