#include "Driver_LED.h"


uint16_t leds[size] = { LED1, LED2, LED3 };

void Driver_LED_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;

    GPIO_InitTypeDef GPIO_InitStruct;

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Pin = (LED1 | LED2 | LED3);
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    Driver_LED_OffAll(leds, size);
}

void Driver_LED_On(uint16_t led) {
    HAL_GPIO_WritePin(GPIOA, led, GPIO_PIN_RESET);
}
void Driver_LED_Off(uint16_t led) {
    HAL_GPIO_WritePin(GPIOA, led, GPIO_PIN_SET);
}

void Driver_LED_Toggle(uint16_t led) {
    HAL_GPIO_TogglePin(GPIOA, led);
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
