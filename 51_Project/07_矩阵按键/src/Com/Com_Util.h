#ifndef __COM_UTIL_H__
#define __COM_UTIL_H__

#include <STC89C5xRC.H>
#include <INTRINS.H>

#define SW_LED P34
#define SW_DigitalTube P36

// ���ͱ���
typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;

/**
 * @brief ʱ����ʱ����
 * @param count ָ����ʱ����ms
 */
void Delay_1ms(u16);

#endif