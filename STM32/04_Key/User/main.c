#include "stm32f10x.h"
#include "driver_led.h"
#include "Dri_Key.h"
#include "Delay.h"
#include <stdbool.h>

#define SIZE 3
extern int8_t flag;

int main() {
    uint16_t leds[SIZE] = { LED1,LED2,LED3 };

    Driver_LED_Init();
    Driver_Key1_init();
    Driver_Key2_init();
    Driver_Key3_init();
    Driver_Key4_init();

    while (1) {
        if (flag >= 0)
        {
            Driver_LED_Off(leds[(flag + 2) % 3]);
            Driver_LED_On(leds[flag]);
        }
    }
}

