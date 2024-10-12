#include "Driver_USART.h"
#include "Driver_CAN.h"

int main(int argc, char const* argv[]) {
    Driver_USART_Init();
    HAL_CAN_MspInit(CAN1);

    HAL_CAN_AddTxMessage(CAN1, 2, "hello", 5);
    HAL_CAN_AddTxMessage(CAN1, 3, "llll", 4);
    HAL_CAN_AddTxMessage(CAN1, 6, "pppppp", 6);
    HAL_CAN_AddTxMessage(CAN1, 9, "qqqqq", 5);
    HAL_CAN_AddTxMessage(CAN1, 10, "wwww", 4);
    // HAL_CAN_AddTxMessage(CAN1, 11, "eeeeee", 6);
    while (1);
}


