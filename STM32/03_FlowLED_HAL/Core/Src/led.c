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
 * @brief ʵ��LED��ˮ��Ч��
 * 
 * ͨ�����ε�����Ϩ��LED�ƣ�ʵ����ˮ�Ƶ�Ч�����ú�����˳��������е�LED�ƣ�
 * Ȼ������Ϩ�����ǡ�ʹ��������forѭ�����ֱ��������Ϩ��Ĺ��̡�
 * 
 * @param leds һ����������LED�Ƶ����飬�����е�ÿ��Ԫ�ش���һ��LED��
 * @param len ��ʾ������LED�Ƶ�����
 */
void LED_FlowLight(uint16_t leds[], uint8_t len) {
    // ˳�ε���LED��
    for (uint8_t i = 0; i < len; i++) {
        LED_Toogle(leds[i]); // �л�LED��״̬
        HAL_Delay(1000); // ��ʱ1��
    }
    
    // ����Ϩ��LED��
    for (int8_t i = (len - 1); i >= 0; i--) {
        LED_Toogle(leds[i]); // �л�LED��״̬
        HAL_Delay(1000); // ��ʱ1��
    }

    // �����ǳ���ʹ�õ�ѭ��ʵ����ͬ���ܵĴ��룬����ע�͵���
    // static uint8_t i = 0; // ���ڼ�¼��ǰ����/Ϩ���LED������
    // static bool flag = 0; // ���ڿ���������������Ƿ���Ϩ��

    // if (0 == i) {
    //     flag = 1; // ���÷����־Ϊ����
    //     LED_Toogle(leds[i]); // �л���һ��LED��״̬
    //     HAL_Delay(1000); // ��ʱ1��
    // } else if ((len - 1) == i) {
    //     flag = 0; // ���÷����־Ϊ����
    //     LED_Toogle(leds[i]); // �л����һ��LED��״̬
    //     HAL_Delay(1000); // ��ʱ1��
    // }
    // (flag == 1) ? (i++) : (i--); // ���ݷ����־�ı�LED������
    // LED_Toogle(leds[i]); // �л���ǰLED��״̬
    // HAL_Delay(1000); // ��ʱ1��
}

