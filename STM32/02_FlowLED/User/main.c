#include "stm32f10x.h"
#include "driver_led.h"
#include "Delay.h"
// | ´ò¿ª   &~ ¹Ø±Õ

int main() {
    uint16_t leds[] = { LED1,LED2,LED3 };

    Driver_LED_Init();

    // Driver_LED_OnAll(leds, 3);
    // Delay_ms(2000);
    // Driver_LED_OffAll(leds, 3);

    while (1) {
        for (uint8_t i = 0; i < 3; i++)
        {
            Driver_LED_On(leds[i]);
            Delay_ms(1000);
            Driver_LED_Off(leds[i]);
        }
    }
}

