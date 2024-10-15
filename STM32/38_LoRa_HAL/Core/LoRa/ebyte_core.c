/**
  **********************************************************************************
  * @file      ebyte_core.c
  * @brief     EBYTE��������ϲ�API��װ�� �����ͻ�����ײ��߼�    
  * @details   ������μ� https://www.ebyte.com/       
  * @author    JiangHeng     
  * @date      2021-05-13     
  * @version   1.0.0     
  **********************************************************************************
  * @copyright BSD License 
  *            �ɶ��ڰ��ص��ӿƼ����޹�˾  
  *   ______   ____   __     __  _______   ______ 
  *  |  ____| |  _ \  \ \   / / |__   __| |  ____|
  *  | |__    | |_) |  \ \_/ /     | |    | |__   
  *  |  __|   |  _ <    \   /      | |    |  __|  
  *  | |____  | |_) |    | |       | |    | |____ 
  *  |______| |____/     |_|       |_|    |______| 
  *
  **********************************************************************************
  */


#include "ebyte_core.h"

/* ָ�� E22x �ײ��������� */
#if defined(EBYTE_E22_400M22S)||defined(EBYTE_E22_900M22S)
const Ebyte_RF_t Ebyte_RF =
{
  Ebyte_E22x_Init,
  Ebyte_E22x_SendPayload,
  Ebyte_E22x_SetSleep,
  Ebyte_E22x_SetRx,  
  Ebyte_E22x_IntOrPollTask,
  Ebyte_E22x_InterruptTrigger,
  Ebyte_E22x_GetName,
  Ebyte_E22x_GetDriverVersion
};

/* ָ�� E220x �ײ��������� */
#elif defined(EBYTE_E220_400M22S)||defined(EBYTE_E220_900M22S)
const Ebyte_RF_t Ebyte_RF =
{
  Ebyte_E220x_Init,
  Ebyte_E220x_SendPayload,
  Ebyte_E220x_SetSleep,
  Ebyte_E220x_SetRx,  
  Ebyte_E220x_IntOrPollTask,
  Ebyte_E220x_InterruptTrigger,
  Ebyte_E220x_GetName,
  Ebyte_E220x_GetDriverVersion
};

/* ָ�� E07x �ײ��������� */
#elif defined(EBYTE_E07_900M10S)
const Ebyte_RF_t Ebyte_RF =
{
  Ebyte_E07x_Init,
  Ebyte_E07x_SendPayload,
  0,
  Ebyte_E07x_SetRx,  
  Ebyte_E07x_IntOrPollTask,
  0
};

/* ָ�� E10x �ײ��������� */
#elif defined(EBYTE_E10_400M20S)||defined(EBYTE_E10_900M20S)
const Ebyte_RF_t Ebyte_RF =
{
  Ebyte_E10x_Init,
  Ebyte_E10x_SendPayload,
  0,
  Ebyte_E10x_SetRx,  
  Ebyte_E10x_IntOrPollTask,
  0
};

#elif defined(EBYTE_E49_400M20S)||defined(EBYTE_E49_900M20S)
const Ebyte_RF_t Ebyte_RF =
{
  Ebyte_E49x_Init,
  Ebyte_E49x_SendPayload,
  0,
  Ebyte_E49x_SetRx,  
  Ebyte_E49x_IntOrPollTask,
  0
};

#else
/* ebyte_conf.h ������ѡ��Ĳ�Ʒ�ͺŲ���ȷ */
#error No product selected !
#endif






