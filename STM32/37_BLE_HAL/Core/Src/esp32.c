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
    // 直接使用USART2发送消息就是发送AT命令
    HAL_UART_Transmit(&huart2, ATCmd, strlen((char*)ATCmd), HAL_MAX_DELAY);

    // 由于不能一次执行多个指令  => 挂起等待执行响应
    ESP32_HandleResponse();
}


/**
 * @brief 接收指令返回消息并通过USART1打印和等待上一条指令发送完成(接收到OK或ERROR)
 *
 */
void ESP32_HandleResponse(void) {
    // 发送上一条命令后等待返回OK或ERROR或连续x条数据未读取到Ok  才能发送下一条指令
    uint8_t count = 2;
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
    printf("ESP32: %s\n", ResponseBuffer);
    printf("end-------------\n");
}


void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef* huart, uint16_t Size) {
    if (huart->Instance == USART2)
    {
        // 最简单的方式  => 直接打印接收到的数据
        // 原则性问题:不能在中断处理中使用运行时间过长的函数
        // printf("接收到ESP32的消息:%s\n", rBuff);
        OnceRerceiveLen = Size;
        HAL_UARTEx_ReceiveToIdle_IT(&huart2, RerceiveBuffer, OnceMax_Len);
    }
}


void ESP32_BLE_Init(void) {
    ESP32_Init();
    // 设置 Bluetooth LE 初始化角色  1: client 角色  2: server 角色
    ESP32_SendCmd("AT+BLEINIT=2\r\n");
    // GATTS 创建Bluetooth LE服务
    ESP32_SendCmd("AT+BLEGATTSSRVCRE\r\n");
    // 服务端开启服务
    ESP32_SendCmd("AT+BLEGATTSSRVSTART\r\n");
    // 服务端获取其 MAC 地址
    ESP32_SendCmd("AT+BLEADDR?\r\n");
    /*
? ? ? ? 设置蓝牙广播参数
? ? ? ? ? ? AT+BLEADVPARAM=<adv_int_min>,<adv_int_max>,<adv_type>,<own_addr_type>,<channel_map>

? ? ? ? ? ? ? ?a： adv_int_min adv_int_max 广播的最小间隔和最大间隔。 等于该值乘上0.625ms
? ? ? ? ? ? ? ?b： adv_type ? ? ? ? ? ? ? ?广播类型 ? 0：通用广播
? ? ? ? ? ? ? ?c： own_addr_type ? ? ? ? ? Bluetooth LE 地址类型 ?0：公共地址 1：随机地址
? ? ? ? ? ? ? ?d： channel_map ? ? ? ? ? ? 广播信道 ? 1: ADV_CHNL_37 2: ADV_CHNL_38
? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ?4: ADV_CHNL_39 7: ADV_CHNL_ALL

? ? */
    ESP32_SendCmd("AT+BLEADVPARAM=50,50,0,0,7,0,,\r\n");
    /*
    设置广播数据并开始广播
    自动设置广播数据 设备名称 UUID 制造商数据 广播数据需包含 TX 功率
? ?     AT+BLEADVDATAEX=<dev_name>,<uuid>,<manufacturer_data>,<include_power>
    */
    ESP32_SendCmd("AT+BLEADVDATAEX=\"ESP-AT-Test\",\"A002\",\"0102030405\",1\r\n");
    // 开始广播
    ESP32_SendCmd("AT+BLEADVSTART\r\n");
    /*
        服务端配置 Bluetooth LE SPP 配置透传
? ? ? ? 配置 Bluetooth LE SPP(Serial Port Profile)
? ? ? ? ? ?选择支持 notify 或者 indicate 的 characteristic 作为写通道发送数据，
? ? ? ? ? ?选择支持写操作的 characteristic 作为读通道接收数据。
? ? */
    ESP32_SendCmd("AT+BLESPPCFG=1,1,7,1,5\r\n");

    /*  需要连接上蓝牙后才使能 Bluetooth LE SPP */

    // 透传模式下，Wi-Fi、socket、Bluetooth LE 或 Bluetooth 状态改变时会打印提示信息  在 SPP 传输中，若未设置 AT+SYSMSG Bit2 为 1，则 AT 不会提示任何连接状态变更的信息。
    ESP32_SendCmd("AT+SYSMSG=4\r\n");
}

// 发送304 接收306
/*
+BLECONN:0,"50:ab:ba:51:a1:85"
+BLEDISCONN:0,"50:ab:ba:51:a1:85"
*/
ESP32State BLE_Handle_Change(void) {
    // 根据ESP32返回的消息来判断处于什么状态
    /* 1. +BLECONN  处于连接状态     只有在 连接 状态才可以发送透传指令进入透传模式 发送完成进入传输数据DATA状态*/
    /* 2. +BLEDISCONN  处于断开状态  只有在 断开 状态才可以发送+++退出透传模式 等待至少1s后 才可以发送AT指令*/
    if (strstr((char*)RerceiveBuffer, "+BLECONN") != NULL)
    {
        // 先清空接收数据的buffer 避免以前的数据影响到本次的数据
        memset(RerceiveBuffer, 0, sizeof(RerceiveBuffer));
        OnceRerceiveLen = 0;
        // 进入透传模式
        printf("连接BLE成功 准备进入透传模式\n");
        ESP32_SendCmd("AT+BLESPP\r\n");

        /* 启动透传后，有一个额外的字节数据，消耗掉 */
        uint8_t tmp;
        HAL_UART_Receive(&huart2, &tmp, 1, 10);
        return BLE_SPP;
    }

    if (strstr((char*)RerceiveBuffer, "+BLEDISCONN") != NULL)
    {
        // 先清空接收数据的buffer 避免以前的数据影响到本次的数据
        memset(RerceiveBuffer, 0, sizeof(RerceiveBuffer));
        OnceRerceiveLen = 0;
        // 断开连接
        printf("BLE断开连接 关闭透传  重新广播\n");
        // ESP32_SendCmd("+++");
        // 当系统收到只含有 +++ 的包时，设备返回到普通命令模式，请至少等待一秒再发送下一个 AT 命令。
        HAL_UART_Transmit(&huart2, "+++", 3, HAL_MAX_DELAY);
        HAL_Delay(2000);
        return BLE_DIS;
    }
    if (strstr((char*)RerceiveBuffer, "+STA_CONNECTED") != NULL ||
        strstr((char*)RerceiveBuffer, "+DIST_STA_IP") != NULL ||
        strstr((char*)RerceiveBuffer, "WIFI") != NULL ||
        strstr((char*)RerceiveBuffer, "+STA_DISCONNECTED") != NULL) {
        // 先清空接收数据的buffer 避免以前的数据影响到本次的数据
        memset(RerceiveBuffer, 0, sizeof(RerceiveBuffer));
        OnceRerceiveLen = 0;
        printf("wifi 连接信息发生变化....\r\n");
        return WIFI_CHANGE;
    }

    return BLE_DATA;
}
void BLE_ReadData(uint8_t data[], uint16_t* rxDataSize) {
    if (OnceRerceiveLen == 0 || (BLE_Handle_Change() != BLE_DATA)) return;
    memset(data, 0, sizeof(data));

    // 将RerceiveBuffer中接收的数据  赋值  到data
    memcpy(data, RerceiveBuffer, OnceRerceiveLen);
    *rxDataSize = OnceRerceiveLen;
    OnceRerceiveLen = 0;
}
void BLE_SendData(uint8_t data[], uint16_t size) {
    // 处于透传模式  =>  直接使用USART2发送数据即是传输给BLE
    HAL_UART_Transmit(&huart2, data, size, HAL_MAX_DELAY);
}
