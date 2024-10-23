#ifndef __INT_MATRIXLED_H__
#define __INT_MATRIXLED_H__

#include "Com_Util.h"
#define SER P10 // �����ź�����
#define SCK P12 // ��λ�Ĵ���ʱ������
#define RCK P11 // �洢�Ĵ���ʱ������

#define DZ_EN P35 // 74HC595оƬʹ�����룬�͵�ƽ��Ч

// ������������
// u8 pic[8] = {0x1,
//              0x2,
//              0x4,
//              0x8,
//              0x10,
//              0x20,
//              0x40,
//              0x80};

// ������������
static u8 picture[4][8] = {
    {0x58,0x58,0x3C,0x1A,0x1A,0x3C,0x42,0x42},
    {0x1A,0x1A,0x3C,0x58,0x58,0x3C,0x42,0x42},
    {0x30,0x30,0x3C,0x5A,0x5A,0x3C,0x42,0x42},
    {0x0C,0x0C,0x3C,0x5A,0x5A,0x3C,0x42,0x42}};

/**
 * @brief ��������ʼ��
 *
 */
void Int_MatrixLED_Init();

/**
 * @brief ��������Ϣ�������������
 *
 * @param pixel ������Ϣ
 */
void Int_MatrixLED_SetPixel(u8 *pixel);

/**
 * @brief �����ˢ�º���
 *
 */
void Int_MatrixLED_Refersh();

/**
 * @brief �ı仺�������е�Ԫ��
 *
 * @param line Ϊ�����е���λԪ�ظ�ֵ
 */
void Int_MatrixLE_ShiftPixel(u8 line);

// /**
//  * @brief ���Ļ��������ڵ�Ԫ��
//  * @param pic ��ά����
//  */
// void Int_Matrix_ChangeBuffer(u8 *pic, u8 time);

#endif /* __INT_MATRIXLED_H__ */