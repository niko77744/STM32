#include "driver_led.h"
// | ��   &~ �ر�


/**
 * ��������Driver_LED_Init
 * ���ܣ���ʼ��LED������
 * ������
 *   - ʹ��GPIOAʱ��
 *   - ����GPIOA���ض�����Ϊ�������ģʽ
 *   - ��ʼ��������LED���ڹر�״̬
 */
void Driver_LED_Init(void) {
    // RCC_APB2ENR_IOPAEN  ((uint32_t)0x00000004)
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;  // |=0x04;

    // ����GPIOA�����ţ�LED1��LED2��Ϊ����50MHZ���ģʽ
    GPIOA->CRL &= ~(GPIO_CRL_CNF0 | GPIO_CRL_CNF1);
    GPIOA->CRL |= (GPIO_CRL_MODE0 | GPIO_CRL_MODE1);

    // ����GPIOA�����ţ�LED3��Ϊ����50MHZ���ģʽ
    GPIOA->CRH &= ~GPIO_CRH_CNF8;
    GPIOA->CRH |= GPIO_CRH_MODE8;

    // ��ʼ����ȷ������LED�����ڹر�״̬
    Driver_LED_Off(LED1);
    Driver_LED_Off(LED2);
    Driver_LED_Off(LED3);
}


/**
 * @brief ����LED��������
 *
 * �ú���ͨ����ָ����LED������Ϊ�͵�ƽ������LED��ʹ�õ���GPIO��������ݼĴ�����ODR��
 * ���в�����ͨ���Ͳ�����AND operation��ʹĿ��LED���ŵ�ƽΪ�͡�
 *
 * @param led Ҫ������LED��λ���롣���磬����PA0���ţ�ledֵΪ1<<0��
 */
void Driver_LED_On(uint16_t led) {
    // ����Ϊ0����
    GPIOA->ODR &= ~led;
}


/**
 * @brief      �ر�ָ����LED
 *
 * @param led  Ҫ�رյ�LED�ı�־λ��LED��־λ����λ����ķ�ʽ��1��ʾ��LED�����رա�
 *
 * @note       ������ͨ���޸�GPIOA��������ݼĴ�����ODR��������LED������
 *             ͨ��ʹ��λ�����������ȷ��ָ����LEDλ������Ϊ1���Ӷ��ر�LED��
 */
void Driver_LED_Off(uint16_t led) {
    GPIOA->ODR |= led;
}

/**
 * ��תLED��״̬��
 * ���LED��ǰϨ�������LED�����LED��ǰ��������Ϩ��LED��
 *
 * @param led Ҫ�л���LED��Ӧ��GPIO��ƽ���롣
 */
void Driver_LED_Toggle(uint16_t led) {
    // ���LED��ǰ״̬�����״̬Ϊ0�����ƣ��������LED������Ϩ��LED��
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
 * @brief ������ָ����LED��
 *
 * ����һ������LED�Ʊ�ŵ����飬�����δ���ЩLED�ơ��ú���ͨ������Driver_LED_On��������ÿ��LED�ơ�
 *
 * @param leds ����LED�Ʊ�ŵ�����ָ�롣�����е�ÿ��Ԫ�ش���һ��LED�Ƶı�š�
 * @param len ��ʾ������LED�Ƶ�������
 */
void Driver_LED_OnAll(uint16_t leds[], uint8_t len) {
    for (uint16_t i = 0; i < len; i++)
    {
        Driver_LED_On(leds[i]);
    }
}

/**
 * @brief �ر�����ָ����LED��
 *
 * �ú���ͨ������һ��LED�����飬������Driver_LED_Off�������ر����������е�LED��
 *
 * @param leds һ��ָ��LED�������ָ�룬�����е�ÿ��Ԫ�ش���һ����Ҫ�رյ�LED��
 * @param len ��ʾLED������ĳ��ȣ�����Ҫ�رյ�LED�Ƶ�����
 */
void Driver_LED_OffAll(uint16_t leds[], uint8_t len) {
    for (uint16_t i = 0; i < len; i++) {
        Driver_LED_Off(leds[i]);
    }
}
