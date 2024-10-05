#ifndef __W25Q32_H__
#define __W25Q32_H__

#include "spi.h"
#include "usart.h"


void W25Q32_SectorErase(uint32_t addr);
void W25Q32_BlockErase(uint32_t addr);

void W25Q32_WriteEnable(void);
void W25Q32_WriteDisable(void);
void W25Q32_WaitNotBusy(void);

void W25Q32_ReadData(uint32_t addr, uint8_t* data, uint32_t size);

void W25Q32_WriteToPage(uint32_t addr, uint8_t* data, uint32_t size);
void W25Q32_StepOverPageWrite(uint32_t addr, uint8_t* data, uint32_t size);
void W25Q32_WriteData(uint32_t addr, uint8_t* data, uint32_t size);

#endif /* __W25Q32_H__ */

