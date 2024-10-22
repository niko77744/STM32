#ifndef __WIFI_H__
#define __WIFI_H__

#include "usart.h"
#include <string.h>
void ESP32_Init(void);
void WiFi_TCP_Serve_Init(void);
void WiFi_SendData(uint8_t data[], uint8_t datasize);

// void Inf_ESP32_Init(void);
// void Inf_ESP32_SendCmd(uint8_t* cmd);
// void Inf_ESP32_WIFI_Init(void);
#endif /* __WIFI_H__ */
