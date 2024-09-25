#include "Driver_SPI.h"

// 输出引脚:  SCK：PA5;    MOSI(主输出)：PA7;    SC#(Chip Selection片选)：PC13
// 输入引脚： MISO(主输入)：PA6
void Driver_SPI_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

    // 通用推挽输出 MODE=11 CNF=00
    GPIOC->CRH &= ~GPIO_CRH_CNF13;
    GPIOC->CRH |= GPIO_CRH_MODE13;

    GPIOA->CRL &= ~GPIO_CRL_CNF5;
    GPIOA->CRL |= GPIO_CRL_MODE5;

    GPIOA->CRL &= ~GPIO_CRL_CNF7;
    GPIOA->CRL |= GPIO_CRL_MODE7;

    // 浮空输入 MDOE=00 CNF=01
    GPIOA->CRL &= ~(GPIO_CRL_CNF6_1 | GPIO_CRL_MODE6);
    GPIOA->CRL |= GPIO_CRL_CNF6_0;

    // 选择模式0   极性POL和相位PHA=0  初始时钟为低电平，等待第一个上升沿
    SCK_LOW;

    // 片选CS#线默认不选中(高电平) 相当于使能 当Start时才打开
    CS_HIGH;
}


void Driver_SPI_Start(void) {
    CS_LOW;
    SPI_DELAY;
}

void Driver_SPI_Stop(void) {
    CS_HIGH;
    SPI_DELAY;
}

// 与芯片交换一个字节  在时钟线SCK=1时采集数据
uint8_t Driver_SPI_SwapByte(uint8_t T_byte) {
    uint8_t R_byte = 0;
    for (uint8_t i = 0; i < 8; i++)
    {
        // 先准备好数据
        ((T_byte << i) & 0x80) == 0 ? MOSI_LOW : MOSI_HIGH;

        // 拉高时钟线，采集数据
        SCK_HIGH;
        SPI_DELAY;

        // 同时采集来自外设的数据
        R_byte <<= 1;
        MISO_READ == 0 ? ((R_byte) |= 0x00) : (R_byte |= 0x01);

        // 拉低时钟，为下次发送准备
        SCK_LOW;
        SPI_DELAY;
    }
    return R_byte;
}
