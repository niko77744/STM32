#include "Driver_USART.h"
#include "Com_Delay.h"
#include "Com_RTC.h"
#include "Com_IWDG.h"
#include "Driver_Key.h"

extern uint8_t Key3Bepressed;

int main(int argc, char const* argv[]) {
    Driver_USART_Init();
    Driver_KEY_Init();
    Com_IWDG_Init();
    printf("hello\n");


    while (1) {
        printf("代码正常执行 约3s\n");
        Delay_s(3);
        if (Key3Bepressed)
        {
            Key3Bepressed = 0;
            printf("按键被按下 程序卡死\n");
            while (1);
        }
        Com_IWDG_Refresh();
    }
}
