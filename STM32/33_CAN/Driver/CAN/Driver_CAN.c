#include "Driver_CAN.h"

void Driver_CAN_Init(void) {
    RCC->APB1ENR |= RCC_APB1ENR_CAN1EN;
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;

    AFIO->MAPR |= AFIO_MAPR_CAN_REMAP_1;
    AFIO->MAPR &= ~AFIO_MAPR_CAN_REMAP_0;

    //PB9(CAN_Tx)������������� PB8(CAN_Rx): �������� 
    Hal_GPIO_Mode_Selection(GPIOB, GPIO_pin_9, GPIO_Mode_AF_PP);
    Hal_GPIO_Mode_Selection(GPIOB, GPIO_pin_8, GPIO_Mode_IN_FLOATING);

    /* ����CAN�Ĵ��� */
    // �˳�˯��ģʽ
    CAN1->MCR &= ~CAN_MCR_SLEEP;
    while ((CAN1->MCR & CAN_MSR_SLAK) != 0);  //�ȵ�SLAK=0

    // �����ʼ��ģʽ
    CAN1->MCR |= CAN_MCR_INRQ;
    while ((CAN1->MCR & CAN_MSR_INAK) == 0);  //�ȵ�INAK=1

    // �Զ����߹�����Զ����ѹ���
    CAN1->MCR |= CAN_MCR_ABOM;
    CAN1->MCR |= CAN_MCR_AWUM;

    // �򿪻��ؾ�Ĭģʽ
    CAN1->BTR |= CAN_BTR_SILM; //Silent mode
    CAN1->BTR |= CAN_BTR_SILM; //Loop back mode

    // ���ò����ʷ�Ƶ��ϵ�� BPR  ��λ������ʱ�䵥Ԫ(tq)��ʱ�䳤��   tq = (BRP[9:0]+1) x tPCLK(1/36MHz) ��Ӧ��Ƶ��1MHz  ���� 1us
    CAN1->BTR &= ~CAN_BTR_BRP;
    CAN1->BTR |= (35 << 0);

    // ����TS1��TS2
    CAN1->BTR &= ~CAN_BTR_TS1;  //4λ
    CAN1->BTR &= ~CAN_BTR_TS2;  //3λ
    CAN1->BTR |= (5 << 16);
    CAN1->BTR |= (2 << 20);

    CAN1->BTR |= CAN_BTR_SJW; //����ͬ����Ծ���  Ϊ������ͬ������λ������CANӲ����ÿλ�п����ӳ������̶��ٸ�ʱ�䵥Ԫ������

    // �˳���ʼ��ģʽ
    CAN1->MCR &= ~CAN_MCR_INRQ;
    while ((CAN1->MCR & CAN_MSR_INAK) != 0);  //�ȵ�INAK=0

    /* ���ù����� */
    // �����������ʼ��ģʽ
    CAN1->FMR |= CAN_FMR_FINIT;

    // ֻʹ�ù�����0   ����ģʽ0   32λ1  ��14����������(13~0)  ÿ����������x��2��32λ�Ĵ���
    CAN1->FM1R &= ~CAN_FM1R_FBM0;
    CAN1->FS1R |= CAN_FS1R_FSC0;  //scale

    //������Ӧ��FIFO0
    CAN1->FFA1R &= ~CAN_FFA1R_FFA0;

    // ��д����ģʽ�µ�ID��mask      
    // 11λstdId  18λEXID IDE RTR 0
    CAN1->sFilterRegister[0].FR1 = 0;  // CAN_TypeDef ����  CAN_FilterRegister_TypeDef sFilterRegister[14]
    // ����  -> ��ЩID��Ҫ����
    CAN1->sFilterRegister[0].FR2 = 0;

    // ���������
    CAN1->FA1R |= CAN_FA1R_FACT0;

    //�˳���������ʼ��ģʽ
    CAN1->FMR &= ~CAN_FMR_FINIT;
}

void Driver_CAN_SendBytes(uint16_t stdID, uint8_t* bytes, uint8_t length) {
    // ���ݳ���0-8�ֽ�
    if (length > 8) return;

    /* �жϷ��͵�����Ϊ�� */
    // ��3������ -> ֻʹ������0 ->3��������Դ�3������
    while ((CAN1->TSR & CAN_TSR_TME0) == 0);  //Transmit mailbox 0 empty ������0��û�еȴ����͵ı���ʱ��Ӳ���Ը�λ�á�1����

    /* �����ݷ��뵽��Ӧ������ */
    // д��׼��ʽ   ����֡
    CAN1->sTxMailBox[0].TIR &= ~CAN_TI0R_IDE; //CAN_TxMailBox_TypeDef sTxMailBox[3];
    CAN1->sTxMailBox[0].TIR &= ~CAN_TI0R_RTR;

    // д��STDID
    CAN1->sTxMailBox[0].TIR &= ~CAN_TI0R_STID;
    CAN1->sTxMailBox[0].TIR |= stdID << 21;

    // д��DLE���ݳ��� (Data length code)
    CAN1->sTxMailBox[0].TDTR &= ~CAN_TDT0R_DLC;
    CAN1->sTxMailBox[0].TDTR |= (length << 0);

    // д������
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

    // ������������  ����������á�1��������������������ݡ������ݷ�����ɣ�����Ϊ��ʱ��Ӳ�������塯0����
    CAN1->sTxMailBox[0].TIR |= CAN_TI0R_TXRQ;
}
void Driver_CAN_ReceiveBytes(CAN_RxData CAN_Rx[], uint8_t* BytesConut) {
    /* ��һ���ַ������ʼ��Ϊȫ 0��ʵ������ '\0' �ַ���
    char str[10];
    memset(str, 0, sizeof(str));  //Ҫ��Ϊ�����ַ���*/

    // ��ȡFIFO0�еı�������
    *BytesConut = (CAN1->RF0R & CAN_RF0R_FMP0);


    // ѭ����ȡ������Ϣ  �����ݴ�ŵ��ṹ��������
    for (uint8_t i = 0; i < *BytesConut; i++)
    {
        CAN_RxData* msg = &CAN_Rx;

        /* 2��FIFO���У�ÿ������FIFO�����Դ��3�������ı��� */

       // ��д�ṹ���stdid
        msg->stdID = (CAN1->sFIFOMailBox[0].RIR & CAN_RI0R_STID) >> 21;  //CAN_FIFOMailBox_TypeDef sFIFOMailBox[2];
        // ��ȡ���ݵĳ���
        msg->length = (CAN1->sFIFOMailBox[0].RDTR & CAN_RDT0R_DLC) >> 0;


        // д����  ���֮ǰ������д��dataֵ
        memset(msg->data, 0, sizeof(msg->data));

        for (uint8_t j = 0; j < msg->length; j++)
        {

        }
    }

}
