#ifndef __DRI_TMER0INTERRUPUT_H__
#define __DRI_TMER0INTERRUPUT_H__

#include "Com_Util.h"
#define MaxFunctionCount 4

// ���庯��ָ��
typedef void(*CallbackFunction)(void);

// ����ָ������
static CallbackFunction FunctionArray[MaxFunctionCount];


/**
 * @brief ��ʱ��0�жϳ�ʼ��
 * 
 */
void Dri_Timer0Interrupt_Init();

/**
 * @brief ע�Ṧ�ܺ���
 * 
 * @param Function ע�Ṧ����
 * @return bit 
 */
bit Dri_Timer0Interrupt_RegisiterFunction (CallbackFunction );

/**
 * @brief ע�����ܺ���
 * 
 * @param Function ע��������
 * @return bit 
 */
bit Dri_Timer0Interrupt_DeregisiterFunction (CallbackFunction);

/**
 * @brief LED������
 * 
 */
void toggle_LED1();








#endif /* __DRI_TMER0INTERRUPUT_H__ */