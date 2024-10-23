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

/**
 * @brief 延时10微秒
 * 
 */
void Delay10us(void);

/**
 * @brief 延时50微秒
 * 
 */
void Delay50us(void);

/**
 * @brief 延时60微秒
 * 
 */
void Delay60us(void);

/**
 * @brief 延时480微秒
 * 
 */
void Delay480us(void);

#endif