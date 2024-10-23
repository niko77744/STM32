#include "Dri_1Wire.h"
#define DQ P44

/**
 * @brief ��ʼ��
 *
 * @return bit ���ش��豸��Ӧ���ź�
 */
bit Dri_1Wire_Init()
{
    bit result;

    // ���͸�λ����
    DQ = 0;
    // ����480��s
    Delay480us();

    // �ͷ�DQ
    DQ = 1;

    // 15~60΢��󣬻�ȡDQ��ֵ
    Delay60us();
    result = DQ;

    // ��DQ�ͷſ�ʼ�������ӳ�480΢��ٽ��к�������
    Delay480us();

    return result;
}

/**
 * @brief ����1���ֽڵ�����
 *
 * @param byte Ҫ���͵��ֽ�
 */
void Dri_1Wire_SendByte(u8 byte)
{
    u8 i;
    // ����ط��ͣ�ѭ��
    for (i = 0; i < 8; i++)
    {
        // ���������ߣ���ʾҪ��������
        DQ = 0;

        // ��Ҫ��15΢��֮�ڣ���DQ�������ݣ� ���ԣ�10΢����޸�DQ��ֵ
        Delay10us();
        DQ = byte >> i;

        /*
        abcdefgh >> 0
        abcdefgh >> 1
        abcdefgh >> 2
        ...
        abcdefgh >> 7
        */

        // ����50΢��
        Delay50us();

        // �ͷ�����
        DQ = 1;
    }
}

/**
 * @brief ����1���ֽڵ�����
 *
 * @return ���ؽ��յ��ֽ�
 */
u8 Dri_1Wire_ReceiveByte()
{
    u8 i;
    // �����������������ֽ� 0000 0000
    u8 byte = 0x00;

    // ѭ����ȡ8�Σ�����ض�ȡ
    for (i = 0; i < 8; i++)
    {
        // ���豸����DQ ����1΢��
        DQ = 0;
        // ���豸�ͷ�DQ
        DQ = 1;

        // 10΢��֮������߲���  ���յ���λ
        Delay10us();
        // byte <<= 1;
        // byte = DQ;

        if (DQ == 1)
        {
            byte = byte | (1 << i);
        }

        /*
        00000000

        ��һ�ν���1�� 00000000 | (1 << 0), ��Ϊ 00000001
        �ڶ��ν���0�� ����������            ��Ϊ 00000001
        �����ν���1�� 00000001 | (1 << 2)   ��Ϊ 00000101

        */

        // ����ʱ50us���չ�60us
        Delay50us();
    }

    return byte;
}