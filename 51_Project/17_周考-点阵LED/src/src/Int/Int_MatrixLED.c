#include "Int_MatrixLED.h"
#include "Dri_Tmer0Interruput.h"





// ���建�����鴢��������Ϣ
static u8 s_buffers[8];


/**
 * @brief ��������ʼ��
 *
 */
void Int_MatrixLED_Init()
{
    u8 i;
    // �ر�LED������ܡ��򿪵�����
    P34 = 0; // LED�ߵ�ƽ��Ч
    P36 = 1; // ����ܵ͵�ƽ��Ч
    P35 = 0; // �������͵�ƽ��Ч
    // �ر����������ź�
    P0 = 0;

    // ��ջ����������Ϣ
    for (i = 0; i < 8; i++)
    {
        s_buffers[i] = 0;
    }

    Dri_Timer0Interrupt_Init();
    //ʱ���ж�ע��ˢ�º���
    Dri_Timer0Interrupt_RegisiterFunction(Int_MatrixLED_Refersh);
}

/**
 * @brief ��������Ϣ�������������
 *
 * @param pixel ������Ϣ
 */
void Int_MatrixLED_SetPixel(u8 *pixel)
{
    u8 i;
    for (i = 0; i < 8; i++)
    {
        s_buffers[i] = pixel[i];
    }
}

/**
 * @brief �����ˢ�º���
 *
 */
void Int_MatrixLED_Refersh()
{
    //���徲̬����������ʱ���жϵ���ʱ����
    static u8 i=0;

    //����i��ֵ��SER���и�ֵ������i=0ʱ��SER=0
    if (!i)SER =1; 
    else SER = 0;

    //ˢ������
    P0  = 0xFF;
    SCK = 0;
    SCK = 1;
    RCK = 0;
    RCK = 1;
    P0 = ~s_buffers[i];

    //��ˢ�µ����1�У�������ʼ��
    i++;
    if (i==8)i=0;
    

    // u8 i;
    // // �ڴ�������˿���������1
    // SER = 1;
    // // ������λ�Ĵ�����λ��0000 0001
    // SCK = 0;
    // SCK = 1;
    // // �ڴ�������˿���������0
    // SER = 0;

    // for (i = 0; i < 8; i++)
    // {
    //     // �����������ݵ�Ӱ��
    //     P0 = 0xFF;

    //     // ������洢�Ĵ��������
    //     RCK = 0;
    //     RCK = 1;
    //     // ��ʾÿ�е�������Ϣ
    //     P0 = ~s_buffers[i];

    //     // ������λ�Ĵ�����λ��0000 0010
    //     SCK = 0;
    //     SCK = 1;
    // }
    // if (i == 8)i =0;
    
}


/**
 * @brief �ı仺�������е�Ԫ��
 * 
 * @param line Ϊ�����е���λԪ�ظ�ֵ
 */
void Int_MatrixLE_ShiftPixel(u8 line)
{
    u8 i;

    for ( i = 7; i > 0; i--)
    {
        //�����е�Ԫ�غ��ƣ���ʱ��һ��Ԫ���൱�ڿճ���
        s_buffers[i] = s_buffers[i-1];
    }
    //Ϊ��λԪ�ظ�ֵ
    s_buffers[0] = line;
}

// /**
//  * @brief ���Ļ��������ڵ�Ԫ��
//  * @param pic ��ά����
//  */
// void Int_Matrix_ChangeBuffer(u8 *pic)
// {
//     staic u8 i =0;
//     s_buffers = pic+i;
//     i++;
//     if (i == 4)i=0;

// }