#ifndef __ESP32_H__
#define __ESP32_H__

#include <string.h>
#include "main.h"
#include "usart.h"

typedef enum
{
    BLE_SPP,     // ����״̬   =>  ָ�����͸��ģʽ
    BLE_DIS,     // �ر�����   =>  �ر�SPP͸��ģʽ  =>  �������ͽ���ATָ��
    BLE_DATA,    // �ȶ����ӿ��Դ������ݵ�״̬   =>  ���պͷ��͵��������ݶ����������������շ�
    WIFI_CHANGE, // WIFI�ı����Ϣ
} ESP32State;

void ESP32_Init(void);
void ESP32_SendCmd(uint8_t* ATCmd);
void ESP32_HandleResponse(void);
void ESP32_BLE_Init(void);


ESP32State BLE_Handle_Change(void);
void BLE_ReadData(uint8_t data[], uint16_t* rxDataSize);
void BLE_SendData(uint8_t data[], uint16_t size);

#endif /* __ESP32_H__ */


