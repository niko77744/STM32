#include "Int_Buzzer.h"
static u16 s_count;

void Int_Buzzer_Init() {
    BUZZER_EN = 0;
    s_count = 0;
    Dri_Timer2_RegisterCallback(Int_Buzzer_Callback);
}


// 定义变量记录蜂鸣器响多少ms
/**
 * @brief 蜂鸣器发出 500Hz 的声音, 响 0.1s
 */
void Int_Buzzer_Buzz(u16 time)
{
    s_count = time;
}

void Int_Buzzer_Callback() {
    if (s_count > 0)
    {
        BUZZER_EN = ~BUZZER_EN;
        s_count--;
    }
    else {
        BUZZER_EN = 0;
    }
}

