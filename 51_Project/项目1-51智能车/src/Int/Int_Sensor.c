/*
    Ѳ��ģ�飺
        ԭ��������Ƚ����͹�������
            �Ƚ���ԭ���Ƚ���·��ƽ�����ݽ�����VCC��GND�ĵ�ƽ��
                �����������������Ӹ�
                    ���йⷴ�䣬��������С����ѹ�󣬱Ƚ�������������跽�� GND����������Ƭ�����յ�0
                    ���޹ⷴ�䣬��������󣬵�ѹС���Ƚ��������������������VCC���Ʋ�������Ƭ�����յ�1

        ˼·��������Ȩƽ��PID
            ������ʾ��ƫ(��������)  ������ʾ��ƫ(��������)   ��ߵĵ��Ǹ������ұ���������Խ����Ȩ��Խ��

        ��������¼��һ�ε������һ����û��ɨ����

        ���������
            һ����û��ɨ���������ϴε����
            ��ɨ�赽����ɨ�赽��Ȩ�غ�/ɨ�赽�ĸ���(��Ȩƽ��)
*/

#include "Int_Sensor.h"
#include "Dri_GPIO.h"
#include "Int_OLED.h"


static u8 s_last_result;

/**
 * @brief ��ȡ���
 * @return  char 0��ʾ�����  ������ʾ��ƫ(��������)  ������ʾ��ƫ(��������)
*/
char Int_Sensor_GetError() {
    char Weight_sum = 0;
    u8 count = 0;
    if (TRC_LL || TRC_ML || TRC_MM || TRC_MR || TRC_RR) {
        if (TRC_LL)
        {
            Weight_sum += -4;
            count++;
        }

        if (TRC_ML)
        {
            Weight_sum += -2;
            count++;
        }

        if (TRC_MM)
        {
            Weight_sum += 0;
            count++;
        }

        if (TRC_MR)
        {
            Weight_sum += 2;
            count++;
        }

        if (TRC_RR)
        {
            Weight_sum += 4;
            count++;
        }
        s_last_result = Weight_sum / count;
    }
    return s_last_result;
}

