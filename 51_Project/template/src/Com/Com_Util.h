#ifndef __COM_UTIL_H__
#define __COM_UTIL_H__

#include <STC89C5xRC.H>
#include <INTRINS.H>

// 类型别名
typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;

/**
 * @brief 时间延时函数
 * @param count 指定延时多少ms
 */
void Delay_1ms(u16);

#endif