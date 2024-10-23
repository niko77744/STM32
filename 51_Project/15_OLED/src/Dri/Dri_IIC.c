#include "Dri_IIC.h"

// ��ʼ�źţ���SCL���ڸߵ�ƽʱ��SDA�ɸ߱�͡�
void Dri_IIC_Start() {
    SCL = 1;
    SDA = 1;
    SDA = 0;

    SCL = 0;
}

// ���ͽ����ź�  ��SCL���ڸߵ�ƽʱ��SDA�ɵͱ��
void Dri_IIC_Stop() {
    SDA = 0;
    SCL = 1;
    SDA = 1;
}

// ��Ƭ������豸�������ݣ�������Ҫһ���β�
/**
 * @brief ����һ���ֽ�����
 * @param byte Ҫ���͵ĵ��ֽ�����
 */
void Dri_IIC_SendByte(u8 byte) {
    u8 i;
    for (i = 0; i < 8; i++)
    {
        SDA = (byte & (0x80 >> i)) == 0 ? 0 : 1;
        SCL = 1;
        SCL = 0;
    }

}

// ��Ϊ�ǽ��մ��豸��һ���ֽڣ����Բ���Ҫ���������س�ȥ����ʹ��
/**
 * @brief ����һ���ֽڵ�����
 * @return u8 ���ؽ��յ�������
*/
u8 Dri_IIC_ReceiveByte() {
    u8 i;
    u8 byte = 0x00;
    SDA = 1;
    for (i = 0; i < 8; i++)
    {
        byte = (byte << 1) | SDA;
        SCL = 1;
        SCL = 0;
    }
    return byte;
}


// ��Ҫһ���β���ȷ���ź�
/**
 * @brief ����һ��Ӧ���źţ�1�������ݣ�
 * @param bit ack Ҫ���͵�1bit����
 */
void Dri_IIC_SendAck(bit ack) {   //0��ʾ�ɹ������Լ����� 1��ʾʧ�ܻ���Ҫ
    SDA = ack;
    SCL = 1;
    SCL = 0;
}


// ��Ϊ�ǽ��մ��豸���źţ����Բ���Ҫ����������ack�������ж�
/**
 * @brief ����Ӧ���ź�
 * @return bit ���ؽ��յ����ź�
*/
bit Dri_IIC_ReceiveAck() {
    bit ack;
    SDA = 1;

    ack = SDA;
    SCL = 1;
    SCL = 0;
    return ack;
}
