#include "Dri_IIC.h"

// ������ʼ�ź�
// ��SCL��1ʱ�򣬼�⵽SDA��1��0
void Dri_IIC_Start()
{
    // ��ʱ���ź�
    SCL = 1;

    // SDA�Ӹߵ���
    SDA = 1;
    SDA = 0;

    // ��ʱ���ź�����
    SCL = 0;

}

/**
 * @brief ����һ���ֽ�����
 *
 * @param byte Ҫ���͵ĵ��ֽ�����
 */
void Dri_IIC_SendByte(u8 byte)
{
    /*
        ȡ���λ��
        (byte & 10000000) == 0 ? 0 : 1

        ȡ�θ�λ
        (byte & 01000000) == 0 ? 0 : 1

        ȡ������λ
        (byte & 00100000) == 0 ? 0 : 1

        ...
        ȡ���λ��
        (byte & 00000001) == 0 ? 0 : 1
    */
    u8 i;
    for (i = 0; i < 8; i++)
    {
        SDA = (byte & (0x80 >> i)) == 0 ? 0 : 1;
        SCL = 1;
        SCL = 0;
    }

}

/**
 * @brief ����һ��Ӧ���źţ�1�������ݣ�
 *
 * @param bit ack Ҫ���͵�1bit����
 */
void Dri_IIC_SendAck(bit ack)
{
    SDA = ack;
    SCL = 1;
    SCL = 0;
}


/**
 * @brief ����Ӧ���ź�
 *
 * @return bit ���ؽ��յ����ź�
 */
bit Dri_IIC_ReceiveAck()
{
    bit ack;

    // ��Ƭ���ͷ�������
    SDA = 1;

    // ʱ���ź��Ǹߵ�ƽ��ʱ�򣬽��������ߵ�����
    SCL = 1;
    ack = SDA;

    SCL = 0;

    return ack;
}

/**
 * @brief ����һ���ֽڵ�����
 *
 * @return u8 ���ؽ��յ�������
 */
 /*
     ������� 11001011

     byte: 0000 0000

     ��һ�Σ�   byte | 1   byte��Ϊ00000001
     �ڶ��Σ�   00000010 | 1   byte��Ϊ00000011
     �����Σ�   00000110 | 0   byte��Ϊ00000110
     ���ĴΣ�   00001100 | 0   byte��Ϊ00001100
     ����Σ�   00011000 | 1   byte��Ϊ00011001

  */
u8 Dri_IIC_ReceiveByte()
{
    // ������� ������յ�����
    u8 byte = 0;        // 0000 0000
    u8 i;

    // �ͷ�������
    SDA = 1;

    // ����ػ�ȡ����
    for (i = 0; i < 8; i++)
    {
        SCL = 1;

        // byte ���յ���SDA�����ݣ������������λ����������1λ
        byte = (byte << 1) | SDA;

        SCL = 0;
    }

    return byte;

}

// ���ͽ����ź�
void Dri_IIC_End()
{
    SDA = 0;
    SCL = 1;
    SDA = 1;
}