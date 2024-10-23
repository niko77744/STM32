#include "App_Remote.h"
#include "Int_Motor.h"
#include "Int_OLED.h"

/**
 * @brief Ò£¿ØÄ£¿é¿ØÖÆº¯Êý
 *
 */
void App_Remote_Control()
{
    char temp;

    // Int_OLED_DisplayStr(0, 1, "STOP");
    // Int_Motor_SetLeftSpeed(0);
    // Int_Motor_SetRightSpeed(0);

    if (Dri_UART_ReceiveChar(&temp))
    {
        switch (temp)
        {
        case 'U':
#ifdef DEBUG
            Int_OLED_DisplayStr(0, 1, "UP   ");
#endif
            Int_Motor_SetLeftSpeed(40);
            Int_Motor_SetRightSpeed(40);
            break;
        case 'D':
#ifdef DEBUG
            Int_OLED_DisplayStr(0, 1, "DOWN ");
#endif
            Int_Motor_SetLeftSpeed(-40);
            Int_Motor_SetRightSpeed(-40);
            break;
        case 'L':
#ifdef DEBUG
            Int_OLED_DisplayStr(0, 1, "LEFT ");
#endif
            Int_Motor_SetLeftSpeed(-40);
            Int_Motor_SetRightSpeed(40);
            break;
        case 'R':
#ifdef DEBUG
            Int_OLED_DisplayStr(0, 1, "RIGHT");
#endif
            Int_Motor_SetLeftSpeed(40);
            Int_Motor_SetRightSpeed(-40);
            break;
        case 'S':
#ifdef DEBUG
            Int_OLED_DisplayStr(0, 1, "STOP");
#endif
            Int_Motor_SetLeftSpeed(0);
            Int_Motor_SetRightSpeed(0);
            break;
        }
    }
}