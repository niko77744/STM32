#include "Com_Delay.h"
#include "Com_SysTick.h"
#include "Driver_IIC_Hard.h"
#include "Driver_IIC_Soft.h"
#include "Driver_Key.h"
#include "Driver_LED.h"
#include "Driver_USART.h"
#include "Inf_EEPROM.h"

uint8_t buffer[100] = { 0 };
uint8_t len = 0;
extern uint8_t USART_BRF;
int main(int argc, char const* argv[])
{
    Com_SysTick_Init();
    Driver_LED_Init();
    Driver_KEY_Init();
    Driver_USART_Init();
    Inf_EEPROM_Hard_Init();
    // Inf_EEPROM_Soft_Init();  //ºÍÓ²¼þ³åÍ»

    // I2C_HardÄ£¿é²âÊÔ  
    // Inf_EEPROM_Hard_WriteBytes("dddddddddddddddddddddddddddddddddddddddddddddd", 48, 0);
    // Inf_EEPROM_Hard_ReadBytes(buffer, 48, 0);
    // printf("buffer = %s\n", buffer);



    // I2C_SoftÄ£¿é²âÊÔ
    // Inf_EEPROM_Soft_WriteBytes("qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq", 60, 0);
    // Inf_EEPROM_Soft_ReadBytes(buffer, 60, 0);
    // printf("buffer = %s\n", buffer);


    while (1) {
        // // USARTÄ£¿é²âÊÔ
        // if (USART_BRF) {
        //     Driver_USART_ReceiveBytes(buffer, &len);
        //     printf("Send it to the upper computer:");
        //     Driver_USART_SendBytes(buffer, len);
        // }
        SysTick_Delay(500);
        Driver_LED_Toggle(LED2);
    }
}

