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
    ESP32_SendCmd("AT+CWMODE=1\r\n");
    ESP32_SendCmd("AT+CWJAP=\"LAPTOP-V9C029E4\",\"83B9i4/9\"\r\n");
    ESP32_SendCmd("AT+CIPMUX=1\r\n");
    ESP32_SendCmd("AT+CIPSERVERMAXCONN=1\r\n");
    ESP32_SendCmd("AT+CIPSERVER=1,8080\r\n");
    ESP32_SendCmd("AT+CIPSTA?\r\n");
    // ESP32_SendCmd("AT+CIPMODE=1\r\n");
    // ESP32_SendCmd("AT+CIPSEND\r\n");
    ESP32_SendCmd("AT+SYSMSG=4\r\n");
    ESP32_SendCmd("AT+CIPSTATE?\r\n"); //查询 TCP/UDP/SSL 连接信息  当没有连接时，AT 返回：OK
}



void WiFi_SendData(uint8_t data[], uint8_t datasize) {
    HAL_UART_Transmit(&huart2, data, datasize, 1000);
}


