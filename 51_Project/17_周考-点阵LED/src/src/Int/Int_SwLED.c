#include "Int_SwLED.h"




bit Int_SwLED_SW1()
{
    if (SW1 == 0)
    {
        Delay1ms(10);//消除抖动
        while (SW1 ==0);//等待抬起
        LED1 =~ LED1;
        return 1;
    }
    return 0;
}

bit Int_SwLED_SW2()
{
    if (SW2 == 0)
    {
        Delay1ms(10);
        while (SW2 == 0)
            ;
        LED2 = ~LED2;
        return 1;
    }
    return 0;
}
bit Int_SwLED_SW3()
{
    if (SW3 == 0)
    {
        Delay1ms(10);
        while (SW3 == 0)
            ;
        LED3 = ~LED3;
        return 1;
    }
    return 0;
}

bit Int_SwLED_SW4()
{
    if (SW4 == 0)
    {
        Delay1ms(10);
        while (SW4 == 0)
            ;
        LED4 = ~LED4;
        return 1;
    }
    return 0;
}