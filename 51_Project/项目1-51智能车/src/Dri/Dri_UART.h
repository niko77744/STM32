#ifndef __DRI_UART_H__
#define __DRI_UART_H__
#include "Com_Util.h"

/**
 * @brief UART 初始化
 *
 */
void Dri_UART_Init();



/**
 * @brief 获取接收到的字符
 *
 * @param char * 将接收到字符保存到该地址处
 * @return bit 1接收到数据 0未接收到数据
 */
bit Dri_UART_ReceiveChar(char*);

/**
   * @brief 获取接收到的字符串（多字节指令）
   *
   * @param char * 将接收到字符串保存到该地址处
   * @return bit 1接收到数据 0未接收到数据
   */
bit Dri_UART_ReceiveStr(char* bytes);

/**
 * @brief 发送多字节数据
 *
 * @param char *str
 */
void Dri_UART_TransmitStr(char*);

#endif /* __DRI_UART_H__ */
