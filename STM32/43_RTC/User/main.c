#include "Driver_USART.h"
#include "Com_Delay.h"
#include "Com_RTC.h"

int main(int argc, char const* argv[]) {
    Driver_USART_Init();
    printf("hello\n");
    RTC_TimeTypeDef datenow;
    Com_RTC_Init();
    printf("init\n");
    // Com_RTC_SetTime(1729248967);
    printf("settime\n");

    while (1) {
        Com_RTC_GetTime(&datenow);
        printf("当前时间：%s\n", datenow.now);
        Delay_s(1);
    }
}
