#ifndef __INT_OLED_H__
#define __INT_OLED_H__

#include "Com_Util.h"
#include "Dri_IIC.h"

#define OLED_ADDR 0x78

/**
 * @brief OLED 初始化
 * 
 */
void Int_OLED_Init();


/**
 * @brief OLED 清屏
 * 
 */
void Int_OLED_Clear();


/**
 * @brief OLED 显示字符串
 * 
 * @param x X坐标
 * @param y Y坐标
 * @param str 要写入的字符串
 */
void Int_OLED_DisplayStr(u8 x, u8 y, u8 *str);

/**
 * @brief OLED 显示数字
 * 
 * @param x X坐标
 * @param y Y坐标
 * @param num 要写入的数字
 */
void Int_OLED_DisplayNum(u8 x, u8 y, long num);


#endif /* __INT_OLED_H__ */