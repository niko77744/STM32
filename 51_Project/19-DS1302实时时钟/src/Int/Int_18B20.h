#ifndef __INT_18B20_H__
#define __INT_18B20_H__

#include "Com_Util.h"
#include "Dri_1Wire.h"

/**
 * @brief ��ȡ��18B20��õ��¶�
 *
 * @return char ��ʾ���¶�
 */
char Int_18B20_GetTemperature();

/**
 * @brief ��ȡ��18B20��õ��¶�
 *
 * @return float ��ʾ���¶�
 */
float Int_18B20_GetTemperatureFloat();


#endif /* __INT_18B20_H__ */