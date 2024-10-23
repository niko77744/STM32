#include "Int_EEPROM.h"

static bit WriteToPage(u8 addr, u8* bytes, u8 len) {
    bit ack;
    u8 i;
    // ����һ����ʼ�źţ���ʼ�ͽ�������Ҫ����ack
    Dri_IIC_Start();

    // !!!���Ƿ��ʹ��豸��ַ+д���; ������EEPROM��Ӧ���ź�
    Dri_IIC_SendByte(EEPROM_Address);
    ack |= Dri_IIC_ReceiveAck();

    // ����д��λ��(EEPROM���ڲ���ַ)��������EEPROM��Ӧ���ź�
    Dri_IIC_SendByte(addr);
    ack |= Dri_IIC_ReceiveAck();

    // �� EEPROM ��������; ���ֽڷ��Ͳ�ȷ��Ӧ���ź�
    for (i = 0; i < len; i++)
    {
        Dri_IIC_SendByte(bytes[i]);
        ack |= Dri_IIC_ReceiveAck();
    }

    // !!! ���Ƿ���ֹͣ�ź�
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
    bit ack;

    // ������� ��¼��ǰҳʣ������
    u8 page_remain;


    // !!!����һ����len > 0������дlen����Ϊ����--
    while (len > 0)
    {
        // ���㵱ǰҳ��ʣ������  !!!���� PAGE_SIZE -
        page_remain = PAGE_SIZE - addr % PAGE_SIZE;
        if (len > page_remain)
        {
            // ��ǰҳ�������㣬��Ҫд���ҳ -----------------
            // д����ǰҳ
            ack |= WriteToPage(addr, bytes, page_remain);

            // ��д���ַ���ƣ��Ƶ���һҳ  ����Ҫ����page_remainλ����һ��
            addr += page_remain;   //��һ�еĵ�ַ

            //��Ϊһ����д��1�У�1��page��һ���Ѿ�д��page_remain���ֽڣ�������һ��д����+page_remain���ֽ�
            bytes += page_remain;

            // �ܳ��ȼ�����д��ĳ���
            len -= page_remain;
        }
        else if (len <= page_remain)
        {
            // ��ǰҳ�������㣬����д��Ҫд������� ----------
            ack |= WriteToPage(addr, bytes, len);

            // !!!���� len = 0
            len = 0;
        }
        // д����ҳ����
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
    u8 i;
    bit ack;

    // 1.αд�����õ�ַ�Ĵ����еĵ�ַ --------------------------------
    // ������ʼ�ź�
    Dri_IIC_Start();

    // ����EEPROM��ַ��д��ǣ�������Ӧ��
    Dri_IIC_SendByte(EEPROM_Address);  //Ĭ��д���� ����һ��αд
    ack |= Dri_IIC_ReceiveAck();

    // ���͵�ַ��EEPROM���ڲ���ַ���ᱻEEPROMд���ַ�Ĵ�����;������Ӧ���ź�
    Dri_IIC_SendByte(addr);  //Ĭ��д���� ����һ��αд
    ack |= Dri_IIC_ReceiveAck();
    // ���ͽ����ź�
    Dri_IIC_Stop();


    // ��ʽ�� ------------------------------------------------------
    // ������ʼ�ź�
    Dri_IIC_Start();

    // ����EEPROM��ַ�Ͷ���ǣ�������Ӧ��
    Dri_IIC_SendByte(0xA1);  // Ҳ����дEEPROM_Address+1
    ack |= Dri_IIC_ReceiveAck();

    // ���ֽڽ��ն�ȡ����EEPROM�е����ݣ�������Ӧ���ź�
    for (i = 0; i < len; i++)
    {
        // ���յ��ֽڲ�����bytes����
        bytes[i] = Dri_IIC_ReceiveByte();

        // ����Ӧ���ź� ������������һ���ֽڣ��ظ�1�������ظ�0
        Dri_IIC_SendAck(i == (len - 1) ? 1 : 0);
    }

    // ��ʼ�ͽ��ն�����Ҫ����ack

    // ���ͽ����ź�
    Dri_IIC_Stop();
    return ack;
}