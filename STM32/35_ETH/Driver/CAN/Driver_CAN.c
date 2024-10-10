#include "Driver_CAN.h"

void HAL_CAN_MspInit(CAN_TypeDef* CANx) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
    RCC->APB1ENR |= RCC_APB1ENR_CAN1EN;

    AFIO->MAPR |= AFIO_MAPR_CAN_REMAP_1;
    AFIO->MAPR &= ~AFIO_MAPR_CAN_REMAP_0;

    //PB9(CAN_Tx)������������� PB8(CAN_Rx): �������� 
    Hal_GPIO_Mode_Selection(GPIOB, GPIO_pin_8, GPIO_Mode_IN_FLOATING);
    Hal_GPIO_Mode_Selection(GPIOB, GPIO_pin_9, GPIO_Mode_AF_PP);

    /* ����CAN�Ĵ��� */
    // �˳�˯��ģʽ
    CANx->MCR &= ~CAN_MCR_SLEEP;
    while ((CANx->MSR & CAN_MSR_SLAK) != 0); //�ȵ�SLAK=0

    // �����ʼ��ģʽ
    CANx->MCR |= CAN_MCR_INRQ;
    while ((CANx->MSR & CAN_MSR_INAK) == 0);  //�ȵ�INAK=1

    // �Զ����߹�����Զ����ѹ���
    CANx->MCR |= CAN_MCR_ABOM;
    CANx->MCR |= CAN_MCR_AWUM;

    // FIFO0�������ж�
    CAN1->IER |= CAN_IER_FFIE0;
    // FIFO 0��Ϣ�Һ��ж�ʹ�� ���յ�һ���±��Ĵ����ж�
    // CANx->IER |= CAN_IER_FMPIE0;

    // �򿪻��ؾ�Ĭģʽ
    CANx->BTR |= CAN_BTR_LBKM;
    CANx->BTR |= CAN_BTR_SILM;

    // ����TS1��TS2
    CANx->BTR &= ~CAN_BTR_TS1;
    CANx->BTR &= ~CAN_BTR_TS2;
    CANx->BTR |= (6 - 1) << 16;
    CANx->BTR |= (3 - 1) << 20;
    //����ͬ����Ծ���  Ϊ������ͬ������λ������CANӲ����ÿλ�п����ӳ������̶��ٸ�ʱ�䵥Ԫ������
    CANx->BTR &= ~CAN_BTR_SJW;
    CANx->BTR |= (1 << 24);
    // ���ò����ʷ�Ƶ��ϵ�� BPR  ��λ������ʱ�䵥Ԫ(tq)��ʱ�䳤��   tq = (BRP[9:0]+1) x tPCLK(1/36MHz) ��Ӧ��Ƶ��1MHz  ���� 1us
    CANx->BTR &= ~CAN_BTR_BRP;
    CANx->BTR |= (36 - 1) << 0;

    // �˳���ʼ��ģʽ
    CANx->MCR &= ~CAN_MCR_INRQ;
    while ((CANx->MSR & CAN_MSR_INAK) != 0);

    /* ���ù����� */
    // �����������ʼ��ģʽ
    CANx->FMR |= CAN_FMR_FINIT;
    // ֻʹ�ù�����0   ����ģʽ0   32λ1  ��14����������(13~0)  ÿ����������x��2��32λ�Ĵ���
    CANx->FM1R &= ~CAN_FM1R_FBM0;
    CANx->FS1R |= CAN_FS1R_FSC0;
    //������Ӧ��FIFO0
    CANx->FFA1R &= ~CAN_FFA1R_FFA0;

    // ��д����ģʽ�µ�ID��mask      
    // 11λstdId  18λEXID IDE RTR 0   -> STDID ��3λ��111  //0xFFE00000
    CANx->sFilterRegister[0].FR1 = 0;  // CAN_TypeDef ����  CAN_FilterRegister_TypeDef sFilterRegister[14]
    // ����  -> ��ЩID��Ҫ����
    CANx->sFilterRegister[0].FR2 = 0;
    // ���������
    CANx->FA1R |= CAN_FA1R_FACT0;
    //�˳���������ʼ��ģʽ
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
    return freelevel; // ���ؿ����������
}


void HAL_CAN_AddTxMessage(CAN_TypeDef* CANx, uint16_t stdID, uint8_t* bytes, uint8_t length) {
    if (length > 8) return;  // ���ݳ���0-8�ֽ�
    /* �жϷ��͵�����Ϊ�� */
    // ��3������ -> ֻʹ������0 ->3��������Դ�3������
    while (HAL_CAN_GetTxMailboxesFreeLevel(CANx) == 0);

    /* �����ݷ��뵽��Ӧ������ */
    // д��׼��ʽ   ����֡
    CANx->sTxMailBox[(CANx->TSR & CAN_TSR_CODE) >> 24].TDLR = 0; //CAN_TxMailBox_TypeDef sTxMailBox[3];
    CANx->sTxMailBox[(CANx->TSR & CAN_TSR_CODE) >> 24].TDHR = 0;

    // д������
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
    // д��STDID DLC���ݳ���
    CANx->sTxMailBox[(CANx->TSR & CAN_TSR_CODE) >> 24].TDTR = length;
    CANx->sTxMailBox[(CANx->TSR & CAN_TSR_CODE) >> 24].TIR = (stdID << 21 | 1 << 0); // 1�Ƿ�����������

    /* Warning: ����Code���1  FreeLevel���2  ������Bug  ��δӰ��ʹ��*/
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
    return filllevel; //���ر�������
}

void HAL_CAN_GetRxMessage(CAN_TypeDef* CANx, CAN_RxData CAN_Rx[], uint8_t* BytesConut) {
    /* ��һ���ַ������ʼ��Ϊȫ 0��ʵ������ '\0' �ַ���
    char str[10];
    memset(str, 0, sizeof(str));  //Ҫ��Ϊ�����ַ���*/

    // ��ȡFIFO0�еı�������  FIFO0����������ģ� FIFO1δʹ��
    *BytesConut = HAL_CAN_GetRxFifoFillLevel(CANx, CAN_RX_FIFO0);
    // ѭ����ȡ������Ϣ  �����ݴ�ŵ��ṹ��������
    for (uint8_t i = 0; i < *BytesConut; i++)
    {
        // ��ruturn��ԭ����CAN_Rxһ���ṹ����������ǽṹ��
        CAN_RxData* msg = &CAN_Rx[i];
        /* 2��FIFO���У�ÿ������FIFO�����Դ��3�������ı��� */

        // ��д�ṹ���stdid
        // ��ȡ���ݵĳ��� 4λ,��ʾ���ݶΰ��������ֽ� 0~8,������Ҫ4λ
        msg->length = (CANx->sFIFOMailBox[CAN_RX_FIFO0].RDTR & CAN_RDT1R_DLC) >> 0;
        msg->stdID = (CANx->sFIFOMailBox[CAN_RX_FIFO0].RIR & CAN_RI0R_STID) >> 21; //CAN_FIFOMailBox_TypeDef sFIFOMailBox[2];

        // д����  ���֮ǰ������д��dataֵ
        memset(msg->data, 0, sizeof(msg->data));

        uint32_t lowdata = CANx->sFIFOMailBox[CAN_RX_FIFO0].RDLR;
        uint32_t highdata = CANx->sFIFOMailBox[CAN_RX_FIFO0].RDHR;
        for (uint8_t j = 0; j < msg->length; j++)
        {
            if (j < 4)
            {
                // data��8λ��,����������
                msg->data[j] = (lowdata >> j * 8);
            }
            else {
                msg->data[j] = (highdata >> (j - 4) * 8);
            }
        }
        //�ͷŵ�ǰ����    
        //��ȡ��һ���ͷ�һ�������FIFO����2�����ϵı��ģ�����FIFO���ص㣬�����Ҫ�ͷ����������ܷ��ʵ�2������
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
