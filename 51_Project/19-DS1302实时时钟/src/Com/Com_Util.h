#ifndef __COM_UTIL_H__
#define __COM_UTIL_H__

#include <STC89C5xRC.H>
#include <INTRINS.H>

// ���ͱ���
typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;

/**
 * @brief ʱ����ʱ����
 * @param count ָ����ʱ����ms
 */
void Delay_1ms(u16);

/**
 * @brief ��ʱ10΢��
 * 
 */
void Delay10us(void);

/**
 * @brief ��ʱ50΢��
 * 
 */
void Delay50us(void);

/**
 * @brief ��ʱ60΢��
 * 
 */
void Delay60us(void);

/**
 * @brief ��ʱ480΢��
 * 
 */
void Delay480us(void);

#endif