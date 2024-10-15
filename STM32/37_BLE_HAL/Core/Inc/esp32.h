#ifndef __ESP32_H__
#define __ESP32_H__

#include <string.h>
#include "main.h"
#include "usart.h"

typedef enum
{
    BLE_SPP,     // 连接状态   =>  指令进入透传模式
    BLE_DIS,     // 关闭连接   =>  关闭SPP透传模式  =>  正常发送接收AT指令
    BLE_DATA,    // 稳定连接可以传输数据的状态   =>  接收和发送的所有数据都当做纯净的数据收发
    WIFI_CHANGE, // WIFI的变更信息
} ESP32State;

void ESP32_Init(void);
void ESP32_SendCmd(uint8_t* ATCmd);
void ESP32_HandleResponse(void);
void ESP32_BLE_Init(void);


ESP32State BLE_Handle_Change(void);
void BLE_ReadData(uint8_t data[], uint16_t* rxDataSize);
void BLE_SendData(uint8_t data[], uint16_t size);

#endif /* __ESP32_H__ */


