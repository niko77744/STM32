#include "App_Water_Level.h"



/* ����ˮλ����ϵͳ  �����У�� */
void App_Water_Level_Start(void) {
    Driver_GPIO_TM7711_Init();
    Inf_W25q32_Init();
    App_Water_Level_calibrate();
}

/* У��ˮλ����ϵͳ */
void App_Water_Level_calibrate(void) {
    // У��ˮλ������ => ����y = a * x + b�е���������ֵ
    // (1) ��һ�β���  ˮλΪ0�ĵ�ѹֵ  y1   y1 = a * 0 + b
    // (2) �ڶ��β���  ˮλΪ10�ĵ�ѹֵ y2   y2 = a * 10 + b
    // �������β����Ľ��  �ܹ������  b = y1  a = (y2-y1) / 10
    
}

/* ֱ�Ӷ�ȡˮλ����ϵͳ�Ľ�� */
double App_Read_Water_Level(void) {
    return;
}
