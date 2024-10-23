#ifndef __FLOW_LED_H__
#define __FLOW_LED_H__
#include "Com_Util.h"

static u8 led_code = 0X01;
static bit led_flag;  //控制方向
static u8 led_init = 0xFF;  //0b 1111 1111 默认code码

void Int_FlowLED();

#endif /* __FLOW_LED_H__ */
