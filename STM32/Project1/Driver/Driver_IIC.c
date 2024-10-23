#include "Driver_IIC.h"


void Driver_IIC_Init(void) {
    //  I2C2-SCL PB10     I2C2-SDA PB11
    RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    Hal_GPIO_Mode_Selection(GPIOB, GPIO_pin_10, GPIO_Mode_AF_OD);
    Hal_GPIO_Mode_Selection(GPIOB, GPIO_pin_11, GPIO_Mode_AF_OD);

    I2C2->CR1 &= ~I2C_CR1_SMBUS;
}
void Driver_IIC_Start(void);
void Driver_IIC_Stop(void);
void Driver_IIC_SendACK(void);
void Driver_IIC_SendAddr(void);
void Driver_IIC_SendNACK(void);
void Driver_IIC_SendData(uint8_t* data);
void Driver_IIC_ReceiveData(uint8_t* data);
