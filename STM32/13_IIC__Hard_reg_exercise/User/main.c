#include "stm32f10x.h"
#include "driver_led.h"
#include "Driver_usart .h"
#include "Dri_Key.h"
#include "Driver_IIC.h"
#include "Inf_m24c02.h"
#include "ctype.h"
// LED 模块
extern uint16_t leds[size];
uint8_t flowLED[6] = { 0 };
uint8_t is_Uart_LED_Finish = 0;
extern int8_t LED_Key_statue;

// usart 模块
extern uint8_t ReceiveLen;
extern uint8_t is_Over;
extern uint8_t ReceiveBuffer[100];

// I2C模块
uint8_t LED_IIC[11] = { 0 };
uint8_t LED_IIC_statue = 0;


// "1,3#3,2#2,1"
int main(int argc, char const* argv[])
{
    Dri_LED_Init();
    Driver_Key_init();
    Dri_USART1_Init();
    Inf_EEPROM_Init();

    Inf_EEPROM_Readbytes(LED_IIC, 11, 0);
    for (uint8_t i = 0; i < 11; i++)
    {
        uint8_t number = 0;
        for (uint8_t i = 0; i < 11; i++) {
            if (LED_IIC[i] != 0)
            {
                LED_IIC_statue++;
            }
            if (LED_IIC[i] >= 48 && LED_IIC[i] <= 57)
            {
                flowLED[number++] = LED_IIC[i] - '0';
            }
        }
    }
    if (LED_IIC_statue)
    {
        LED_IIC_statue = 1;
    }
    else {
        LED_IIC_statue = 0;
    }
    printf("LED_IIC_statue = %d\n", LED_IIC_statue);


    while (1) {
        /*  work1:通过串口下发3组流水灯显示顺序*/
        if (is_Over)
        {
            /*  work4:通过IIC下发3组流水灯显示顺序*/
            Inf_EEPROM_Writebytes(ReceiveBuffer, 11, 0);
            printf("buffer = %s\n", ReceiveBuffer);
            uint8_t number = 0;
            for (uint8_t i = 0; i < 11; i++) {
                if (ReceiveBuffer[i] >= 48 && ReceiveBuffer[i] <= 57)
                {
                    flowLED[number++] = ReceiveBuffer[i] - '0';
                }
            }
            is_Over = 0;
            is_Uart_LED_Finish = 1;
            ReceiveLen = 0;
        }

        if (is_Uart_LED_Finish)
        {
            for (uint8_t i = 0; i < 6; i++)
            {
                Dri_LED_On(leds[flowLED[i] - 1]);
                printf("Usart_On[%d] = %d\n", i, flowLED[i]);
                Delay_ms(1000);
                Dri_LED_Off(leds[flowLED[i] - 1]);
            }
        }

        /*  work2:通过按键下发3组流水灯显示顺序*/
        //Key3最上面的按键开始  最下面的按键Key4关闭
        if (LED_Key_statue >= 0)
        {
            for (uint8_t i = 2 * LED_Key_statue; i < 2 * LED_Key_statue + 2; i++)
            {
                Dri_LED_On(leds[flowLED[i] - 1]);
                printf("Key_On[%d] = %d\n", i, flowLED[i]);
                Delay_ms(1000);
                Dri_LED_Off(leds[flowLED[i] - 1]);
            }
        }


        /* work3: 通过IIC的EEPROM下发3组流水灯显示顺序*/
        if (LED_IIC_statue == 1)
        {
            for (uint8_t i = 0; i < 2; i++)
            {
                Dri_LED_On(leds[flowLED[i] - 1]);
                printf("IIC_On[%d] = %d\n", i, flowLED[i]);
                Delay_ms(1000);
                Dri_LED_Off(leds[flowLED[i] - 1]);
            }
        }

    }

}


