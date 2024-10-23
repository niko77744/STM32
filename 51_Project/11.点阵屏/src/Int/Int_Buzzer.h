#ifndef __Int_Buzzer_H__
#define __Int_Buzzer_H__

#include "Com_Util.h"

/**
 * @brief 蜂鸣器发出 500Hz 的声音
 */
void Int_Buzzer_Buzz();

//可变频率
void Int_Buzzer_frequency(u8, u16);

#endif /* __Int_Buzzer_H__ */
