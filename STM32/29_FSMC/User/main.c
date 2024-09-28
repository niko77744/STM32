#include "Com_Delay.h"
#include "Com_SysTick.h"
#include "Driver_Key.h"
#include "Driver_LED.h"
#include "Driver_USART.h"
#include "Driver_IIC_Hard.h"
#include "Driver_IIC_Soft.h"
#include "Driver_SPI.h"
#include "Driver_BaseTimer.h"
#include "Driver_GeneralTimer.h"
#include "Driver_AdvancedTimer.h"
#include "Driver_DMA.h"
#include "Driver_ADC.h"
#include "Driver_FSMC.h"
#include "GPIO.h"
#include "Inf_EEPROM.h"
#include "Inf_w25q32.h"

uint16_t v1 __attribute__((at(0x68000000)));
uint16_t v2 __attribute__((at(0x68000004)));
uint16_t v3 = 30;

int main(int argc, char const* argv[])
{
    // 1.初始化USART1模块
    Driver_USART_Init();
    Driver_FSMC_Init();

    uint16_t v4 __attribute__((at(0x68000008)));
    v1 = 10;
    v2 = 20;
    v4 = 40;
    uint16_t v5 = 50;

    printf("v1 = %d \t %p\n", v1, &v1);
    printf("v2 = %d \t %p\n", v2, &v2);
    printf("v3 = %d \t %p\n", v3, &v3);
    printf("v4 = %d \t %p\n", v4, &v4);
    printf("v5 = %d \t %p\n", v5, &v5);

    // 方式二:指定定义指针,给定地址
    uint8_t* p = (uint8_t*)0x68000013;
    // *p = 60;

    uint8_t* p1 = (uint8_t*)0x68000020;
    // *p1 = 200;
    printf("*v1 = %d \t \n", *((uint8_t*)0x68000000));
    printf("*p = %d \t %p\n", *p, p);
    printf("*p1 = %d \t %p\n", *p1, p1);

    while (1);
}


