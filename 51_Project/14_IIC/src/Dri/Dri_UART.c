#include "Dri_UART.h"

// 定义变量 标记是否正在发送数据  1表示正在发送
static bit Send_data_state = 0;
// 定义变量 标记是否正在接收数据  1表示接收完成，正在处理
static bit Receiving_data_state = 0;
// 记录接收字符的长度
static u8 Receiving_data_len = 0;
// 记录接收字符的长度
// 定义数组保存接收到一帧数据
static char s_buffers[15];
static char s_buffer;


/**
 * @brief UART 初始化
 *
 */
void Dri_UART_Init() {
    // 总开关
    EA = 1;

    //设置Timer1和波特率
    PCON &= 0x7F;
    TMOD &= 0x0F; // 0b 0000 1111
    TMOD |= 0x20;      // 0b 0010 0000
    TR1 = 1;
    TH1 = 253;
    TL1 = 253;

    // 设置串口工作模式
    SM0 = 0;
    SM1 = 1;
    SM2 = 0;  // 不检测停止位

    // 开关类
    REN = 1;  //数据接收使能
    ES = 1;   //串口开关
    // 将串口中断标志位置0
    TI = 0;
    RI = 0;
}



/**
 * @brief 获取接收到的字符
 * @param char * 将接收到字符保存到该地址处
 * @return bit 1接收到数据 0未接收到数据
 */
bit Dri_UART_ReceiveChar(char* receive_char) {
    if (s_buffer != '\0')
    {
        // s_buffer = SBUF;  在中断函数已经写过了
        *receive_char = s_buffer;  //将s_buffer,也就是SBUF的值给receive_char指针
        s_buffer = 0; // 将s_buffer置为0
        return 1;
    }
    return 0;
}


/**
  * @brief 获取接收到的字符串（多字节指令）
  *
  * @param char * 将接收到字符串保存到该地址处
  * @return bit 1接收到数据 0未接收到数据
  */
bit Dri_UART_ReceiveStr(char* bytes) {
    if (Receiving_data_state)
    {
        u8 i;
        for (i = 0; i < Receiving_data_len; i++)
        {
            bytes[i] = s_buffers[i];
        }
        bytes[i] = '\0';
        Receiving_data_len = 0;
        Receiving_data_state = 0;
        return 1;
    }
    return 0;
}


/**
 * @brief 发送单字节数据
 * @param char ch
 */
static void Dri_UART_TransmitChar(char ch)
{
    //一直等到允许发送数据（前面的数据发送完成）
    // 发送完这一个字节，串口中断将 Send_data_state 置为 0，就可以发送下一个字节
    while (Send_data_state);
    SBUF = ch;  //发送数据
    // 标记正在发送数据
    Send_data_state = 1;
}


/**
 * @brief 发送多字节数据
 * @param char *str
 */
void Dri_UART_TransmitStr(char* send_str) {
    while (*send_str != '\0') {
        Dri_UART_TransmitChar(*(send_str++));  // 利用指针后移遍历字符串数组
    };
}


/**
  * @brief 定义串口中断服务程序
  *
  */
void Dri_UART_Handler() interrupt 4 {

    // 如果接收数据触发的中断
    if (RI == 1)
    {
        if (SBUF == '\n')
        {
            Receiving_data_state = 1;
        }
        else {
            s_buffers[Receiving_data_len++] = SBUF;
        }
        RI = 0; // 复位中断标记位
    }
    // 如果发送完数据
    else if (TI == 1)
    {
        Send_data_state = 0;
        TI = 0; // 复位中断标记位
    }
}