#include "Com_Util.h"
#include "Dri_INT0.h"
void Dri_INT0_init() {
    // ���ж��ܿ���
    EA = 1;  //open global interrupt switch

    // �� INT0 ����
    EX0 = 1;  //enable INT0 interrupt

    // �����ⲿ�ж� INT0 ������ʽ�� 0��ʾ�͵�ƽ������1��ʾ�½��ش���
    IT0 = 1; //set INT0 interrupt type (1:Falling 0:Low level)

    // �����ⲿ�ж� INT0 ���ȼ����ѵȼ�����Ϊ1����λ0��λ1 ���ȼ���0 ��1�� 2�� 3��
    PX0 = 1;
}


// �ⲿ�ж� INT0 �ķ������
void INT0_Handler() interrupt 0
{
    // LED ����
    P00 = ~P00;
}

