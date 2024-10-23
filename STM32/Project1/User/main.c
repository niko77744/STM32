#include "Driver_Usart.h"
#include "Com_Debug.h"
#include "Com_Delay.h"
#include "Inf_LCD.h"

int main(int argc, char const* argv[])
{
    Debug_Init();
    Inf_LCD_Init();
    Inf_LCD_Clear();
    // Inf_LCD_DisplayChar(100, 100, 'a', 32);
    // Inf_LCD_DisplayChar(200, 100, 'b', 16);
    // Inf_LCD_DisplayString(100, 100, "hello dasdasdsadasd", 32);
    // Inf_LCD_DisplayChineseTitle(100, 100);
    Inf_LCD_DisplayLogo(0, 0);
    while (1);
}


