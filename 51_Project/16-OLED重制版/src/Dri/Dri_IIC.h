#ifndef __DRI_IIC_H__
#define __DRI_IIC_H__
#include "Com/Com_Util.h"

#define SCL P17  // �궨��ʱ����
#define SDA P16  // �궨��������

// ������ʼ�ź�λ
void Dri_IIC_Start();
// ���ͽ����ź�λ
void Dri_IIC_Stop();

// ����һ���ֽ� @param byte Ҫ���͵ĵ��ֽ����� 
void Dri_IIC_SendByte(u8 byte);

// ����һ���ֽ�  ���ؽ��յ�������
u8 Dri_IIC_ReceiveByte();

// ����ȷ���ź�  @param bit ack Ҫ���͵�1bit����
void Dri_IIC_SendAck(bit ack);

// ����ȷ���ź�  @param bit ���ؽ��յ����ź�
bit Dri_IIC_ReceiveAck();

#endif /* __DRI_IIC_H__ */