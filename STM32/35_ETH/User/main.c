#include "Driver_USART.h"
#include "Com_Delay.h"
#include "Driver_ETH.h"


int main(int argc, char const* argv[]) {
    Driver_USART_Init();
    printf("hello eth...\n");

    Driver_ETH_Init();
    while (1);
}


