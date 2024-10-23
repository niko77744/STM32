#ifndef __DRI_TIMER0_H__
#define __DRI_TIMER0_H__
#include "Com_Util.h"
#include "STDIO.H"

#define Max_Timer0CallbackFun_Count 4
typedef void(*Timer0_Callback)(void);

static Timer0_Callback s_Dri_Timer0CallbackFunArr[Max_Timer0CallbackFun_Count];

// 定时器Timer0的初始化
void Dri_Timer0_Init();

// 注册定时器0的 回调函数 参数1：回调函数
bit Dri_Timer0_setInterval(Timer0_Callback);

//  注销定时器0的 回调函数
bit Dri_Timer0_clearInterval(Timer0_Callback);

#endif /* __DRI_TIMER0_H__ */