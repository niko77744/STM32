#ifndef __INT_BUZZER_H__
#define __INT_BUZZER_H__


#include "Com_Util.h"

//����Ƶ������
static Int_Buzzer_HzNumber[17]={48,43,38,36,32,30,28,25,24,21,19,18,16,14,13,10,100};

/**
 * @brief ��������Ӧ
 * 
 * @param number ����������Ƶ��
 */
void Int_Buzzer_HzBuzzer(u8 number);

#endif

