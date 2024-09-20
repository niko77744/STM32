#include "Com_Delay.h"
#include "Com_SysTick.h"
#include "Driver_IIC_Hard.h"
#include "Driver_IIC_Soft.h"
#include "Driver_Key.h"
#include "Driver_LED.h"
#include "Driver_USART.h"
#include "Driver_BaseTimer.h"
#include "Driver_GeneralTimer.h"
#include "Inf_EEPROM.h"

uint8_t buffer[100] = { 0 };
uint8_t len = 0;
extern uint8_t USART_BRF;

uint8_t LED1_DutyCycle = 0;
uint8_t LED2_DutyCycle = 99;
uint8_t LED1_flag = 1;
uint8_t LED2_flag = 1;

double T = 0;
double F = 0;
int main(int argc, char const* argv[])
{
    Driver_GeneralTimer4_Init();
    Driver_GeneralTimer5_Init();
    Driver_USART_Init();

    while (1) {
        // if (USART_BRF)
        // {
        //     Driver_USART_ReceiveBytes(buffer, &len);
        //     Driver_USART_SendBytes(buffer, len);
        // }

        // if (LED1_DutyCycle == 99)
        // {
        //     LED1_flag = 0;
        // }
        // else if (LED1_DutyCycle == 0)
        // {
        //     LED1_flag = 1;
        // }
        // if (LED2_DutyCycle == 99)
        // {
        //     LED2_flag = 0;
        // }
        // else if (LED2_DutyCycle == 0)
        // {
        //     LED2_flag = 1;
        // }

        // (LED1_flag == 1) ? (LED1_DutyCycle++) : (LED1_DutyCycle--);
        // (LED2_flag == 1) ? (LED2_DutyCycle++) : (LED2_DutyCycle--);
        // Driver_GeneralTimer5_LED1_SetDutyCycle(LED1_DutyCycle);
        // Driver_GeneralTimer5_LED2_SetDutyCycle(LED2_DutyCycle);

        T = Driver_GeneralTimer4_GetCycle();
        F = Driver_GeneralTimer4_GetFrequency();
        printf("T = %.2f(ms),  F=%.2f(Hz/s)\n", T, F);

        Delay_ms(1000);
    }
}

