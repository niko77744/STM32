#include "Driver_USART.h"
#include "Driver_FSMC.h"
#include "GPIO.h"
#include "Inf_LCD.h"
#include "Com_Delay.h"



int main(int argc, char const* argv[]) {
    // 1.初始化USART1模块
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

    while (1) {
        // Inf_LCD_BouncingBall();
    }
}


