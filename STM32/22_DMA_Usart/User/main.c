#include "Driver_Key.h"
#include "Driver_LED.h"
#include "Driver_USART.h"
#include "Driver_IIC_Hard.h"
#include "Driver_IIC_Soft.h"
#include "Com_Delay.h"
#include "Com_SysTick.h"
#include "Driver_BaseTimer.h"
#include "Driver_GeneralTimer.h"
#include "Driver_AdvancedTimer.h"
#include "Driver_DMA.h"
#include "GPIO.h"
#include "Inf_EEPROM.h"

// DMA_USART
uint8_t buffer[5] = "1234";

// DMA M2M
const uint8_t src[5] = { 'a','b','c','d','e' };
uint8_t target[20] = {};

extern uint8_t DMA_IS_BRF;

int main(int argc, char const* argv[])
{
    Driver_USART_Init();
    Driver_DMA1_Channel1_Init();
    Driver_DMA1_Channel4_Init();
    Driver_DMA1_Channel5_Init();

    // M_2_USART 
    Driver_DMA1_Channel4_TransmitStart((uint32_t)buffer, (uint32_t)(&USART1->DR), (uint16_t)(strlen((char*)buffer)));
    
    // 定长,需要接收到5位
    Driver_DMA1_Channel5_ReceiveStart((uint32_t)(&USART1->DR), (uint32_t)buffer, 5);

    printf("src = %p target = %p\n", src, target);
    // 开启DMA通道传输数据
    Driver_DMA1_Channel1_TransmitStart((uint32_t)src, (uint32_t)target, 5);
    printf("M_2_M: target = %s\n", target);

    while (1) {
        if (DMA_IS_BRF)
        {
            printf("USART_2_M: buffer = %s\n", buffer);
            DMA_IS_BRF = 0;
            Driver_DMA1_Channel5_ReceiveStart((uint32_t)(&USART1->DR), (uint32_t)buffer, 5);
        }
    }
}


