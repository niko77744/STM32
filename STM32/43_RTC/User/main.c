#include "Driver_USART.h"
#include "Com_Delay.h"
#include "Com_RTC.h"
#include "Com_Sleep.h"
#include "Driver_LED.h"

int main(int argc, char const* argv[]) {
    Driver_USART_Init();
    RTC_TimeTypeDef datenow;
    Driver_LED_Init();
    printf("hello\n");
    // Driver_LED_On(LED3);
    Com_RTC_Init();


    // Com_RTC_SetTime(1729298798);
    STANDBYMode_WUF();

    while (1) {
        Com_RTC_GetTime(&datenow);
        printf("当前时间：%s\n", datenow.now);
        Delay_s(3);

        // printf("6s后进入待机模式\n");
        // Delay_s(3);
        // // Driver_LED_Off(LED3);
        // Com_RTC_WakeUp(10);
        // HAL_PWR_EnterSTANDBYMode();
    }
}
