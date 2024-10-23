#include "App_Water_Level.h"



/* 启动水位测量系统  并完成校验 */
void App_Water_Level_Start(void) {
    Driver_GPIO_TM7711_Init();
    Inf_W25q32_Init();
    App_Water_Level_calibrate();
}

/* 校验水位测量系统 */
void App_Water_Level_calibrate(void) {
    // 校验水位传感器 => 计算y = a * x + b中的两个常量值
    // (1) 第一次测量  水位为0的电压值  y1   y1 = a * 0 + b
    // (2) 第二次测量  水位为10的电压值 y2   y2 = a * 10 + b
    // 根据两次测量的结果  能够计算出  b = y1  a = (y2-y1) / 10
    
}

/* 直接读取水位测量系统的结果 */
double App_Read_Water_Level(void) {
    return;
}
