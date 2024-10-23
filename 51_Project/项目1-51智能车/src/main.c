/**
 * *********************************************
 * 8051 project
 * *********************************************
*/
#include "Com_Util.h"

#include "Dri_Timer2.h"
#include "Dri_UART.h"
#include "Dri_IIC.h"
#include "Dri_GPIO.h"

#include "Int_Range.h"
// #include "Int_Buzzer.h"
#include "Int_OLED.h"
#include "Int_Motor.h"
#include "Int_Sensor.h"
#include "Int_Bluetooth.h"
#include "Int_Key.h"


#include "App_Remote.h"
#include "App_Patrol.h"
#include "App_Avoidance.h"
#include "App_Mode.h"


void main()
{
    // Dri_Timer2_Init();
    // Dri_UART_Init();

    // Int_OLED_Init();
    // Int_OLED_Clear();

    // Int_Motor_Init();
    // Int_Range_Init();
    // Int_Key_Init();

    // ��ʱ����ʼ��
    Dri_Timer2_Init();
    // UART��ʼ��
    Dri_UART_Init();
    // OLED��ʼ��
    Int_OLED_Init();
    Int_OLED_Clear();
    // ��ʼ������
    if (Int_Bluetooth_Init())
    {
        Int_OLED_DisplayStr(0, 0, "BT:OK!");
    }
    else
    {
        Int_OLED_DisplayStr(0, 0, "BT:ERROR!");
        while (1)
            ;
    }
    // ������ʼ��
    Int_Key_Init();
    // ����ģ���ʼ��
    Int_Range_Init();
    // �޸���������
    /// Int_Bluetooth_SetName();
    // ���ģ���ʼ��
    Int_Motor_Init();
    // ��������ʼ��
    // Int_Buzzer_Init();
    // ģʽѡ���ʼ��
    App_Mode_Init();

    while (1)
    {
        switch (App_Mode_GetMode())
        {
        case REMOTE:
            App_Remote_Control();
            break;
        case PATROL:
            App_Patrol_Control();
            break;
        case AVOIDANCE:
            APP_AvoidanceControl();
            break;
        }
    }
}


