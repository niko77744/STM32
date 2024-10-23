/*
    ����˼·��������ʼ״̬��1������⺯��ע�ᵽ��ʱ��2(�����ϼ�ⰴ����Ӧ���ŵ�״̬��Ҳ���ǽ� 1bit��״̬������䵽status�ĵ�λ�����status=0��ʾ����8��״̬����0����ʾ�����¡�)
    �����������һ����δ�����£�����״̬�ǰ��£�����Ա������£�ͬʱ����������½���
*/


#include "Int_Key.h"
#include "Dri_Timer2.h"


// ��¼ÿ���������������ź�
u8 key1_status = 0xff;
u8 key2_status = 0xff;


// ��¼ÿ��������һ�ε�״̬��1��ʾ̧��0��ʾ����
bit sw1_last_status = 1;
bit sw2_last_status = 1;

// ��ʼ������
void Int_KeyDetection_Timer2Callback() {
    key1_status <<= 1;
    key1_status |= KEY_SW1;


    key2_status <<= 1;
    key2_status |= KEY_SW2;
}


/**
 * @brief ������ʼ��, �����Ļص�����ע�ᵽ��ʱ��2��
 */
void Int_Key_Init() {
    Dri_Timer2_RegisterCallback(Int_KeyDetection_Timer2Callback);
}

/**
 * @brief �жϰ���1��״̬
 *
 * @return 0:�����ޱ仯 1:�������ڱ����£��½��أ� 2:��������̧�������أ�
 *
 */
u8 Int_Key_GetSw1Status() {

    // ����δ������
    if (sw1_last_status == 1 && key1_status == 1)
    {
        return 0;
    }

    // �������� �½���
    if (sw1_last_status == 1 && key1_status == 0)
    {
        sw1_last_status = 0;  //�ϴ�״̬��0��ʾ���£�1��ʾ̧��
        return 1;
    }

    // ����̧�� ������
    if (sw1_last_status == 0 && key1_status == 1)
    {
        sw1_last_status = 1;
        return 2;
    }
    return 0;

}

/**
 * @brief �жϰ���2��״̬
 *
 * @return 0:�����ޱ仯 1:�������ڱ����£��½��أ� 2:��������̧�������أ�
 *
 */
u8 Int_Key_GetSw2Status() {

    // ����δ������
    if (sw2_last_status == 1 && key2_status == 1)
    {
        return 0;
    }

    // �������� �½���
    if (sw2_last_status == 1 && key2_status == 0)
    {
        sw2_last_status = 0;
        return 1;
    }

    // ����̧�� ������
    if (sw2_last_status == 0 && key2_status == 1)
    {
        sw2_last_status = 1;
        return 2;
    }
    return 0;

}

