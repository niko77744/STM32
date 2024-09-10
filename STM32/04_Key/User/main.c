#include "stm32f10x.h"
#include "driver_led.h"
#include "Dri_Key.h"
#include "Delay.h"
#include <stdbool.h>

#define SIZE 3

extern uint8_t flag;

int main() {
    uint16_t leds[SIZE] = { LED1,LED2,LED3 };

    Driver_LED_Init();
    Driver_Key1_init();
    Driver_Key2_init();
    Driver_Key3_init();
    Driver_Key4_init();

    while (1) {
        if (flag)
        {
            switch (flag)
            {
            case 1:
                Driver_LED_Off(leds[SIZE - 1]);
                Driver_LED_On(leds[flag - 1]); 
                break;
            case 2:
                Driver_LED_Off(leds[flag - 2]);
                Driver_LED_On(leds[flag - 1]); 
                break;
            case 3:
                Driver_LED_Off(leds[flag - 2]);
                Driver_LED_On(leds[flag - 1]); 
                break;
            default:
                Driver_LED_OffAll(leds, 3);
                break;
            }
            // for (uint8_t i = 0; i < 3; i++)
            // {
            //     Driver_LED_On(leds[i]);
            //     Delay_ms(200);
            //     Driver_LED_Off(leds[i]);
            //     if (flag == 0)
            //     {
            //         break;
            //     }
            // }

            
        }
    }
}

