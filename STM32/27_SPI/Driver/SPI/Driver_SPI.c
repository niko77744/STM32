#include "Driver_SPI.h"

// �������:  SCK��PA5;    MOSI(�����)��PA7;    SC#(Chip SelectionƬѡ)��PC13
// �������ţ� MISO(������)��PA6
void Driver_SPI_Init(void) {
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


void Driver_SPI_Start(void) {
    CS_LOW;
    SPI_DELAY;
}

void Driver_SPI_Stop(void) {
    CS_HIGH;
    SPI_DELAY;
}

// ��оƬ����һ���ֽ�  ��ʱ����SCK=1ʱ�ɼ�����
uint8_t Driver_SPI_SwapByte(uint8_t T_byte) {
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
