#include "Com_Delay.h"
#include "Com_SysTick.h"
#include "Driver_Key.h"
#include "Driver_LED.h"
#include "Driver_USART.h"
#include "Driver_IIC_Hard.h"
#include "Driver_IIC_Soft.h"
#include "Driver_BaseTimer.h"
#include "Driver_GeneralTimer.h"
#include "Driver_AdvancedTimer.h"
#include "Driver_DMA.h"
#include "Driver_ADC.h"
#include "GPIO.h"
#include "Inf_EEPROM.h"

uint16_t buffer[2] = { 0 };  // !!!! 16位的数据

int main(int argc, char const* argv[])
{
    Driver_USART_Init();
    Driver_ADC1_Init();
    // Driver_ADC1_Start();
    Driver_ADC1_DMA1_Init();
    Driver_ADC1_DMA1_Start((uint32_t)(&ADC1->DR), (uint32_t)buffer, 2);


    while (1) {
        printf("V1 = %.2lf\t V1 = %.2lf\n", (buffer[0] * (3.3 / 4095.0)), (buffer[1] * (3.3 / 4095.0)));
        Delay_s(1);
    }
}


