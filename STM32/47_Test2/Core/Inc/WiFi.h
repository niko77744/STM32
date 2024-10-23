#ifndef __WIFI_H__
#define __WIFI_H__

#include "usart.h"
#include <string.h>

typedef enum
{
    WiFi_SPP,     // 连接状态   =>  指令进入透传模式
    WiFi_DIS,     // 关闭连接   =>  关闭SPP透传模式  =>  正常发送接收AT指令
    WiFi_DATA,    // 稳定连接可以传输数据的状态   =>  接收和发送的所有数据都当做纯净的数据收发
} ESP32State;

void ESP32_Init(void);
void WiFi_TCP_Serve_Init(void);
void ESP32_HandleResponse(void);
void WiFi_SendData(uint8_t data[], uint8_t datasize);
void WiFi_ReceiveData(uint8_t data[], uint16_t* rxDataSize);
ESP32State WiFi_Handle_Change(void);
#endif /* __WIFI_H__ */
