#include "stm32f10x.h"
#include "driver_led.h"
#include "Delay.h"
// | ´ò¿ª   &~ ¹Ø±Õ


int main() {
    uint16_t temp[] = { LED1,LED2,LED3 };

    Driver_LED_Init();

    // Driver_LED_OnAll(temp, 3);
    // Delay_ms(2000);
    // Driver_LED_OffAll(temp, 3);

    while (1) {
        for (uint8_t i = 0; i < 3; i++)
        {
            Driver_LED_On(temp[i]);
            Delay_ms(1000);
            Driver_LED_Off(temp[i]);
        }
    }
}

