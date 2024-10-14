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
AT              ���� AT ����
AT + RST = 0    ����ģ��
AT + GMR      �鿴�汾��Ϣ
AT + CWMODE = 1 ���� Wi - Fi ģʽ  1:Station ģʽ  2 : SoftAP ģʽ  3 : SoftAP + Station ģʽ
AT + CWSTATE ? ��ѯ Wi - Fi ״̬�� Wi - Fi ��Ϣ  0δ���� 1������δ��ȡIPv4  2�����ӻ�ȡIPv4  3��������  4�Ͽ�
AT + CWJAP = "username", "password"  ���� AP
AT + CIPMUX = 1 ������ģʽ
AT + CIPSERVER = 1, 8080   ����TCP�����  1 : ����������  ��� <mode> �� 1��<param2> ����˿ںš�Ĭ��ֵ��333
AT + CIPDINFO = 1   ���� + IPD ��Ϣ����
AT + CIPSEND = id, datasize   ����ͨ����ģʽ �� Wi - Fi ͸��ģʽ �·�������
*/
