#include "Dri_Timer2.h"

// ���������¼��ע��Ļص���������
static u8 s_timer2_callback_count = 0;
// �������鱣�� Timer2 �Ļص�����
static Timer2_Callback s_Timer2_callbacks[MAX_CALLBACK_COUNT];

/**
 * @brief ��ʱ��2 ��ʼ��
 *
 */
void Dri_Timer2_Init()
{
    u8 i;
    // ��һ�� �򿪶�ʱ������ ------------------------------------------------------------
    // ���ж��ܿ���
    EA = 1;
    ET2 = 1;


    // �ڶ��� ѡ��ʱ������ģʽ --------------------------------------------------------
    // ����Ϊ16λ�Զ���װ��
    // TF2 = 0; //�����־ ��Ҫ�ֶ���Ϊ0
    // C_T2 = 0; //�ڲ���ʱ��
    RCLK = 0;
    TCLK = 0;
    CP_RL2 = 0;


    // ������ ��������������ĳ�ʼֵ   Timer2 ��Ӧ TH2 TL2  ------------------------------
    // �� ����ÿ����������(��������)��Ҫ�೤ʱ��        12 / 11059200 s
    // �� ���� 1 ������Ҫ�������ٴ�                    0.001 / (12 / 11059200)
    // �� �����������������ʼֵ                       65536 - 0.001 / (12 / 11059200) = 64614
    RCAP2L = 64614;
    RCAP2H = 64614 >> 8;  //���ﲻҪд����
    TH2 = RCAP2H;
    TL2 = RCAP2L;

    // ���Ĳ� ���ÿ�ʼ������������ʱ����---------------------------------------------------
    TR2 = 1;

    // ��ʼ�� �ص��������� --------------------------------------------------------------------------
    for (i = 0; i < s_timer2_callback_count; i++)
    {
        s_Timer2_callbacks[i] = NULL;
    }
}

/**
 * @brief ����ʱ��2 ע��ص�����
 *
 * @param callback Ҫע��ص�����
 * @return bit 1��ʾע��ɹ� 0��ʾע��ʧ��
 */
bit Dri_Timer2_RegisterCallback(Timer2_Callback callback)
{
    u8 i;
    // ����ͬһ���ص������ظ�ע��
    for (i = 0; i < s_timer2_callback_count; i++)
    {
        // ����ûص��������������Ѿ�����
        if (s_Timer2_callbacks[i] == callback)
        {
            return 1;
        }
    }

    if (s_timer2_callback_count < MAX_CALLBACK_COUNT)
    {
        s_Timer2_callbacks[s_timer2_callback_count++] = callback;
        // s_timer2_callback_count++;
        return 1;
    }


    return 0;
}

/**
 * @brief ע����ʱ��2�Ļص�����
 *
 * @param callback Ҫע���Ļص�����
 * @return bit 1��ʾע���ɹ� 0��ʾע��ʧ��
 */
bit Dri_Timer2_DeregisterCallback(Timer2_Callback callback)
{
    u8 i;
    bit flag = 0; // ����Ƿ�ע����ûص�����
    // �������飬�ҵ� callback
    for (i = 0; i < s_timer2_callback_count; i++)
    {

        if (flag)
        {
            // ��һ�β�ִ�����ִ��else��Ȼ��ִ��s_timer2_callback_count-1������պ�Ҳ��λ��ô���
            // ����Ԫ��ǰ��  ��Ǻ���������i����+1
            s_Timer2_callbacks[i - 1] = s_Timer2_callbacks[i];
        }
        else
        {
            if (s_Timer2_callbacks[i] == callback)
            {
                flag = 1;
            }
        }
    }

    if (flag == 1)
    {
        s_timer2_callback_count--;
    }

    return flag;
}

// ���� Timer2 ���жϷ������ �������� s_Timer2_callbacks �еĻص�����
void Dri_Timer2_Handler() interrupt 5
{
    u8 i;
    // ��������
    for (i = 0; i < s_timer2_callback_count; i++)
    {
        s_Timer2_callbacks[i](); // ����
    }

    // ��ʱ��2���жϱ�־λ��λ
    TF2 = 0;
}
