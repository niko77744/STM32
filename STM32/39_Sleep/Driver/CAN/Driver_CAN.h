#ifndef __DRIVER_CAN_H__
#define __DRIVER_CAN_H__

#include "stm32f10x.h"
#include "GPIO.h"
#include <string.h>

typedef struct
{
    uint16_t stdID : 11;
    uint8_t data[8];
    uint8_t length : 3;
}CAN_RxData;

#define CAN_RX_FIFO0                (0x00000000U)  /*!< CAN receive FIFO 0 */
#define CAN_RX_FIFO1                (0x00000001U)  /*!< CAN receive FIFO 1 */

void HAL_CAN_MspInit(CAN_TypeDef* CANx);
uint32_t HAL_CAN_GetTxMailboxesFreeLevel(CAN_TypeDef* CANx);
void HAL_CAN_AddTxMessage(CAN_TypeDef* CANx, uint16_t stdID, uint8_t* bytes, uint8_t length);
uint32_t HAL_CAN_GetRxFifoFillLevel(CAN_TypeDef* CANx, uint32_t RxFifo);
void HAL_CAN_GetRxMessage(CAN_TypeDef* CANx, CAN_RxData CAN_Rx[], uint8_t* BytesConut);



#endif /* __DRIVER_CAN_H__ */
