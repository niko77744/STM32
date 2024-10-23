#ifndef __COM_UTIL_H__
#define __COM_UTIL_H__

#include <STC89C5xRC.H>
#include <INTRINS.H>

typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;

/**
 * @brief ��ʱ1ms����
 *
 */
void Delay1ms(u16 times); //@11.0592MHz

/**
 * @brief ��ʱ10us����
 * 
 * @param times 
 */
void Delay10us(u16 times);//@11.0592MHz


#endif


