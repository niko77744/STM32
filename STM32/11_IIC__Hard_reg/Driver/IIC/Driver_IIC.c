#include "Driver_IIC.h"

void Driver_I2C_Init(void) {
    // 1.����ʱ��   ʹ��IIC2����APB1
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;

    // 2.ʹ��I2C2   PB10��SCL    PB11��SDA
    // ���ģ�⣬���ÿ�©��� MDOE11 CNF11
    GPIOB->CRH |= (GPIO_CRH_MODE10 | GPIO_CRH_MODE11);
    GPIOB->CRH |= (GPIO_CRH_CNF10 | GPIO_CRH_CNF11);

    // 3.����I2C2��ģ��
    // 3.1 ����ʹ��I2Cģʽ  Ĭ������0 I2C   1  SMBus
    I2C2->CR1 &= ~I2C_CR1_SMBUS;

    // 3.2 I2C_CR2_FREQ  CR2ʱ��Ƶ��  36MHz
    I2C2->CR2 |= 36;

    // 3.3 ���ñ�׼ģʽ  0:100k   1:400k
    I2C2->CCR &= ~I2C_CCR_FS;

    // 3.4 ����CCR ����/��׼ģʽ�µ�ʱ�ӿ��Ʒ�Ƶϵ��
    // stm32��IICģ���б�׼ģʽ����100kb�£�ʱ��Ƶ����36Mhz����I2C��׼ģʽ��SMBusģʽ�£�Thigh = CCR ��TPCLK1Tlow = CCR ��TPCLK1��crr����Ϊ����
    // Th = Tl = CCR �� Tpclk[1/36Mhz]
    // 100kb/s== 100khz== Fiic == 1/(Th+Tl) == 1/(2*CRR*Tpclk)
    // 100kHz = 1/(2*CRR*(1/36Mhz))  CRR=180; �����λ
    // �򵥼��㣺��Ƶ��*10/2
    I2C2->CCR |= 180;

    // 3.5 �������������ʱ�� 1us+1��ʱ������
    // ��׼ģʽTRISE = (t_r/ TPCLK1) + 1
    // TPCLK1 = 1/36MHz �� 27.78ns��ͨ�� t_r �����ֵΪ 1000ns��
    // �򵥼��㣺��Ƶ��+1
    I2C2->TRISE |= 37;

    // 3.6 I2Cģ��ʹ��
    I2C2->CR1 |= I2C_CR1_PE;
}


uint8_t Driver_I2C_Start(void) {
    // 1.��ʼѭ��������ʼ�ź�
    I2C2->CR1 |= I2C_CR1_START;

    // 2.�жϷ��ͳɹ�  SB ��ʼλ(��ģʽ) (Start bit)
    // �����ȡSR1�Ĵ�����д���ݼĴ���DR�Ĳ����������λ 
    uint16_t timeout = 0xffff;
    while ((I2C2->SR1 & I2C_SR1_SB) == 0 && timeout--);

    // 3.����timeout�������ֵ
    return timeout ? Ok : Error;
}
void Driver_I2C_Stop(void) {
    //��Ӳ��������λ֮ǰ�������Ҫִ���κζ�2C_CR1��д����
    I2C2->CR1 |= I2C_CR1_STOP;
}

// �����ڽ������һ���ֽں����һ��ACK�ź�
void Driver_I2C_SendAck(void) {
    //1���ڽ��յ�һ���ֽں󷵻�һ��Ӧ��(ƥ��ĵ�ַ������)��
    I2C2->CR1 |= I2C_CR1_ACK;
}
void Driver_I2C_SendNAck(void) {
    // 0����Ӧ�𷵻أ�
    I2C2->CR1 &= ~I2C_CR1_ACK;
}

uint8_t Driver_I2C_SendAddr(uint8_t addr) {
    // 1.д��ַ��������ݼĴ��� 
    I2C2->DR = addr;  //ע�⣺����|=

    // 2.�ж��Ƿ��͵�ַ�ɹ� 
    uint16_t timeout = 0xffff;
    // 1����ַ���ͽ���,���յ���ַ��ACK���λ����1
    // �������ȡSR1�Ĵ����󣬶�SR2�Ĵ����Ķ������������λ
    while ((I2C2->SR1 & I2C_SR1_ADDR) == 0 && timeout--);

    // 3.�����Ƿ��͵�ַ�ɹ� 
    if (timeout)
    {
        // ����ADDR��־λ
        I2C2->SR1;
        I2C2->SR2;
        return Ok;
    }
    else {
        return Error;
    }
}

// uint8_t Driver_I2C_ReceiveAck(void) //�Զ�����ack

uint8_t Driver_I2C_Sendbyte(uint8_t byte) {
    // 1.�ȴ��������ݼĴ���Ϊ�� 
    uint16_t timeout = 0xffff;
    //  ���д���ݵ�DR�Ĵ����������λ
    while ((I2C2->SR1 & I2C_SR1_TXE) == 0 && timeout--);

    // 2.�ж��Ƿ�ʱ,����Ҫ��Ҫд������ 
    if (timeout)
    {
        I2C2->DR = byte;
    }
    else {
        return Error;
    }

    // 3.�ȴ��������,ACK 
    timeout = 0xffff;
    //�ֽڷ��ͽ��� (Byte transfer finished)  1���ֽڷ��ͽ���
    // �������ȡSR1�Ĵ����󣬶����ݼĴ���DR�Ķ���д�����������λ
    while ((I2C2->SR1 & I2C_SR1_BTF) == 0 && timeout--);

    // 4.�����Ƿ��ͳɹ� 
    return timeout ? Ok : Error;
}


uint8_t Driver_I2C_Receivebyte(void) {
    uint16_t timeout = 0xffff;
    // ��������ݼĴ���DR�Ķ�д���������λ
    while ((I2C2->SR1 & I2C_SR1_RXNE) == 0 && timeout--);
    uint8_t byte = timeout ? I2C2->DR : Error;
    return byte;
}
