#include "App_Mode.h"
#include "Dri_Timer2.h"
#include "Int_OLED.h"
#include "Int_Key.h"
#include "Int_Motor.h"

// �������������ѡ���ģʽ Ĭ����ң��ģʽ
static Enum_Mode s_mode = REMOTE;
// ���嵹��ʱ��ֵ
static u16 down_count = 0;
// ���嵹��ʱ��־λ
static bit is_down = 0;
// ������Ļ��ձ�־λ
static bit is_oled_clear = 0;

// �ص����� ��ʱ��2�����ڵ���ʱ3s
void App_Mode_Timer2Callback()
{
    if (is_down)
    {
        down_count--;
    }
}

/**
 * @brief ģʽѡ���ʼ��
 */
void App_Mode_Init()
{
    // Ĭ��ң��ģʽ
    s_mode = REMOTE;
    // ��ʼ��ʱ
    is_down = 1;
    down_count = 4000;
    // ������ʾ��Ļ��Ϣ
    is_oled_clear = 1;

    // �ص�����ע��
    Dri_Timer2_RegisterCallback(App_Mode_Timer2Callback);
}

/**
 * @brief ���ذ������º���ѡ���ģʽ
 * @return ģʽ
 */
Enum_Mode App_Mode_GetMode()
{
    // �жϰ����Ƿ���
    if (Int_Key_GetSw1Status() == 1)
    {
        // ֹͣ���
        Int_Motor_SetLeftSpeed(0);
        Int_Motor_SetRightSpeed(0);

        // �л����¸�ģʽ
        s_mode++;
        if (s_mode > AVOIDANCE)
        {
            s_mode = REMOTE;
        }

        // �����Ļ����
        is_oled_clear = 1;

        // ���õ���ʱ����ʼֵ
        is_down = 1;
        down_count = 4000;
    }


    // ��Ļ��ʾģʽ
    if (is_oled_clear)
    {
        Int_OLED_Clear();

        switch (s_mode)
        {
        case REMOTE:
            Int_OLED_DisplayStr(0, 0, "Mode:REMOTE");
            break;
        case PATROL:
            Int_OLED_DisplayStr(0, 0, "Mode:PATROL");
            break;
        case AVOIDANCE:
            Int_OLED_DisplayStr(0, 0, "Mode:AVOIDANCE");
            break;
        }

        is_oled_clear = 0;
    }

    // ��Ļ��ʾ����ʱ
    if (is_down)
    {
        Int_OLED_DisplayNum(0, 1, (down_count / 1000) + 1);
        if (down_count < 100)
        {
            Int_OLED_DisplayStr(0, 1, "GO!");
            is_down = 0;
        }

        return STOP;
    }


    // ����û�а��£������ϴε�ģʽ
    return s_mode;
}