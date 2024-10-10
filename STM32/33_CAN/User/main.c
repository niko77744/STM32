#include "Driver_USART.h"
#include "Com_Delay.h"
#include "Driver_CAN.h"

int main(int argc, char const* argv[]) {


    Driver_USART_Init();
    Driver_CAN_Init();
    printf("start\n");

    // Driver_CAN_SendBytes(7, "look", 5);
    // Driver_CAN_SendBytes(0x17, "hello", 6);
    // Driver_CAN_SendBytes(0x7FF, "pop", 4);

    // Delay_ms(100);


    CAN_RxData rxdata[3];
    uint8_t BytesConut;
    // Driver_CAN_ReceiveBytes(rxdata, &BytesConut);
    // for (uint8_t i = 0; i < BytesConut; i++)
    // {
    //     printf("The %d message,stdId:%d,length:%d,data:%s\n", i + 1, rxdata[i].stdID, rxdata[i].length, rxdata[i].data);
    // }

    while (1) {
        Driver_CAN_ReceiveBytes(rxdata, &BytesConut);
        for (uint8_t i = 0; i < BytesConut; i++)
        {
            printf("The %d message,stdId:%d,length:%d,data:%s\n", i + 1, rxdata[i].stdID, rxdata[i].length, rxdata[i].data);
        }
        Delay_s(1);
    }
}


