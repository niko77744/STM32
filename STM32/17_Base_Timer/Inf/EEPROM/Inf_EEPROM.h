#ifndef __INF_EEPROM_H__
#define __INF_EEPROM_H__

#include "stm32f10x.h"
#include "Driver_IIC_Hard.h"
#include "Driver_IIC_Soft.h"
#include "Com_Delay.h"

#define EEPROM_ADDR_W 0xA0
#define EEPROM_ADDR_R 0xA1


void Inf_EEPROM_Hard_Init(void);
void Inf_EEPROM_Hard_WriteByte(uint8_t byte, uint8_t InsiderAddr);
void Inf_EEPROM_Hard_WriteBytes(uint8_t* bytes, uint8_t len, uint8_t InsiderAddr);

void Inf_EEPROM_Hard_ReadByte(uint8_t* byte, uint8_t InsiderAddr);
void Inf_EEPROM_Hard_ReadBytes(uint8_t* bytes, uint8_t len, uint8_t InsiderAddr);


void Inf_EEPROM_Soft_Init(void);
void Inf_EEPROM_Soft_WriteByte(uint8_t byte, uint8_t InsiderAddr);
void Inf_EEPROM_Soft_WriteBytes(uint8_t* bytes, uint8_t len, uint8_t InsiderAddr);

void Inf_EEPROM_Soft_ReadByte(uint8_t* byte, uint8_t InsiderAddr);
void Inf_EEPROM_Soft_ReadBytes(uint8_t* bytes, uint8_t len, uint8_t InsiderAddr);

#endif /* __INF_EEPROM_H__ */
