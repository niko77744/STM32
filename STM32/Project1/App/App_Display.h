#ifndef __APP_DISPLAY_H__
#define __APP_DISPLAY_H__

#include "Inf_LCD.h"

void App_Display_Init(void);

void App_Display_Back(void);

void App_Display_String(uint16_t x, uint16_t y, uint8_t* str);

void App_Display_ClearString(void);


#endif /* __APP_DISPLAY_H__ */

