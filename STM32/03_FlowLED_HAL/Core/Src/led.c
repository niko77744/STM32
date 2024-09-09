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


void LED_FlowLight(uint16_t leds[], uint8_t len) {
    static  uint8_t i = 0;
    static bool flag = 0;

    if (0 == i)
    {
        flag = 1;
        LED_Toogle(leds[i]);
        HAL_Delay(1000);
    }
    else if ((len - 1) == i)
    {
        flag = 0;
        LED_Toogle(leds[i]);
        HAL_Delay(1000);
    }
    (flag == 1) ? (i++) : (i--);
    LED_Toogle(leds[i]);
    HAL_Delay(1000);
}

