#ifndef __DRI_GPIO_H__
#define __DRI_GPIO_H__

#include <STC89C5xRC.H>

// ·äÃùÆ÷
#define BUZZER_EN P07

// LED
#define LED_LF P24
#define LED_RF P23
#define LED_RB P22
#define LED_LB P21

// ³¬Éù²¨Ä£¿é
#define RANGE_TRIG P33
#define RANGE_ECHO P32

// Ñ­¼£
#define TRC_RR P00
#define TRC_MR P01
#define TRC_MM P02
#define TRC_ML P03
#define TRC_LL P04

// µç»úÇý¶¯
#define MOTOR_EN  P14
#define MOTOR_FAULT  P42
#define MOTOR_A1 P11
#define MOTOR_A2 P10
#define MOTOR_B1 P12
#define MOTOR_B2 P13

// ¶ÀÁ¢°´¼ü
#define KEY_SW1 P41
#define KEY_SW2 P46

#endif /* __DRI_GPIO_H__ */