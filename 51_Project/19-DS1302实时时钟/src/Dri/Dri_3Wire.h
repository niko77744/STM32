#ifndef __DRI_3WIRE_H__
#define __DRI_3WIRE_H__

#include "Com_Util.h"

#define CE P41
#define SCLK P37
#define IO P40

/**
 * @brief ����һ���ֽ� ��д������
 * 
 * @param u8 byte Ҫ���͵��ֽ� 
 */
void Dri_3Wire_SendByte(u8 byte);

/**
 * @brief ����һ���ֽڣ���������
 * 
 * @return ���ؽ��յ����ֽ�
 */
u8 Dri_3Wire_ReceiveByte();

#endif /* __DRI_3WIRE_H__ */