#ifndef __DRI_IIC_H__
#define __DRI_IIC_H__

#include "Com_Util.h"

#define SCL P17
#define SDA P16

// 发送起始信号
void Dri_IIC_Start();

// 发送结束信号
void Dri_IIC_End();

/**
 * @brief 发送一个字节数据
 * 
 * @param byte 要发送的单字节数据 
 */
void Dri_IIC_SendByte(u8 byte);


/**
 * @brief 发送一个应答信号（1比特数据）
 * 
 * @param bit ack 要发送的1bit数据
 */
void Dri_IIC_SendAck(bit ack);



/**
 * @brief 接收应答信号
 * 
 * @return bit 返回接收到的信号
 */
bit Dri_IIC_ReceiveAck();

/**
 * @brief 接收一个字节的数据
 * 
 * @return u8 返回接收到的数据
 */
u8 Dri_IIC_ReceiveByte();


#endif /* __DRI_IIC_H__ */