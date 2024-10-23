#include "Dri_IIC.h"

void Dri_IIC_Start() {
    SDA = 1;
    SCL = 1;
    SDA = 0;

    SCL = 0;
}



void Dri_IIC_SendByte(u8 byte) {
    u8 i;

    for (i = 0; i < 8; i++)
    {
        SDA = (byte & (0x80 >> i)) == 0 ? 0 : 1;
        SCL = 1;
        SCL = 0;
    }
}



void Dri_IIC_SendAck(bit ack) {
    SDA = ack;
    SCL = 1;
    SCL = 0;
}


bit Dri_IIC_ReceiveAck() {
    bit ack;
    SDA = 1;

    ack = SDA;

    SCL = 1;
    SCL = 0;
    return ack;
}

u8 Dri_IIC_ReceiveByte() {
    u8 i;
    u8 byte = 0x00;
    SDA = 1; //½â³ýÕ¼ÓÃ

    for (i = 0; i < 8; i++)
    {
        byte = ((byte << 1) | SDA);  // byte = ((byte << i) | SDA);
        SCL = 1;
        SCL = 0;
    }
    return byte;
}

void Dri_IIC_End() {
    SDA = 0;
    SCL = 1;
    SDA = 1;
}