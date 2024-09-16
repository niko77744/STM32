#include "Driver_IIC.h"

void Driver_I2C_Init(void) {
    // 1.开启时钟   使用IIC2，在APB1
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;

    // 2.使用I2C2   PB10：SCL    PB11：SDA
    // 软件模拟，复用开漏输出 MDOE11 CNF11
    GPIOB->CRH |= (GPIO_CRH_MODE10 | GPIO_CRH_MODE11);
    GPIOB->CRH |= (GPIO_CRH_CNF10 | GPIO_CRH_CNF11);

    // 3.配置I2C2，模块
    // 3.1 配置使用I2C模式  默认配置0 I2C   1  SMBus
    I2C2->CR1 &= ~I2C_CR1_SMBUS;

    // 3.2 I2C_CR2_FREQ  CR2时钟频率  36MHz
    I2C2->CR2 |= 36;

    // 3.3 配置标准模式  0:100k   1:400k
    I2C2->CCR &= ~I2C_CCR_FS;

    // 3.4 配置CCR 快速/标准模式下的时钟控制分频系数
    // stm32中IIC模块中标准模式速率100kb下，时钟频率是36Mhz，在I2C标准模式或SMBus模式下：Thigh = CCR ×TPCLK1Tlow = CCR ×TPCLK1，crr设置为多少
    // Th = Tl = CCR × Tpclk[1/36Mhz]
    // 100kb/s== 100khz== Fiic == 1/(Th+Tl) == 1/(2*CRR*Tpclk)
    // 100kHz = 1/(2*CRR*(1/36Mhz))  CRR=180; 在最低位
    // 简单计算：总频率*10/2
    I2C2->CCR |= 180;

    // 3.5 配置上升沿最大时间 1us+1个时钟周期
    // 标准模式TRISE = (t_r/ TPCLK1) + 1
    // TPCLK1 = 1/36MHz ≈ 27.78ns，通常 t_r 的最大值为 1000ns。
    // 简单计算：总频率+1
    I2C2->TRISE |= 37;

    // 3.6 I2C模块使能
    I2C2->CR1 |= I2C_CR1_PE;
}


uint8_t Driver_I2C_Start(void) {
    // 1.开始循环发送起始信号
    I2C2->CR1 |= I2C_CR1_START;

    // 2.判断发送成功  SB 起始位(主模式) (Start bit)
    // 软件读取SR1寄存器后，写数据寄存器DR的操作将清除该位 
    uint16_t timeout = 0xffff;
    while ((I2C2->SR1 & I2C_SR1_SB) == 0 && timeout--);

    // 3.根据timeout结果返回值
    return timeout ? Ok : Error;
}
void Driver_I2C_Stop(void) {
    //在硬件清除这个位之前，软件不要执行任何对2C_CR1的写操作
    I2C2->CR1 |= I2C_CR1_STOP;
}

// 配置在接收完成一个字节后产生一个ACK信号
void Driver_I2C_SendAck(void) {
    //1：在接收到一个字节后返回一个应答(匹配的地址或数据)。
    I2C2->CR1 |= I2C_CR1_ACK;
}
void Driver_I2C_SendNAck(void) {
    // 0：无应答返回；
    I2C2->CR1 &= ~I2C_CR1_ACK;
}

uint8_t Driver_I2C_SendAddr(uint8_t addr) {
    // 1.写地址到输出数据寄存器 
    I2C2->DR = addr;  //注意：不能|=

    // 2.判断是否发送地址成功 
    uint16_t timeout = 0xffff;
    // 1：地址发送结束,当收到地址的ACK后该位被置1
    // 在软件读取SR1寄存器后，对SR2寄存器的读操作将清除该位
    while ((I2C2->SR1 & I2C_SR1_ADDR) == 0 && timeout--);

    // 3.返回是否发送地址成功 
    if (timeout)
    {
        // 清理ADDR标志位
        I2C2->SR1;
        I2C2->SR2;
        return Ok;
    }
    else {
        return Error;
    }
}

// uint8_t Driver_I2C_ReceiveAck(void) //自动接收ack

uint8_t Driver_I2C_Sendbyte(uint8_t byte) {
    // 1.等待发送数据寄存器为空 
    uint16_t timeout = 0xffff;
    //  软件写数据到DR寄存器可清除该位
    while ((I2C2->SR1 & I2C_SR1_TXE) == 0 && timeout--);

    // 2.判断是否超时,决定要不要写出数据 
    if (timeout)
    {
        I2C2->DR = byte;
    }
    else {
        return Error;
    }

    // 3.等待发送完成,ACK 
    timeout = 0xffff;
    //字节发送结束 (Byte transfer finished)  1：字节发送结束
    // 在软件读取SR1寄存器后，对数据寄存器DR的读或写操作将清除该位
    while ((I2C2->SR1 & I2C_SR1_BTF) == 0 && timeout--);

    // 4.返回是否发送成功 
    return timeout ? Ok : Error;
}


uint8_t Driver_I2C_Receivebyte(void) {
    uint16_t timeout = 0xffff;
    // 软件对数据寄存器DR的读写操作清除该位
    while ((I2C2->SR1 & I2C_SR1_RXNE) == 0 && timeout--);
    uint8_t byte = timeout ? I2C2->DR : Error;
    return byte;
}
