#ifndef __INT_MOTOR_H__
#define __INT_MOTOR_H__

#include "Com_Util.h"
#include "Dri_GPIO.h"

void Int_Motor_Init();
void Int_Motor_SetLeftSpeed(char speed);
void Int_Motor_SetRightSpeed(char speed);
#endif /* __INT_MOTOR_H__ */