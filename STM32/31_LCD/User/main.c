#include "Driver_USART.h"
#include "Driver_FSMC.h"
#include "GPIO.h"
#include "Inf_LCD.h"
#include "Com_Delay.h"
#include "Inf_w25q32.h"
#include "Inf_LCD_font.h"



int main(int argc, char const* argv[]) {

    // 1.��ʼ��ģ��
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



    // 2.��ȡID����оƬ�Ƿ����� 0x548066
    uint32_t id = Inf_LCD_ReadID();
    printf("ID = %#x\n", id);

    // 3.ʹ��ָ����ɫ�����������
    Inf_LCD_Clear(Black);

    // 4.����Ļ����ʾһ���ַ� 480~320PX
    // Inf_LCD_DisplayChar(100, 100, SS, 'e', LightCoral, White);
    // Inf_LCD_DisplayChar(300, 300, SL, 'f', Black, LightCoral);
    // Inf_LCD_DisplayChar(200, 200, LS, 'G', LightCoral, White);
    // Inf_LCD_DisplayChar(0, 0, LL, 'H', Black, LightCoral);
    // Inf_LCD_DisplayString(300, 20, LL, "Hel\nlo World", Black, White);
    // Inf_LCD_DispalyPicture(0, 0);
    // Inf_LCD_DispalySingleChinese(100, 100, 0, Black, White);
    // Inf_LCD_DispalySingleChinese(132, 100, 1, Black, White);
    // Inf_LCD_DispalySingleChinese(164, 100, 2, Black, White);
    Inf_LCD_DisplayChinese(0, 0, 16, "��������ĳ����У�����һЩ΢С��ȷʵ���Ҹ�����ͬ��㷱����������ƽ�������ӣ���ЩСȷ�һ���΢�������ȴ�����������ĵ��������峿������һ������͸�������ķ�϶������������ϣ���˿˿ů�����һ��Сȷ�ҡ����ڰ��ΰ���֮�������������������һ��Ŀ�ʼ��û�з����������Ĵ��ţ����ּ򵥵�������һ�����ȵ�ţ�̣���������������ڽ�ͷ��β��żȻ���ŵ�һ����Ϥ�Ļ��㡣���ǽֽ������²�֪����С��ɢ�������ķҷ����һ᲻��������ͣ�½Ų�������һ���������ǵ��ŵ�����������ǻ����һ˲�䣬�·�ʱ�䶼Ϊ���ƻ������ֹ����Χ��һ�����Ӷ���ʧ������ֻ�����Լ�����һĨ��Ȼ�����ã����Ǵ���Ȼ������Сȷ�ҡ�����һ���飬�����ֵĺ���������Ҳ��һ��Сȷ�ҡ����ҳ�����һ��������ʱ���ҷ·��������һ�����硣�����������˹���ϲŭ���ֶ����������Щ��̵�˼������������Ϊ�顣��ʱ�򣬽����Ƕ���һ�δ�����������֣��ͻ����Ҹе����ĳ��������������ںڰ����ҵ���һյ���ƣ����־����ϵ���������κ����ʶ��޷�����ġ�������������ѹ��ȵ�ʱ�⡣���Χ����һ�𣬷������ճ������£�Ц���ڷ�����ص�����", SeaGreen);
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
    // Inf_LCD_DisplayChinese(80, 120, 16, "������ʮ��ÿ����", Green);
    */

    while (1) {
        // Inf_LCD_BouncingBall();
    }
}


