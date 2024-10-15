#ifndef __LORA_H__
#define __LORA_H__

#include "stm32f1xx_hal.h"
#include "ebyte_core.h"

void LoRa_Init(void);
void LoRa_Start(void);
void LoRa_Send(uint8e_t* buffer, uint8e_t size);

#endif /* __LORA_H__ */
