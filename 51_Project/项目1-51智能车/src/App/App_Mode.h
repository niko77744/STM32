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
 * @brief ģʽѡ���ʼ��
 */
void App_Mode_Init();

/**
 * @brief ���ذ������º���ѡ���ģʽ
 * @return ģʽ
 */
Enum_Mode App_Mode_GetMode();

#endif /* __APP_MODE_H__ */