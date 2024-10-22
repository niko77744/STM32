#include "esp32.h"
/*
AT              测试 AT 启动
AT + RST = 0    重启模块
AT + GMR      查看版本信息
AT + CWMODE = 1 设置 Wi - Fi 模式  1:Station 模式  2 : SoftAP 模式  3 : SoftAP + Station 模式
AT + CWSTATE ? 查询 Wi - Fi 状态和 Wi - Fi 信息  0未连接 1已连接未获取IPv4  2已连接获取IPv4  3正在连接  4断开
AT + CWJAP = "username", "password"  连接 AP
AT + CIPMUX = 1 多连接模式
AT + CIPSERVER = 1, 8080   建立TCP服务端  1 : 建立服务器  如果 <mode> 是 1，<param2> 代表端口号。默认值：333
AT + CIPDINFO = 1   设置 + IPD 消息详情
AT + CIPSEND = id, datasize   在普通传输模式 或 Wi - Fi 透传模式 下发送数据
*/


#define OnceMax_Len 128
uint8_t RerceiveBuffer[OnceMax_Len] = { 0 };
uint8_t OnceRerceiveLen = 0;
uint8_t ResponseBuffer[1024] = { 0 };
uint8_t ResponseLen = 0;

void ESP32_Init(void) {
    HAL_UARTEx_ReceiveToIdle_IT(&huart2, RerceiveBuffer, OnceMax_Len);
    ESP32_SendCmd("AT+RST=0\r\n");
    HAL_Delay(3000);
}


void ESP32_SendCmd(uint8_t* ATCmd) {
    HAL_UART_Transmit(&huart2, ATCmd, strlen((char*)ATCmd), HAL_MAX_DELAY);
    ESP32_HandleResponse();
}
void ESP32_HandleResponse(void) {
    // 发送上一条命令后等待返回OK或ERROR或连续x条数据未读取到Ok  才能发送下一条指令
    uint8_t count = 5;
    memset(ResponseBuffer, 0, 1024);
    ResponseLen = 0;
    do
    {
        // printf("rDataSize = %d", rDataSize);  //需要注释
        // 将单次接收到的数据存放到responseBuff中
        while (OnceRerceiveLen == 0);
        memcpy(&ResponseBuffer[ResponseLen], RerceiveBuffer, OnceRerceiveLen);
        ResponseLen += OnceRerceiveLen;
        OnceRerceiveLen = 0;
        memset(RerceiveBuffer, 0, OnceMax_Len);
        // 循环等待接收多次5消息 = > 一直到接收完毕 或者 收到OK或者ERROR
/* 2. 直到等到有数据过来  =>  存放到大的缓存中*/
    } while ((strstr((char*)ResponseBuffer, "OK") == NULL) && (strstr((char*)ResponseBuffer, "ERROR") == NULL) && count--);

    printf("start-------------\n");
    printf("ResponseBuffer = %s\n", ResponseBuffer);
    printf("end-------------\n");
}


void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef* huart, uint16_t Size) {
    if (huart->Instance == USART2)
    {
        OnceRerceiveLen = Size;
        HAL_UARTEx_ReceiveToIdle_IT(&huart2, RerceiveBuffer, OnceMax_Len);
    }
}


void ESP32_WiFi_Init(void) {
    ESP32_Init();
    // 热点 LAPTOP-V9C029E4    83B9i4/9
    // ESP32 IP：192.168.137.104  MAC：f0:f5:bd:c9:6e:1c
    ESP32_SendCmd("AT+CWMODE=1\r\n");
    ESP32_SendCmd("AT+CWJAP=\"LAPTOP-V9C029E4\",\"83B9i4/9\"\r\n");
}


/*
作为服务器 IP：192.168.137.104  port：8080
本机ip  192.168.137.1
*/
void ESP32_TCPServer_Init(void) {
    ESP32_SendCmd("AT+CIPMUX=1\r\n");
    ESP32_SendCmd("AT+CIPSERVER=1,8080\r\n");
    ESP32_SendCmd("AT+CIPDINFO=1\r\n");
    ESP32_SendCmd("AT+CIPSTA?\r\n");
}


/**
 * +IPD,0,2,"192.168.137.1",1179:OK
 * /r/n+IPD固定格式  0 => ID  2 => recvDataLength  IP地址  端口号 : OK =>data
 */
void Inf_ESP32_TCP_ReceiveData(uint8_t rxBuff[], uint8_t* id, uint16_t* recvDataLength, uint8_t* ip, uint16_t* port) {
    if (OnceRerceiveLen == 0) return;
    memset(rxBuff, 0, sizeof(rxBuff));
    // 2. 拆分匹配数据
    // %*忽略/r/n  +IPD,  %[^\"] 匹配字符串直到遇见"
    sscanf((char*)RerceiveBuffer, "%*[\r\n]+IPD,%d,%d,\"%[^\"]\",%d",
        (int*)id,
        (int*)recvDataLength,
        ip,
        (int*)port);
    // 切分字符串
    strtok((char*)RerceiveBuffer, ":"); // 获取到切分之前的字符串
    memcpy(rxBuff, strtok(NULL, ":"), *recvDataLength);

    // 3. 接收数据清空
    memset(RerceiveBuffer, 0, 128);
    OnceRerceiveLen = 0;
}
void Inf_ESP32_TCP_SendData(uint8_t id, uint8_t data[], uint8_t datasize) {
    uint8_t ATcmd[100] = { 0 };
    // 拼接字符串到ATcmd
    sprintf((char*)ATcmd, "AT+CIPSEND=%d,%d\r\n", id, datasize);
    ESP32_SendCmd(ATcmd);
    // 2. 发送数据 => 达到dataSize的长度固定开始发送
    HAL_UART_Transmit(&huart2, data, datasize, 1000);
}
