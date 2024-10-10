#include "Driver_CAN.h"

void HAL_CAN_MspInit(CAN_TypeDef* CANx) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
    RCC->APB1ENR |= RCC_APB1ENR_CAN1EN;

    AFIO->MAPR |= AFIO_MAPR_CAN_REMAP_1;
    AFIO->MAPR &= ~AFIO_MAPR_CAN_REMAP_0;

    //PB9(CAN_Tx)：复用推挽输出 PB8(CAN_Rx): 浮空输入 
    Hal_GPIO_Mode_Selection(GPIOB, GPIO_pin_8, GPIO_Mode_IN_FLOATING);
    Hal_GPIO_Mode_Selection(GPIOB, GPIO_pin_9, GPIO_Mode_AF_PP);

    /* 配置CAN寄存器 */
    // 退出睡眠模式
    CANx->MCR &= ~CAN_MCR_SLEEP;
    while ((CANx->MSR & CAN_MSR_SLAK) != 0); //等到SLAK=0

    // 进入初始化模式
    CANx->MCR |= CAN_MCR_INRQ;
    while ((CANx->MSR & CAN_MSR_INAK) == 0);  //等到INAK=1

    // 自动离线管理和自动唤醒功能
    CANx->MCR |= CAN_MCR_ABOM;
    CANx->MCR |= CAN_MCR_AWUM;

    // FIFO0满触发中断
    CAN1->IER |= CAN_IER_FFIE0;
    // FIFO 0消息挂号中断使能 接收到一个新报文触发中断
    // CANx->IER |= CAN_IER_FMPIE0;

    // 打开环回静默模式
    CANx->BTR |= CAN_BTR_LBKM;
    CANx->BTR |= CAN_BTR_SILM;

    // 设置TS1和TS2
    CANx->BTR &= ~CAN_BTR_TS1;
    CANx->BTR &= ~CAN_BTR_TS2;
    CANx->BTR |= (6 - 1) << 16;
    CANx->BTR |= (3 - 1) << 20;
    //重新同步跳跃宽度  为了重新同步，该位域定义了CAN硬件在每位中可以延长或缩短多少个时间单元的上限
    CANx->BTR &= ~CAN_BTR_SJW;
    CANx->BTR |= (1 << 24);
    // 设置波特率分频器系数 BPR  该位域定义了时间单元(tq)的时间长度   tq = (BRP[9:0]+1) x tPCLK(1/36MHz) 对应的频率1MHz  周期 1us
    CANx->BTR &= ~CAN_BTR_BRP;
    CANx->BTR |= (36 - 1) << 0;

    // 退出初始化模式
    CANx->MCR &= ~CAN_MCR_INRQ;
    while ((CANx->MSR & CAN_MSR_INAK) != 0);

    /* 配置过滤器 */
    // 进入过滤器初始化模式
    CANx->FMR |= CAN_FMR_FINIT;
    // 只使用过滤器0   掩码模式0   32位1  共14个过滤器组(13~0)  每个过滤器组x由2个32位寄存器
    CANx->FM1R &= ~CAN_FM1R_FBM0;
    CANx->FS1R |= CAN_FS1R_FSC0;
    //关联对应的FIFO0
    CANx->FFA1R &= ~CAN_FFA1R_FFA0;

    // 填写屏蔽模式下的ID和mask      
    // 11位stdId  18位EXID IDE RTR 0   -> STDID 低3位是111  //0xFFE00000
    CANx->sFilterRegister[0].FR1 = 0;  // CAN_TypeDef 下有  CAN_FilterRegister_TypeDef sFilterRegister[14]
    // 掩码  -> 哪些ID需要接收
    CANx->sFilterRegister[0].FR2 = 0;
    // 激活过滤器
    CANx->FA1R |= CAN_FA1R_FACT0;
    //退出过滤器初始化模式
    CANx->FMR &= ~CAN_FMR_FINIT;

    NVIC_SetPriorityGrouping(3);
    NVIC_SetPriority(USB_LP_CAN1_RX0_IRQn, 4);
    NVIC_EnableIRQ(USB_LP_CAN1_RX0_IRQn);
}


uint32_t HAL_CAN_GetTxMailboxesFreeLevel(CAN_TypeDef* CANx) {
    uint32_t freelevel = 0U;
    if ((CANx->TSR & CAN_TSR_TME0) != 0U)
    {
        freelevel++;
    }
    if ((CANx->TSR & CAN_TSR_TME1) != 0U)
    {
        freelevel++;
    }
    if ((CANx->TSR & CAN_TSR_TME2) != 0U)
    {
        freelevel++;
    }
    return freelevel; // 返回空闲邮箱个数
}


void HAL_CAN_AddTxMessage(CAN_TypeDef* CANx, uint16_t stdID, uint8_t* bytes, uint8_t length) {
    if (length > 8) return;  // 数据长度0-8字节
    /* 判断发送的邮箱为空 */
    // 有3个邮箱 -> 只使用邮箱0 ->3个邮箱可以存3个报文
    while (HAL_CAN_GetTxMailboxesFreeLevel(CANx) == 0);

    /* 将数据放入到对应的邮箱 */
    // 写标准格式   数据帧
    CANx->sTxMailBox[(CANx->TSR & CAN_TSR_CODE) >> 24].TDLR = 0; //CAN_TxMailBox_TypeDef sTxMailBox[3];
    CANx->sTxMailBox[(CANx->TSR & CAN_TSR_CODE) >> 24].TDHR = 0;

    // 写入数据
    for (uint8_t i = 0; i < length; i++)
    {
        if (i < 4)
        {
            CANx->sTxMailBox[(CANx->TSR & CAN_TSR_CODE) >> 24].TDLR |= bytes[i] << (8 * i);
        }
        else {
            CANx->sTxMailBox[(CANx->TSR & CAN_TSR_CODE) >> 24].TDHR |= bytes[i] << (8 * (i - 4));
        }
    }
    // 写入STDID DLC数据长度
    CANx->sTxMailBox[(CANx->TSR & CAN_TSR_CODE) >> 24].TDTR = length;
    CANx->sTxMailBox[(CANx->TSR & CAN_TSR_CODE) >> 24].TIR = (stdID << 21 | 1 << 0); // 1是发送数据请求

    /* Warning: 测试Code恒等1  FreeLevel恒等2  可能有Bug  暂未影响使用*/
}

uint32_t HAL_CAN_GetRxFifoFillLevel(CAN_TypeDef* CANx, uint32_t RxFifo) {
    uint32_t filllevel = 0U;
    if (RxFifo == CAN_RX_FIFO0)
    {
        filllevel = CANx->RF0R & CAN_RF0R_FMP0;
    }
    else /* RxFifo == CAN_RX_FIFO1 */
    {
        filllevel = CANx->RF1R & CAN_RF1R_FMP1;
    }
    return filllevel; //返回报文数量
}

void HAL_CAN_GetRxMessage(CAN_TypeDef* CANx, CAN_RxData CAN_Rx[], uint8_t* BytesConut) {
    /* 将一个字符数组初始化为全 0（实际上是 '\0' 字符）
    char str[10];
    memset(str, 0, sizeof(str));  //要求为定长字符串*/

    // 读取FIFO0中的报文数量  FIFO0最多三个报文， FIFO1未使用
    *BytesConut = HAL_CAN_GetRxFifoFillLevel(CANx, CAN_RX_FIFO0);
    // 循环读取报文信息  将内容存放到结构体数组中
    for (uint8_t i = 0; i < *BytesConut; i++)
    {
        // 不ruturn的原因是CAN_Rx一个结构体数组而不是结构体
        CAN_RxData* msg = &CAN_Rx[i];
        /* 2个FIFO队列，每个队列FIFO都可以存放3个完整的报文 */

        // 填写结构体的stdid
        // 获取数据的长度 4位,表示数据段包含多少字节 0~8,所以需要4位
        msg->length = (CANx->sFIFOMailBox[CAN_RX_FIFO0].RDTR & CAN_RDT1R_DLC) >> 0;
        msg->stdID = (CANx->sFIFOMailBox[CAN_RX_FIFO0].RIR & CAN_RI0R_STID) >> 21; //CAN_FIFOMailBox_TypeDef sFIFOMailBox[2];

        // 写数据  清空之前可能填写的data值
        memset(msg->data, 0, sizeof(msg->data));

        uint32_t lowdata = CANx->sFIFOMailBox[CAN_RX_FIFO0].RDLR;
        uint32_t highdata = CANx->sFIFOMailBox[CAN_RX_FIFO0].RDHR;
        for (uint8_t j = 0; j < msg->length; j++)
        {
            if (j < 4)
            {
                // data是8位的,所以是右移
                msg->data[j] = (lowdata >> j * 8);
            }
            else {
                msg->data[j] = (highdata >> (j - 4) * 8);
            }
        }
        //释放当前报文    
        //读取完一个释放一个。如果FIFO中有2个以上的报文，由于FIFO的特点，软件需要释放输出邮箱才能访问第2个报文
        CANx->RF0R |= CAN_RF0R_RFOM0;
    }
}


void USB_LP_CAN1_RX0_IRQHandler(void) {
    if ((CAN1->RF0R & CAN_RF0R_FULL0) != 0)
    {
        printf("full\n");
    }
    else {
        printf("single\n");
    }
    CAN_RxData rxdata[3];
    uint8_t msgCount;
    HAL_CAN_GetRxMessage(CAN1, rxdata, &msgCount);
    for (uint8_t i = 0; i < msgCount; i++)
    {
        printf("The %d message,stdId:%d,length:%d,data:%s\n", i + 1, rxdata[i].stdID, rxdata[i].length, rxdata[i].data);
    }
}
