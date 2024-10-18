#ifndef __COM_RTC_H__
#define __COM_RTC_H__

#include <time.h>
#include <stdio.h>
#include "stm32f10x.h"

typedef struct
{
    uint16_t year;
    uint8_t month;
    uint8_t week;
    uint8_t day;
    uint8_t hour;
    uint8_t mintue;
    uint8_t second;
    uint8_t now[64];
} RTC_TimeTypeDef;

void Com_RTC_Init(void);
void Com_RTC_SetTime(uint32_t UnixTimestamp);
void Com_RTC_GetTime(RTC_TimeTypeDef* datatime);

#endif /* __COM_RTC_H__ */
