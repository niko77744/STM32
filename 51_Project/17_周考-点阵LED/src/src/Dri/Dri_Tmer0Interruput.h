#ifndef __DRI_TMER0INTERRUPUT_H__
#define __DRI_TMER0INTERRUPUT_H__

#include "Com_Util.h"
#define MaxFunctionCount 4

// 定义函数指针
typedef void(*CallbackFunction)(void);

// 定义指针数组
static CallbackFunction FunctionArray[MaxFunctionCount];


/**
 * @brief 定时器0中断初始化
 * 
 */
void Dri_Timer0Interrupt_Init();

/**
 * @brief 注册功能函数
 * 
 * @param Function 注册功能名
 * @return bit 
 */
bit Dri_Timer0Interrupt_RegisiterFunction (CallbackFunction );

/**
 * @brief 注销功能函数
 * 
 * @param Function 注销功能名
 * @return bit 
 */
bit Dri_Timer0Interrupt_DeregisiterFunction (CallbackFunction);

/**
 * @brief LED亮灭功能
 * 
 */
void toggle_LED1();








#endif /* __DRI_TMER0INTERRUPUT_H__ */