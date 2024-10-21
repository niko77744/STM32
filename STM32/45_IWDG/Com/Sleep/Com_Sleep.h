#ifndef __COM_SLEEP_H__
#define __COM_SLEEP_H__

#include "stm32f10x.h"
#include "Driver_USART.h"
#include "Com_Delay.h"

typedef struct
{
    uint32_t System_Clock;
    uint32_t AHB_Clock;
    uint32_t APB1_Clock;
    uint32_t APB2_Clock;
}Clock;


void HAL_PWR_EnterSLEEPMode(void);
void HAL_PWR_EnterSTOPMode(void);
void HAL_PWR_EnterSTANDBYMode(void);
void STANDBYMode_WUF(void);
void SystemClock_Config(void);
Clock Get_SystemClock_Config(void);

#endif /* __COM_SLEEP_H__ */
