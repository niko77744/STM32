#include "Driver_IIC_Hard.h"


void Driver_I2C_Hard_Init(void) {
    // I2C2-SCL PB10  -------------  I2C2-SDA PB11 
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;

    // 复用开漏输出 MODE=11  CNF=11
    GPIOB->CRH |= (GPIO_CRH_CNF10 | GPIO_CRH_CNF11 | GPIO_CRH_MODE10 | GPIO_CRH_MODE11);

    I2C2->CCR &= ~I2C_CCR_FS;
    I2C2->CCR |= 180;
    I2C2->CR1 &= ~I2C_CR1_SMBUS;
    I2C2->CR2 |= 36;
    I2C2->TRISE |= 37;
    I2C2->CR1 |= I2C_CR1_PE;
}
uint8_t Driver_I2C_Hard_Start(void) {
    uint16_t timeout = 0xFFFF;
    I2C2->CR1 |= I2C_CR1_START;
    // 读取SR1寄存器后，写数据寄存器的操作将清除该位 !!!  在Driver_I2C_Hard_SendAddr写了DR
    while ((I2C2->SR1 & I2C_SR1_SB) == 0 && timeout--);
    return timeout ? Ok : Fail;
}
void Driver_I2C_Hard_Stop(void) {
    I2C2->CR1 |= I2C_CR1_STOP;
}

uint8_t Driver_I2C_Hard_SendAddr(uint8_t addr) {
    I2C2->DR = addr;
    uint16_t timeout = 0xFFFF;
    // 在软件读取SR1寄存器后，对SR2寄存器的读操作将清除该位，
    while ((I2C2->SR1 & I2C_SR1_ADDR) == 0 && timeout--);
    if (timeout)
    {
        I2C2->SR1;
        I2C2->SR2;
        return Ok;
    }
    else {
        return Fail;
    }
}
void Driver_I2C_Hard_SendAck(void) {
    I2C2->CR1 |= I2C_CR1_ACK;
}
void Driver_I2C_Hard_SendNAck(void) {
    I2C2->CR1 &= ~I2C_CR1_ACK;
}
uint8_t Driver_I2C_Hard_Sendbyte(uint8_t byte) {
    uint16_t timeout = 0xFFFF;
    // 写数据到DR寄存器可清除该位；
    while ((I2C2->SR1 & I2C_SR1_TXE) == 0 && timeout--);
    if (timeout)
    {
        I2C2->DR = byte;
    }
    else {
        return Fail;
    }
    timeout = 0xFFFF;
    // 在软件读取SR1寄存器后，对数据寄存器的读或写操作将清除该位或在传输中发送一个起始或停止条件后，或当PE=0时，由硬件清除该位。 !!! 后面都是start或stop
    while ((I2C2->SR1 & I2C_SR1_BTF) == 0 && timeout--);
    return timeout ? Ok : Fail;
}

uint8_t Driver_I2C_Hard_Receivebyte(void) {
    uint16_t timeout = 0xFFFF;
    // 对数据寄存器的读写操作清除该位
    while ((I2C2->SR1 & I2C_SR1_RXNE) == 0 && timeout--);
    return timeout ? I2C2->DR : Fail;
}

