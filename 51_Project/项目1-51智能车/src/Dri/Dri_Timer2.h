#ifndef __DRI_Timer2_H__
#define __DRI_Timer2_H__

#include <STDIO.H>
#include "Com_Util.h"

// 定义Timer2 可以注册回调函数的数量
#define MAX_CALLBACK_COUNT 4

// 给函数指针（指向要注册给定时器的回调函数）设置别名
typedef void (*Timer2_Callback)(void);

/**
 * @brief 定时器0 初始化
 *
 */
void Dri_Timer2_Init();

/**
 * @brief 给定时器0 注册回调函数
 *
 * @param callback 要注册回调函数
 * @return bit 1表示注册成功 0表示注册失败
 */
bit Dri_Timer2_RegisterCallback(Timer2_Callback);

/**
 * @brief 注销定时器0的回调函数
 *
 * @param callback 要注销的回调函数
 * @return bit 1表示注销成功 0表示注销失败
 */
bit Dri_Timer2_DeregisterCallback(Timer2_Callback);


#endif /* __DRI_Timer2_H__ */