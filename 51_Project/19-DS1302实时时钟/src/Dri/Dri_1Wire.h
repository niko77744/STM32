#ifndef __DRI_1WIRE_H__
#define __DRI_1WIRE_H__

#include "Com_Util.h"

/**
 * @brief ��ʼ��
 * 
 * @return bit ���ش��豸��Ӧ���ź�
 */
bit Dri_1Wire_Init();


/**
 * @brief ����1���ֽڵ�����
 * 
 * @param byte Ҫ���͵��ֽ�
 */
void Dri_1Wire_SendByte(u8 byte);

/**
 * @brief ����1���ֽڵ�����
 * 
 * @return ���ؽ��յ��ֽ�
 */
u8 Dri_1Wire_ReceiveByte();

#endif /* __DRI_1WIRE_H__ */