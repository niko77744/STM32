#include "stm32f10x.h"
#include "driver_led.h"
#include "Dri_Key.h"
#include "Delay.h"
#include <stdbool.h>

int main() {
    Driver_LED_Init();
    Driver_Key1_init();
    Driver_Key3_init();
    Driver_Key4_init();

    while (1);
}

