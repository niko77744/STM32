#include "led.h"


void LED_On(uint16_t LED) {
    HAL_GPIO_WritePin(GPIOA, LED, GPIO_PIN_RESET);
}

void LED_Off(uint16_t LED) {
    HAL_GPIO_WritePin(GPIOA, LED, GPIO_PIN_SET);
}


void LED_Toogle(uint16_t LED) {
    HAL_GPIO_TogglePin(GPIOA, LED);
}


void LED_OnAll(uint16_t leds[], uint8_t len) {
    for (uint8_t i = 0; i < len; i++)
    {
        HAL_GPIO_WritePin(GPIOA, leds[i], GPIO_PIN_RESET);
    }
}
void LED_OffAll(uint16_t leds[], uint8_t len) {
    for (uint8_t i = 0; i < len; i++)
    {
        HAL_GPIO_WritePin(GPIOA, leds[i], GPIO_PIN_SET);
    }
}


/**
 * @brief 实现LED流水灯效果
 * 
 * 通过依次点亮和熄灭LED灯，实现流水灯的效果。该函数按顺序点亮所有的LED灯，
 * 然后逆序熄灭它们。使用了两个for循环来分别处理点亮和熄灭的过程。
 * 
 * @param leds 一个包含所有LED灯的数组，数组中的每个元素代表一个LED灯
 * @param len 表示数组中LED灯的数量
 */
void LED_FlowLight(uint16_t leds[], uint8_t len) {
    // 顺次点亮LED灯
    for (uint8_t i = 0; i < len; i++) {
        LED_Toogle(leds[i]); // 切换LED灯状态
        HAL_Delay(1000); // 延时1秒
    }
    
    // 逆序熄灭LED灯
    for (int8_t i = (len - 1); i >= 0; i--) {
        LED_Toogle(leds[i]); // 切换LED灯状态
        HAL_Delay(1000); // 延时1秒
    }

    // 以下是尝试使用单循环实现相同功能的代码，但被注释掉了
    // static uint8_t i = 0; // 用于记录当前点亮/熄灭的LED灯索引
    // static bool flag = 0; // 用于控制是正向点亮还是反向熄灭

    // if (0 == i) {
    //     flag = 1; // 设置方向标志为正向
    //     LED_Toogle(leds[i]); // 切换第一个LED灯状态
    //     HAL_Delay(1000); // 延时1秒
    // } else if ((len - 1) == i) {
    //     flag = 0; // 设置方向标志为反向
    //     LED_Toogle(leds[i]); // 切换最后一个LED灯状态
    //     HAL_Delay(1000); // 延时1秒
    // }
    // (flag == 1) ? (i++) : (i--); // 根据方向标志改变LED灯索引
    // LED_Toogle(leds[i]); // 切换当前LED灯状态
    // HAL_Delay(1000); // 延时1秒
}

