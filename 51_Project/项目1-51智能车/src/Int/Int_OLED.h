#ifndef __INT_OLED_H__
#define __INT_OLED_H__

#include "Com_Util.h"
#include "Dri_IIC.h"

#define OLED_ADDR 0x78

/**
 * @brief OLED ��ʼ��
 * 
 */
void Int_OLED_Init();


/**
 * @brief OLED ����
 * 
 */
void Int_OLED_Clear();


/**
 * @brief OLED ��ʾ�ַ���
 * 
 * @param x X����
 * @param y Y����
 * @param str Ҫд����ַ���
 */
void Int_OLED_DisplayStr(u8 x, u8 y, u8 *str);

/**
 * @brief OLED ��ʾ����
 * 
 * @param x X����
 * @param y Y����
 * @param num Ҫд�������
 */
void Int_OLED_DisplayNum(u8 x, u8 y, long num);


#endif /* __INT_OLED_H__ */