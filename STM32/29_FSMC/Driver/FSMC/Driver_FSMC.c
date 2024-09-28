#include "Driver_FSMC.h"


void Driver_FSMC_GPIO_Init(void) {
    RCC->APB2ENR |= (RCC_APB2ENR_IOPDEN | RCC_APB2ENR_IOPEEN | RCC_APB2ENR_IOPFEN | RCC_APB2ENR_IOPGEN);

    // GPIO_InitTypeDef GPIO_FSCM_InitStruct = { 0 };

    // GPIO_FSCM_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    // GPIO_FSCM_InitStruct.GPIO_Pin = (GPIO_pin_11 | GPIO_pin_12 | GPIO_pin_13 | GPIO_pin_14 | GPIO_pin_15 | GPIO_pin_0, GPIO_pin_1, GPIO_pin_8, GPIO_pin_9, GPIO_pin_10, GPIO_pin_4, GPIO_pin_5);
    // GPIO_FSCM_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    // HAL_GPIO_Init(GPIOD, &GPIO_FSCM_InitStruct);

    // GPIO_FSCM_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    // GPIO_FSCM_InitStruct.GPIO_Pin = (GPIO_pin_7 | GPIO_pin_8 | GPIO_pin_9 | GPIO_pin_10 | GPIO_pin_11 | GPIO_pin_12, GPIO_pin_13, GPIO_pin_14, GPIO_pin_15, GPIO_pin_0, GPIO_pin_1);
    // GPIO_FSCM_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    // HAL_GPIO_Init(GPIOE, &GPIO_FSCM_InitStruct);

    // GPIO_FSCM_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    // GPIO_FSCM_InitStruct.GPIO_Pin = (GPIO_pin_0 | GPIO_pin_1 | GPIO_pin_2 | GPIO_pin_3 | GPIO_pin_4 | GPIO_pin_5, GPIO_pin_12, GPIO_pin_13, GPIO_pin_14, GPIO_pin_15);
    // GPIO_FSCM_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    // HAL_GPIO_Init(GPIOF, &GPIO_FSCM_InitStruct);

    // GPIO_FSCM_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    // GPIO_FSCM_InitStruct.GPIO_Pin = (GPIO_pin_0 | GPIO_pin_1 | GPIO_pin_2 | GPIO_pin_3 | GPIO_pin_4 | GPIO_pin_5, GPIO_pin_10);
    // GPIO_FSCM_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    // HAL_GPIO_Init(GPIOG, &GPIO_FSCM_InitStruct);
    Hal_GPIO_Mode_Selection(GPIOD, GPIO_pin_11, GPIO_Mode_AF_PP);
    Hal_GPIO_Mode_Selection(GPIOD, GPIO_pin_12, GPIO_Mode_AF_PP);
    Hal_GPIO_Mode_Selection(GPIOD, GPIO_pin_13, GPIO_Mode_AF_PP);
    Hal_GPIO_Mode_Selection(GPIOD, GPIO_pin_14, GPIO_Mode_AF_PP);
    Hal_GPIO_Mode_Selection(GPIOD, GPIO_pin_15, GPIO_Mode_AF_PP);
    Hal_GPIO_Mode_Selection(GPIOD, GPIO_pin_0, GPIO_Mode_AF_PP);
    Hal_GPIO_Mode_Selection(GPIOD, GPIO_pin_1, GPIO_Mode_AF_PP);
    Hal_GPIO_Mode_Selection(GPIOD, GPIO_pin_8, GPIO_Mode_AF_PP);
    Hal_GPIO_Mode_Selection(GPIOD, GPIO_pin_9, GPIO_Mode_AF_PP);
    Hal_GPIO_Mode_Selection(GPIOD, GPIO_pin_10, GPIO_Mode_AF_PP);
    Hal_GPIO_Mode_Selection(GPIOD, GPIO_pin_4, GPIO_Mode_AF_PP);
    Hal_GPIO_Mode_Selection(GPIOD, GPIO_pin_5, GPIO_Mode_AF_PP);

    Hal_GPIO_Mode_Selection(GPIOE, GPIO_pin_7, GPIO_Mode_AF_PP);
    Hal_GPIO_Mode_Selection(GPIOE, GPIO_pin_8, GPIO_Mode_AF_PP);
    Hal_GPIO_Mode_Selection(GPIOE, GPIO_pin_9, GPIO_Mode_AF_PP);
    Hal_GPIO_Mode_Selection(GPIOE, GPIO_pin_10, GPIO_Mode_AF_PP);
    Hal_GPIO_Mode_Selection(GPIOE, GPIO_pin_11, GPIO_Mode_AF_PP);
    Hal_GPIO_Mode_Selection(GPIOE, GPIO_pin_12, GPIO_Mode_AF_PP);
    Hal_GPIO_Mode_Selection(GPIOE, GPIO_pin_13, GPIO_Mode_AF_PP);
    Hal_GPIO_Mode_Selection(GPIOE, GPIO_pin_14, GPIO_Mode_AF_PP);
    Hal_GPIO_Mode_Selection(GPIOE, GPIO_pin_15, GPIO_Mode_AF_PP);
    Hal_GPIO_Mode_Selection(GPIOE, GPIO_pin_0, GPIO_Mode_AF_PP);
    Hal_GPIO_Mode_Selection(GPIOE, GPIO_pin_1, GPIO_Mode_AF_PP);

    Hal_GPIO_Mode_Selection(GPIOF, GPIO_pin_0, GPIO_Mode_AF_PP);
    Hal_GPIO_Mode_Selection(GPIOF, GPIO_pin_1, GPIO_Mode_AF_PP);
    Hal_GPIO_Mode_Selection(GPIOF, GPIO_pin_2, GPIO_Mode_AF_PP);
    Hal_GPIO_Mode_Selection(GPIOF, GPIO_pin_3, GPIO_Mode_AF_PP);
    Hal_GPIO_Mode_Selection(GPIOF, GPIO_pin_4, GPIO_Mode_AF_PP);
    Hal_GPIO_Mode_Selection(GPIOF, GPIO_pin_5, GPIO_Mode_AF_PP);
    Hal_GPIO_Mode_Selection(GPIOF, GPIO_pin_12, GPIO_Mode_AF_PP);
    Hal_GPIO_Mode_Selection(GPIOF, GPIO_pin_13, GPIO_Mode_AF_PP);
    Hal_GPIO_Mode_Selection(GPIOF, GPIO_pin_14, GPIO_Mode_AF_PP);
    Hal_GPIO_Mode_Selection(GPIOF, GPIO_pin_15, GPIO_Mode_AF_PP);

    Hal_GPIO_Mode_Selection(GPIOG, GPIO_pin_0, GPIO_Mode_AF_PP);
    Hal_GPIO_Mode_Selection(GPIOG, GPIO_pin_1, GPIO_Mode_AF_PP);
    Hal_GPIO_Mode_Selection(GPIOG, GPIO_pin_2, GPIO_Mode_AF_PP);
    Hal_GPIO_Mode_Selection(GPIOG, GPIO_pin_3, GPIO_Mode_AF_PP);
    Hal_GPIO_Mode_Selection(GPIOG, GPIO_pin_4, GPIO_Mode_AF_PP);
    Hal_GPIO_Mode_Selection(GPIOG, GPIO_pin_5, GPIO_Mode_AF_PP);
    Hal_GPIO_Mode_Selection(GPIOG, GPIO_pin_10, GPIO_Mode_AF_PP);
}
void Driver_FSMC_Init(void) {
    /* 1.����ʱ�� */
    RCC->AHBENR |= RCC_AHBENR_FSMCEN;

    /* 2.����GPIO���Ź���ģʽ ����������� CNF:10 MODE:11 */
    Driver_FSMC_GPIO_Init();

    /* 3.FSMC���ƼĴ������� BCR3 -- BTCR[4] */
    // 3.1 �洢����ʹ��
    FSMC_Bank1->BTCR[4] |= FSMC_BCR3_MBKEN;

    // 3.2 ѡ��洢������ SRAM  00
    FSMC_Bank1->BTCR[4] &= ~FSMC_BCR3_MTYP;

    // 3.3 ���÷���Flash
    FSMC_Bank1->BTCR[4] &= ~FSMC_BCR3_FACCEN;

    // 3.4 ���ø���ģʽ
    FSMC_Bank1->BTCR[4] &= ~FSMC_BCR3_MUXEN;

    // 3.5 ���ݿ��  00 -- 8λ  01 -- 16
    FSMC_Bank1->BTCR[4] &= ~FSMC_BCR3_MWID_1;
    FSMC_Bank1->BTCR[4] |= FSMC_BCR3_MWID_0;

    // 3.6 дʹ��
    FSMC_Bank1->BTCR[4] |= FSMC_BCR3_WREN;

    /* 4.FSMCʱ��Ĵ������� BTR3 -- BTCR[5] */
    // 4.1 ��ַ����ʱ�� ���β�����оƬû��Ҫ��,ֱ��д0
    FSMC_Bank1->BTCR[5] &= ~FSMC_BTR3_ADDSET;

    // 4.2 ���ݱ���ʱ�� оƬҪ��55ns����,��һ��1us
    FSMC_Bank1->BTCR[5] &= ~FSMC_BTR3_DATAST;
    FSMC_Bank1->BTCR[5] |= (71 << 8);
}


/*
��ַ�ߣ�
PF0 ? ------> FSMC_A0
PF1 ? ------> FSMC_A1
PF2 ? ------> FSMC_A2
PF3 ? ------> FSMC_A3
PF4 ? ------> FSMC_A4
PF5 ? ------> FSMC_A5
PF12 ? ------> FSMC_A6
PF13 ? ------> FSMC_A7
PF14 ? ------> FSMC_A8
PF15 ? ------> FSMC_A9
PG0 ? ------> FSMC_A10
PG1 ? ------> FSMC_A11
PG2 ? ------> FSMC_A12
PG3 ? ------> FSMC_A13
PG4 ? ------> FSMC_A14
PG5 ? ------> FSMC_A15
PD11 ? ------> FSMC_A16
PD12 ? ------> FSMC_A17
PD13 ? ------> FSMC_A18

�����ߣ�
PD14 ? ------> FSMC_D0
PD15 ? ------> FSMC_D1
PD0 ? ------> FSMC_D2
PD1 ? ------> FSMC_D3
PE7 ? ------> FSMC_D4
PE8 ? ------> FSMC_D5
PE9 ? ------> FSMC_D6
PE10 ? ------> FSMC_D7
PE11 ? ------> FSMC_D8
PE12 ? ------> FSMC_D9
PE13 ? ------> FSMC_D10
PE14 ? ------> FSMC_D11
PE15 ? ------> FSMC_D12
PD8 ? ------> FSMC_D13
PD9 ? ------> FSMC_D14
PD10 ? ------> FSMC_D15

������
PD4 ? ------> FSMC_NOE
PD5 ? ------> FSMC_NWE
PG10 ? ------> FSMC_NE3
PE0 ? ------> FSMC_NBL0
PE1 ? ------> FSMC_NBL1
*/
