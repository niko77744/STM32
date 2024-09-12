#include "Driver_usart .h"

void Driver_USART1_Init(void) {
    // 1.开启时钟  1.GPIOA PA9和PA10   2.USART自己
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    // 2.配置GPIO工作模式
    // 2.1 PA9 TX 输出 复用推挽输出 MODE：11  CNF：10
    GPIOA->CRH |= GPIO_CRH_MODE9;
    GPIOA->CRH &= ~GPIO_CRH_CNF9_0;
    GPIOA->CRH |= GPIO_CRH_CNF9_1;
    // 2.2 PA10 RX 输入 浮空输入 MDOE：00 CNF：01
    GPIOA->CRH &= ~GPIO_CRH_MODE10;
    GPIOA->CRH |= GPIO_CRH_CNF10_0;
    GPIOA->CRH &= ~GPIO_CRH_CNF10_1;

    // 3.USART模块配置
    // 3.1 USART_BRR波特率  115200  0x0271
    USART1->BRR = 0x271;
    // 3.2 USART_CR1 接收发送使能  RE,TE
    USART1->CR1 |= USART_CR1_TE;
    USART1->CR1 |= USART_CR1_RE;
    // 3.3 USART_CR1 字长 M 默认0表示数据长度8
    USART1->CR1 &= ~USART_CR1_M;
    // 3.4 USART_CR1 不需要校验位 PCE  默认0不开启校验
    USART1->CR1 &= ~USART_CR1_PCE;
    // 3.5 USART_CR2配置停止位 默认00表示停止位STOP为1位
    USART1->CR2 &= ~USART_CR2_STOP;
    // 3.6 配置中断 RXENIE和IDLEIE
    USART1->CR1 |= USART_CR1_RXNEIE;
    USART1->CR1 |= USART_CR1_IDLEIE;

    // 3.7 USART_CR1 USART串口模块使能 (模块使能放在最后，有些配置使能开启后不能更改配置) UE 
    USART1->CR1 |= USART_CR1_UE;

    // // 4.设置NVIC优先级
    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(USART1_IRQn, 3);
    NVIC_EnableIRQ(USART1_IRQn);
}

void Driver_USART1_SendChar(uint8_t byte) {
    // 等到发送数据寄存器为空，放到移位寄存器  SR的TXE==1
    while ((USART1->SR & USART_SR_TXE) == 0);  //发送数据寄存器空
    USART1->DR = byte;
}
void Driver_USART1_SendString(uint8_t* str, uint8_t len) {
    // 不需要判断有没有发送完，因为我们知道发送数据的长度
    for (uint8_t i = 0; i < len; i++)
    {
        Driver_USART1_SendChar(str[i]);
    }
}

uint8_t Driver_USART1_ReceiveChar(void) {
    while ((USART1->SR & USART_SR_RXNE) == 0); // RXNE读取数据寄存器非空  没有数据的时候卡住
    return USART1->DR;
}
void Driver_USART1_ReceiveString(uint8_t* buff, uint8_t* len) {
    // uint8_t i = 0;
    // while (1)
    // {
    //     while ((USART1->SR & USART_SR_RXNE) == 0) {  // 读取数据寄存器为空
    //         if (USART1->SR & USART_SR_IDLE) { // 并且检测到空闲帧  不能仅仅只有空闲帧，否则独到的数据就是仅有一个字节
    //             // 推断数据发送完成
    //             *len = i;
    //             return;
    //         }
    //     };
    //     buff[i] = USART1->DR;
    //     i++;
    // }
}
uint8_t buffer[100] = { 0 };
uint8_t len = 0;
uint8_t is_over = 0;
void USART1_IRQHandler(void) {
    // 当RDR移位寄存器中的数据被转移到USART_DR寄存器中，该位被硬件置位。如果USART_CR1寄存器中的RXNEIE为1，则产生中断。对USART_DR的读操作可以将该位清零。
    if (USART1->SR & USART_SR_RXNE)  // 读数据寄存器非空 1收到数据可以读出
    {
        // 1个字节接收完成cc
        buffer[len++] = USART1->DR;  //读取DR寄存器会清除寄存器 
    }
    //监测到总线空闲  1检测到空闲 当检测到总线空闲时，该位被硬件置位。如果USART_CR1中的IDLEIE为’1’，则产生中断。由软件序列清除该位(先读USART_SR，然后读USART_DR)。
    else if (USART1->SR & USART_SR_IDLE)
    {
        // 清除中断标志位
        USART1->SR;
        USART1->DR;
        is_over = 1;

        // 表示接收变长数据完成,发回PC
        // Driver_USART1_SendString(buffer, len);
        // len = 0;
    }
}
