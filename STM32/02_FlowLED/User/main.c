#include "stm32f10x.h"
#include "driver_led.h"
#include "Delay.h"
#include <stdbool.h>
// | ��   &~ �ر�

int main() {
    // ����һ���޷���16λ��������leds������3��LED�ı�ʶ��
    uint16_t leds[] = { LED1,LED2,LED3 };

    // ��ʼ��LED������
    Driver_LED_Init();

    // ���´���α�ע�͵���ԭ����LED��ֱ�ӿ��ƣ������أ��ڴ˰汾��δʵ��
    // Driver_LED_OnAll(leds, 3);
    // Delay_ms(2000);
    // Driver_LED_OffAll(leds, 3);

    // ����ѭ�������Ͻ��������Ϩ��LED��ʵ����ˮ��Ч��
    while (1) {
        // Driver_LED_ToggleFlowLights(leds, 3);
        Driver_LED_LightsOnAndOff(leds, 3);
    }
}

