#ifndef __DRI_IIC_H__
#define __DRI_IIC_H__

#include "Com_Util.h"

#define SCL P17
#define SDA P16

// ������ʼ�ź�
void Dri_IIC_Start();

// ���ͽ����ź�
void Dri_IIC_End();

/**
 * @brief ����һ���ֽ�����
 * 
 * @param byte Ҫ���͵ĵ��ֽ����� 
 */
void Dri_IIC_SendByte(u8 byte);


/**
 * @brief ����һ��Ӧ���źţ�1�������ݣ�
 * 
 * @param bit ack Ҫ���͵�1bit����
 */
void Dri_IIC_SendAck(bit ack);



/**
 * @brief ����Ӧ���ź�
 * 
 * @return bit ���ؽ��յ����ź�
 */
bit Dri_IIC_ReceiveAck();

/**
 * @brief ����һ���ֽڵ�����
 * 
 * @return u8 ���ؽ��յ�������
 */
u8 Dri_IIC_ReceiveByte();


#endif /* __DRI_IIC_H__ */