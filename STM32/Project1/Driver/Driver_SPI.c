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

    /* ˫��˫��ģʽ | 8λ����֡��ʽ���з���/���� | �ȷ���λ | BRԤ��Ƶ���� | ��λ�ӵ�һ�����ز��� | ���Կ���Ϊ�͵�ƽ*/
    SPI1->CR1 &= ~(SPI_CR1_BIDIMODE | SPI_CR1_DFF | SPI_CR1_LSBFIRST | SPI_CR1_BR | SPI_CR1_CPHA | SPI_CR1_CPOL);
    /* ����������豸����|NSS�ϵĵ�ƽ | ��Ƶ������18MHz 4��Ƶ | ����Ϊ���豸 | SPIʹ��*/
    SPI1->CR1 |= (SPI_CR1_SSM | SPI_CR1_SSI | SPI_CR1_BR_0 | SPI_CR1_MSTR | SPI_CR1_SPE);
}

void Driver_SPI_CS_Start(void) {
    /* �͵�ƽ��Ч CS_LOW */
    HAL_GPIO_WritePin(GPIOC, GPIO_pin_13, GPIO_PIN_RESET);
}
void Driver_SPI_CS_Stop(void) {
    /* �͵�ƽ��Ч CS_High */
    HAL_GPIO_WritePin(GPIOC, GPIO_pin_13, GPIO_PIN_SET);
}
uint8_t Driver_SPI_SwapData(uint8_t T_Data) {
    uint16_t timeout = 0xFFFF;
    // �ȴ��������ݼĴ���Ϊ��
    while (((SPI1->SR & SPI_SR_TXE) == 0) && timeout--);
    SPI1->DR = T_Data;

    timeout = 0xFFFF;
    // �ȴ��������ݼĴ�����Ϊ��
    while (((SPI1->SR & SPI_SR_RXNE) == 0) && timeout--);
    return SPI1->DR;
}
