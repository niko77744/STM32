#ifndef __APP_WATER_LEVEL_H__
#define __APP_WATER_LEVEL_H__

#include "Inf_TM7711.h"
#include "App_display.h"
#include "Inf_W25Q32.h"
#include "Driver_GPIO.h"

/* ����ˮλ����ϵͳ  �����У�� */
void App_Water_Level_Start(void);

/* У��ˮλ����ϵͳ */
void App_Water_Level_calibrate(void);

/* ֱ�Ӷ�ȡˮλ����ϵͳ�Ľ�� */
double App_Read_Water_Level(void);

#endif /* __APP_WATER_LEVEL_H__ */
