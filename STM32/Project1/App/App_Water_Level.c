#include "App_Water_Level.h"

double wl_const_k[1];   // 水深模块 斜率
double wl_const_b[1];   // 水深模块 截距



/* 启动水位测量系统  并完成校验 */
void App_Water_Level_Start(void) {
    Inf_TM7711_Init();
    Inf_W25q32_Init();
    App_Water_Level_calibrate();
}

/* 校验水位测量系统 */
/**
 * @brief x就是水的深度  校验是在求k和b  测量得到y就可以反推水深x
 *
 */
void App_Water_Level_calibrate(void) {
    // 校验水位传感器 => 计算y = k * x + b中的两个常量值  
    // (1) 第一次测量  水位为0的电压值  y1   y1 = k * 0 + b
    // (2) 第二次测量  水位为10的电压值 y2   y2 = k * 10 + b
    // 根据两次测量的结果  能够计算出  b = y1  k = (y2-y1) / 10
    App_Display_Hint(10, 120, "请根据提示按下按键开始水位校准");
    while (Driver_GPIO_IsKey3Pressed() == 0);  //等待按键按下
    App_Display_ClearHint();
    App_Display_Hint(10, 120, "第一步：将水管放在空中按下按键");
    while (Driver_GPIO_IsKey3Pressed() == 0);  //等待按键按下
    App_Display_ClearHint();

    // 第一次测量检验
    uint32_t y1 = Inf_TM7711_ReadV();

    App_Display_Hint(10, 120, "第二步：将水管放在水深十厘米处并再次按下按键");
    while (Driver_GPIO_IsKey3Pressed() == 0);  //等待按键按下
    App_Display_ClearHint();

    // 第一次测量检验
    uint32_t y2 = Inf_TM7711_ReadV();

    wl_const_b[0] = y1;
    wl_const_k[0] = (double)(y2 - y1) / 10.0;

    App_Display_Hint(10, 120, "完成校验，可以开始测量");
}

/* 直接读取水位测量系统的结果 */
double App_Read_Water_Level(void) {
    uint32_t y = Inf_TM7711_ReadV();
    double water_level = (y - wl_const_b[0]) / wl_const_k[0];
    return (water_level >= 0) ? water_level : 0;
}
