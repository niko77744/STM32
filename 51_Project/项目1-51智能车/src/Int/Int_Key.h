#ifndef __INT_KEY_H__
#define __INT_KEY_H__

#include "Com_Util.h"
#include "Dri_GPIO.h"


/**
 * @brief 按键初始化
 */
void Int_Key_Init();

/**
 * @brief 判断按键1的状态
 *
 * @return 0:按键无变化 1:按键正在被按下（下降沿） 2:按键正在抬起（上升沿）
 *
 */
u8 Int_Key_GetSw1Status();

/**
 * @brief 判断按键2的状态
 *
 * @return 0:按键无变化 1:按键正在被按下（下降沿） 2:按键正在抬起（上升沿）
 *
 */
u8 Int_Key_GetSw2Status();


#endif