#ifndef __MATRIXLED_H__
#define __MATRIXLED_H__
#include "Com_Util.h"
#include "Dri_Timer0.h"




void Int_MatrixLED_Init(void);

void Int_MatrixLED_SetPixels(u8 pixels[8]);

void Int_MatrixLED_ShiftPixels(u8);

void Int_MatrixLED_Refresh(void);

#endif /* __MATRIXLED_H__ */