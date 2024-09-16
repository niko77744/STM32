#include "stm32f10x.h"
#include "driver_led.h"
#include "Driver_usart .h"
#include "Dri_Key.h"
#include "Driver_IIC.h"
#include "Inf_m24c02.h"



int main(int argc, char const* argv[])
{
    Dri_LED_Init();
    Driver_Key_init();
    Dri_USART1_Init();
    Inf_EEPROM_Init();


    uint8_t ch;
    // Inf_EEPROM_Writebyte('c', 0);
    ch = Inf_EEPROM_Readbyte(0);
    printf("ch=%c\n", ch);

    // uint8_t buffer[100] = { 0 };
    // Inf_EEPROM_Writebytes("nihao", 5, 0);
    // Inf_EEPROM_Readbytes(buffer, 10, 0);
    // printf("buffer = %s\n", buffer);
    while (1);
}

