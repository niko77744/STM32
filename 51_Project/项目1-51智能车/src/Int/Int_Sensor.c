/*
    巡线模块：
        原理分析：比较器和光敏电阻
            比较器原理：比较两路电平，根据结果输出VCC或GND的电平。
                光敏接正，滑阻器接负
                    当有光反射，光敏电阻小，电压大，比较器输出光明电阻方的 GND，灯亮，单片机接收到0
                    当无光反射，光敏电阻大，电压小，比较器输出滑动变阻器方的VCC，灯不亮，单片机接收到1

        思路分析：加权平均PID
            正数表示左偏(黑线在右)  负数表示右偏(黑线在在)   左边的灯是负数，右边是正数，越靠边权重越大

        变量：记录上一次的误差（如果一个都没有扫到）

        几种情况：
            一个都没有扫到：返回上次的误差
            有扫描到：将扫描到的权重和/扫描到的个数(加权平均)
*/

#include "Int_Sensor.h"
#include "Dri_GPIO.h"
#include "Int_OLED.h"


static u8 s_last_result;

/**
 * @brief 获取误差
 * @return  char 0表示无误差  正数表示左偏(黑线在右)  负数表示右偏(黑线在在)
*/
char Int_Sensor_GetError() {
    char Weight_sum = 0;
    u8 count = 0;
    if (TRC_LL || TRC_ML || TRC_MM || TRC_MR || TRC_RR) {
        if (TRC_LL)
        {
            Weight_sum += -4;
            count++;
        }

        if (TRC_ML)
        {
            Weight_sum += -2;
            count++;
        }

        if (TRC_MM)
        {
            Weight_sum += 0;
            count++;
        }

        if (TRC_MR)
        {
            Weight_sum += 2;
            count++;
        }

        if (TRC_RR)
        {
            Weight_sum += 4;
            count++;
        }
        s_last_result = Weight_sum / count;
    }
    return s_last_result;
}

