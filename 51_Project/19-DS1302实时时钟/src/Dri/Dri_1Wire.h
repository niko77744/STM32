#ifndef __DRI_1WIRE_H__
#define __DRI_1WIRE_H__

#include "Com_Util.h"

/**
 * @brief 初始化
 * 
 * @return bit 返回从设备的应答信号
 */
bit Dri_1Wire_Init();


/**
 * @brief 发送1个字节的数据
 * 
 * @param byte 要发送的字节
 */
void Dri_1Wire_SendByte(u8 byte);

/**
 * @brief 接收1个字节的数据
 * 
 * @return 返回接收的字节
 */
u8 Dri_1Wire_ReceiveByte();

#endif /* __DRI_1WIRE_H__ */