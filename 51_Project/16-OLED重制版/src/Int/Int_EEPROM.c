#include "Int_EEPROM.h"
#include "Dri_IIC.h"
#include "Com_Util.h"

#define EEPROM_ADDR 0xA0  //包含地址+写标记
#define Page_Size 0x10

/*
    两个错误：三元和重置len
*/

bit Int_EEPROM_WriteToPage(u8 addr, u8* bytes, u8 len) {
    u8 i;
    bit ack;
    Dri_IIC_Start();
    Dri_IIC_SendByte(EEPROM_ADDR);
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

bit Int_EEPROM_WriteBytes(u8 addr, u8* bytes, u8 len) {
    bit ack;
    u8 page_remain;
    while (len > 0) {
        page_remain = Page_Size - (addr % Page_Size);
        if (len > page_remain)
        {
            ack |= Int_EEPROM_WriteToPage(addr, bytes, page_remain);
            len -= page_remain;
            addr += page_remain;
            bytes += page_remain;
        }
        else
        {
            ack |= Int_EEPROM_WriteToPage(addr, bytes, len);
            len = 0;
        }
        Delay_1ms(5);
    }
    return ack;
}

bit Int_EEPROM_ReadBytes(u8 addr, u8* bytes, u8 len) {
    u8 i;
    bit ack;
    Dri_IIC_Start();
    Dri_IIC_SendByte(EEPROM_ADDR);
    ack |= Dri_IIC_ReceiveAck();
    Dri_IIC_SendByte(addr);
    ack |= Dri_IIC_ReceiveAck();
    Dri_IIC_Stop();


    Dri_IIC_Start();
    Dri_IIC_SendByte(EEPROM_ADDR + 1);
    ack |= Dri_IIC_ReceiveAck();

    for (i = 0; i < len; i++)
    {
        bytes[i] = Dri_IIC_ReceiveByte();
        Dri_IIC_SendAck(i == (len - 1) ? 1 : 0);
    }
    Dri_IIC_Stop();
    return ack;
}