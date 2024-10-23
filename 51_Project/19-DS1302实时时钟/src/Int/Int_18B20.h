#ifndef __INT_18B20_H__
#define __INT_18B20_H__

#include "Com_Util.h"
#include "Dri_1Wire.h"

/**
 * @brief 获取到18B20测得的温度
 *
 * @return char 表示的温度
 */
char Int_18B20_GetTemperature();

/**
 * @brief 获取到18B20测得的温度
 *
 * @return float 表示的温度
 */
float Int_18B20_GetTemperatureFloat();


#endif /* __INT_18B20_H__ */