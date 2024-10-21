#include "Driver_ETH.h"

uint8_t mac[6] = { 0x00,0x08,0xdc,0x11,0x11,0x11 };
uint8_t ip[4] = { 192, 168, 23, 104 };
uint8_t sub[4] = { 255, 255, 255, 0 };
uint8_t gw[4] = { 192, 168, 23, 1 };
uint8_t dns[4] = { 8,8,8,8 };
uint8_t ETH_Rbuffer[128] = { 0 };
#define w5500_port 8080


void Driver_ETH_Reset(void);
void Driver_ETH_SetMac(void);
void Driver_ETH_SetIP(void);

void Driver_ETH_Init(void) {
    Driver_SPIx_Init(SPI2);
    user_register_function();
    /* ����W5500 */
    Driver_ETH_Reset();
    /* ����MAC��ַ */
    Driver_ETH_SetMac();
    /* ����IP��Ϣ */
    Driver_ETH_SetIP();
}

void Driver_ETH_Reset(void) {
    // W5500�ĳ�ʼ������  PG7 �͵�ƽ500us
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
    // 1. ����ip��ַ
    setSIPR(ip); //local IP It should be allocated 4 bytes
    Delay_ms(1);
    // 2. ������������
    setSUBR(sub); //subnet mask address It should be allocated 4 bytes
    Delay_ms(1);
    // 3. ��������
    setGAR(gw);  //gateway IP It should be allocated 4 bytes
    Delay_ms(1);
}


/**
 * @brief ��W5500��ΪTCP�ķ����
 * @param sn  (uint8_t)sn Socket number. It should be <b>0 ~ 7</b>.
 * @return * void
 */
void TCP_Server_Socket(uint8_t sn) {
    // 1. ��ȡ��ǰsocket0��״̬
    uint8_t socket_state = getSn_SR(sn);
    if (socket_state == SOCK_CLOSED)
    {
        // 2. ��ǰΪ�ر�״̬ ->  ��ʾ����˻�û�г�ʼ�� socketû����
        int8_t socket_return = socket(sn, Sn_MR_TCP, w5500_port, SF_TCP_NODELAY); //����sn��
        socket_return == sn ? printf("Socket Init Success\n") : printf("Socket Init Error\n");
    }
    else if (socket_state == SOCK_INIT)
    {
        // 3. ��ʼ����� -> �������״̬ �ȴ��ͻ�������
        int8_t listen_return = listen(sn);
        listen_return == SOCK_OK ? printf("Listen Init Success\n") : printf("Listen %d Init Error\n", close(sn));
    }
    else if (socket_state == SOCK_ESTABLISHED)
    {
        // 4.˵���Ѿ����ӳɹ� -> ���Խ����շ�������
        // ��ӡ�ͻ��˵�ip��ַ�Ͷ˿ں�
        uint8_t Client_Ip[4] = { 0 };
        uint16_t Client_port = 0;
        getSn_DIPR(sn, Client_Ip);
        Client_port = getSn_DPORT(sn);
        printf("Connect Success! Client_Ip:port = %d.%d.%d.%d:%d\n", Client_Ip[0], Client_Ip[1], Client_Ip[2], Client_Ip[3], Client_port);

        // һֱ��ѯ��������,֪���Ͽ�����
        while (1) {
            // 5. ����շ�����
            // �жϵ�ǰ�Ƿ��յ�����
            while ((getSn_IR(sn) & Sn_IR_RECV) == 0)
            {
                // ��û���յ�����   ����ȴ�
                // �����ж��Ƿ������Ѿ��ر�
                if (getSn_SR(sn) != SOCK_ESTABLISHED)
                {
                    // ���ղ�������  �����Ѿ��ر�
                    close(sn);
                    printf("Connection has been disconnected\n");
                    return;
                }
            }
            // �����ݽ���  -> ����жϱ�־λ
            // �����Ҫ��ձ�׼λ  ���ղ�Ʒ�ֲ�д1
            setSn_IR(sn, Sn_IR_RECV);

            // ��ȡ����  ->  �ȶ�ȡ���յ����ݳ���
            uint16_t datalen = getSn_RX_RSR(sn);

            //�ɷ���˷�����Ϣ  Ȼ����Ϣ��ӡ������
            recv(sn, ETH_Rbuffer, datalen);
            printf("ReceiveData => len:%d,data:%s\n", datalen, ETH_Rbuffer);
            // w5500 �����յ�������ԭ�ⲻ���ķ���
            send(sn, ETH_Rbuffer, datalen);
            memset(ETH_Rbuffer, 0, sizeof(ETH_Rbuffer));
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
        // 3. ��ʼ��״̬ -> ѡ����Ϊ�ͻ��� -> ��������
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
        // 4. ����״̬ -> ��������hello
        send(0, "hello\n", 6);

        while (1) {
            // �ȴ�����(�ظ�)����  -> ԭ�ⲻ����������
            while ((getSn_IR(sn) & Sn_IR_RECV) == 0)
            {
                if (getSn_SR(sn) != SOCK_ESTABLISHED)
                {
                    close(sn);
                    printf("Connection has been disconnected\n");
                    return;
                }
            }
            // ��λ�жϱ�־λ
            // �����Ҫ��0   ��Ϊ1
            setSn_IR(sn, Sn_IR_RECV);

            // ��ȡ�������ݵĳ���
            uint16_t datalen = getSn_RX_RSR(sn);
            // ��������
            recv(sn, ETH_Rbuffer, datalen);
            printf("The client receives the data=> len:%d,data:%s\n", datalen, ETH_Rbuffer);
            // ��������
            send(sn, ETH_Rbuffer, datalen);
            memset(ETH_Rbuffer, 0, sizeof(ETH_Rbuffer));
        }
    }
}


void UDP_Socket(uint8_t sn) {
    // 1. ��ȡsocket0״̬
    uint8_t socket_state = getSn_SR(sn);
    if (socket_state == SOCK_CLOSED)
    {
        // 2. �ر�״̬  ->  ѡ��ʹ��UDPЭ��
        int8_t socket_return = socket(sn, Sn_MR_UDP, w5500_port, 0);
        socket_return == sn ? printf("Socket Init Success\n") : printf("Socket Init Error\n");
    }
    else if (socket_state == SOCK_UDP)
    {
        // 3. ����UDP�������״̬
        // ��֪���Է���IP�Ͷ˿ں�
        // �ȴ������������  ->  ���յ������л�����Է���IP��ַ�˿ں�
        uint16_t datalen = 0;
        uint8_t UDP_Ip[4] = { 0 };
        uint16_t UDP_port = 0;

        // ��֪���������ݵĳ���
        while (1) {
            while ((getSn_IR(sn) & Sn_IR_RECV) == 0)
            {
                if (getSn_SR(sn) != SOCK_UDP)
                {
                    close(sn);
                    printf("Connection has been disconnected\n");
                    return;
                }
            }
            setSn_IR(sn, Sn_IR_RECV);
            // ���յ�����
            // ��ȡ�������ݵĳ���  ->  UDP���յ������ݻ��8�ֽ� �յ�  ��־
            datalen = getSn_RX_RSR(sn);
            if (datalen > 0)
            {
                recvfrom(sn, ETH_Rbuffer, datalen, UDP_Ip, &UDP_port);
                printf("received from UDP=> IP:%d.%d.%d.%d:%d,len:%d,data:%s\n", UDP_Ip[0], UDP_Ip[1], UDP_Ip[2], UDP_Ip[3], UDP_port, datalen - 8, ETH_Rbuffer);

                if (datalen - 8 > 0)
                {
                    sendto(sn, ETH_Rbuffer, datalen - 8, UDP_Ip, UDP_port);
                }

                memset(ETH_Rbuffer, 0, sizeof(ETH_Rbuffer));
            }
        }
    }
}

// http://192.168.23.104/index.html
uint8_t tx_buff[2048];
uint8_t rx_buff[2048];
uint8_t cnt = 1;
uint8_t sockList[1] = { 0 };
uint8_t* content_name = "index.html";

/* ��Ӧ����ҳ������ */
uint8_t content[2048] = "<!doctype html>\n"
"<html lang=\"en\">\n"
"<head>\n"
"    <meta charset=\"GBK\">\n"
"    <meta name=\"viewport\"\n"
"          content=\"width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0\">\n"
"    <meta http-equiv=\"X-UA-Compatible\" content=\"ie=edge\">\n"
"    <title>Webserver Test</title>\n"
"\n"
"    <style type=\"text/css\">\n"
"        #open_red{\n"
"            color: red;\n"
"            width: 100px;\n"
"            height: 40px;\n"
"\n"
"\n"
"        }\n"
"        #close_red{\n"
"            color: black;\n"
"            width: 100px;\n"
"            height: 40px;\n"
"        }\n"
"    </style>\n"
"</head>\n"
"<body>\n"
"<a href=\"/index.html?action=1\"><button id=\"open_red\" >����</button></a>\n"
"<a href=\"/index.html?action=2\"><button id=\"close_red\" >�ص�</button></a>\n"
"</body>\n"
"</html>";


void Web_serever_Init(void) {
    httpServer_init(tx_buff, rx_buff, cnt, sockList);
    reg_httpServer_webContent(content_name, content);
}

void Web_serever_Start(void) {
    while (1)
    {
        httpServer_run(0);
    }
}

// ת���ַ�������
// /index.html?action=1  =>  1
// /index.html?action=2  =>  2
// ����                  =>  0
uint8_t parse_url_action(uint8_t* url)
{
    // ���Ҵ���ĵ�һ������url���Ƿ�����ڶ�������action=
    // ���������  =>  ����NULL
    // �������  => ָ�� -> ָ��ڶ��������Ŀ�ʼλ��
    char* result = strstr((char*)url, "action=");
    if (result == NULL)
    {
        // ������ȷ�İ�ť
        return 0;
    }
    else
    {
        // action=1
        return (uint8_t)(*(result + 7));
    }
}

// �������û��Զ���ĺ���Ƕ�׽�Դ������
// ÿ���û������ҳ�Ŀ��صư�ť  ->  /index.html?action=1��Ϊurl��������������ĺ���
void user_handle_function(uint8_t* url)
{
    uint8_t action = parse_url_action(url);
    printf("���յ���urlΪ:%s,����֮���action:%d\n", url, action);
    if (action == '1')
    {
        // ����
        Driver_LED_On(LED1);
    }
    else if (action == '2')
    {
        Driver_LED_Off(LED1);
    }
}
