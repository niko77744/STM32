#ifndef __INF_W25Q32_H__
#define __INF_W25Q32_H__

#include "stm32f10x.h"
#include "Com_Debug.h"
#include "Driver_SPI.h"

#define WriterEnable 0x06
#define WriterDisable 0x04
#define ReadID 0x9F
#define ReadData 0x03
#define PageWrite 0x02
#define SectorErase 0x20
#define BlockHalfErase 0x52
#define BlockErase 0xD8
#define IsBusy 0x05   //13页， Statue Register-1 最低位为BUSY 忙=1  不忙=0


#define W25Q32_PAGE_SIZE	256		//页大小256字节  256b
#define W25Q32_SECTOR_SIZE	4096	//扇区大小4096字节 4Kb
#define W25Q32_Block_SIZE	65536	//扇区大小65536字节 64Kb   65536/1024=64kb
#define W25Q32_FontLibrary  766080
// #define W25Q32_Block_RANGE_64(n) ((n >= 0 && n <= 63)? (n * (65536) : -1))


void Inf_W25q32_Init(void);
void Inf_W25q32_ReadID(uint8_t* mid, uint16_t* did);
void Inf_W25q32_WriteENABLE(void);
void Inf_W25q32_WriteDisable(void);
void Inf_W25q32_WaitNotBusy(void);
void Inf_W25q32_SectorErase(uint32_t addr);
void Inf_W25q32_BlockErase(uint32_t addr);

void Inf_W25q32_ReadData(uint32_t addr, uint8_t* data, uint16_t size);
void Inf_W25q32_PageWrite(uint32_t addr, uint8_t* data, uint16_t size);
void Inf_W25q32_StepOverPageWrite(uint32_t addr, uint8_t* data, uint32_t size);
void Inf_W25q32_WriteData(uint32_t addr, uint8_t* data, uint32_t size);

#endif /* __INF_W25Q32_H__ */
