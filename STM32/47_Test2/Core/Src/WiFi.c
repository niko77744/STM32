#include "WiFi.h"
uint8_t buffer[128] = { 0 };
#define Max_Size 128
volatile uint8_t size = 0;
uint8_t ResponseBuffer[512] = { 0 };
uint8_t ResponseSize = 0;

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef* huart, uint16_t Size) {
    if (huart->Instance == USART2)
    {
        size = Size;
        HAL_UARTEx_ReceiveToIdle_IT(&huart2, buffer, Max_Size);
    }
}

void ESP32_HandleResponse(void) {
    uint8_t count = 4;
    memset(ResponseBuffer, 0, sizeof(ResponseBuffer));
    ResponseSize = 0;
    do
    {
        while (size == 0);
        memcpy(&ResponseBuffer[ResponseSize], buffer, size);
        ResponseSize += size;
        size = 0;
        memset(buffer, 0, sizeof(buffer));
    } while ((strstr((char*)ResponseBuffer, "OK") == NULL) && (strstr((char*)ResponseBuffer, "ERROR") == NULL) && count--);
    printf("ResponseBuffer = %s\n", ResponseBuffer);
    printf("End=====================\n");
}

void ESP32_SendCmd(uint8_t* cmd) {
    HAL_UART_Transmit(&huart2, cmd, strlen((char*)cmd), HAL_MAX_DELAY);
    ESP32_HandleResponse();
}
void ESP32_Init(void) {
    MX_USART2_UART_Init();
    HAL_UARTEx_ReceiveToIdle_IT(&huart2, buffer, Max_Size);
    ESP32_SendCmd("AT+RST=0\r\n");
    HAL_Delay(3000);
}

void WiFi_TCP_Serve_Init(void) {
    ESP32_Init();
    // ESP32_SendCmd("AT+CWMODE=1\r\n");
    // ESP32_SendCmd("AT+CWJAP=\"LAPTOP-V9C029E4\",\"83B9i4/9\"\r\n");
    // ESP32_SendCmd("AT+CIPMUX=1\r\n");
    // ESP32_SendCmd("AT+CIPSERVERMAXCONN=1\r\n");
    // ESP32_SendCmd("AT+CIPSERVER=1,8080\r\n");
    // ESP32_SendCmd("AT+CIPSTA?\r\n");
    // ESP32_SendCmd("AT+SYSMSG=4\r\n");
    // ESP32_SendCmd("AT+CIPSTATE?\r\n"); //查询 TCP/UDP/SSL 连接信息  当没有连接时，AT 返回：OK

    ESP32_SendCmd("AT+CWMODE=1\r\n");
    ESP32_SendCmd("AT+CWJAP=\"LAPTOP-V9C029E4\",\"83B9i4/9\"\r\n");
    ESP32_SendCmd("AT+CIPMUX=1\r\n");
    ESP32_SendCmd("AT+CIPSERVER=1,8080\r\n");
    ESP32_SendCmd("AT+CIPDINFO=1\r\n");
    ESP32_SendCmd("AT+CIPSTA?\r\n");
}


// CLOSED  CONNECT
ESP32State WiFi_Handle_Change(void) {
    if ((strstr((char*)buffer, "CONNECT") != NULL))
    {
        memset(buffer, 0, sizeof(buffer));
        size = 0;
        printf("连接成功,进入到数据传输模式\n");
        ESP32_SendCmd("AT+CIPMODE=1\r\n");
        ESP32_SendCmd("AT+CIPSEND\r\n");
        // return WiFi_SPP;
        return WiFi_DATA;
    }

    if ((strstr((char*)buffer, "CLOSED") != NULL))
    {
        memset(buffer, 0, sizeof(buffer));
        size = 0;
        printf("WiFi断开连接 关闭透传  等待重新连接\n");
        HAL_UART_Transmit(&huart2, "+++", 3, HAL_MAX_DELAY);
        HAL_Delay(2000);
        return WiFi_DIS;
    }
    // return WiFi_DATA;
    return WiFi_SPP;
}

void WiFi_SendData(uint8_t data[], uint8_t datasize) {
    uint8_t ATcmd[100] = { 0 };
    // 拼接字符串到ATcmd
    sprintf((char*)ATcmd, "AT+CIPSEND=0,%d\r\n", datasize);
    ESP32_SendCmd(ATcmd);
    // // 2. 发送数据 => 达到dataSize的长度固定开始发送
    HAL_UART_Transmit(&huart2, data, datasize, 1000);
}


void WiFi_ReceiveData(uint8_t data[], uint16_t* rxDataSize) {
    if (size == 0 || (WiFi_Handle_Change() != WiFi_DATA)) return;
    memset(data, 0, sizeof(data));
    // 将RerceiveBuffer中接收的数据  赋值  到data
    memcpy(data, buffer, size);
    *rxDataSize = size;
    size = 0;
}

