#ifndef __Dri_Timer_H__
#define __Dri_Timer_H__

#include <STDIO.H>
#include "Com_Util.h"


#define MAX_CALLBACK_COUNT 4
// typedef void (*Timer0_Callback)(void);
typedef void (*Timer0_Callback)(void);


// 定时器Timer0的初始化
void Dri_Timer0_Init();

// 注册定时器0的 回调函数 参数1：回调函数  参数2：频率TriggerFrequency ms一次
bit Dri_Timer0_setInterval(Timer0_Callback, u16);

//  注销定时器0的 回调函数
bit Dri_Timer0_clearInterval(Timer0_Callback);

#endif /*  __Dri_Timer_H__ */


