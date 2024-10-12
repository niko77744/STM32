#include "Driver_ETH.h"

uint8_t mac[6] = { 0x00,0x08,0xdc,0x11,0x11,0x11 };
uint8_t ip[4] = { 192, 168, 23, 104 };
uint8_t sub[4] = { 255, 255, 255, 0 };
uint8_t gw[4] = { 192, 168, 23, 1 };
uint8_t dns[4] = { 8,8,8,8 };


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
 * @param Socket_sn  (uint8_t)sn Socket number. It should be <b>0 ~ 7</b>.
 * @return * void
 */
void Inf_TCP_Server(uint8_t Socket_sn) {
    // 1. ��ȡ��ǰsocket0��״̬
    uint8_t socket_state = getSn_SR(Socket_sn);
    if (socket_state == SOCK_CLOSED)
    {
        // 2. ��ǰΪ�ر�״̬ ->  ��ʾ����˻�û�г�ʼ�� socketû����
        int8_t socket_return = socket(Socket_sn, Sn_MR_TCP, 8080, SF_TCP_NODELAY); //����sn��
        socket_return == Socket_sn ? printf("Socket Init Success\n") : printf("Socket Init Error\n");
    }
    else if (socket_state == SOCK_INIT)
    {
        // 3. ��ʼ����� -> �������״̬ �ȴ��ͻ�������
        int8_t listen_return = listen(Socket_sn);
        listen_return == SOCK_OK ? printf("Listen Init Success\n") : printf("Listen %d Init Error\n", close(Socket_sn));
    }
    else if (socket_state == SOCK_ESTABLISHED)
    {
        // 4.˵���Ѿ����ӳɹ� -> ���Խ����շ�������
        // ��ӡ�ͻ��˵�ip��ַ�Ͷ˿ں�
        uint8_t Client_Ip[4] = { 0 };
        uint16_t Client_port = 0;
        getSn_DIPR(Socket_sn, Client_Ip);
        Client_port = getSn_DPORT(Socket_sn);
        printf("Connect Success! Client_Ip:port = %d.%d.%d.%d:%d\n", Client_Ip[0], Client_Ip[1], Client_Ip[2], Client_Ip[3], Client_port);
        
    }
}
