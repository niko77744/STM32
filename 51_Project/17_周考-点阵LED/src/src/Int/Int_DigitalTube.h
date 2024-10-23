#ifndef __INT_DIGITAL_TUBE_H__
#define __INT_DIGITAL_TUBE_H__

#include "Com_Util.h"



// ��������ܵ�Ƭѡ����
static u8 DigitalTube_codes[10] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F  // 9
};

//��������ܵ���ʾ����
/**
 * @brief �����ָ��λ����ʾ����
 * 
 * @param dig λѡ��
 * @param num Ƭѡ��
 */
void Int_DigitalTube_single (u8 dig ,u8 num);

//���庯��������ѭ����ֵ����������
/**
 * @brief �����ִ��浽��������
 * 
 * @param number 
 */
void Int_DigitalTube_DisplayNum(u32 number);


/**
 * @brief ˢ�������
 * 
 */
void Int_DigitalTube_Refresh();

/**
 * @brief ��ʼ�������
 * 
 */
void Int_DigitalTube_Init();

#endif


