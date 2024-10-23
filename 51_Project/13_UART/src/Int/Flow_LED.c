#include "Int/Flow_LED.h"

void Int_FlowLED() {
    // ��Ъcount msִ��һ��
    static u8 count;
    if (count == 0)
    {
        P0 = led_init ^ led_code;
        if (led_code == 0x80)
        {
            led_flag = 0;
        }
        else if (led_code == 0x01)
        {
            led_flag = 1;
        }
        led_flag ? (led_code <<= 1) : (led_code >>= 1);
    }
    count--;
}