#ifndef __WIFI_H__
#define __WIFI_H__

#include "usart.h"
#include <string.h>

typedef enum
{
    WiFi_SPP,     // ����״̬   =>  ָ�����͸��ģʽ
    WiFi_DIS,     // �ر�����   =>  �ر�SPP͸��ģʽ  =>  �������ͽ���ATָ��
    WiFi_DATA,    // �ȶ����ӿ��Դ������ݵ�״̬   =>  ���պͷ��͵��������ݶ����������������շ�
} ESP32State;

void ESP32_Init(void);
void WiFi_TCP_Serve_Init(void);
void ESP32_HandleResponse(void);
void WiFi_SendData(uint8_t data[], uint8_t datasize);
void WiFi_ReceiveData(uint8_t data[], uint16_t* rxDataSize);
ESP32State WiFi_Handle_Change(void);
#endif /* __WIFI_H__ */
