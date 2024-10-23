#ifndef __INT_DIGITAL_TUBE_H__
#define __INT_DIGITAL_TUBE_H__

#include "Com_Util.h"



// 定义数码管的片选数组
static u8 DigitalTube_codes[10] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F  // 9
};

//定义数码管的显示函数
/**
 * @brief 数码管指定位置显示数字
 * 
 * @param dig 位选数
 * @param num 片选数
 */
void Int_DigitalTube_single (u8 dig ,u8 num);

//定义函数将数字循环赋值给缓存数组
/**
 * @brief 将数字储存到缓存数字
 * 
 * @param number 
 */
void Int_DigitalTube_DisplayNum(u32 number);


/**
 * @brief 刷新数码管
 * 
 */
void Int_DigitalTube_Refresh();

/**
 * @brief 初始化数码管
 * 
 */
void Int_DigitalTube_Init();

#endif


