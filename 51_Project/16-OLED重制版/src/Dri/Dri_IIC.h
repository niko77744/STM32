#ifndef __DRI_IIC_H__
#define __DRI_IIC_H__
#include "Com/Com_Util.h"

#define SCL P17  // 宏定义时钟线
#define SDA P16  // 宏定义数据线

// 发送起始信号位
void Dri_IIC_Start();
// 发送结束信号位
void Dri_IIC_Stop();

// 发送一个字节 @param byte 要发送的单字节数据 
void Dri_IIC_SendByte(u8 byte);

// 接收一个字节  返回接收到的数据
u8 Dri_IIC_ReceiveByte();

// 发送确认信号  @param bit ack 要发送的1bit数据
void Dri_IIC_SendAck(bit ack);

// 接收确认信号  @param bit 返回接收到的信号
bit Dri_IIC_ReceiveAck();

#endif /* __DRI_IIC_H__ */