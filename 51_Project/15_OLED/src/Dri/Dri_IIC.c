#include "Dri_IIC.h"

// 起始信号：当SCL处于高电平时，SDA由高变低。
void Dri_IIC_Start() {
    SCL = 1;
    SDA = 1;
    SDA = 0;

    SCL = 0;
}

// 发送结束信号  当SCL处于高电平时，SDA由低变高
void Dri_IIC_Stop() {
    SDA = 0;
    SCL = 1;
    SDA = 1;
}

// 单片机向从设备发送数据，所以需要一个形参
/**
 * @brief 发送一个字节数据
 * @param byte 要发送的单字节数据
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

// 因为是接收从设备的一个字节，所以不需要参数，返回出去可以使用
/**
 * @brief 接收一个字节的数据
 * @return u8 返回接收到的数据
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


// 需要一个形参来确认信号
/**
 * @brief 发送一个应答信号（1比特数据）
 * @param bit ack 要发送的1bit数据
 */
void Dri_IIC_SendAck(bit ack) {   //0表示成功，可以继续。 1表示失败或不需要
    SDA = ack;
    SCL = 1;
    SCL = 0;
}


// 因为是接收从设备的信号，所以不需要参数，返回ack可以做判断
/**
 * @brief 接收应答信号
 * @return bit 返回接收到的信号
*/
bit Dri_IIC_ReceiveAck() {
    bit ack;
    SDA = 1;

    ack = SDA;
    SCL = 1;
    SCL = 0;
    return ack;
}
