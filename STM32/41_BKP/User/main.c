#include "Driver_USART.h"
#include "Com_Delay.h"
#include "Driver_LED.h"
#include "Driver_Key.h"
#include "Com_BKP.h"

int main(int argc, char const* argv[]) {
    Driver_USART_Init();
    Driver_LED_Init();
    Driver_KEY_Init();
    Com_RTCEx_BKPInit();
    printf("hello\n");

    
    // Com_RTCEx_BKPWrite(RTC_BKP_DR1, 9999);
    uint32_t bkpdata = Com_RTCEx_BPKRead(RTC_BKP_DR1);
    printf("bkpdata = %d\n", bkpdata);
    printf("DK1 = %d \n", BKP->DR1);

    while (1);
}
