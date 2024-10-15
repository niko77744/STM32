#include "LoRa.h"

void LoRa_Init(void) {
    Ebyte_RF.Init();
}
void LoRa_Start(void) {
    Ebyte_RF.StartPollTask();
}
void LoRa_Send(uint8e_t* buffer, uint8e_t size) {
    /* ����ʱʱ�䶨��Ϊ0  ��ʹ�ó�ʱ��� */
    uint32e_t timeout = 0;
    Ebyte_RF.Send(buffer, size, timeout);
}
