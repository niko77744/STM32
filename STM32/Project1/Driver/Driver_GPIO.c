/*
* @Description: ˮλģ��Ͱ���(ͨ������У׼)�����ų�ʼ��
* @Author: niko77744
* @Date: 2024-10-23 17:06:35
*/


#include "Driver_GPIO.h"

/**
 * @brief TM7711����ˮλ ѹ��������  ѹ����ֵ�ʹ����������ĵ�ѹֵ�����Թ�ϵ
 * @param PB12 ʱ���ź� ͨ������
 * @param PB13 ��������ź� ��������
 * @param PF8  ����KEY1 �������� Ĭ�Ͻӵ�
 *
 */
void Driver_GPIO_TM7711_Init(void) {
    RCC->APB2ENR |= (RCC_APB2ENR_IOPBEN | RCC_APB2ENR_IOPFEN);
    Hal_GPIO_Mode_Selection(GPIOB, GPIO_pin_12, GPIO_Mode_Out_PP);
    Hal_GPIO_Mode_Selection(GPIOB, GPIO_pin_13, GPIO_Mode_IN_FLOATING);
    Hal_GPIO_Mode_Selection(GPIOF, GPIO_pin_8, GPIO_Mode_IPU);
}


/**
 * @brief ʹ����ѯ�ķ�ʽ�жϰ����Ƿ��� Ĭ�ϸߵ�ƽ ���½ӵ�
 *
 * @return uint8_t 1����  0δ����
 */
uint8_t Driver_GPIO_IsKey3Pressed(void) {
    /* �ȴ����������� */
    while (HAL_GPIO_ReadPin(GPIOF, GPIO_pin_8) != 0);
    Delay_ms(10); //����
    if (HAL_GPIO_ReadPin(GPIOF, GPIO_pin_8) == 0)
    {
        /* �ȴ��ɿ����� */
        while (HAL_GPIO_ReadPin(GPIOF, GPIO_pin_8) == 0);
        debug_print("key");
        return 1;
    }
    return 0;
}
