#ifndef __DRI_3WIRE_H__
#define __DRI_3WIRE_H__

#include "Com_Util.h"

#define CE P41
#define SCLK P37
#define IO P40

/**
 * @brief 发送一个字节 （写操作）
 * 
 * @param u8 byte 要发送的字节 
 */
void Dri_3Wire_SendByte(u8 byte);

/**
 * @brief 接收一个字节（读操作）
 * 
 * @return 返回接收到的字节
 */
u8 Dri_3Wire_ReceiveByte();

#endif /* __DRI_3WIRE_H__ */