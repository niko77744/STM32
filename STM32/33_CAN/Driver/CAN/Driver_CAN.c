#include "Driver_CAN.h"

void Driver_CAN_Init(void) {
    RCC->APB1ENR |= RCC_APB1ENR_CAN1EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

    AFIO->MAPR |= AFIO_MAPR_CAN_REMAP_1;
    AFIO->MAPR &= ~AFIO_MAPR_CAN_REMAP_0;

    //PB9(CAN_Tx)：复用推挽输出 PB8(CAN_Rx): 浮空输入 
    Hal_GPIO_Mode_Selection(GPIOB, GPIO_pin_9, GPIO_Mode_AF_PP);
    Hal_GPIO_Mode_Selection(GPIOB, GPIO_pin_8, GPIO_Mode_IN_FLOATING);

    /* 配置CAN寄存器 */
    // 退出睡眠模式
    CAN1->MCR &= ~CAN_MCR_SLEEP;
    while ((CAN1->MCR & CAN_MSR_SLAK) != 0);  //等到SLAK=0

    // 进入初始化模式
    CAN1->MCR |= CAN_MCR_INRQ;
    while ((CAN1->MCR & CAN_MSR_INAK) == 0);  //等到INAK=1

    // 自动离线管理和自动唤醒功能
    CAN1->MCR |= CAN_MCR_ABOM;
    CAN1->MCR |= CAN_MCR_AWUM;

    // 打开环回静默模式
    CAN1->BTR |= CAN_BTR_SILM; //Silent mode
    CAN1->BTR |= CAN_BTR_SILM; //Loop back mode

    // 设置波特率分频器系数 BPR  该位域定义了时间单元(tq)的时间长度   tq = (BRP[9:0]+1) x tPCLK(1/36MHz) 对应的频率1MHz  周期 1us
    CAN1->BTR &= ~CAN_BTR_BRP;
    CAN1->BTR |= (35 << 0);

    // 设置TS1和TS2
    CAN1->BTR &= ~CAN_BTR_TS1;  //4位
    CAN1->BTR &= ~CAN_BTR_TS2;  //3位
    CAN1->BTR |= (5 << 16);
    CAN1->BTR |= (2 << 20);

    CAN1->BTR |= CAN_BTR_SJW; //重新同步跳跃宽度  为了重新同步，该位域定义了CAN硬件在每位中可以延长或缩短多少个时间单元的上限

    // 退出初始化模式
    CAN1->MCR &= ~CAN_MCR_INRQ;
    while ((CAN1->MCR & CAN_MSR_INAK) != 0);  //等到INAK=0

    /* 配置过滤器 */
    // 进入过滤器初始化模式
    CAN1->FMR |= CAN_FMR_FINIT;

    // 只使用过滤器0   掩码模式0   32位1  共14个过滤器组(13~0)  每个过滤器组x由2个32位寄存器
    CAN1->FM1R &= ~CAN_FM1R_FBM0;
    CAN1->FS1R |= CAN_FS1R_FSC0;  //scale

    //关联对应的FIFO0
    CAN1->FFA1R &= ~CAN_FFA1R_FFA0;

    // 填写屏蔽模式下的ID和mask      
    // 11位stdId  18位EXID IDE RTR 0
    CAN1->sFilterRegister[0].FR1 = 0;  // CAN_TypeDef 下有  CAN_FilterRegister_TypeDef sFilterRegister[14]
    // 掩码  -> 哪些ID需要接收
    CAN1->sFilterRegister[0].FR2 = 0;

    // 激活过滤器
    CAN1->FA1R |= CAN_FA1R_FACT0;

    //退出过滤器初始化模式
    CAN1->FMR &= ~CAN_FMR_FINIT;
}

void Driver_CAN_SendBytes(uint16_t stdID, uint8_t* bytes, uint8_t length) {
    // 数据长度0-8字节
    if (length > 8) return;

    /* 判断发送的邮箱为空 */
    // 有3个邮箱 -> 只使用邮箱0 ->3个邮箱可以存3个报文
    while ((CAN1->TSR & CAN_TSR_TME0) == 0);  //Transmit mailbox 0 empty 当邮箱0中没有等待发送的报文时，硬件对该位置’1’。

    /* 将数据放入到对应的邮箱 */
    // 写标准格式   数据帧
    CAN1->sTxMailBox[0].TIR &= ~CAN_TI0R_IDE; //CAN_TxMailBox_TypeDef sTxMailBox[3];
    CAN1->sTxMailBox[0].TIR &= ~CAN_TI0R_RTR;

    // 写入STDID
    CAN1->sTxMailBox[0].TIR &= ~CAN_TI0R_STID;
    CAN1->sTxMailBox[0].TIR |= stdID << 21;

    // 写入DLE数据长度 (Data length code)
    CAN1->sTxMailBox[0].TDTR &= ~CAN_TDT0R_DLC;
    CAN1->sTxMailBox[0].TDTR |= (length << 0);

    // 写入数据
    CAN1->sTxMailBox[0].TDHR = 0;
    CAN1->sTxMailBox[0].TDLR = 0;
    for (uint8_t i = 0; i < length; i++)
    {
        if (i < 4)
        {
            CAN1->sTxMailBox[0].TDLR |= (bytes[i] << (8 * i));
        }
        else
        {
            CAN1->sTxMailBox[0].TDHR |= (bytes[i] << (8 * (i - 4)));
        }
    }

    // 发送数据请求  由软件对其置’1’，来请求发送邮箱的数据。当数据发送完成，邮箱为空时，硬件对其清’0’。
    CAN1->sTxMailBox[0].TIR |= CAN_TI0R_TXRQ;
}
void Driver_CAN_ReceiveBytes(CAN_RxData CAN_Rx[], uint8_t* BytesConut) {
    /* 将一个字符数组初始化为全 0（实际上是 '\0' 字符）
    char str[10];
    memset(str, 0, sizeof(str));  //要求为定长字符串*/

    // 读取FIFO0中的报文数量
    *BytesConut = (CAN1->RF0R & CAN_RF0R_FMP0);


    // 循环读取报文信息  将内容存放到结构体数组中
    for (uint8_t i = 0; i < *BytesConut; i++)
    {
        CAN_RxData* msg = &CAN_Rx;

        /* 2个FIFO队列，每个队列FIFO都可以存放3个完整的报文 */

       // 填写结构体的stdid
        msg->stdID = (CAN1->sFIFOMailBox[0].RIR & CAN_RI0R_STID) >> 21;  //CAN_FIFOMailBox_TypeDef sFIFOMailBox[2];
        // 获取数据的长度
        msg->length = (CAN1->sFIFOMailBox[0].RDTR & CAN_RDT0R_DLC) >> 0;


        // 写数据  清空之前可能填写的data值
        memset(msg->data, 0, sizeof(msg->data));

        for (uint8_t j = 0; j < msg->length; j++)
        {

        }
    }

}
