#include "Driver_IIC.h"



void Driver_I2C_Init(void) {
    // 1.开启时钟
    RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

    // 2.使用I2C2   PB10：SCL    PB11：SDA
    // 软件模拟，通用开漏输出 MDOE11 CNF01
    GPIOB->CRH |= (GPIO_CRH_MODE10 | GPIO_CRH_MODE11);
    GPIOB->CRH &= ~(GPIO_CRH_CNF10_1 | GPIO_CRH_CNF11_1);
    GPIOB->CRH |= (GPIO_CRH_CNF10_0 | GPIO_CRH_CNF11_0);

    // 软件模拟不需要开启IIC模块
}

void Driver_I2C_Start(void) {
    SDA_Up;
    SCL_Up;
    Delay_I2C2;

    SDA_Down;
    Delay_I2C2;


    SCL_Down;
    Delay_I2C2;
}
void Driver_I2C_Stop(void) {
    SDA_Down;
    SCL_Up;
    Delay_I2C2;

    SDA_Up;
    Delay_I2C2;
}

uint8_t Driver_I2C_ReceiveAck(void) {
    uint8_t ack;
    // 释放SDA总线
    SDA_Up;
    Delay_I2C2;

    SCL_Down;
    Delay_I2C2;

    SCL_Up;
    Delay_I2C2;

    ack = Read_SDA;
    SCL_Down;
    Delay_I2C2;

    return (ack == 0) ? ACK : NACK;
}

void Driver_I2C_SendAck(void) {
    SDA_Down;
    Delay_I2C2;

    SCL_Up;
    Delay_I2C2;

    SCL_Down;
    Delay_I2C2;

    SDA_Up;
    Delay_I2C2;
}
void Driver_I2C_SendNAck(void) {
    SDA_Up;
    Delay_I2C2;

    SCL_Up;
    Delay_I2C2;

    SCL_Down;
    Delay_I2C2;
}

void Driver_I2C_Sendbyte(uint8_t byte) {
    for (uint8_t i = 0; i < 8; i++)
    {
        SCL_Down;
        Delay_I2C2;

        (byte & 0x80) == 0 ? SDA_Down : SDA_Up;
        byte << 1;

        SCL_Up;
        Delay_I2C2;
    }
    SCL_Down;
    Delay_I2C2;
}
uint8_t Driver_I2C_Receivebyte(void) {
    uint8_t byte;
    for (uint8_t i = 0; i < 8; i++)
    {
        SCL_Up;
        Delay_I2C2;

        byte << 1;
        byte = Read_SDA;

        SCL_Down;
        Delay_I2C2;
    }
}