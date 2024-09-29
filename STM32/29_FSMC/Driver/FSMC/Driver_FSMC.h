#ifndef __DRIVER_FSMC_H__
#define __DRIVER_FSMC_H__

#include "stm32f10x.h"
#include "GPIO.h"

#define SRAM_Start ((uint8_t*)0x68000000)

void Driver_FSMC_Init(void);

#endif /* __DRIVER_FSMC_H__ */
