#include "Int_DigitalTube.h"


//定义数组用于缓存数组
static Int_DigitalTube_SetBuffer[8];

void Int_DigitalTube_single (u8 dig ,u8 num)
{

    P0 =0;

    //选择位选
    P1 &= 0xC7;
    dig <<= 3;
    P1 |= dig;

    //片选数字
    P0 = num;

}

void Int_DigitalTube_DisplayNum(u32 number)
{
    //清空缓存数组
    u8 i;
    for ( i = 0; i < 8; i++)
    {
        Int_DigitalTube_SetBuffer[i]=0;
    }


    //如果number是0，直接在数码管第7位显示
    if (!number)
    {
        Int_DigitalTube_SetBuffer[7] = DigitalTube_codes[0];
        return;
    }
    
    //number不是0，逐个给缓存数组赋值，，注意数码管上从做左往右依次为数组的0~7元素
   i=7;
    while (number)
    {

            Int_DigitalTube_SetBuffer[i] = DigitalTube_codes[(number % 10)]; 
            i--;
            number /= 10;
        
    }   
}


void Int_DigitalTube_Refresh()
{
    u8 i;
    for ( i = 0; i < 8; i++)
    {
        Int_DigitalTube_single(i,Int_DigitalTube_SetBuffer[i]);
        Delay1ms(1);
    }
    return;
    
}

void Int_DigitalTube_Init()
{
    //打开数码管开关
    P34 = 0;
    P36 = 0;
    Int_DigitalTube_DisplayNum(0);
}