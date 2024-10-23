#ifndef __APP_MODE_H__
#define __APP_MODE_H__

#include "Com_Util.h"

typedef enum
{
    STOP,
    REMOTE,
    PATROL,
    AVOIDANCE
} Enum_Mode;

/**
 * @brief 模式选择初始化
 */
void App_Mode_Init();

/**
 * @brief 返回按键按下后所选择的模式
 * @return 模式
 */
Enum_Mode App_Mode_GetMode();

#endif /* __APP_MODE_H__ */