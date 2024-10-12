#include "Driver_ETH.h"

uint8_t mac[6] = { 0x00,0x08,0xdc,0x11,0x11,0x11 };
uint8_t ip[4] = { 192, 168, 23, 104 };
uint8_t sub[4] = { 255, 255, 255, 0 };
uint8_t gw[4] = { 192, 168, 23, 1 };
uint8_t dns[4] = { 8,8,8,8 };
uint8_t TCP_Rbuffer[128] = { 0 };
#define w5500_port 8080


void Driver_ETH_Reset(void);
void Driver_ETH_SetMac(void);
void Driver_ETH_SetIP(void);

void Driver_ETH_Init(void) {
    Driver_SPIx_Init(SPI2);
    user_register_function();
    /* 重置W5500 */
    Driver_ETH_Reset();
    /* 设置MAC地址 */
    Driver_ETH_SetMac();
    /* 设置IP信息 */
    Driver_ETH_SetIP();
}

void Driver_ETH_Reset(void) {
    // W5500的初始化引脚  PG7 低电平500us
    RCC->APB2ENR |= RCC_APB2ENR_IOPGEN;
    Hal_GPIO_Mode_Selection(GPIOG, GPIO_pin_7, GPIO_Mode_Out_PP);
    HAL_GPIO_WritePin(GPIOG, GPIO_pin_7, GPIO_PIN_RESET);
    Delay_ms(1);
    HAL_GPIO_WritePin(GPIOG, GPIO_pin_7, GPIO_PIN_SET);
}
void Driver_ETH_SetMac(void) {
    setSHAR(mac);   //local MAC  It should be allocated 6 bytes  Source Hardware Address
    Delay_ms(1);
}

void Driver_ETH_SetIP(void) {
    // 1. 设置ip地址
    setSIPR(ip); //local IP It should be allocated 4 bytes
    Delay_ms(1);
    // 2. 设置子网掩码
    setSUBR(sub); //subnet mask address It should be allocated 4 bytes
    Delay_ms(1);
    // 3. 设置网关
    setGAR(gw);  //gateway IP It should be allocated 4 bytes
    Delay_ms(1);
}


/**
 * @brief 让W5500作为TCP的服务端
 * @param sn  (uint8_t)sn Socket number. It should be <b>0 ~ 7</b>.
 * @return * void
 */
void TCP_Server_Socket(uint8_t sn) {
    // 1. 获取当前socket0的状态
    uint8_t socket_state = getSn_SR(sn);
    if (socket_state == SOCK_CLOSED)
    {
        // 2. 当前为关闭状态 ->  表示服务端还没有初始化 socket没人用
        int8_t socket_return = socket(sn, Sn_MR_TCP, w5500_port, SF_TCP_NODELAY); //返回sn号
        socket_return == sn ? printf("Socket Init Success\n") : printf("Socket Init Error\n");
    }
    else if (socket_state == SOCK_INIT)
    {
        // 3. 初始化完成 -> 进入监听状态 等待客户端连接
        int8_t listen_return = listen(sn);
        listen_return == SOCK_OK ? printf("Listen Init Success\n") : printf("Listen %d Init Error\n", close(sn));
    }
    else if (socket_state == SOCK_ESTABLISHED)
    {
        // 4.说明已经连接成功 -> 可以进行收发数据了
        // 打印客户端的ip地址和端口号
        uint8_t Client_Ip[4] = { 0 };
        uint16_t Client_port = 0;
        getSn_DIPR(sn, Client_Ip);
        Client_port = getSn_DPORT(sn);
        printf("Connect Success! Client_Ip:port = %d.%d.%d.%d:%d\n", Client_Ip[0], Client_Ip[1], Client_Ip[2], Client_Ip[3], Client_port);

        // 一直轮询接受数据,知道断开连接
        while (1) {
            // 5. 完成收发数据
            // 判断当前是否收到数据
            while ((getSn_IR(sn) & Sn_IR_RECV) == 0)
            {
                // 还没有收到数据   挂起等待
                // 单独判断是否连接已经关闭
                if (getSn_SR(sn) != SOCK_ESTABLISHED)
                {
                    // 接收不到数据  连接已经关闭
                    close(sn);
                    printf("Connection has been disconnected\n");
                    return;
                }
            }
            // 有数据进来  -> 清空中断标志位
            // 如果想要清空标准位  按照产品手册写1
            setSn_IR(sn, Sn_IR_RECV);

            // 读取数据  ->  先读取接收的数据长度
            uint16_t datalen = getSn_RX_RSR(sn);

            //由服务端发送消息  然后将消息打印至串口
            recv(sn, TCP_Rbuffer, datalen);
            printf("ReceiveData => len:%d,data:%s\n", datalen, TCP_Rbuffer);
            // w5500 将接收到的数据原封不动的返回
            send(sn, TCP_Rbuffer, datalen);
        }
    }
}



void TCP_Client_Socket(uint8_t sn) {
    uint8_t socket_state = getSn_SR(sn);
    if (socket_state == SOCK_CLOSED)
    {
        int8_t socket_return = socket(sn, Sn_MR_TCP, w5500_port, SF_TCP_NODELAY);
        socket_return == sn ? printf("Socket Init Success\n") : printf("Socket Init Error\n");
    }
    else if (socket_state == SOCK_INIT)
    {
        // 3. 初始化状态 -> 选择作为客户端 -> 主动连接
        uint8_t serverIp[4] = { 192,168,23,101 };
        uint16_t serverPort = 8080;
        int8_t connect_return = connect(sn, serverIp, serverPort);
        if (connect_return == SOCK_OK)
        {
            printf("Successfully connected to %d.%d.%d.%d:%d server\n", serverIp[0], serverIp[1], serverIp[2], serverIp[3], serverPort);
        }
        else if (connect_return == SOCKERR_SOCKCLOSED)
        {
            close(sn);
            printf("SOCKCLOSED\n");
        }
        else if (connect_return == SOCKERR_TIMEOUT)
        {
            printf("TIMEOUT Please Delay\n");
            Delay_ms(100);
        }
        else {
            printf("Unknown Error\n");
        }
    }
    else if (socket_state == SOCK_ESTABLISHED)
    {
        // 4. 连接状态 -> 主动发送hello
        send(0, "hello\n", 6);

        while (1) {
            // 等待接收(回复)数据  -> 原封不动返回数据
            while ((getSn_IR(sn) & Sn_IR_RECV) == 0)
            {
                if (getSn_SR(sn) != SOCK_ESTABLISHED)
                {
                    close(sn);
                    printf("Connection has been disconnected\n");
                    return;
                }
            }
            // 复位中断标志位
            // 如果需要清0   置为1
            setSn_IR(sn, Sn_IR_RECV);

            // 获取接收数据的长度
            uint16_t datalen = getSn_RX_RSR(sn);
            // 接收数据
            recv(sn, TCP_Rbuffer, datalen);
            printf("The client receives the data=> len:%d,data:%s\n", datalen, TCP_Rbuffer);
            // 返回数据
            send(sn, TCP_Rbuffer, datalen);
            memset(TCP_Rbuffer, 0, sizeof(TCP_Rbuffer));
        }
    }
}
