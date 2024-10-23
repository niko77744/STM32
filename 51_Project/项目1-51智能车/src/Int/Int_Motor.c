/*
    ���ԭ��
        ת���Ŀ��ƣ�ͬһ������������Ʋ�
        ת���ٶȵĿ��ƣ�����ռ�ձ�, ����һ�������PWM�ߵͣ���һ��0���γɵ�ѹ��

    ����ʵ�֣�
        �ĸ����������ַ��������ٶȣ����ַ��������ٶ�
        ��ʼ����
            ע��Timer2�Ļص�������ʵ�ֿ���ռ�ձ�
        �ص�������
            ͨ���ٶȺ����õ�����ͨ������ִ�д�������ռ�ձȣ�ִ�д���ߵ�ƽ
            // ����  A1��  A2��  flag = 1
            // ����  A1��  A2��  flag = 0
        �����ٶȣ����Խ��ܸ�����������
        �����ٶȣ����Խ��ܸ�����������

        ���Դ��룺
        Dri_Timer2_Init();
        Int_Motor_Init();

        Int_Motor_SetLeftSpeed(40);
        Delay_1ms(1000);
        Int_Motor_SetLeftSpeed(-40);
        Delay_1ms(1000);
        Int_Motor_SetLeftSpeed(0);
        Int_Motor_SetRightSpeed(40);
        Delay_1ms(1000);
        Int_Motor_SetRightSpeed(-40);
        Delay_1ms(1000);
        Int_Motor_SetRightSpeed(0);
*/

#include "Int_Motor.h"
#include "Dri_Timer2.h"
#include "MATH.H"

static u8 s_LeftWheelSpeed = 0;  // �趨40msһ�����ڣ�ֵ������40ms�ڸߵ�ƽ��ʱ��
static u8 s_RightWheelSpeed = 0;

static bit s_LeftWheelDirection = 0;  // 1��ǰ 0���  ���ò���ת��
static bit s_RightWheelDirection = 0;

void Int_Timer2_MotorCallBack() {
    // ���ö�ʱ��2��������ռ�ձ� 
    static u8 count;
    if (count == 40)
    {
        count = 0;
    }
    count++;

    if (count < s_LeftWheelSpeed)
    {
        // ����  A1��  A2��  flag = 1
        // ����  A1��  A2��  flag = 0
        MOTOR_A1 = s_LeftWheelDirection;
        MOTOR_A2 = !s_LeftWheelDirection;
    }
    else {
        MOTOR_A1 = 0;
        MOTOR_A2 = 0;
    }

    if (count < s_RightWheelSpeed)
    {
        // ����  A1��  A2��  flag = 1
        // ����  A1��  A2��  flag = 0
        MOTOR_B1 = s_RightWheelDirection;
        MOTOR_B2 = !s_RightWheelDirection;
    }
    else {
        MOTOR_B1 = 0;
        MOTOR_B2 = 0;
    }
}

void Int_Motor_Init() {
    MOTOR_A1 = 0;
    MOTOR_A2 = 0;
    // ��MotorCallBackע�ᵽ��ʱ��2��Timer2�ĳ�ʼ������������ͳһ��ʼ��
    Dri_Timer2_RegisterCallback(Int_Timer2_MotorCallBack);
}

void Int_Motor_SetLeftSpeed(char speed) {
    // ���Խ��ո�������ʾ����
    s_LeftWheelDirection = speed > 0 ? 1 : 0;
    speed = abs(speed);
    if (speed > 40)
    {
        speed = 40;
    }
    s_LeftWheelSpeed = speed;
}

void Int_Motor_SetRightSpeed(char speed) {
    // ���Խ��ո�������ʾ����
    s_RightWheelDirection = speed > 0 ? 1 : 0;
    speed = abs(speed);
    if (speed > 40)
    {
        speed = 40;
    }
    s_RightWheelSpeed = speed;
}