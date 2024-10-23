#ifndef __Int_DigitalTube__
#define __Int_DigitalTube__

#include "Com_Util.h"

// ��ʼ��
void Int_DigitalTube_Init(void);

// ��̬��ʾ
void Int_DigitalTube_StaticDisplay(u8);

// ����λѡ�Ͷ�ѡ ��������뵽CU ��������ʾ���� ͨ������P1����38����������ѡ��
void Int_DigitalTube_Single(u8, u8);

// ��Buffer����д������ ��ʮ���Ƶ�����ÿһλ�������ŵ� ��ѡ ��buffer�������
void Int_DigitalTube_SetBuffer(u32);

// ������ʾ
void Int_DigitalTube_SetNegativeBuffer(float);

// ����buffer����
void Int_DigitalTube_Refresh(void);

#endif /* __Int_DigitalTube__ */
