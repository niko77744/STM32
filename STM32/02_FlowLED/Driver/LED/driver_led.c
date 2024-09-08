#include "driver_led.h"
// | 打开   &~ 关闭


/**
 * 函数名：Driver_LED_Init
 * 功能：初始化LED驱动器
 * 描述：
 *   - 使能GPIOA时钟
 *   - 配置GPIOA的特定引脚为推挽输出模式
 *   - 初始化后所有LED处于关闭状态
 */
void Driver_LED_Init(void) {
    // RCC_APB2ENR_IOPAEN  ((uint32_t)0x00000004)
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;  // |=0x04;

    // 配置GPIOA的引脚（LED1和LED2）为推挽50MHZ输出模式
    GPIOA->CRL &= ~(GPIO_CRL_CNF0 | GPIO_CRL_CNF1);
    GPIOA->CRL |= (GPIO_CRL_MODE0 | GPIO_CRL_MODE1);

    // 配置GPIOA的引脚（LED3）为推挽50MHZ输出模式
    GPIOA->CRH &= ~GPIO_CRH_CNF8;
    GPIOA->CRH |= GPIO_CRH_MODE8;

    // 初始化后，确保所有LED都处于关闭状态
    Driver_LED_Off(LED1);
    Driver_LED_Off(LED2);
    Driver_LED_Off(LED3);
}


/**
 * @brief 驱动LED点亮函数
 *
 * 该函数通过将指定的LED引脚置为低电平来点亮LED。使用的是GPIO的输出数据寄存器（ODR）
 * 进行操作，通过和操作（AND operation）使目标LED引脚电平为低。
 *
 * @param led 要点亮的LED的位掩码。例如，对于PA0引脚，led值为1<<0。
 */
void Driver_LED_On(uint16_t led) {
    // 设置为0开灯
    GPIOA->ODR &= ~led;
}


/**
 * @brief      关闭指定的LED
 *
 * @param led  要关闭的LED的标志位。LED标志位采用位掩码的方式，1表示该LED将被关闭。
 *
 * @note       本函数通过修改GPIOA的输出数据寄存器（ODR）来控制LED的亮灭。
 *             通过使用位或操作，可以确保指定的LED位被设置为1，从而关闭LED。
 */
void Driver_LED_Off(uint16_t led) {
    GPIOA->ODR |= led;
}

/**
 * 翻转LED的状态。
 * 如果LED当前熄灭，则点亮LED；如果LED当前点亮，则熄灭LED。
 *
 * @param led 要切换的LED对应的GPIO电平掩码。
 */
void Driver_LED_Toggle(uint16_t led) {
    // 检查LED当前状态，如果状态为0（亮灯），则点亮LED；否则熄灭LED。
    if ((GPIOA->IDR & led) == 0)
    {
        Driver_LED_Off(led);
    }
    else
    {
        Driver_LED_On(led);
    }
}

/**
 * @brief 批量打开指定的LED灯
 *
 * 遍历一个包含LED灯编号的数组，并依次打开这些LED灯。该函数通过调用Driver_LED_On函数来打开每个LED灯。
 *
 * @param leds 包含LED灯编号的数组指针。数组中的每个元素代表一个LED灯的编号。
 * @param len 表示数组中LED灯的数量。
 */
void Driver_LED_OnAll(uint16_t leds[], uint8_t len) {
    for (uint16_t i = 0; i < len; i++)
    {
        Driver_LED_On(leds[i]);
    }
}

/**
 * @brief 关闭所有指定的LED灯
 *
 * 该函数通过遍历一个LED灯数组，并调用Driver_LED_Off函数来关闭数组中所有的LED灯
 *
 * @param leds 一个指向LED灯数组的指针，数组中的每个元素代表一个需要关闭的LED灯
 * @param len 表示LED灯数组的长度，即需要关闭的LED灯的数量
 */
void Driver_LED_OffAll(uint16_t leds[], uint8_t len) {
    for (uint16_t i = 0; i < len; i++) {
        Driver_LED_Off(leds[i]);
    }
}
