#ifndef __INF_W25Q32_H__
#define __INF_W25Q32_H__

#include "stm32f10x.h"
#include "Driver_SPI.h"
#include "Driver_USART.h"

void Inf_W25Q32_Init(void);
void Inf_W25Q32_ReadId(uint8_t* mid, uint16_t* did);
// void Inf_W25Q32_WriteEnable(void);
// void Inf_W25Q32_WriteDisable(void);
// void Inf_W25Q32_WaitNotBusy(void);
void Inf_W25Q32_EraseSector(uint8_t block, uint8_t sector);
void Inf_W25Q32_EraseBlock(uint8_t block);
void Inf_W25Q32_PageWrite(uint8_t block, uint8_t sector, uint8_t page, uint8_t innerAddr, const uint8_t* data, uint16_t dataLen);
void Inf_W25Q32_SectorWrite(uint8_t block, uint8_t sector, uint8_t page, uint8_t innerAddr, uint8_t* data, uint16_t dataLen);
void Inf_W25Q32_Read(uint8_t block, uint8_t sector, uint8_t page, uint8_t innerAddr, uint8_t* buffer, uint16_t dataLen);
void Inf_W25Q32_ReadData(uint32_t addr, uint8_t* data, uint16_t size);
void Inf_W25Q32_RandomWrite(const uint8_t* src, uint32_t addr);

/* -------------------------------------------- */

uint8_t W25Q32_ReadState(void);
void W25Q32_WriteENABLE(void);
void W25Q32_SectorErase(uint32_t addr);
void W25Q32_BlockErase(uint32_t addr);
void W25Q32_ReadData(uint32_t addr, uint8_t* data, uint16_t size);
void W25Q32_PageWrite(uint32_t addr, uint8_t* data, uint16_t size);
void W25Q32_StepOverPageWrite(uint32_t addr, uint8_t* data, uint32_t size);
void W25Q32_WriteData(uint32_t addr, uint8_t* data, uint32_t size);

#endif /* __INF_W25Q32_H__ */
