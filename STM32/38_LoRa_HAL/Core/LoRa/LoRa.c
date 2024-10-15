#include "LoRa.h"

void LoRa_Init(void) {
    /* ģ��Ĭ�Ͻ������ģʽ */
    Ebyte_RF.Init();
}
void LoRa_Start(void) {
    /* ���뱻�ͻ������Ե��ã������޷����յ�����  BBYTE ����ģ���������� */
    Ebyte_RF.StartPollTask();
}
void LoRa_Send(uint8e_t* buffer, uint8e_t size) {
    /* ����ʱʱ�䶨��Ϊ0  ��ʹ�ó�ʱ��� */ 
    uint32e_t timeout = 0;
    Ebyte_RF.Send(buffer, size, timeout);
    /* ģ����뷢��״̬ ��ʼ������������ ��ɺ��ڲ��Ĵ�����λ  
    Ebyte_E220x_SetTx(timeout);  ʹ��ģ�� �������߷���   timeout ��ʱʱ��  @arg 0:�����г�ʱ�ж�
    */
    
}
