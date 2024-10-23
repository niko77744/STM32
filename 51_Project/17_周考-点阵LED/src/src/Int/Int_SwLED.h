#ifndef __INT_SWLED_H__
#define __INT_SWLED_H__

#include "Com_Util.h"

#define SW1 P42
#define SW2 P43
#define SW3 P32
#define SW4 P33
#define LED1 P00
#define LED2 P01
#define LED3 P02
#define LED4 P03

/**
 * @brief 判断sw1是否被按下
 * 
 * @return bit 
 */
bit Int_SwLED_SW1();
bit Int_SwLED_SW2();
bit Int_SwLED_SW3();
bit Int_SwLED_SW4();



#endif