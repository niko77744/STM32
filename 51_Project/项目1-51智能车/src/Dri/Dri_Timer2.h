#ifndef __DRI_Timer2_H__
#define __DRI_Timer2_H__

#include <STDIO.H>
#include "Com_Util.h"

// ����Timer2 ����ע��ص�����������
#define MAX_CALLBACK_COUNT 4

// ������ָ�루ָ��Ҫע�����ʱ���Ļص����������ñ���
typedef void (*Timer2_Callback)(void);

/**
 * @brief ��ʱ��0 ��ʼ��
 *
 */
void Dri_Timer2_Init();

/**
 * @brief ����ʱ��0 ע��ص�����
 *
 * @param callback Ҫע��ص�����
 * @return bit 1��ʾע��ɹ� 0��ʾע��ʧ��
 */
bit Dri_Timer2_RegisterCallback(Timer2_Callback);

/**
 * @brief ע����ʱ��0�Ļص�����
 *
 * @param callback Ҫע���Ļص�����
 * @return bit 1��ʾע���ɹ� 0��ʾע��ʧ��
 */
bit Dri_Timer2_DeregisterCallback(Timer2_Callback);


#endif /* __DRI_Timer2_H__ */