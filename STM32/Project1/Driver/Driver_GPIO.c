/*
* @Description: 水位模块和按键(通过按键校准)的引脚初始化
* @Author: niko77744
* @Date: 2024-10-23 17:06:35
*/


#include "Driver_GPIO.h"

/**
 * @brief TM7711测量水位 压力传感器  压力的值和传感器产生的电压值是线性关系
 * @param PB12 时钟信号 通用推挽
 * @param PB13 数据输出信号 浮空输入
 * @param PF8  按键KEY1 上拉输入 默认接地
 *
 */
void Driver_GPIO_TM7711_Init(void) {
    RCC->APB2ENR |= (RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPFEN);
    Hal_GPIO_Mode_Selection(GPIOB, GPIO_pin_12, GPIO_Mode_Out_PP);
    Hal_GPIO_Mode_Selection(GPIOB, GPIO_pin_13, GPIO_Mode_IN_FLOATING);
    Hal_GPIO_Mode_Selection(GPIOF, GPIO_pin_8, GPIO_Mode_IPU);
}


/**
 * @brief 使用轮询的方式判断按键是否按下 默认高电平 按下接地
 *
 * @return uint8_t 1按下  0未按下
 */
uint8_t Driver_GPIO_IsKey3Pressed(void) {
    /* 等待按键被按下 */
    while (HAL_GPIO_ReadPin(GPIOF, GPIO_pin_8) != 0);
    Delay_ms(10); //消抖
    if (HAL_GPIO_ReadPin(GPIOF, GPIO_pin_8) == 0)
    {
        /* 等待松开按键 */
        while (HAL_GPIO_ReadPin(GPIOF, GPIO_pin_8) == 0);
        debug_print("key");
        return 1;
    }
    return 0;
}
