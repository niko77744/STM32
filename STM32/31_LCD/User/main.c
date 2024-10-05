#include "Driver_USART.h"
#include "Driver_FSMC.h"
#include "GPIO.h"
#include "Inf_LCD.h"
#include "Com_Delay.h"
#include "Inf_w25q32.h"
#include "Inf_LCD_font.h"



int main(int argc, char const* argv[]) {
    // W25Q32_WriteData(0, (uint8_t*)Chinses_16_0, 383041);
    // W25Q32_WriteData(0 + 383041, (uint8_t*)Chinses_16_1, 383039);

    // 1.初始化模块
    Inf_W25Q32_Init();
    Driver_USART_Init();
    Inf_LCD_Init();

    // 2.读取ID测试芯片是否正常 0x548066
    uint32_t id = Inf_LCD_ReadID();
    printf("ID = %#x\n", id);

    // 3.使用指定颜色完成清屏操作
    Inf_LCD_Clear(White);

    // 4.在屏幕上显示一个字符 480~320PX
    // Inf_LCD_DisplayChar(100, 100, SS, 'e', LightCoral, White);
    // Inf_LCD_DisplayChar(300, 300, SL, 'f', Black, LightCoral);
    // Inf_LCD_DisplayChar(200, 200, LS, 'G', LightCoral, White);
    // Inf_LCD_DisplayChar(0, 0, LL, 'H', Black, LightCoral);
    // Inf_LCD_DisplayString(300, 20, LL, "Hel\nlo World", Black, White);
    // Inf_LCD_DispalyPicture(0, 0);
    // Inf_LCD_DispalySingleChinese(100, 100, 0, Black, White);
    // Inf_LCD_DispalySingleChinese(132, 100, 1, Black, White);
    // Inf_LCD_DispalySingleChinese(164, 100, 2, Black, White);
    // Inf_LCD_DisplayChinese(0, 0, 16, "你好世界，终端将被任务重用，按任意键关闭。", Black);
    // Inf_LCD_DisplayCycle(200, 200, 20, 3, Black);
    // Inf_LCD_DisplaySolidCycle(200, 200, 20, 3, Black);
    // Inf_LCD_DisplayLine(10, 10, 100, 100, 5, Black);
    // Inf_LCD_DisplayLine(10, 10, 10, 100, 5, Black);
    // Inf_LCD_DisplayLine(50, 100, 100, 100, 5, Black);
    // Inf_LCD_DisplayRectangle(50, 50, 100, 100, 5, Black);


    /*
    // Inf_LCD_DisplayString(0, 0, LS, "   using", BlueViolet, Black);
    // Inf_LCD_DisplayString(100, 0, LS, " System.Miband;", SeaGreen, Black);
    // Inf_LCD_DisplayString(0, 30, LS, "   namespace", DarkSlateBlue, Black);
    // Inf_LCD_DisplayString(150, 30, LS, " WatchFace;", SeaGreen, Black);
    // Inf_LCD_DisplayString(0, 60, LS, "   {", White, Black);
    // Inf_LCD_DisplayString(0, 90, LS, "     static class", Blue, Black);
    // Inf_LCD_DisplayString(230, 90, LS, "Program", SeaGreen, Black);
    // Inf_LCD_DisplayString(0, 120, LS, "     {", White, Black);
    // // Inf_LCD_DisplayString(80, 120, LS, "//Pulse:70 Bpm", Green, Black);
    // Inf_LCD_DisplayChinese(80, 120, 16, "心率七十次每分钟", Green);
    */

    while (1) {
        // Inf_LCD_BouncingBall();
    }
}


