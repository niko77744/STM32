#ifndef __INT_SENSOR_H__
#define __INT_SENSOR_H__

#include "Com_Util.h"


/**
 * @brief 获取误差
 * @return  char 0表示无误差  正数表示左偏(黑线在右)  负数表示右偏(黑线在在)
*/
char Int_Sensor_GetError();
#endif /* __INT_SENSOR_H__ */