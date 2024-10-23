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
 * @brief 指定内容指定长度，写入EEPROM指定位置
 *
 * @param u8 addr 要写入位置（EEPROM内部地址）
 * @param u8 *bytes 要写入的内容
 * @param u8 len 要写入的字节个数（bytes的长度）
 *
 * @return bit 0表示所有步骤的应答信号都是0,1表示步骤中至少有一次的应答信号是1
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
 * @brief 读取指定地址指定长度的内容，写入第二个参数中
 *
 * @param u8 addr 要读取位置（EEPROM内部地址）
 * @param u8 *bytes 将接收的内容写入该地址
 * @param u8 len 要读取的字节个数
 *
 * @return bit 0表示所有步骤的应答信号都是0,1表示步骤中至少有一次的应答信号是1
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