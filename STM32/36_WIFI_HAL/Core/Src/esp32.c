#include "esp32.h"
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
    // ������һ�������ȴ�����OK��ERROR������x������δ��ȡ��Ok  ���ܷ�����һ��ָ��
    uint8_t count = 5;
    memset(ResponseBuffer, 0, 1024);
    ResponseLen = 0;
    do
    {
        // printf("rDataSize = %d", rDataSize);  //��Ҫע��
        // �����ν��յ������ݴ�ŵ�responseBuff��
        while (OnceRerceiveLen == 0);
        memcpy(&ResponseBuffer[ResponseLen], RerceiveBuffer, OnceRerceiveLen);
        ResponseLen += OnceRerceiveLen;
        OnceRerceiveLen = 0;
        memset(RerceiveBuffer, 0, OnceMax_Len);
        // ѭ���ȴ����ն��5��Ϣ = > һֱ��������� ���� �յ�OK����ERROR
/* 2. ֱ���ȵ������ݹ���  =>  ��ŵ���Ļ�����*/
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
    // �ȵ� LAPTOP-V9C029E4    83B9i4/9
    // ESP32 IP��192.168.137.104  MAC��f0:f5:bd:c9:6e:1c
    ESP32_SendCmd("AT+CWMODE=1\r\n");
    ESP32_SendCmd("AT+CWJAP=\"LAPTOP-V9C029E4\",\"83B9i4/9\"\r\n");
}


/*
��Ϊ������ IP��192.168.137.104  port��8080
����ip  192.168.137.1
*/
void ESP32_TCPServer_Init(void) {
    ESP32_SendCmd("AT+CIPMUX=1\r\n");
    ESP32_SendCmd("AT+CIPSERVER=1,8080\r\n");
    ESP32_SendCmd("AT+CIPDINFO=1\r\n");
    ESP32_SendCmd("AT+CIPSTA?\r\n");
}


/**
 * +IPD,0,2,"192.168.137.1",1179:OK
 * /r/n+IPD�̶���ʽ  0 => ID  2 => recvDataLength  IP��ַ  �˿ں� : OK =>data
 */
void Inf_ESP32_TCP_ReceiveData(uint8_t rxBuff[], uint8_t* id, uint16_t* recvDataLength, uint8_t* ip, uint16_t* port) {
    if (OnceRerceiveLen == 0) return;
    memset(rxBuff, 0, sizeof(rxBuff));
    // 2. ���ƥ������
    // %*����/r/n  +IPD,  %[^\"] ƥ���ַ���ֱ������"
    sscanf((char*)RerceiveBuffer, "%*[\r\n]+IPD,%d,%d,\"%[^\"]\",%d",
        (int*)id,
        (int*)recvDataLength,
        ip,
        (int*)port);
    // �з��ַ���
    strtok((char*)RerceiveBuffer, ":"); // ��ȡ���з�֮ǰ���ַ���
    memcpy(rxBuff, strtok(NULL, ":"), *recvDataLength);

    // 3. �����������
    memset(RerceiveBuffer, 0, 128);
    OnceRerceiveLen = 0;
}
void Inf_ESP32_TCP_SendData(uint8_t id, uint8_t data[], uint8_t datasize) {
    uint8_t ATcmd[100] = { 0 };
    // ƴ���ַ�����ATcmd
    sprintf((char*)ATcmd, "AT+CIPSEND=%d,%d\r\n", id, datasize);
    ESP32_SendCmd(ATcmd);
    // 2. �������� => �ﵽdataSize�ĳ��ȹ̶���ʼ����
    HAL_UART_Transmit(&huart2, data, datasize, 1000);
}
