/*
 * @Date: 2024-10-21 14:06:40
 * @LastEditTime: 2024-10-23 16:25:01
 * @FilePath: \Project1\User\main.c
 * @Description: 测量水质水位，并显示到LCD上
 */

#include "Com_Debug.h"
#include "Com_Delay.h"
#include "App_Display.h"
#include "App_Water_Level.h"
uint8_t level_buffer[128];
int main(int argc, char const* argv[])
{
    Debug_Init();
    App_Display_Init();
    App_Display_BackGround();
    App_Water_Level_Start();

    while (1) {
        double water_lever = App_Read_Water_Level();
        sprintf((char*)level_buffer, "WaterLevel = %.2lfcm      ", water_lever);
        App_Dispaly_Message(10, 120, level_buffer);
        Delay_ms(100);
    }
}


