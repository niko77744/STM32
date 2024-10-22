#include "Driver_Fsmc.h"


void Driver_FSMC_LCD_GPIO_Init(void);

void Driver_FSMC_LCD_Init(void) {
    // 1.����ʱ��
    RCC->AHBENR |= RCC_AHBENR_FSMCEN;

    // 2.����GPIO���Ź���ģʽ 
    Driver_FSMC_LCD_GPIO_Init();

    /* 3.FSMC���ƼĴ������� BCR4 -- BTCR[6] */
    // 3.1 �洢����ʹ��
    FSMC_Bank1->BTCR[6] |= FSMC_BCR4_MBKEN;

    // 3.2 �洢������ 00��SRAM��ROM(�洢����2...4�ڸ�λ���Ĭ��ֵ) 
    FSMC_Bank1->BTCR[6] &= ~FSMC_BCR4_MTYP;

    // 3.3 ���÷���Flash
    FSMC_Bank1->BTCR[6] &= ~FSMC_BCR4_FACCEN;

    // 3.4 ���ø�λģʽ
    FSMC_Bank1->BTCR[6] &= ~FSMC_BCR4_MUXEN;

    // 3.5 ���ݿ��  00 -- 8λ  01 -- 16
    FSMC_Bank1->BTCR[6] &= ~FSMC_BCR4_MWID_1;
    FSMC_Bank1->BTCR[6] |= FSMC_BCR4_MWID_0;

    // 3.6 дʹ��
    FSMC_Bank1->BTCR[6] |= FSMC_BCR4_WREN;

    /* 4.FSMCʱ��Ĵ������� BTR4 -- BTCR[7] */
    // 4.1 ��ַ����ʱ�� ���β�����оƬû��Ҫ��,ֱ��д0
    FSMC_Bank1->BTCR[7] &= ~FSMC_BTR4_ADDSET;

    // 4.2 ���ݱ���ʱ�� оƬҪ��55ns����,��һ��1us
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

    /* 1 ���� A0-A18 ��ַ�˿ڵ����ģʽ �����������CNF:10 50MHz�ٶ� MODE:11*/
    /*
        2 ���ݶ˿� �����������
            ��ʵ��Ӧ���У���ʹ�����߱�����Ϊ���ģʽ��FSMC��������Ȼ�ܹ����������ߵķ���ʹ������Ҫʱ��Ϊ�����ߡ�
            �����Զ��л�����FSMC������Ӳ������ģ�����Ҫ�����Ԥ��
            ��ˣ���ʹGPIO����Ϊ�������������FSMC��Ȼ����ʵ�ֶ�ȡ������
    */

    GPIO_InitTypeDef GPIO_FSCM_InitStruct = { 0 };

    /* ͨ������  �������� PB0 ͨ��������� 00 11*/
    GPIO_FSCM_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_FSCM_InitStruct.GPIO_Pin = (GPIO_pin_0);
    GPIO_FSCM_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    HAL_GPIO_Init(GPIOB, &GPIO_FSCM_InitStruct);

    /* ͨ������ ��λ�ź��� PG15 ͨ��������� 00 11*/
    GPIO_FSCM_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_FSCM_InitStruct.GPIO_Pin = (GPIO_pin_15);
    GPIO_FSCM_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    HAL_GPIO_Init(GPIOG, &GPIO_FSCM_InitStruct);

    /* �������� */
    GPIO_FSCM_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_FSCM_InitStruct.GPIO_Pin = (GPIO_pin_0 | GPIO_pin_1 | GPIO_pin_8 | GPIO_pin_9 | GPIO_pin_10 | GPIO_pin_14 | GPIO_pin_15 | GPIO_pin_4 | GPIO_pin_5);
    GPIO_FSCM_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    HAL_GPIO_Init(GPIOD, &GPIO_FSCM_InitStruct);

    /* �������� */
    GPIO_FSCM_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_FSCM_InitStruct.GPIO_Pin = (GPIO_pin_7 | GPIO_pin_8 | GPIO_pin_9 | GPIO_pin_10 | GPIO_pin_11 | GPIO_pin_12 | GPIO_pin_13 | GPIO_pin_14 | GPIO_pin_15);
    GPIO_FSCM_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    HAL_GPIO_Init(GPIOE, &GPIO_FSCM_InitStruct);

    /* ��������  12��Ƭѡ�ź��� */
    GPIO_FSCM_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_FSCM_InitStruct.GPIO_Pin = (GPIO_pin_0 | GPIO_pin_12);
    GPIO_FSCM_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    HAL_GPIO_Init(GPIOG, &GPIO_FSCM_InitStruct);
}
