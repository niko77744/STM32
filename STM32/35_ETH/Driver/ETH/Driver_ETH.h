#ifndef __DRIVER_ETH_H__
#define __DRIVER_ETH_H__

#include "stm32f10x.h"
#include "Driver_USART.h"
#include "Driver_SPI.h"
#include "Com_Delay.h"

#include "wizchip_conf.h"
#include "socket.h"
#include "httpServer.h"
#include "httpParser.h"

void Driver_ETH_Init(void);
void Inf_TCP_Server(uint8_t Socket_sn);

#endif /* __DRIVER_ETH_H__ */
