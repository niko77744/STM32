#include "Driver_Usart.h"
#include "Com_Debug.h"
#include "Com_Delay.h"

int main(int argc, char const* argv[])
{
    Debug_Init();

    while (1) {
        debug_print("hello");
        Delay_s(1);
    }
}


