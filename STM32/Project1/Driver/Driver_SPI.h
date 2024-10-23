#ifndef __DRIVER_SPI_H__
#define __DRIVER_SPI_H__

#include "stm32f10x.h"
#include "Com_Gpio.h"
#include "Com_Debug.h"


void Driver_SPI_Init(void);
void Driver_SPI_CS_Start(void);
void Driver_SPI_CS_Stop(void);
uint8_t Driver_SPI_SwapData(uint8_t T_Data);


#endif /* __DRIVER_SPI_H__ */
