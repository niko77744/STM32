#include "Driver_DMA.h"
uint8_t DMA_IS_BRF = 0;

// Channel 4 串口的发送
void Driver_DMA1_Channel4_Init(void) { // USART TX
    /* 1.开启时钟*/
    RCC->AHBENR |= RCC_AHBENR_DMA1EN;

    //!!!!! 不用配置引脚GPIO模式

    /* 2.DMA相关配置 */
    // 2.1 选择内存和外设
    DMA1_Channel4->CCR &= ~DMA_CCR4_MEM2MEM;  //0：非存储器到存储器模式；
    DMA1_Channel4->CCR |= DMA_CCR4_DIR;  //0 外设到存储  1存储到外设

    // 2.2 DMA优先级
    DMA1_Channel4->CCR &= ~DMA_CCR4_PL;

    // 2.3 数据字长
    /* 00:8位 01:16位 10:32位 11:保留 */
    DMA1_Channel4->CCR &= ~DMA_CCR4_MSIZE;
    DMA1_Channel4->CCR &= ~DMA_CCR4_PSIZE;

    // 2.4 地址是否自增
    DMA1_Channel4->CCR &= ~DMA_CCR4_PINC;  /* 串口外设地址USART1->DR不能自增 */
    DMA1_Channel4->CCR |= DMA_CCR4_MINC;  /* 存储器地址自增 不然重复发送第一个字符 */

    // 2.5 循环模式
    DMA1_Channel4->CCR &= ~DMA_CCR4_CIRC;
    // DMA1_Channel4->CCR |= DMA_CCR4_CIRC; //先注释中断DMA1_Channel4->CCR &= ~DMA_CCR4_EN;


    // 2.6 开启中断
    DMA1_Channel4->CCR |= DMA_CCR4_TCIE;

    /* 3. 开启USART的DMAT */
    USART1->CR3 |= USART_CR3_DMAT;

    /* 4. NVIC */
    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(DMA1_Channel4_IRQn, 3);
    NVIC_EnableIRQ(DMA1_Channel4_IRQn);
}


// Channel 5 串口的接收
void Driver_DMA1_Channel5_Init(void) { // USART RX
    /* 1.开启时钟*/
    RCC->AHBENR |= RCC_AHBENR_DMA1EN;

    /* 2.DMA相关配置 */
    // 2.1 选择内存和外设
    DMA1_Channel5->CCR &= ~DMA_CCR5_MEM2MEM;  //0：非存储器到存储器模式；
    DMA1_Channel5->CCR &= ~DMA_CCR5_DIR;  //0 外设到存储  1存储到外设  !!!唯一区别

    // 2.2 DMA优先级
    DMA1_Channel5->CCR &= ~DMA_CCR5_PL;

    // 2.3 数据字长
    /* 00:8位 01:16位 10:32位 11:保留 */
    DMA1_Channel5->CCR &= ~DMA_CCR5_MSIZE;
    DMA1_Channel5->CCR &= ~DMA_CCR5_PSIZE;

    // 2.4 地址是否自增
    DMA1_Channel5->CCR &= ~DMA_CCR5_PINC;  /* 串口外设地址USART1->DR不能自增 */
    DMA1_Channel5->CCR |= DMA_CCR5_MINC;  /* 存储器地址自增 不然重复发送第一个字符 */

    // 2.5 循环模式
    DMA1_Channel5->CCR &= ~DMA_CCR5_CIRC;
    // DMA1_Channel4->CCR |= DMA_CCR4_CIRC; //先注释中断DMA1_Channel4->CCR &= ~DMA_CCR4_EN;


    // 2.6 开启中断
    DMA1_Channel5->CCR |= DMA_CCR5_TCIE;

    /* 3. 开启USART的DMAT */
    USART1->CR3 |= USART_CR3_DMAR;

    /* 4. NVIC */
    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(DMA1_Channel5_IRQn, 3);
    NVIC_EnableIRQ(DMA1_Channel5_IRQn);
}

// 从只读存储器ROM(const等常量 Flash)到静态存取存储器SRAM(变量)
void Driver_DMA1_Channel1_Init(void) { // Mem2Mem   
    /* 1.开启时钟 */
    RCC->AHBENR |= RCC_AHBENR_DMA1EN;

    /* 2.DMA相关配置 */
    // 2.1 a.选择存储器与存储器  b.从内存读
    DMA1_Channel1->CCR |= DMA_CCR1_MEM2MEM;
    DMA1_Channel1->CCR &= ~DMA_CCR1_DIR;  //???这里选择把SRAM当作外设

    // 2.2 配置DMA优先级
    DMA1_Channel1->CCR &= ~DMA_CCR1_PL;

    // 2.3 传输数据字长
    DMA1_Channel1->CCR &= ~DMA_CCR1_MSIZE;
    DMA1_Channel1->CCR &= ~DMA_CCR1_PSIZE;

    // 2.4 地址是否自增 内存地址自增,外设地址自增
    DMA1_Channel1->CCR |= DMA_CCR1_MINC;
    DMA1_Channel1->CCR |= DMA_CCR1_PINC;

    // 2.5 关闭循环模式
    DMA1_Channel1->CCR &= ~DMA_CCR1_CIRC;

    // 2.6 开启中断
    DMA1_Channel1->CCR |= DMA_CCR1_TCIE;

    /* 4.NVIC配置 */
    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(DMA1_Channel1_IRQn, 3);
    NVIC_EnableIRQ(DMA1_Channel1_IRQn);
}
void Driver_DMA1_Channel4_TransmitStart(uint32_t SrcAddr, uint32_t TargetAddr, uint16_t DateLen) {
    DMA1_Channel4->CMAR = SrcAddr;      //发送的时候将数据的地址buffer作为源地址
    DMA1_Channel4->CPAR = TargetAddr;   //发送的时候将USART->DR作为外设地址
    DMA1_Channel4->CNDTR = DateLen;     //Channel Number of Data to Transfer Register

    DMA1_Channel4->CCR |= DMA_CCR4_EN;
}

void Driver_DMA1_Channel5_ReceiveStart(uint32_t SrcAddr, uint32_t TargetAddr, uint16_t DateLen) {
    DMA1_Channel5->CMAR = TargetAddr;   //接收的时候将USART->DR作为源地址
    DMA1_Channel5->CPAR = SrcAddr;      //接收的时候将数据的地址buffer作为外设地址
    DMA1_Channel5->CNDTR = DateLen;     //Channel Number of Data to Transfer Register

    DMA1_Channel5->CCR |= DMA_CCR5_EN;
}

void Driver_DMA1_Channel1_TransmitStart(uint32_t srcAddr, uint32_t destAddr, uint16_t dataLen) {
    DMA1_Channel1->CMAR = destAddr;     //将变量当作目标地址
    DMA1_Channel1->CPAR = srcAddr;      //将Rom常量当作源地址
    DMA1_Channel1->CNDTR = dataLen;

    DMA1_Channel1->CCR |= DMA_CCR1_EN;
}

void DMA1_Channel4_IRQHandler(void) {
    if (DMA1->ISR & DMA_ISR_TCIF4)
    {
        // DMA1->IFCR |= DMA_IFCR_CTCIF4;  //CTEIF:Error   CGIF:global  CHTIF:half
        DMA1->IFCR |= DMA_IFCR_CGIF4;
        DMA1_Channel4->CCR &= ~DMA_CCR4_EN;
    }
}

void DMA1_Channel5_IRQHandler(void) {
    if (DMA1->ISR & DMA_ISR_TCIF5)
    {
        // DMA1->IFCR |= DMA_IFCR_CTCIF4;  //CTEIF:Error   CGIF:global  CHTIF:half
        DMA1->IFCR |= DMA_IFCR_CGIF5;
        DMA1_Channel5->CCR &= ~DMA_CCR5_EN;
        DMA_IS_BRF = 1;
    }
}


void DMA1_Channel1_IRQHandler(void) {
    if (DMA1->ISR & DMA_ISR_TCIF1)
    {
        // 1.清除中断标志位
        DMA1->IFCR |= DMA_IFCR_CGIF1;
        // 2.关闭DMA模块
        DMA1_Channel1->CCR &= ~DMA_CCR1_EN;
    }
}
