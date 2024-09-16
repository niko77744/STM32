#ifndef __INF_M24C02_H__
#define __INF_M24C02_H__

#include "stm32f10x.h"
#include "Driver_IIC.h"
#define  EEP_ADDR_W 0xA0

void Inf_EEPROM_Init(void);
uint8_t Inf_EEPROM_Readbyte(uint8_t InsideAddr);
void Inf_EEPROM_Readbytes(uint8_t* bytes, uint8_t len, uint8_t InsideAddr);

void Inf_EEPROM_Writebyte(uint8_t byte, uint8_t InsideAddr);
void Inf_EEPROM_WritePage(uint8_t* bytes, uint8_t len, uint8_t InsideAddr);
void Inf_EEPROM_Writebytes(uint8_t* bytes, uint8_t len, uint8_t InsideAddr);

#endif /* __INF_M24C02_H__ */
