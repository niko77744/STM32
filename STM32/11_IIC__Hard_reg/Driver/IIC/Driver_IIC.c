#include "Driver_IIC.h"

void Driver_I2C_Init(void) {
    // 1.����ʱ��
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;

    // 2.ʹ��I2C2   PB10��SCL    PB11��SDA
    // ���ģ�⣬ͨ�ÿ�©��� MDOE11 CNF01
    GPIOB->CRH |= (GPIO_CRH_MODE10 | GPIO_CRH_MODE11);
    GPIOB->CRH &= ~(GPIO_CRH_CNF10_1 | GPIO_CRH_CNF11_1);
    GPIOB->CRH |= (GPIO_CRH_CNF10_0 | GPIO_CRH_CNF11_0);

    // ���ģ�ⲻ��Ҫ����IICģ��
}


void Driver_I2C_Start(void) {
    SDA_HIGH;
    SCL_HIGH;
    Delay_I2C2;

    SDA_LOW;
    Delay_I2C2;

    SCL_LOW;
    Delay_I2C2;
}
void Driver_I2C_Stop(void) {
    SCL_HIGH;
    // �м䲻��delay
    SDA_LOW;
    Delay_I2C2;

    SDA_HIGH;
    Delay_I2C2;
}


void Driver_I2C_SendAck(void) {

    SDA_LOW;
    Delay_I2C2;

    SCL_HIGH;
    Delay_I2C2;

    SCL_LOW;
    Delay_I2C2;

    // �ǵ�����sda
    SDA_HIGH;
    Delay_I2C2;
}
void Driver_I2C_SendNAck(void) {
    SDA_HIGH;
    Delay_I2C2;

    SCL_HIGH;
    Delay_I2C2;

    SCL_LOW;
    Delay_I2C2;
}

uint8_t Driver_I2C_ReceiveAck(void) {
    uint8_t ack;
    // �ͷ�����
    SDA_HIGH;
    Delay_I2C2;

    SCL_HIGH;
    Delay_I2C2;

    ack = READ_SDA;
    Delay_I2C2;

    SCL_LOW;
    Delay_I2C2;

    return ack;
}

void Driver_I2C_Sendbyte(uint8_t byte) {
    for (uint8_t i = 0; i < 8; i++)
    {
        // ע�⣺���͵ĸߵ͵�ƽ��Ҫ����
        (byte & 0x80) == 0 ? SDA_LOW : SDA_HIGH;

        SCL_HIGH; // ����ʱ���ߣ����SDA�Ĳɼ��źţ�Ȼ������ʱ����
        Delay_I2C2;

        SCL_LOW;
        Delay_I2C2;
        byte <<= 1;
    }
}
uint8_t Driver_I2C_Receivebyte(void) {
    uint8_t byte;
    // SDA_HIGH;
    for (uint8_t i = 0; i < 8; i++)
    {
        SCL_LOW;
        Delay_I2C2;

        byte <<= 1;

        // ע��  byte = (byte << 1) | READ_SDA; ����
        if (READ_SDA)
        {
            byte |= 0x01;
        }

        SCL_HIGH;
        Delay_I2C2;
    }

    SCL_LOW;
    Delay_I2C2;
    return byte;
}
 