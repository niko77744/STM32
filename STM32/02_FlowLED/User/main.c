#include "stm32f10x.h"
#include "driver_led.h"
#include "Delay.h"
#include <stdbool.h>
// | 打开   &~ 关闭

int main() {
    // 定义一个无符号16位整型数组leds，包含3个LED的标识符
    uint16_t leds[] = { LED1,LED2,LED3 };

    // 初始化LED驱动器
    Driver_LED_Init();

    // 以下代码段被注释掉，原因是LED的直接控制（开、关）在此版本中未实现
    // Driver_LED_OnAll(leds, 3);
    // Delay_ms(2000);
    // Driver_LED_OffAll(leds, 3);

    // 无限循环，不断交替点亮和熄灭LED，实现流水灯效果
    while (1) {
        // Driver_LED_ToggleFlowLights(leds, 3);
        Driver_LED_LightsOnAndOff(leds, 3);
    }
}

