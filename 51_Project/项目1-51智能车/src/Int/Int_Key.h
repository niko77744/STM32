#ifndef __INT_KEY_H__
#define __INT_KEY_H__

#include "Com_Util.h"
#include "Dri_GPIO.h"


/**
 * @brief ������ʼ��
 */
void Int_Key_Init();

/**
 * @brief �жϰ���1��״̬
 *
 * @return 0:�����ޱ仯 1:�������ڱ����£��½��أ� 2:��������̧�������أ�
 *
 */
u8 Int_Key_GetSw1Status();

/**
 * @brief �жϰ���2��״̬
 *
 * @return 0:�����ޱ仯 1:�������ڱ����£��½��أ� 2:��������̧�������أ�
 *
 */
u8 Int_Key_GetSw2Status();


#endif