#include "App_Water_Level.h"

double wl_const_k[1];   // ˮ��ģ�� б��
double wl_const_b[1];   // ˮ��ģ�� �ؾ�



/* ����ˮλ����ϵͳ  �����У�� */
void App_Water_Level_Start(void) {
    Inf_TM7711_Init();
    Inf_W25q32_Init();
    App_Water_Level_calibrate();
}

/* У��ˮλ����ϵͳ */
/**
 * @brief x����ˮ�����  У��������k��b  �����õ�y�Ϳ��Է���ˮ��x
 *
 */
void App_Water_Level_calibrate(void) {
    // У��ˮλ������ => ����y = k * x + b�е���������ֵ  
    // (1) ��һ�β���  ˮλΪ0�ĵ�ѹֵ  y1   y1 = k * 0 + b
    // (2) �ڶ��β���  ˮλΪ10�ĵ�ѹֵ y2   y2 = k * 10 + b
    // �������β����Ľ��  �ܹ������  b = y1  k = (y2-y1) / 10
    App_Display_Hint(10, 120, "�������ʾ���°�����ʼˮλУ׼");
    while (Driver_GPIO_IsKey3Pressed() == 0);  //�ȴ���������
    App_Display_ClearHint();
    App_Display_Hint(10, 120, "��һ������ˮ�ܷ��ڿ��а��°���");
    while (Driver_GPIO_IsKey3Pressed() == 0);  //�ȴ���������
    App_Display_ClearHint();

    // ��һ�β�������
    uint32_t y1 = Inf_TM7711_ReadV();

    App_Display_Hint(10, 120, "�ڶ�������ˮ�ܷ���ˮ��ʮ���״����ٴΰ��°���");
    while (Driver_GPIO_IsKey3Pressed() == 0);  //�ȴ���������
    App_Display_ClearHint();

    // ��һ�β�������
    uint32_t y2 = Inf_TM7711_ReadV();

    wl_const_b[0] = y1;
    wl_const_k[0] = (double)(y2 - y1) / 10.0;

    App_Display_Hint(10, 120, "���У�飬���Կ�ʼ����");
}

/* ֱ�Ӷ�ȡˮλ����ϵͳ�Ľ�� */
double App_Read_Water_Level(void) {
    uint32_t y = Inf_TM7711_ReadV();
    double water_level = (y - wl_const_b[0]) / wl_const_k[0];
    return (water_level >= 0) ? water_level : 0;
}
