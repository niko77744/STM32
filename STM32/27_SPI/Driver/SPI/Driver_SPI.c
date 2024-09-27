#include "Driver_SPI.h"

/* Ӳ����ʽʵ�֣�----------------------------------------------------------- */

// �������:  SCK��PA5;    MOSI(�����)��PA7;    SC#(Chip SelectionƬѡ)��PC13
// �������ţ� MISO(������)��PA6
void Driver_SPI_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
    RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

    // CS(NSS/SS)Ƭѡ�� ͨ��������� MODE=11 CNF=00
    GPIOC->CRH &= ~GPIO_CRH_CNF13;
    GPIOC->CRH |= GPIO_CRH_MODE13;

    // SCK�����MOSI  �����������  MODE=11 CNF=10
    GPIOA->CRL &= ~GPIO_CRL_CNF5_0;
    GPIOA->CRL |= GPIO_CRL_CNF5_1;
    GPIOA->CRL |= GPIO_CRL_MODE5;

    GPIOA->CRL &= ~GPIO_CRL_CNF7_0;
    GPIOA->CRL |= GPIO_CRL_CNF7_1;
    GPIOA->CRL |= GPIO_CRL_MODE7;

    // �������� MDOE=00 CNF=01
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


void Driver_SPI_Start(void) {
    CS_LOW;
}

void Driver_SPI_Stop(void) {
    CS_HIGH;
}

// ��оƬ����һ���ֽ�  ��ʱ����SCK=1ʱ�ɼ�����
uint8_t Driver_SPI_SwapByte(uint8_t T_byte) {
    uint16_t timeout = 0xFFFF;
    // �ȴ��������ݼĴ���Ϊ��
    while (((SPI1->SR & SPI_SR_TXE) == 0) && timeout--);
    SPI1->DR = T_byte;

    timeout = 0xFFFF;
    // �ȴ��������ݼĴ�����Ϊ��
    while (((SPI1->SR & SPI_SR_RXNE) == 0) && timeout--);
    return SPI1->DR;
}



/* �����ʽʵ�֣�----------------------------------------------------------- */


// �������:  SCK��PA5;    MOSI(�����)��PA7;    SC#(Chip SelectionƬѡ)��PC13
// �������ţ� MISO(������)��PA6
void Driver_SPI_Soft_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;

    // ͨ��������� MODE=11 CNF=00
    GPIOC->CRH &= ~GPIO_CRH_CNF13;
    GPIOC->CRH |= GPIO_CRH_MODE13;

    GPIOA->CRL &= ~GPIO_CRL_CNF5;
    GPIOA->CRL |= GPIO_CRL_MODE5;

    GPIOA->CRL &= ~GPIO_CRL_CNF7;
    GPIOA->CRL |= GPIO_CRL_MODE7;

    // �������� MDOE=00 CNF=01
    GPIOA->CRL &= ~(GPIO_CRL_CNF6_1 | GPIO_CRL_MODE6);
    GPIOA->CRL |= GPIO_CRL_CNF6_0;

    // ѡ��ģʽ0   ����POL����λPHA=0  ��ʼʱ��Ϊ�͵�ƽ���ȴ���һ��������
    SCK_LOW;

    // ƬѡCS#��Ĭ�ϲ�ѡ��(�ߵ�ƽ) �൱��ʹ�� ��Startʱ�Ŵ�
    CS_HIGH;
}


void Driver_SPI_Soft_Start(void) {
    CS_LOW;
    SPI_DELAY;
}

void Driver_SPI_Soft_Stop(void) {
    CS_HIGH;
    SPI_DELAY;
}

// ��оƬ����һ���ֽ�  ��ʱ����SCK=1ʱ�ɼ�����
uint8_t Driver_SPI_Soft_SwapByte(uint8_t T_byte) {
    uint8_t R_byte = 0;
    for (uint8_t i = 0; i < 8; i++)
    {
        // ��׼��������
        ((T_byte << i) & 0x80) == 0 ? MOSI_LOW : MOSI_HIGH;

        // ����ʱ���ߣ��ɼ�����
        SCK_HIGH;
        SPI_DELAY;

        // ͬʱ�ɼ��������������
        R_byte <<= 1;
        MISO_READ == 0 ? ((R_byte) |= 0x00) : (R_byte |= 0x01);

        // ����ʱ�ӣ�Ϊ�´η���׼��
        SCK_LOW;
        SPI_DELAY;
    }
    return R_byte;
}
