#include "Dri_IIC.h"

// 发送起始信号
// 当SCL是1时候，检测到SDA从1到0
void Dri_IIC_Start()
{
    // 打开时钟信号
    SCL = 1;

    // SDA从高到低
    SDA = 1;
    SDA = 0;

    // 将时钟信号拉低
    SCL = 0;

}

/**
 * @brief 发送一个字节数据
 *
 * @param byte 要发送的单字节数据
 */
void Dri_IIC_SendByte(u8 byte)
{
    /*
        取最高位：
        (byte & 10000000) == 0 ? 0 : 1

        取次高位
        (byte & 01000000) == 0 ? 0 : 1

        取第三高位
        (byte & 00100000) == 0 ? 0 : 1

        ...
        取最低位：
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
 * @brief 发送一个应答信号（1比特数据）
 *
 * @param bit ack 要发送的1bit数据
 */
void Dri_IIC_SendAck(bit ack)
{
    SDA = ack;
    SCL = 1;
    SCL = 0;
}


/**
 * @brief 接收应答信号
 *
 * @return bit 返回接收到的信号
 */
bit Dri_IIC_ReceiveAck()
{
    bit ack;

    // 单片机释放数据线
    SDA = 1;

    // 时钟信号是高电平的时候，接受数据线的数据
    SCL = 1;
    ack = SDA;

    SCL = 0;

    return ack;
}

/**
 * @brief 接收一个字节的数据
 *
 * @return u8 返回接收到的数据
 */
 /*
     假设接收 11001011

     byte: 0000 0000

     第一次：   byte | 1   byte变为00000001
     第二次：   00000010 | 1   byte变为00000011
     第三次：   00000110 | 0   byte变为00000110
     第四次：   00001100 | 0   byte变为00001100
     第五次：   00011000 | 1   byte变为00011001

  */
u8 Dri_IIC_ReceiveByte()
{
    // 定义变量 保存接收的数据
    u8 byte = 0;        // 0000 0000
    u8 i;

    // 释放数据线
    SDA = 1;

    // 逐比特获取数据
    for (i = 0; i < 8; i++)
    {
        SCL = 1;

        // byte 接收到了SDA的数据，并放在了最低位，其他左移1位
        byte = (byte << 1) | SDA;

        SCL = 0;
    }

    return byte;

}

// 发送结束信号
void Dri_IIC_End()
{
    SDA = 0;
    SCL = 1;
    SDA = 1;
}