#include "Driver_Fsmc.h"


void Driver_FSMC_LCD_GPIO_Init(void);

void Driver_FSMC_LCD_Init(void) {
    // 1.开启时钟
    RCC->AHBENR |= RCC_AHBENR_FSMCEN;

    // 2.配置GPIO引脚工作模式 
    Driver_FSMC_LCD_GPIO_Init();

    /* 3.FSMC控制寄存器配置 BCR4 -- BTCR[6] */
    // 3.1 存储器块使能
    FSMC_Bank1->BTCR[6] |= FSMC_BCR4_MBKEN;

    // 3.2 存储器类型 00：SRAM、ROM(存储器块2...4在复位后的默认值) 
    FSMC_Bank1->BTCR[6] &= ~FSMC_BCR4_MTYP;

    // 3.3 禁用访问Flash
    FSMC_Bank1->BTCR[6] &= ~FSMC_BCR4_FACCEN;

    // 3.4 禁用复位模式
    FSMC_Bank1->BTCR[6] &= ~FSMC_BCR4_MUXEN;

    // 3.5 数据宽度  00 -- 8位  01 -- 16
    FSMC_Bank1->BTCR[6] &= ~FSMC_BCR4_MWID_1;
    FSMC_Bank1->BTCR[6] |= FSMC_BCR4_MWID_0;

    // 3.6 写使能
    FSMC_Bank1->BTCR[6] |= FSMC_BCR4_WREN;

    /* 4.FSMC时序寄存器配置 BTR4 -- BTCR[7] */
    // 4.1 地址建立时间 本次操作的芯片没有要求,直接写0
    FSMC_Bank1->BTCR[7] &= ~FSMC_BTR4_ADDSET;

    // 4.2 数据保持时间 芯片要求55ns以上,给一个1us
    FSMC_Bank1->BTCR[7] &= ~FSMC_BTR4_DATAST;
    FSMC_Bank1->BTCR[7] |= (71 << 8);
}


void Driver_FSMC_LCD_GPIO_Init(void) {
    RCC->APB2ENR |= (
        RCC_APB2ENR_IOPBEN |
        RCC_APB2ENR_IOPDEN |
        RCC_APB2ENR_IOPEEN |
        RCC_APB2ENR_IOPFEN |
        RCC_APB2ENR_IOPGEN);

    /* 1 配置 A0-A18 地址端口的输出模式 复用推挽输出CNF:10 50MHz速度 MODE:11*/
    /*
        2 数据端口 复用推挽输出
            在实际应用中，即使数据线被配置为输出模式，FSMC控制器仍然能够管理数据线的方向，使其在需要时成为输入线。
            这种自动切换是由FSMC控制器硬件管理的，不需要软件干预。
            因此，即使GPIO配置为复用推挽输出，FSMC依然可以实现读取操作。
    */

    GPIO_InitTypeDef GPIO_FSCM_InitStruct = { 0 };

    /* 通用推挽  背光引脚 PB0 通用推挽输出 00 11*/
    GPIO_FSCM_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_FSCM_InitStruct.GPIO_Pin = (GPIO_pin_0);
    GPIO_FSCM_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    HAL_GPIO_Init(GPIOB, &GPIO_FSCM_InitStruct);

    /* 通用推挽 复位信号线 PG15 通用推挽输出 00 11*/
    GPIO_FSCM_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_FSCM_InitStruct.GPIO_Pin = (GPIO_pin_15);
    GPIO_FSCM_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    HAL_GPIO_Init(GPIOG, &GPIO_FSCM_InitStruct);

    /* 复用推挽 */
    GPIO_FSCM_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_FSCM_InitStruct.GPIO_Pin = (GPIO_pin_0 | GPIO_pin_1 | GPIO_pin_8 | GPIO_pin_9 | GPIO_pin_10 | GPIO_pin_14 | GPIO_pin_15 | GPIO_pin_4 | GPIO_pin_5);
    GPIO_FSCM_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    HAL_GPIO_Init(GPIOD, &GPIO_FSCM_InitStruct);

    /* 复用推挽 */
    GPIO_FSCM_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_FSCM_InitStruct.GPIO_Pin = (GPIO_pin_7 | GPIO_pin_8 | GPIO_pin_9 | GPIO_pin_10 | GPIO_pin_11 | GPIO_pin_12 | GPIO_pin_13 | GPIO_pin_14 | GPIO_pin_15);
    GPIO_FSCM_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    HAL_GPIO_Init(GPIOE, &GPIO_FSCM_InitStruct);

    /* 复用推挽  12：片选信号线 */
    GPIO_FSCM_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_FSCM_InitStruct.GPIO_Pin = (GPIO_pin_0 | GPIO_pin_12);
    GPIO_FSCM_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    HAL_GPIO_Init(GPIOG, &GPIO_FSCM_InitStruct);
}
