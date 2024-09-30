#include "Driver_USART.h"
#include "Driver_FSMC.h"
#include "GPIO.h"
#include "Inf_LCD.h"



int main(int argc, char const* argv[]) {
    // 1.��ʼ��USART1ģ��
    Driver_USART_Init();
    Inf_LCD_Init();

    // 2.��ȡID����оƬ�Ƿ����� 0x548066
    printf("Atguigu~\n");
    uint32_t id = Inf_LCD_ReadID();
    printf("ID = %#x\n", id);

    // 3.ʹ��ָ����ɫ�����������
    Inf_LCD_Clear(WHITE);

    // 4.����Ļ����ʾһ���ַ� 480~320PX
    Inf_LCD_DisplayChar(100, 100, SS, 'e', BLACK, WHITE);
    Inf_LCD_DisplayChar(300, 300, SL, 'f', BLACK, WHITE);
    Inf_LCD_DisplayChar(200, 200, LS, 'G', BLACK, WHITE);
    Inf_LCD_DisplayChar(0, 0, LL, 'H', BLACK, WHITE);


    while (1);
}


