#include "Driver_USART.h"
#include "Driver_FSMC.h"
#include "GPIO.h"
#include "Inf_LCD.h"
#include "Com_Delay.h"
#include "Inf_w25q32.h"
#include "Inf_LCD_font.h"



int main(int argc, char const* argv[]) {

    // 1.初始化模块
    Inf_W25Q32_Init();
    Driver_USART_Init();
    Inf_LCD_Init();

    // Inf_W25Q32_EraseBlock(0);
    // Inf_W25Q32_EraseBlock(1);
    // Inf_W25Q32_EraseBlock(2);
    // Inf_W25Q32_EraseBlock(3);
    // Inf_W25Q32_EraseBlock(4);
    // Inf_W25Q32_EraseBlock(5);
    // Inf_W25Q32_EraseBlock(6);
    // Inf_W25Q32_EraseBlock(7);
    // Inf_W25Q32_EraseBlock(8);
    // Inf_W25Q32_EraseBlock(9);
    // Inf_W25Q32_EraseBlock(10);
    // W25Q32_WriteData(0, (uint8_t*)Chinses_16_0, 383041);
    // W25Q32_WriteData(0 + 383041, (uint8_t*)Chinses_16_1, 383039);



    // 2.读取ID测试芯片是否正常 0x548066
    uint32_t id = Inf_LCD_ReadID();
    printf("ID = %#x\n", id);

    // 3.使用指定颜色完成清屏操作
    Inf_LCD_Clear(Black);

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
    Inf_LCD_DisplayChinese(0, 0, 16, "《在生活的长河中，总有一些微小而确实的幸福，如同点点繁星照亮我们平凡的日子，这些小确幸或许微不足道，却有着治愈人心的力量。清晨，当第一缕阳光透过窗帘的缝隙轻柔地洒在脸上，那丝丝暖意就是一种小确幸。我在半梦半醒之间伸个懒腰，感受着新一天的开始，没有烦恼与喧嚣的打扰，这种简单的惬意就像一杯温热的牛奶，滋润着心田。漫步在街头巷尾，偶然间闻到一阵熟悉的花香。那是街角老树下不知名的小花散发出来的芬芳。我会不由自主地停下脚步，深吸一口气，让那淡雅的香气充满鼻腔。这一瞬间，仿佛时间都为这缕花香而静止，周围的一切嘈杂都消失不见，只留下自己与这一抹自然的美好，这是大自然馈赠的小确幸。翻开一本书，在文字的海洋里遨游也是一种小确幸。当我沉浸在一本好书里时，我仿佛进入了另一个世界。跟随书中主人公的喜怒哀乐而起伏，与那些深刻的思想和优美的语句为伴。有时候，仅仅是读到一段触动心灵的文字，就会让我感到内心充满力量，像是在黑暗中找到了一盏明灯，这种精神上的满足感是任何物质都无法替代的。还有与家人朋友共度的时光。大家围坐在一起，分享着日常的琐事，笑声在房间里回荡。》", SeaGreen);
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


