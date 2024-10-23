#ifndef __COM_UTIL_H__
#define __COM_UTIL_H__

#include <STC89C5xRC.H>
#include <INTRINS.H>
#include "string.h"

// LED��ˮ�ƿ���  0��1����Ĭ�Ͽ�
#define  LED_SwitchH P34  // #define PI 3.14

// ����ܿ��� 0��1��
#define  DigitalTube_SwitchL P36

// ����������
#define MatrixLED_SwitchL P35
#define SER P10  // ������������
#define SCK P12  // ��λ�Ĵ���ʱ�� �����ش���
#define RCK P11  // �洢�Ĵ���ʱ�� �����ش���


// ���ͱ���
typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;


/**
 * @brief ʱ����ʱ����
 * @param count ָ����ʱ����ms
 */
void Delay_1ms(u16);
void Delay_10us(u16);

#endif