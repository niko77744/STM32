#ifndef __INT_BUZZER_H__
#define __INT_BUZZER_H__


#include "Com_Util.h"

//定义频率数组
static Int_Buzzer_HzNumber[17]={48,43,38,36,32,30,28,25,24,21,19,18,16,14,13,10,100};

/**
 * @brief 蜂鸣器响应
 * 
 * @param number 蜂鸣器响声频率
 */
void Int_Buzzer_HzBuzzer(u8 number);

#endif

