#ifndef __INT_MatrixLED_H__
#define __INT_MatrixLED_H__
#include "Com_Util.h"

/**
 * @brief 点阵LED初始化
 *
 */
void Int_MatrixLED_Init(void);


/**
 * @brief 设置点阵屏要显示的信息 给 存储点阵屏每行的显示信息 的数组赋值
 * @param pixels 点阵屏信息，长度必须是8，每个元素必须是8bit整数
 */
void Int_MatrixLED_SetPixels(u8[8]);



/**
 * @brief 让数组中的元素整体后移，0位置添加新元素
 *
 * @param new_line
 */
void Int_MatrixLED_ShiftPixels(u8);



/**
 * @brief 刷新显示信息
 */
void Int_MatrixLED_Refresh();

#endif /* __INT_MatrixLED_H__ */
