#include "Driver_CAN.h"

void Driver_CAN_Init(void) {
    RCC->APB1ENR |= RCC_APB1ENR_CAN1EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

    AFIO->MAPR |= AFIO_MAPR_CAN_REMAP_1;
    AFIO->MAPR &= ~AFIO_MAPR_CAN_REMAP_0;

    //PB9(CAN_Tx)：复用推挽输出 PB8(CAN_Rx): 浮空输入 
    Hal_GPIO_Mode_Selection(GPIOB, GPIO_pin_9, GPIO_Mode_AF_PP);
    Hal_GPIO_Mode_Selection(GPIOB, GPIO_pin_8, GPIO_Mode_IN_FLOATING);

    CAN1->sTxMailBox[0].TIR |= CAN_TI0R_TXRQ;

}
void Driver_CAN_SendBytes(uint16_t stdID, uint8_t* bytes, uint8_t length);
void Driver_CAN_ReceiveBytes(Driver_CAN_Rx CAN_Rx[], uint8_t* BytesConut) {
    //将一个字符数组初始化为全 0（实际上是 '\0' 字符）
    char str[10];
    memset(str, 0, sizeof(str));
}
