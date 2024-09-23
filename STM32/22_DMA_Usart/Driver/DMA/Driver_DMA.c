#include "Driver_DMA.h"

void Driver_DMA1_Init(void) {
    /* 1.开启时钟*/
    RCC->AHBENR |= RCC_AHBENR_DMA1EN;

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
    // DMA1_Channel4->CCR |= DMA_CCR4_TCIE;

    /* 3. 开启USART的DMAT */
    USART1->CR3 |= USART_CR3_DMAT;

    /* 4. NVIC */
    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(DMA1_Channel4_IRQn, 3);
    NVIC_EnableIRQ(DMA1_Channel4_IRQn);
}

void Driver_DMA1_TransmitStart(uint32_t SrcAddr, uint32_t TargetAddr, uint16_t DateLen) {
    DMA1_Channel4->CMAR = SrcAddr;
    DMA1_Channel4->CPAR = TargetAddr;
    DMA1_Channel4->CNDTR = DateLen;  //Channel Number of Data to Transfer Register

    DMA1_Channel4->CCR |= DMA_CCR4_EN;
}

void DMA1_Channel4_IRQHandler(void) {
    if (DMA1->ISR & DMA_ISR_TCIF4)
    {
        // DMA1->IFCR |= DMA_IFCR_CTCIF4;  //CTEIF:Error   CGIF:global  CHTIF:half
        DMA1->IFCR |= DMA_IFCR_CGIF4;
        DMA1_Channel4->CCR &= ~DMA_CCR4_EN;
    }
}
