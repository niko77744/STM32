#ifndef __DRI_TIMER0_H__
#define __DRI_TIMER0_H__
#include "Com_Util.h"
#include "STDIO.H"

#define Max_Timer0CallbackFun_Count 4
typedef void(*Timer0_Callback)(void);

static Timer0_Callback s_Dri_Timer0CallbackFunArr[Max_Timer0CallbackFun_Count];

// ��ʱ��Timer0�ĳ�ʼ��
void Dri_Timer0_Init();

// ע�ᶨʱ��0�� �ص����� ����1���ص�����
bit Dri_Timer0_setInterval(Timer0_Callback);

//  ע����ʱ��0�� �ص�����
bit Dri_Timer0_clearInterval(Timer0_Callback);

#endif /* __DRI_TIMER0_H__ */