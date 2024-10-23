#include "Dri_3Wire.h"


/**
 * @brief 发送一个字节 （写操作）
 *
 * @param u8 byte 要发送的字节
 */
void Dri_3Wire_SendByte(u8 byte) {
    u8 i;

    // 这里与循环里的SCLK形成第一个上升沿，且末尾SCLK是0
    SCLK = 0;
    // 上升沿发送数据，下降沿接收数据 ,先发低位
    for (i = 0; i < 8; i++)
    {
        IO = (byte >> i) & 0x01;  //数据在前
        // 本来应该是一个上升沿，但是在循环外SCLK已经是0，进入循环时已经有一个上升沿
        // 如果这里是一个上升沿，发送和接受末尾SCLK都是1，读取数据需要先发送一个命令，在字节末尾同时需要发送这1bit，还需要接受DS1302发送的第1个bit
        // 所以如果这里写上升沿，接受末尾和发送的第一个SCLK都是1，无法形成下降沿接收数据，也可以在接收的循环前面加SCLK=0
        SCLK = 1;
        SCLK = 0;
    }
}

/**
 * @brief 接收一个字节（读操作）
 *
 * @return 返回接收到的字节
 */
u8 Dri_3Wire_ReceiveByte() {
    u8 i;
    u8 byte = 0x00;
    // 上升沿发送数据，下降沿接收数据 ,先发低位
    for (i = 0; i < 8; i++)
    {
        if (1 == IO)
        {
            byte |= (1 << i);
        }
        SCLK = 1;
        SCLK = 0;
    }
    return byte;
}