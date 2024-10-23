#ifndef __Dri_Timer_H__
#define __Dri_Timer_H__

#include <STDIO.H>
#include "Com_Util.h"


#define MAX_CALLBACK_COUNT 4
// typedef void (*Timer0_Callback)(void);
typedef void (*Timer0_Callback)(void);


// ��ʱ��Timer0�ĳ�ʼ��
void Dri_Timer0_Init();

// ע�ᶨʱ��0�� �ص����� ����1���ص�����  ����2��Ƶ��TriggerFrequency msһ��
bit Dri_Timer0_setInterval(Timer0_Callback, u16);

//  ע����ʱ��0�� �ص�����
bit Dri_Timer0_clearInterval(Timer0_Callback);

#endif /*  __Dri_Timer_H__ */


