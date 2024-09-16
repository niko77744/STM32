#include "Driver_IIC.h"

void Driver_I2C_Init(void) {
    // 1.开启时钟
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

    // 2.使用I2C2   PB10：SCL    PB11：SDA
    // 软件模拟，通用开漏输出 MDOE11 CNF01
    GPIOB->CRH |= (GPIO_CRH_MODE10 | GPIO_CRH_MODE11);
    GPIOB->CRH &= ~(GPIO_CRH_CNF10_1 | GPIO_CRH_CNF11_1);
    GPIOB->CRH |= (GPIO_CRH_CNF10_0 | GPIO_CRH_CNF11_0);

    // 软件模拟不需要开启IIC模块
}


void Driver_I2C_Start(void) {
    SDA_HIGH;
    SCL_HIGH;
    Delay_I2C2;

    SDA_LOW;
    Delay_I2C2;

    SCL_LOW;
    Delay_I2C2;
}
void Driver_I2C_Stop(void) {
    SCL_HIGH;
    // 中间不能delay
    SDA_LOW;
    Delay_I2C2;

    SDA_HIGH;
    Delay_I2C2;
}


void Driver_I2C_SendAck(void) {

    SDA_LOW;
    Delay_I2C2;

    SCL_HIGH;
    Delay_I2C2;

    SCL_LOW;
    Delay_I2C2;

    // 记得拉回sda
    SDA_HIGH;
    Delay_I2C2;
}
void Driver_I2C_SendNAck(void) {
    SDA_HIGH;
    Delay_I2C2;

    SCL_HIGH;
    Delay_I2C2;

    SCL_LOW;
    Delay_I2C2;
}

uint8_t Driver_I2C_ReceiveAck(void) {
    uint8_t ack;
    // 释放总线
    SDA_HIGH;
    Delay_I2C2;

    SCL_HIGH;
    Delay_I2C2;

    ack = READ_SDA;
    Delay_I2C2;

    SCL_LOW;
    Delay_I2C2;

    return ack;
}

void Driver_I2C_Sendbyte(uint8_t byte) {
    for (uint8_t i = 0; i < 8; i++)
    {
        // 注意：发送的高低电平都要发送
        (byte & 0x80) == 0 ? SDA_LOW : SDA_HIGH;

        SCL_HIGH; // 拉高时钟线，完成SDA的采集信号，然后拉低时钟线
        Delay_I2C2;

        SCL_LOW;
        Delay_I2C2;
        byte <<= 1;
    }
}
uint8_t Driver_I2C_Receivebyte(void) {
    uint8_t byte;
    // SDA_HIGH;
    for (uint8_t i = 0; i < 8; i++)
    {
        SCL_LOW;
        Delay_I2C2;

        byte <<= 1;

        // 注意  byte = (byte << 1) | READ_SDA; 错误
        if (READ_SDA)
        {
            byte |= 0x01;
        }

        SCL_HIGH;
        Delay_I2C2;
    }

    SCL_LOW;
    Delay_I2C2;
    return byte;
}
 