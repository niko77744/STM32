/**
 * *********************************************
 * 8051 project
 * *********************************************
*/
#include "Com_Util.h"
#include "Int/Int_DigitalTube.h"
#include "Int/Int_Matrix.h"
void main()
{
    // u8 time;
    u32 temp_num = 12345678;
    SW_DigitalTube = 0;
    SW_LED = 0;
    Int_DigitalTube_SetBuffer(temp_num);
    while (1)
    {
        // ˢ�������
        Int_DigitalTube_Refresh();  //һ��Լ8ms
    }
}

