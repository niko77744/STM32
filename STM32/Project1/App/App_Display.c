#include "App_Display.h"


void App_Display_Init(void) {
    Inf_LCD_Init();
    Inf_W25q32_Init();
}

void App_Display_BackGround(void) {
    Inf_LCD_Clear();
    Inf_LCD_DisplayLogo((LCD_W - Img.w) / 2, 10);
    Inf_LCD_DisplayChineseTitle(16, 70);
}

void App_Display_Hint(uint16_t x, uint16_t y, uint8_t* str) {
    Inf_LCD_DisplayChinese(x, y, 16, (char*)str);
}

void App_Display_ClearHint(void) {
    // 只清空110行往下的内容
    Inf_LCD_SetArea(0, 110, LCD_W, LCD_H - 110);
    for (uint32_t i = 0; i < LCD_W * (LCD_H - 110); i++)
    {
        Inf_LCD_WriteData(BackgroundColor);
    }
}


void App_Dispaly_Message(uint16_t x, uint16_t y, uint8_t* str) {
    Inf_LCD_DisplayString(x, y, str, 16);
}
