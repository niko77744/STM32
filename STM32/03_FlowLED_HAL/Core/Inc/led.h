#ifndef __LED_H__
#define __LED_H__

#include "gpio.h"
#include "stdbool.h"

void LED_On(uint16_t);
void LED_Off(uint16_t);
void LED_Toogle(uint16_t);
void LED_OnAll(uint16_t[], uint8_t);
void LED_OffAll(uint16_t[], uint8_t);
void LED_FlowLight(uint16_t[], uint8_t);


#endif /* __LED_H__ */
