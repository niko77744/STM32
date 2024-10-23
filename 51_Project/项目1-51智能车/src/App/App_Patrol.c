/*
    PID�Ż���
        ��������ϵ��KP * ���E[k]��ֻ��ƽ�Ŀ��ֵ���޷�����Ŀ��ֵ
        ���֣���ϵ��KI * �������ĺ�SUM(E[k])�����䳬��Ŀ��ֵ  ����ʱ������ƣ����Сƫ��ϱ����֣�������Խ��Խ��
        ΢�֣���ϵ��KD * (�������-�ϴ����)(E[k]-E[k-1]) ���Ϊ��ƫֵ����һ�� ��Ԥ������
        PID ������Ϊ����������Ҫ���ϵļ��㡣����С��Ŀǰ��ƫ(�ұ�������)����Ҫ������̬����ô������ǰ����(+PID)�����ַ������(-PID)����ʱPIDΪ������������������̬�������ƫ(����Ǹ���)������+PID������PID�Ǹ�����ʵ���Ƿ�������������١�

    ����ʵ��:
        ��������ֻ�ܵ���
        ����PID�����ּ�ֵ,���������ܴ���80(�����ת�ٶ�-���ת�ٶ�)������ͬ������̫�󣬷���������ͷ

*/

#include "App_Patrol.h"
#include "Int_Sensor.h"  //��������ģ�飬���������ļ�Ȩƽ�� Int_Sensor_GetError
#include "Int_Motor.h"
#include "Int_OLED.h"

#define KP 1000  //��������С����������
#define KI 1
#define KD 600

// ��¼��һ�����
char last_error;
// ��¼�������
char now_error;
// ��¼����
int sum_error;



int App_Patrol_GetPID() {
    int result;
    now_error = Int_Sensor_GetError();
    // ���ֲ��֣� 
    sum_error += now_error;
    // ���ƻ������ֵint
    if (sum_error > 2000)
    {
        sum_error = 2000;
    }
    if (sum_error < -2000)
    {
        sum_error = -2000;
    }

    result = KP * now_error + KI * sum_error + KD * (now_error - last_error);

    // ���������ݸ���һ�����
    last_error = now_error;


    // ������
    result /= 50;  // ��������С����������,�ٳ����������Ҳ��ܴ���80(�����ת�ٶ�-���ת�ٶ�)
    if (result > 80)
    {
        result = 80;
    }
    if (result < -80)
    {
        result = -80;
    }

    return result;
}


/**
 * @brief Ѳ��ģʽ�Ŀ��ƺ���
 */
void App_Patrol_Control()
{

    char pid = App_Patrol_GetPID();

    Int_Motor_SetLeftSpeed(40 + pid);
    Int_Motor_SetRightSpeed(40 - pid);
}
