#include "Driver_IIC_Soft.h"

// I2C2-SDA PB10
// I2C2-SCL PB11
void Driver_I2C_Soft_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

    // 通用开漏输出(总线结构 开漏) MODE=11  CNF=01
    GPIOB->CRH |= (GPIO_CRH_MODE10 | GPIO_CRH_MODE11);
    GPIOB->CRH |= (GPIO_CRH_CNF10_0 | GPIO_CRH_CNF11_0);
    GPIOB->CRH &= ~(GPIO_CRH_CNF10_1 | GPIO_CRH_CNF11_1);
}
void Driver_I2C_Soft_Start(void) {
    SDA_HIGH;
    SCL_HIGH;
    Delay_I2C_Soft;

    SDA_LOW;
    Delay_I2C_Soft;

    SCL_LOW;
    Delay_I2C_Soft;
}

void Driver_I2C_Soft_Stop(void) {
    SCL_HIGH;
    SDA_LOW;
    Delay_I2C_Soft;

    SDA_HIGH;
    Delay_I2C_Soft;
}
void Driver_I2C_Soft_SendAck(void) {
    SDA_LOW;
    Delay_I2C_Soft;

    SCL_HIGH;
    Delay_I2C_Soft;

    SCL_LOW;
    Delay_I2C_Soft;

    SDA_HIGH;
    Delay_I2C_Soft;
}

void Driver_I2C_Soft_SendNAck(void) {
    SDA_HIGH;
    Delay_I2C_Soft;

    SCL_HIGH;
    Delay_I2C_Soft;

    SCL_LOW;
    Delay_I2C_Soft;
}
uint8_t Driver_I2C_Soft_ReceivAck(void) {
    uint8_t ack;
    SDA_HIGH;
    Delay_I2C_Soft;

    SCL_LOW;
    Delay_I2C_Soft;

    SCL_HIGH;
    Delay_I2C_Soft;

    ack = READ_SDA;
    Delay_I2C_Soft;

    SCL_LOW;
    Delay_I2C_Soft;
    return ack;
}

void Driver_I2C_Soft_SendAddr(uint8_t addr) {
    for (uint8_t i = 0; i < 8; i++)
    {
        if ((addr & 0x80) == 0)
        {
            SDA_LOW;
        }
        else {
            SDA_HIGH;
        }
        SCL_HIGH;
        Delay_I2C_Soft;

        SCL_LOW;
        Delay_I2C_Soft;

        addr <<= 1;
    }
}

void Driver_I2C_Soft_Sendbyte(uint8_t byte) {
    for (uint8_t i = 0; i < 8; i++)
    {
        if ((byte & 0x80) == 0)
        {
            SDA_LOW;
        }
        else {
            SDA_HIGH;
        }
        SCL_HIGH;
        Delay_I2C_Soft;

        SCL_LOW;
        Delay_I2C_Soft;

        byte <<= 1;
    }
}
uint8_t Driver_I2C_Soft_Receivebyte(void) {
    uint8_t byte;
    for (uint8_t i = 0; i < 8; i++)
    {
        byte <<= 1;

        SCL_LOW;
        Delay_I2C_Soft;

        SCL_HIGH;
        Delay_I2C_Soft;

        if (READ_SDA)
        {
            byte |= 0x01;
        }
    }
    SCL_LOW;
    Delay_I2C_Soft;
    return byte;
}
