#include "led.h"


void LED_On(uint16_t LED) {
    HAL_GPIO_WritePin(GPIOA, LED, GPIO_PIN_RESET);
}

void LED_Off(uint16_t LED) {
    HAL_GPIO_WritePin(GPIOA, LED, GPIO_PIN_SET);
}


void LED_Toogle(uint16_t LED) {
    HAL_GPIO_TogglePin(GPIOA, LED);
}


void LED_OnAll(uint16_t leds[], uint8_t len) {
    for (uint8_t i = 0; i < len; i++)
    {
        HAL_GPIO_WritePin(GPIOA, leds[i], GPIO_PIN_RESET);
    }
}
void LED_OffAll(uint16_t leds[], uint8_t len) {
    for (uint8_t i = 0; i < len; i++)
    {
        HAL_GPIO_WritePin(GPIOA, leds[i], GPIO_PIN_SET);
    }
}

