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
 * @brief 驱动指定LED灯点亮的函数
 *
 * @param led 需要点亮的LED灯，通过位掩码指定具体的LED。例如，对于LED1，led值为0x0001。
 */
void Driver_LED_On(uint16_t led) {
    // GPIOA->ODR &= ~led;
    // 以下两行代码的目的都是使指定的LED灯点亮
    // 通过清除对应位来设置LED灯为低电平（点亮），但由于寄存器锁存机制，实际操作会有不同
    GPIOA->BRR |= led;
}


/**
 * @brief      关闭指定的LED。
 *
 * @param led  要关闭的LED的标识符。LED的标识符与硬件相关的GPIO引脚相对应。
 *
 * @note       本函数通过修改GPIOA的BSRR寄存器来关闭LED。使用BSRR寄存器而不是ODR寄存器的原因是，
 *             BSRR寄存器提供了独立的置位和复位输入，可以更安全地分别控制输出状态，避免意外修改其他引脚的状态。
 *             这里注释掉的行是另一种设置LED的方法，但考虑到代码的意图是关闭LED，应使用BSRR的下半部来实现复位（即置0）操作。
 */
void Driver_LED_Off(uint16_t led) {
    // GPIOA->ODR |= led; 
    GPIOA->BSRR |= led; // 使用BSRR寄存器的上半部来置位（即置1），实际效果是设置LED引脚为高电平，关闭LED
}

/**
 * 翻转LED的状态。
 * 如果LED当前熄灭，则点亮LED；如果LED当前点亮，则熄灭LED。
 *
 * @param led 要切换的LED对应的GPIO电平掩码。
 */
void Driver_LED_Toggle(uint16_t led) {
    // 检查LED当前状态，如果状态为0（亮灯），则点亮LED；否则熄灭LED。
    if ((GPIOA->IDR & led) == 0)  // 也可以写GPIOA->IDR
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
