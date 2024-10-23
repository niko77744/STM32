#ifndef __INT_RANGE_H__
#define __INT_RANGE_H__

#include "Dri_Timer2.h"
#include "Com_Util.h"
#include "Dri_GPIO.h"

void Int_Range_Timer2Callback();
void Int_Range_Init();
u16 Int_Range_GetRange();

#endif /* __INT_RANGE_H__ */