#include "Int_MatrixLED.h"
#include "Dri_Timer.h"
#include "Com_Util.h"

// �������飬�洢������ÿ�е���ʾ��Ϣ
static s_matrix_line_pixels[8];

/**
 * @brief ����LED��ʼ��
 *
 */
void Int_MatrixLED_Init(void)
{
    // �ر���ˮ��,1��
    P34 = 0;
    // �ر�����ܣ�0��
    P36 = 1;
    // �򿪵�������0��
    P35 = 0;

    Dri_Timer0_Init();
    Dri_Timer0_setInterval(Int_MatrixLED_Refresh, 1000);
}

/**
 * @brief ���õ�����Ҫ��ʾ����Ϣ �� �洢������ÿ�е���ʾ��Ϣ �����鸳ֵ
 *
 * @param pixels ��������Ϣ�����ȱ�����8��ÿ��Ԫ�ر�����8bit����
 */
void Int_MatrixLED_SetPixels(u8 pixels[8])
{
    u8 i;
    // �� s_matrix_line_pixels ��ֵ
    for (i = 0; i < 8; i++)
    {
        s_matrix_line_pixels[i] = pixels[i];
    }
}

/**
 * @brief ˢ����ʾ��Ϣ ��϶�ʱ���жϣ���Ϊ��ʱ���жϵĻص�����
 *
 */
void Int_MatrixLED_Refresh()
{
    static u8 i = 0;


    // ��Ϩ��ǰ�е�LED
    // P0 = 0XFF;
    // ���õ�ǰ�е���ʾ��Ϣ
    P0 = ~s_matrix_line_pixels[i];

    // ��һ�е�ʱ����595��λ������1���Ժ������0
    if (i == 0)
    {
        SER = 1;
    }
    else
    {
        SER = 0;
    }

    // �� SER ��Ϣ������λ�Ĵ���  SCK ������
    SCK = 0;
    SCK = 1;
    SCK = 0;

    // ����λ�Ĵ�������Ϣ����洢�Ĵ��� RCK ������
    RCK = 0;
    RCK = 1;
    RCK = 0;

    // i ����
    i++;
    // ˢ�����һ�У���ͷ����
    if (i == 8)
    {
        i = 0;
    }
}