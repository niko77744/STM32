#include "Dri_Extern0Interrruput.h"

//�жϷ������
void Extern0_Handler() interrupt 0
{
    P00 = ~P00;
}


/**
 * @brief �ⲿ�ж�0��ʼ��
 * 
 */
void Dri_Extern0Interruput_Init()
{
    //���жϿ���
    EA = 1;
    //���ⲿ�жϿ���
    EX0 =1;
    //�����жϴ�����ʽ
    IT0=0;
    //�����ж����ȼ�
    PX0 =1;
}