#include "Driver_SPI.h"


void Driver_SPI_Init(void) {
    /* SPI1:  NSS:PC13      SCK:PA5     MISO:PA6    MOSI:PA7 */
    /* SPI2:  NSS:PD3       SCK:PB13    MISO:PB14   MOSI:PB15 */
    /* SPI3:  NSS:unknown   SCK:PB3     MISO:PB4    MOSI:PB5 */

    /* 72MHz */
    RCC->APB2ENR |= (RCC_APB2ENR_SPI1EN | RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPCEN);
    Hal_GPIO_Mode_Selection(GPIOC, GPIO_pin_13, GPIO_Mode_Out_PP);
    Hal_GPIO_Mode_Selection(GPIOA, GPIO_pin_5, GPIO_Mode_AF_PP);
    Hal_GPIO_Mode_Selection(GPIOA, GPIO_pin_6, GPIO_Mode_IN_FLOATING);
    Hal_GPIO_Mode_Selection(GPIOA, GPIO_pin_7, GPIO_Mode_AF_PP);

    /* 双线双向模式 | 8位数据帧格式进行发送/接收 | 先发高位 | BR预分频清零 | 相位从第一个边沿采样 | 极性空闲为低电平*/
    SPI1->CR1 &= ~(SPI_CR1_BIDIMODE | SPI_CR1_DFF | SPI_CR1_LSBFIRST | SPI_CR1_BR | SPI_CR1_CPHA | SPI_CR1_CPOL);
    /* 启用软件从设备管理|NSS上的电平 | 分频不超过18MHz 4分频 | 配置为主设备 | SPI使能*/
    SPI1->CR1 |= (SPI_CR1_SSM | SPI_CR1_SSI | SPI_CR1_BR_0 | SPI_CR1_MSTR | SPI_CR1_SPE);
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
