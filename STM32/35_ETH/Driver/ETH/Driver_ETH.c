#include "Driver_ETH.h"

uint8_t mac[6] = { 101, 129, 220, 89, 143, 212 };  //随意
uint8_t ip[4] = { 192, 168, 23, 104 };  //103 104

uint8_t sub[4] = { 255, 255, 255, 0 };
uint8_t gw[4] = { 192, 168, 23, 1 };

void Inf_ETH_Reset(void);
void Inf_ETH_SetMac(void);
void Inf_ETH_SetIP(void);

void Driver_ETH_Init(void) {
    Driver_SPIx_Init(SPI2);
    user_register_function();
    /* 重置W5500 */
    Inf_ETH_Reset();
    /* 设置MAC地址 */
    Inf_ETH_SetMac();
    /* 设置IP信息 */
    Inf_ETH_SetIP();
}

void Inf_ETH_Reset(void) {
    // W5500的初始化引脚  PG7 低电平500us
    RCC->APB2ENR |= RCC_APB2ENR_IOPGEN;
    Hal_GPIO_Mode_Selection(GPIOG, GPIO_pin_7, GPIO_Mode_Out_PP);
    HAL_GPIO_WritePin(GPIOG, GPIO_pin_7, GPIO_PIN_RESET);
    Delay_ms(1);
    HAL_GPIO_WritePin(GPIOG, GPIO_pin_7, GPIO_PIN_SET);
}
void Inf_ETH_SetMac(void) {
    printf("mac start\n");
    setSHAR(mac);
    Delay_ms(1);
    printf("mac end\n");
}

void Inf_ETH_SetIP(void) {
    // 1. 设置ip地址
    printf("ip start\n");
    setSIPR(ip);
    Delay_ms(1);
    printf("ip end\n");
    // 2. 设置子网掩码
    printf("msak start\n");
    setSUBR(sub);
    Delay_ms(1);
    printf("msak end\n");
    // 3. 设置网关
    printf("gar start\n");
    setGAR(gw);
    Delay_ms(1);
    printf("gar end\n");
}
