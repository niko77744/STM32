#ifndef __APP_WATER_LEVEL_H__
#define __APP_WATER_LEVEL_H__

#include "Inf_TM7711.h"
#include "App_display.h"
#include "Inf_W25Q32.h"
#include "Driver_GPIO.h"

/* 启动水位测量系统  并完成校验 */
void App_Water_Level_Start(void);

/* 校验水位测量系统 */
void App_Water_Level_calibrate(void);

/* 直接读取水位测量系统的结果 */
double App_Read_Water_Level(void);

#endif /* __APP_WATER_LEVEL_H__ */
