#ifndef __INT_MatrixLED_H__
#define __INT_MatrixLED_H__
#include "Com_Util.h"

/**
 * @brief ����LED��ʼ��
 *
 */
void Int_MatrixLED_Init(void);


/**
 * @brief ���õ�����Ҫ��ʾ����Ϣ �� �洢������ÿ�е���ʾ��Ϣ �����鸳ֵ
 * @param pixels ��������Ϣ�����ȱ�����8��ÿ��Ԫ�ر�����8bit����
 */
void Int_MatrixLED_SetPixels(u8[8]);



/**
 * @brief �������е�Ԫ��������ƣ�0λ�������Ԫ��
 *
 * @param new_line
 */
void Int_MatrixLED_ShiftPixels(u8);



/**
 * @brief ˢ����ʾ��Ϣ
 */
void Int_MatrixLED_Refresh();

#endif /* __INT_MatrixLED_H__ */
