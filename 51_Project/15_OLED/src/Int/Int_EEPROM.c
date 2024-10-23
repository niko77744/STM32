#include "Int_EEPROM.h"

static bit WriteToPage(u8 addr, u8* bytes, u8 len) {
    u8 i;
    bit ack;
    Dri_IIC_Start();

    Dri_IIC_SendByte(EEPROM_Address);
    ack |= Dri_IIC_ReceiveAck();

    Dri_IIC_SendByte(addr);
    ack |= Dri_IIC_ReceiveAck();

    for (i = 0; i < len; i++)
    {
        Dri_IIC_SendByte(bytes[i]);
        ack |= Dri_IIC_ReceiveAck();
    }

    Dri_IIC_Stop();

    return ack;
}

/**
 * @brief ָ������ָ�����ȣ�д��EEPROMָ��λ��
 *
 * @param u8 addr Ҫд��λ�ã�EEPROM�ڲ���ַ��
 * @param u8 *bytes Ҫд�������
 * @param u8 len Ҫд����ֽڸ�����bytes�ĳ��ȣ�
 *
 * @return bit 0��ʾ���в����Ӧ���źŶ���0,1��ʾ������������һ�ε�Ӧ���ź���1
 */
bit Int_EEPROM_WriteBytes(u8 addr, u8* bytes, u8 len) {
    u8 page_remain;
    bit ack;
    while (len >= 0)
    {
        page_remain = PAGE_SIZE - addr % 0x10;
        if (len > page_remain)
        {
            ack |= WriteToPage(addr, bytes, page_remain);
            // page_remain -= len;
            len -= page_remain;
            addr += page_remain;
            bytes += page_remain;
        }
        else if (len <= page_remain)
        {
            ack |= WriteToPage(addr, bytes, len);
            len = 0;
        }
        Delay_1ms(5);
    }
    return ack;
}

/**
 * @brief ��ȡָ����ַָ�����ȵ����ݣ�д��ڶ���������
 *
 * @param u8 addr Ҫ��ȡλ�ã�EEPROM�ڲ���ַ��
 * @param u8 *bytes �����յ�����д��õ�ַ
 * @param u8 len Ҫ��ȡ���ֽڸ���
 *
 * @return bit 0��ʾ���в����Ӧ���źŶ���0,1��ʾ������������һ�ε�Ӧ���ź���1
 */
bit Int_EEPROM_ReadBytes(u8 addr, u8* bytes, u8 len) {
    bit ack;
    u8 i;

    Dri_IIC_Start();

    Dri_IIC_SendByte(EEPROM_Address);
    ack |= Dri_IIC_ReceiveAck();

    Dri_IIC_SendByte(addr);
    ack |= Dri_IIC_ReceiveAck();

    Dri_IIC_Stop();


    Dri_IIC_Start();
    Dri_IIC_SendByte(EEPROM_Address + 1);
    ack |= Dri_IIC_ReceiveAck();

    for (i = 0; i < len; i++)
    {
        bytes[i] = Dri_IIC_ReceiveByte();
        Dri_IIC_SendAck(i == (len - 1) ? 1 : 0);
    }

    Dri_IIC_Stop();

    return ack;
}