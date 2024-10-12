#ifndef __DRIVER_ETH_H__
#define __DRIVER_ETH_H__

#include "stm32f10x.h"
#include "Driver_USART.h"
#include "Driver_SPI.h"
#include "Com_Delay.h"
#include "Driver_LED.h"

#include "wizchip_conf.h"
#include "socket.h"
#include "httpServer.h"
#include "httpParser.h"

void Driver_ETH_Init(void);
void TCP_Server_Socket(uint8_t sn);
void TCP_Client_Socket(uint8_t sn);
void UDP_Socket(uint8_t sn);
void user_handle_function(uint8_t* url);
void Web_serever_Init(void);
void Web_serever_Start(void);
#endif /* __DRIVER_ETH_H__ */
