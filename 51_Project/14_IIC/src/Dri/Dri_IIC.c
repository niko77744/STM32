#include "Dri_IIC.h"

// ��ʼ�źţ���SCL���ڸߵ�ƽʱ��SDA�ɸ߱�͡�
void Dri_IIC_Start() {
    SDA = 1;  // SDA��1��0
    SCL = 1;  // ���豸����ʱ����

    // ����������
    SDA = 0;

    // ����ʱ���ߣ�������һ������ʱ���ߣ�������Ҫ�ȴ�ʱ���������������ͬ������
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
    // ע�⣺SDA��һλһλ�ģ����ܸ�SDAֱ�Ӹ�ֵ
    /* &1����   &0��0  ��������ȡ��һ���ֽڵ�ÿһ��λ��ֵ����������SDA
    ȡ���λ��(byte & 10000000) == 0 ? 0 : 1
    ȡ�θ�λ��(byte & 01000000) == 0 ? 0 : 1
    �δθ�λ��(byte & 00100000) == 0 ? 0 : 1
    ...
    ȡ���λ��(byte & 00000001) == 0 ? 0 : 1
    */
    u8 i;
    for (i = 0; i < 8; i++)
    {
        // ��1��0����
        // ��ȡ��λ �ж��������0 ��ô ��λ����0
        SDA = (byte & (0x80 >> i)) == 0 ? 0 : 1;  //��ɶ�SDA��λ��ֵ ͨ���ж���0? 1:0 ��ȷ�ϸ�λ�ǲ���0��������1 ע�����ȼ�
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
    /*
    �������(SDA��һλһλ��) 11001011

    byte: 0000 0000  ����������յ�����      ��0���䣬����Ϊ��֤���һλ����0
    ��һ�Σ�   0000 0000 | 1(SDA���λ)   	  byte��Ϊ00000001  Ȼ������1λ
    �ڶ��Σ�   0000 0010 | 1(SDA�θ�λ)   	  byte��Ϊ00000011  Ȼ������1λ
    �����Σ�   0000 0110 | 0(SDA�δθ�λ)  	 byte��Ϊ00000110  Ȼ������1λ
    ���ĴΣ�   0000 1100 | 0   				byte��Ϊ00001100  Ȼ������1λ
    ����Σ�   0001 1000 | 1   				byte��Ϊ00011001  Ȼ������1λ
    ...
    ԭ����������λ�Ĵ���
    */
    u8 i;
    u8 bytes = 0x00;

    // �ͷ������ߣ����У�����ʽ���õ�Ƭ�����������߶Ͽ�  ���豸�ͷ�SDA���������豸����SDA
    // �൱�ڿ�©ģʽ��SDA=1�൱�ڵ�Ƭ����SDA�Ͽ����ӣ�����������ά�ָߵ�ƽ
    SDA = 1;

    // ����ػ�ȡ����
    for (i = 0; i < 8; i++)
    {
        //  byte ���յ���SDA�����ݣ������������λ����������1λ
        bytes = (bytes << 1) | SDA;
        SCL = 1;
        SCL = 0;
    }
    return bytes;
}


// ��Ҫһ���β���ȷ���ź�
/**
 * @brief ����һ��Ӧ���źţ�1�������ݣ�
 * @param bit ack Ҫ���͵�1bit����
 */
void Dri_IIC_SendAck(bit ack) {   //0��ʾ�ɹ������Լ����� 1��ʾʧ�ܻ���Ҫ
    SDA = ack;  //��׼�������ݣ�������ʱ����
    SCL = 1;   //����ʱ���ߣ����SDA�Ĳɼ��źţ�Ȼ������ʱ����
    SCL = 0;
}


// ��Ϊ�ǽ��մ��豸���źţ����Բ���Ҫ����������ack�������ж�
/**
 * @brief ����Ӧ���ź�
 * @return bit ���ؽ��յ����ź�
*/
bit Dri_IIC_ReceiveAck() {
    bit ack;  //0��ʾ�ɹ������Լ����� 1��ʾʧ�ܻ���Ҫ

    // ��Ƭ���ͷ������ߣ����У�����ʽ���õ�Ƭ�����������߶Ͽ�  ���豸�ͷ�SDA���������豸����SDA
    // �൱�ڿ�©ģʽ��SDA=1�൱�ڵ�Ƭ����SDA�Ͽ����ӣ�����������ά�ָߵ�ƽ
    SDA = 1;

    // ʱ���ź��Ǹߵ�ƽ��ʱ�򣬽��������ߵ�����
    SCL = 1;
    ack = SDA;  //��Ϊack��1λ�ģ�����ֱ����SDA��ֵ
    SCL = 0;

    return ack;
}