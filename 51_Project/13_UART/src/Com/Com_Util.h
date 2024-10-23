#ifndef __COM_UTIL_H__
#define __COM_UTIL_H__

#include <STC89C5xRC.H>
#include <INTRINS.H>
#include "string.h"

// LED流水灯开关  0关1开，默认开
#define  LED_SwitchH P34  // #define PI 3.14

// 数码管开关 0开1关
#define  DigitalTube_SwitchL P36

// 点阵屏开关
#define MatrixLED_SwitchL P35
#define SER P10  // 串行数据输入
#define SCK P12  // 移位寄存器时钟 上升沿触发
#define RCK P11  // 存储寄存器时钟 上升沿触发


// 类型别名
typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;


/**
 * @brief 时间延时函数
 * @param count 指定延时多少ms
 */
void Delay_1ms(u16);
void Delay_10us(u16);

#endif