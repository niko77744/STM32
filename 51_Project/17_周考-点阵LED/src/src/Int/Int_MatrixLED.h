#ifndef __INT_MATRIXLED_H__
#define __INT_MATRIXLED_H__

#include "Com_Util.h"
#define SER P10 // 串行信号输入
#define SCK P12 // 移位寄存器时钟输入
#define RCK P11 // 存储寄存器时钟输入

#define DZ_EN P35 // 74HC595芯片使能输入，低电平有效

// 定义像素数组
// u8 pic[8] = {0x1,
//              0x2,
//              0x4,
//              0x8,
//              0x10,
//              0x20,
//              0x40,
//              0x80};

// 定义像素数组
static u8 picture[4][8] = {
    {0x58,0x58,0x3C,0x1A,0x1A,0x3C,0x42,0x42},
    {0x1A,0x1A,0x3C,0x58,0x58,0x3C,0x42,0x42},
    {0x30,0x30,0x3C,0x5A,0x5A,0x3C,0x42,0x42},
    {0x0C,0x0C,0x3C,0x5A,0x5A,0x3C,0x42,0x42}};

/**
 * @brief 点阵屏初始化
 *
 */
void Int_MatrixLED_Init();

/**
 * @brief 将像素信息储存进缓存数组
 *
 * @param pixel 像素信息
 */
void Int_MatrixLED_SetPixel(u8 *pixel);

/**
 * @brief 数码管刷新函数
 *
 */
void Int_MatrixLED_Refersh();

/**
 * @brief 改变缓存数组中的元素
 *
 * @param line 为数组中的首位元素赋值
 */
void Int_MatrixLE_ShiftPixel(u8 line);

// /**
//  * @brief 更改缓存数组内的元素
//  * @param pic 二维数组
//  */
// void Int_Matrix_ChangeBuffer(u8 *pic, u8 time);

#endif /* __INT_MATRIXLED_H__ */