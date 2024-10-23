#include "Dri_Extern0Interrruput.h"

//中断服务程序
void Extern0_Handler() interrupt 0
{
    P00 = ~P00;
}


/**
 * @brief 外部中断0初始化
 * 
 */
void Dri_Extern0Interruput_Init()
{
    //打开中断开关
    EA = 1;
    //打开外部中断开关
    EX0 =1;
    //配置中断触发方式
    IT0=0;
    //配置中断优先级
    PX0 =1;
}