#include "Driver_USART.h"
#include "Com_Delay.h"
#include "Driver_ETH.h"


int main(int argc, char const* argv[]) {
    Driver_USART_Init();
    printf("hello eth...\n");
    Driver_LED_Init();

    Driver_ETH_Init();
    Web_serever_Init();
    Web_serever_Start();
    while (1) {
        // UDP_Socket(0);
    }
}


