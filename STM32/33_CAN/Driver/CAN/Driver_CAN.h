#ifndef __DRIVER_CAN_H__
#define __DRIVER_CAN_H__

#include "stm32f10x.h"
#include "GPIO.h"
#include <string.h>

typedef struct
{
    uint16_t stdID;
    uint8_t data[8];
    uint8_t length;
}CAN_RxData;

void Driver_CAN_Init(void);
void Driver_CAN_SendBytes(uint16_t stdID, uint8_t* bytes, uint8_t length);
void Driver_CAN_ReceiveBytes(CAN_RxData CAN_Rx[], uint8_t* BytesConut);



#endif /* __DRIVER_CAN_H__ */
