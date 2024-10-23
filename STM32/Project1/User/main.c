#include "Com_Debug.h"
#include "Com_Delay.h"
#include "Inf_LCD.h"
#include "Inf_W25q32.h"

int main(int argc, char const* argv[])
{
    Debug_Init();
    Inf_LCD_Init();
    Inf_W25q32_Init();
    uint8_t Manufacture_ID = 0;
    uint16_t Device_Id = 0;
    Inf_W25q32_ReadID(&Manufacture_ID, &Device_Id);
    debug_print("W25q32: mid = %#x \t did = %#x\n", Manufacture_ID, Device_Id);

    // for (uint8_t i = 0; i < 16; i++)
    // {
    //     Inf_W25q32_BlockErase(W25Q32_Block_SIZE * i);
    // }
    // Inf_W25q32_WriteData(0, (uint8_t*)Chinses_16_0, 383041);
    // Inf_W25q32_WriteData(0 + 383041, (uint8_t*)Chinses_16_1, 383039);

    Inf_LCD_Clear();
    Inf_LCD_DisplayChinese(100, 100, 16, "ÄãºÃ");
    // Inf_LCD_DisplayChar(100, 100, 'a', 32);
    // Inf_LCD_DisplayChar(200, 100, 'b', 16);
    // Inf_LCD_DisplayString(100, 100, "hello dasdasdsadasd", 32);
    // Inf_LCD_DisplayChineseTitle(100, 100);
    // Inf_LCD_DisplayLogo(0, 0);
    while (1);
}


