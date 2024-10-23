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

    // /* ˫��˫��ģʽ | 8λ����֡��ʽ���з���/���� | �ȷ���λ | BRԤ��Ƶ���� | ��λ�ӵ�һ�����ز��� | ���Կ���Ϊ�͵�ƽ*/
    // SPI1->CR1 &= ~(SPI_CR1_BIDIMODE | SPI_CR1_DFF | SPI_CR1_LSBFIRST | SPI_CR1_BR | SPI_CR1_CPHA | SPI_CR1_CPOL);
    // /* ����������豸����|NSS�ϵĵ�ƽ | ��Ƶ������18MHz 4��Ƶ | ����Ϊ���豸 | SPIʹ��*/
    // SPI1->CR1 |= (SPI_CR1_SSM | SPI_CR1_SSI | SPI_CR1_BR_0 | SPI_CR1_MSTR | SPI_CR1_SPE);


    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

    // CS(NSS / SS)Ƭѡ�� ͨ��������� MODE = 11 CNF = 00
    GPIOC->CRH &= ~GPIO_CRH_CNF13;
    GPIOC->CRH |= GPIO_CRH_MODE13;

    // SCK�����MOSI  �����������  MODE=11 CNF=10
    GPIOA->CRL &= ~GPIO_CRL_CNF5_0;
    GPIOA->CRL |= GPIO_CRL_CNF5_1;
    GPIOA->CRL |= GPIO_CRL_MODE5;

    GPIOA->CRL &= ~GPIO_CRL_CNF7_0;
    GPIOA->CRL |= GPIO_CRL_CNF7_1;
    GPIOA->CRL |= GPIO_CRL_MODE7;

    // �������� MDOE = 00 CNF = 01
    GPIOA->CRL &= ~(GPIO_CRL_CNF6_1 | GPIO_CRL_MODE6);
    GPIOA->CRL |= GPIO_CRL_CNF6_0;
    SPI1->CR1 &= ~SPI_CR1_BIDIMODE;  //0��ѡ��˫��˫��ģʽ
    SPI1->CR1 &= ~SPI_CR1_DFF;   // ����֡��ʽ(Data frame format)   0��ʹ��8λ����֡��ʽ���з���/����
    SPI1->CR1 |= SPI_CR1_SSM;    // ������豸���� (Software slave management)  1������������豸����
    SPI1->CR1 |= SPI_CR1_SSI;   //SSI���ڲ����豸ѡ�� (Internal slave select) 
    SPI1->CR1 &= ~SPI_CR1_LSBFIRST;  // ֡��ʽ (Frame format)  0���ȷ���MSB��
    SPI1->CR1 |= SPI_CR1_BR_0; // 001 fPCLK/4 = 72/4 = 18MHz
    SPI1->CR1 |= SPI_CR1_MSTR; // ���豸ѡ�� (Master selection)  1������Ϊ���豸
    SPI1->CR1 &= ~SPI_CR1_CPOL; // ʱ�Ӽ��� (Clock polarity)  0�� ����״̬ʱ��SCK���ֵ͵�ƽ��
    SPI1->CR1 &= ~SPI_CR1_CPHA; // CPHA��ʱ����λ (Clock phase)  0�� ���ݲ����ӵ�һ��ʱ�ӱ��ؿ�ʼ
    SPI1->CR1 |= SPI_CR1_SPE;
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
