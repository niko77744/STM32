#include "Driver_SPI.h"


void Driver_SPI_Init(void) {
    /* SPI1:  NSS:PC13      SCK:PA5     MISO:PA6    MOSI:PA7 */
    /* SPI2:  NSS:PD3       SCK:PB13    MISO:PB14   MOSI:PB15 */
    /* SPI3:  NSS:unknown   SCK:PB3     MISO:PB4    MOSI:PB5 */

    /* 72MHz */
    // RCC->APB2ENR |= (RCC_APB2ENR_SPI1EN | RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPCEN);
    // Hal_GPIO_Mode_Selection(GPIOC, GPIO_pin_13, GPIO_Mode_Out_PP);
    // Hal_GPIO_Mode_Selection(GPIOA, GPIO_pin_5, GPIO_Mode_AF_PP);
    // Hal_GPIO_Mode_Selection(GPIOA, GPIO_pin_6, GPIO_Mode_IN_FLOATING);
    // Hal_GPIO_Mode_Selection(GPIOA, GPIO_pin_7, GPIO_Mode_AF_PP);

    // /* 双线双向模式 | 8位数据帧格式进行发送/接收 | 先发高位 | BR预分频清零 | 相位从第一个边沿采样 | 极性空闲为低电平*/
    // SPI1->CR1 &= ~(SPI_CR1_BIDIMODE | SPI_CR1_DFF | SPI_CR1_LSBFIRST | SPI_CR1_BR | SPI_CR1_CPHA | SPI_CR1_CPOL);
    // /* 启用软件从设备管理|NSS上的电平 | 分频不超过18MHz 4分频 | 配置为主设备 | SPI使能*/
    // SPI1->CR1 |= (SPI_CR1_SSM | SPI_CR1_SSI | SPI_CR1_BR_0 | SPI_CR1_MSTR | SPI_CR1_SPE);


    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

    // CS(NSS / SS)片选： 通用推挽输出 MODE = 11 CNF = 00
    GPIOC->CRH &= ~GPIO_CRH_CNF13;
    GPIOC->CRH |= GPIO_CRH_MODE13;

    // SCK和输出MOSI  复用推挽输出  MODE=11 CNF=10
    GPIOA->CRL &= ~GPIO_CRL_CNF5_0;
    GPIOA->CRL |= GPIO_CRL_CNF5_1;
    GPIOA->CRL |= GPIO_CRL_MODE5;

    GPIOA->CRL &= ~GPIO_CRL_CNF7_0;
    GPIOA->CRL |= GPIO_CRL_CNF7_1;
    GPIOA->CRL |= GPIO_CRL_MODE7;

    // 浮空输入 MDOE = 00 CNF = 01
    GPIOA->CRL &= ~(GPIO_CRL_CNF6_1 | GPIO_CRL_MODE6);
    GPIOA->CRL |= GPIO_CRL_CNF6_0;
    SPI1->CR1 &= ~SPI_CR1_BIDIMODE;  //0：选择“双线双向”模式
    SPI1->CR1 &= ~SPI_CR1_DFF;   // 数据帧格式(Data frame format)   0：使用8位数据帧格式进行发送/接收
    SPI1->CR1 |= SPI_CR1_SSM;    // 软件从设备管理 (Software slave management)  1：启用软件从设备管理。
    SPI1->CR1 |= SPI_CR1_SSI;   //SSI：内部从设备选择 (Internal slave select) 
    SPI1->CR1 &= ~SPI_CR1_LSBFIRST;  // 帧格式 (Frame format)  0：先发送MSB；
    SPI1->CR1 |= SPI_CR1_BR_0; // 001 fPCLK/4 = 72/4 = 18MHz
    SPI1->CR1 |= SPI_CR1_MSTR; // 主设备选择 (Master selection)  1：配置为主设备
    SPI1->CR1 &= ~SPI_CR1_CPOL; // 时钟极性 (Clock polarity)  0： 空闲状态时，SCK保持低电平；
    SPI1->CR1 &= ~SPI_CR1_CPHA; // CPHA：时钟相位 (Clock phase)  0： 数据采样从第一个时钟边沿开始
    SPI1->CR1 |= SPI_CR1_SPE;
}
void Driver_SPI_CS_Start(void) {
    /* 低电平有效 CS_LOW */
    HAL_GPIO_WritePin(GPIOC, GPIO_pin_13, GPIO_PIN_RESET);
}
void Driver_SPI_CS_Stop(void) {
    /* 低电平有效 CS_High */
    HAL_GPIO_WritePin(GPIOC, GPIO_pin_13, GPIO_PIN_SET);
}
uint8_t Driver_SPI_SwapData(uint8_t T_Data) {
    uint16_t timeout = 0xFFFF;
    // 等待发送数据寄存器为空
    while (((SPI1->SR & SPI_SR_TXE) == 0) && timeout--);
    SPI1->DR = T_Data;

    timeout = 0xFFFF;
    // 等待接收数据寄存器不为空
    while (((SPI1->SR & SPI_SR_RXNE) == 0) && timeout--);
    return SPI1->DR;
}
