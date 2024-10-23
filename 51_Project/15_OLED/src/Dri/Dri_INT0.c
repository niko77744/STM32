#include "Com_Util.h"
#include "Dri_INT0.h"
void Dri_INT0_init() {
    // 打开中断总开关
    EA = 1;  //open global interrupt switch

    // 打开 INT0 开关
    EX0 = 1;  //enable INT0 interrupt

    // 配置外部中断 INT0 触发方式： 0表示低电平触发、1表示下降沿触发
    IT0 = 1; //set INT0 interrupt type (1:Falling 0:Low level)

    // 配置外部中断 INT0 优先级，把等级设置为1，高位0低位1 （等级：0 、1、 2、 3）
    PX0 = 1;
}


// 外部中断 INT0 的服务程序
void INT0_Handler() interrupt 0
{
    // LED 亮灭
    P00 = ~P00;
}

