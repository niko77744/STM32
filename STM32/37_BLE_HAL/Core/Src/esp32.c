#include "esp32.h"
/*

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
    // ֱ��ʹ��USART2������Ϣ���Ƿ���AT����
    HAL_UART_Transmit(&huart2, ATCmd, strlen((char*)ATCmd), HAL_MAX_DELAY);

    // ���ڲ���һ��ִ�ж��ָ��  => ����ȴ�ִ����Ӧ
    ESP32_HandleResponse();
}


/**
 * @brief ����ָ�����Ϣ��ͨ��USART1��ӡ�͵ȴ���һ��ָ������(���յ�OK��ERROR)
 *
 */
void ESP32_HandleResponse(void) {
    // ������һ�������ȴ�����OK��ERROR������x������δ��ȡ��Ok  ���ܷ�����һ��ָ��
    uint8_t count = 2;
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
    printf("ESP32: %s\n", ResponseBuffer);
    printf("end-------------\n");
}


void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef* huart, uint16_t Size) {
    if (huart->Instance == USART2)
    {
        // ��򵥵ķ�ʽ  => ֱ�Ӵ�ӡ���յ�������
        // ԭ��������:�������жϴ�����ʹ������ʱ������ĺ���
        // printf("���յ�ESP32����Ϣ:%s\n", rBuff);
        OnceRerceiveLen = Size;
        HAL_UARTEx_ReceiveToIdle_IT(&huart2, RerceiveBuffer, OnceMax_Len);
    }
}


void ESP32_BLE_Init(void) {
    ESP32_Init();
    // ���� Bluetooth LE ��ʼ����ɫ  1: client ��ɫ  2: server ��ɫ
    ESP32_SendCmd("AT+BLEINIT=2\r\n");
    // GATTS ����Bluetooth LE����
    ESP32_SendCmd("AT+BLEGATTSSRVCRE\r\n");
    // ����˿�������
    ESP32_SendCmd("AT+BLEGATTSSRVSTART\r\n");
    // ����˻�ȡ�� MAC ��ַ
    ESP32_SendCmd("AT+BLEADDR?\r\n");
    /*
? ? ? ? ���������㲥����
? ? ? ? ? ? AT+BLEADVPARAM=<adv_int_min>,<adv_int_max>,<adv_type>,<own_addr_type>,<channel_map>

? ? ? ? ? ? ? ?a�� adv_int_min adv_int_max �㲥����С������������ ���ڸ�ֵ����0.625ms
? ? ? ? ? ? ? ?b�� adv_type ? ? ? ? ? ? ? ?�㲥���� ? 0��ͨ�ù㲥
? ? ? ? ? ? ? ?c�� own_addr_type ? ? ? ? ? Bluetooth LE ��ַ���� ?0��������ַ 1�������ַ
? ? ? ? ? ? ? ?d�� channel_map ? ? ? ? ? ? �㲥�ŵ� ? 1: ADV_CHNL_37 2: ADV_CHNL_38
? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ?4: ADV_CHNL_39 7: ADV_CHNL_ALL

? ? */
    ESP32_SendCmd("AT+BLEADVPARAM=50,50,0,0,7,0,,\r\n");
    /*
    ���ù㲥���ݲ���ʼ�㲥
    �Զ����ù㲥���� �豸���� UUID ���������� �㲥��������� TX ����
? ?     AT+BLEADVDATAEX=<dev_name>,<uuid>,<manufacturer_data>,<include_power>
    */
    ESP32_SendCmd("AT+BLEADVDATAEX=\"ESP-AT-Test\",\"A002\",\"0102030405\",1\r\n");
    // ��ʼ�㲥
    ESP32_SendCmd("AT+BLEADVSTART\r\n");
    /*
        ��������� Bluetooth LE SPP ����͸��
? ? ? ? ���� Bluetooth LE SPP(Serial Port Profile)
? ? ? ? ? ?ѡ��֧�� notify ���� indicate �� characteristic ��Ϊдͨ���������ݣ�
? ? ? ? ? ?ѡ��֧��д������ characteristic ��Ϊ��ͨ���������ݡ�
? ? */
    ESP32_SendCmd("AT+BLESPPCFG=1,1,7,1,5\r\n");

    /*  ��Ҫ�������������ʹ�� Bluetooth LE SPP */

    // ͸��ģʽ�£�Wi-Fi��socket��Bluetooth LE �� Bluetooth ״̬�ı�ʱ���ӡ��ʾ��Ϣ  �� SPP �����У���δ���� AT+SYSMSG Bit2 Ϊ 1���� AT ������ʾ�κ�����״̬�������Ϣ��
    ESP32_SendCmd("AT+SYSMSG=4\r\n");
}

// ����304 ����306
/*
+BLECONN:0,"50:ab:ba:51:a1:85"
+BLEDISCONN:0,"50:ab:ba:51:a1:85"
*/
ESP32State BLE_Handle_Change(void) {
    // ����ESP32���ص���Ϣ���жϴ���ʲô״̬
    /* 1. +BLECONN  ��������״̬     ֻ���� ���� ״̬�ſ��Է���͸��ָ�����͸��ģʽ ������ɽ��봫������DATA״̬*/
    /* 2. +BLEDISCONN  ���ڶϿ�״̬  ֻ���� �Ͽ� ״̬�ſ��Է���+++�˳�͸��ģʽ �ȴ�����1s�� �ſ��Է���ATָ��*/
    if (strstr((char*)RerceiveBuffer, "+BLECONN") != NULL)
    {
        // ����ս������ݵ�buffer ������ǰ������Ӱ�쵽���ε�����
        memset(RerceiveBuffer, 0, sizeof(RerceiveBuffer));
        OnceRerceiveLen = 0;
        // ����͸��ģʽ
        printf("����BLE�ɹ� ׼������͸��ģʽ\n");
        ESP32_SendCmd("AT+BLESPP\r\n");

        /* ����͸������һ��������ֽ����ݣ����ĵ� */
        uint8_t tmp;
        HAL_UART_Receive(&huart2, &tmp, 1, 10);
        return BLE_SPP;
    }

    if (strstr((char*)RerceiveBuffer, "+BLEDISCONN") != NULL)
    {
        // ����ս������ݵ�buffer ������ǰ������Ӱ�쵽���ε�����
        memset(RerceiveBuffer, 0, sizeof(RerceiveBuffer));
        OnceRerceiveLen = 0;
        // �Ͽ�����
        printf("BLE�Ͽ����� �ر�͸��  ���¹㲥\n");
        // ESP32_SendCmd("+++");
        // ��ϵͳ�յ�ֻ���� +++ �İ�ʱ���豸���ص���ͨ����ģʽ�������ٵȴ�һ���ٷ�����һ�� AT ���
        HAL_UART_Transmit(&huart2, "+++", 3, HAL_MAX_DELAY);
        HAL_Delay(2000);
        return BLE_DIS;
    }
    if (strstr((char*)RerceiveBuffer, "+STA_CONNECTED") != NULL ||
        strstr((char*)RerceiveBuffer, "+DIST_STA_IP") != NULL ||
        strstr((char*)RerceiveBuffer, "WIFI") != NULL ||
        strstr((char*)RerceiveBuffer, "+STA_DISCONNECTED") != NULL) {
        // ����ս������ݵ�buffer ������ǰ������Ӱ�쵽���ε�����
        memset(RerceiveBuffer, 0, sizeof(RerceiveBuffer));
        OnceRerceiveLen = 0;
        printf("wifi ������Ϣ�����仯....\r\n");
        return WIFI_CHANGE;
    }

    return BLE_DATA;
}
void BLE_ReadData(uint8_t data[], uint16_t* rxDataSize) {
    if (OnceRerceiveLen == 0 || (BLE_Handle_Change() != BLE_DATA)) return;
    memset(data, 0, sizeof(data));

    // ��RerceiveBuffer�н��յ�����  ��ֵ  ��data
    memcpy(data, RerceiveBuffer, OnceRerceiveLen);
    *rxDataSize = OnceRerceiveLen;
    OnceRerceiveLen = 0;
}
void BLE_SendData(uint8_t data[], uint16_t size) {
    // ����͸��ģʽ  =>  ֱ��ʹ��USART2�������ݼ��Ǵ����BLE
    HAL_UART_Transmit(&huart2, data, size, HAL_MAX_DELAY);
}
