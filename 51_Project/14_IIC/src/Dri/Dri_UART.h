#ifndef __DRI_UART_H__
#define __DRI_UART_H__
#include "Com_Util.h"

/**
 * @brief UART ��ʼ��
 *
 */
void Dri_UART_Init();



/**
 * @brief ��ȡ���յ����ַ�
 *
 * @param char * �����յ��ַ����浽�õ�ַ��
 * @return bit 1���յ����� 0δ���յ�����
 */
bit Dri_UART_ReceiveChar(char*);

/**
   * @brief ��ȡ���յ����ַ��������ֽ�ָ�
   *
   * @param char * �����յ��ַ������浽�õ�ַ��
   * @return bit 1���յ����� 0δ���յ�����
   */
bit Dri_UART_ReceiveStr(char* bytes);

/**
 * @brief ���Ͷ��ֽ�����
 *
 * @param char *str
 */
void Dri_UART_TransmitStr(char*);

#endif /* __DRI_UART_H__ */
