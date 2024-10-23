#include "Int_MatrixLED.h"
#include "Dri_Timer0.h"

#define SER P10
#define RCK P11
#define SCK P12

// �������飬�洢������ÿ�е���ʾ��Ϣ
static u8 s_matrix_line_pixels[8] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 };

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

    // ������ʱ��
    Dri_Timer0_Init();

    // ������LED��ˢ�º���ע��Ϊ Timer0 �Ļص�����
    Dri_Timer0_setInterval(Int_MatrixLED_Refresh);
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
 * @brief �������е�Ԫ��������ƣ�0λ�������Ԫ��
 *
 * @param new_line
 */
void Int_MatrixLED_ShiftPixels(u8 new_line)
{

    u8 i;
    // ԭ����������� ��ǰ��Ԫ�ص�ֵ��ֵ������  �Ӻ���ǰ����
    for (i = 7; i > 0; i--)
    {
        s_matrix_line_pixels[i] = s_matrix_line_pixels[i - 1];
    }

    // ��0λ�������µ�ֵ
    s_matrix_line_pixels[0] = new_line;
}

/**
 * @brief ˢ����ʾ��Ϣ ��϶�ʱ���жϣ���Ϊ��ʱ���жϵĻص�����
 *
 */
void Int_MatrixLED_Refresh()
{
    static u8 i = 0;

    // ��һ�е�ʱ����595��λ������1���Ժ������0
    if (i == 0)
    {
        SER = 1;
    }
    else
    {
        SER = 0;
    }

    // ��Ϩ��ǰ�е�LED
    P0 = 0XFF;

    // �� SER ��Ϣ������λ�Ĵ���  SCK ������
    SCK = 0;
    SCK = 1;

    // ����λ�Ĵ�������Ϣ����洢�Ĵ��� RCK ������
    RCK = 0;
    RCK = 1;

    // ���õ�ǰ�е���ʾ��Ϣ
    P0 = ~s_matrix_line_pixels[i];

    // i ����
    i++;
    // ˢ�����һ�У���ͷ����
    if (i == 8)
    {
        i = 0;
    }
}

// void Int_MatrixLED_Refresh()
// {
//     u8 i;
//     // ѭ������ˢ��
//     for (i = 0; i < 8; i++)
//     {
//         // ��һ��ѭ������595��λ������1���Ժ��ѭ������0
//         if (i == 0)
//         {
//             SER = 1;
//         }
//         else
//         {
//             SER = 0;
//         }

//         // ��Ϩ��ǰ�е�LED
//         P0 = 0XFF;

//         // �� SER ��Ϣ������λ�Ĵ���  SCK ������
//         SCK = 0;
//         SCK = 1;

//         // ����λ�Ĵ�������Ϣ����洢�Ĵ��� RCK ������
//         RCK = 0;
//         RCK = 1;

//         // ���õ�ǰ�е���ʾ��Ϣ
//         P0 = ~s_matrix_line_pixels[i];

//         // ��ʱ
//         Delay_1ms(1);
//     }
// }