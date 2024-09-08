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
 * @brief ����ָ��LED�Ƶ����ĺ���
 *
 * @param led ��Ҫ������LED�ƣ�ͨ��λ����ָ�������LED�����磬����LED1��ledֵΪ0x0001��
 */
void Driver_LED_On(uint16_t led) {
    // GPIOA->ODR &= ~led;
    // �������д����Ŀ�Ķ���ʹָ����LED�Ƶ���
    // ͨ�������Ӧλ������LED��Ϊ�͵�ƽ���������������ڼĴ���������ƣ�ʵ�ʲ������в�ͬ
    GPIOA->BRR |= led;
}


/**
 * @brief      �ر�ָ����LED��
 *
 * @param led  Ҫ�رյ�LED�ı�ʶ����LED�ı�ʶ����Ӳ����ص�GPIO�������Ӧ��
 *
 * @note       ������ͨ���޸�GPIOA��BSRR�Ĵ������ر�LED��ʹ��BSRR�Ĵ���������ODR�Ĵ�����ԭ���ǣ�
 *             BSRR�Ĵ����ṩ�˶�������λ�͸�λ���룬���Ը���ȫ�طֱ�������״̬�����������޸��������ŵ�״̬��
 *             ����ע�͵���������һ������LED�ķ����������ǵ��������ͼ�ǹر�LED��Ӧʹ��BSRR���°벿��ʵ�ָ�λ������0��������
 */
void Driver_LED_Off(uint16_t led) {
    // GPIOA->ODR |= led; 
    GPIOA->BSRR |= led; // ʹ��BSRR�Ĵ������ϰ벿����λ������1����ʵ��Ч��������LED����Ϊ�ߵ�ƽ���ر�LED
}

/**
 * ��תLED��״̬��
 * ���LED��ǰϨ�������LED�����LED��ǰ��������Ϩ��LED��
 *
 * @param led Ҫ�л���LED��Ӧ��GPIO��ƽ���롣
 */
void Driver_LED_Toggle(uint16_t led) {
    // ���LED��ǰ״̬�����״̬Ϊ0�����ƣ��������LED������Ϩ��LED��
    if ((GPIOA->IDR & led) == 0)  // Ҳ����дGPIOA->IDR
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
