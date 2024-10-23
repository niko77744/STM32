/*
    Ŀ�꣺�ѳ������͵���������
    ˼·��
        1.����main��������
        2.����������أ����С��300mm����ʼת�򣬲����Ҫһֱ���ã��������Ҫһֱ���վ���
            Int_Range_Init�Ѿ������ע�����ʱ��2
            �ж� < 300mm ת��
            ���� ֱ��
*/
#include "App_Avoidance.h"
#include "Int_Motor.h"
#include "Int_Range.h"

static u16 range;
/**
 * @brief ���Ͽ��ƺ���
 */
void APP_AvoidanceControl() {
    range = Int_Range_GetRange();
#ifdef DEBUG
    Int_OLED_DisplayNum(1, 0, range);
#endif

    if (range > 300)
    {
#ifdef DEBUG
        Int_OLED_DisplayStr(1, 1, "Go Straight!");
#endif
        Int_Motor_SetLeftSpeed(40);
        Int_Motor_SetRightSpeed(40);

    }
    else {
#ifdef DEBUG
        Int_OLED_DisplayStr(1, 2, "Turn Right!");
#endif
        Int_Motor_SetLeftSpeed(10);
        Int_Motor_SetRightSpeed(-10);
    }
}