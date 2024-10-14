#ifndef __ESP32_H__
#define __ESP32_H__

#include <string.h>
#include "main.h"
#include "usart.h"
void ESP32_Init(void);
void ESP32_SendCmd(uint8_t* ATCmd);
void ESP32_HandleResponse(void);
void ESP32_WiFi_Init(void);
void ESP32_TCPServer_Init(void);
void Inf_ESP32_TCP_ReceiveData(uint8_t rxBuff[], uint8_t* id, uint16_t* recvDataLength, uint8_t* ip, uint16_t* port);
void Inf_ESP32_TCP_SendData(uint8_t id, uint8_t data[], uint8_t datasize);
#endif /* __ESP32_H__ */


/*
AT              测试 AT 启动
AT + RST = 0    重启模块
AT + GMR      查看版本信息
AT + CWMODE = 1 设置 Wi - Fi 模式  1:Station 模式  2 : SoftAP 模式  3 : SoftAP + Station 模式
AT + CWSTATE ? 查询 Wi - Fi 状态和 Wi - Fi 信息  0未连接 1已连接未获取IPv4  2已连接获取IPv4  3正在连接  4断开
AT + CWJAP = "username", "password"  连接 AP
AT + CIPMUX = 1 多连接模式
AT + CIPSERVER = 1, 8080   建立TCP服务端  1 : 建立服务器  如果 <mode> 是 1，<param2> 代表端口号。默认值：333
AT + CIPDINFO = 1   设置 + IPD 消息详情
AT + CIPSEND = id, datasize   在普通传输模式 或 Wi - Fi 透传模式 下发送数据
*/
