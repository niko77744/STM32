#ifndef __GPIO_H__
#define __GPIO_H__

#include "stm32f10x.h"
#include <math.h>
#include <stdlib.h>

typedef enum
{
    GPIO_PIN_RESET = 0u,
    GPIO_PIN_SET
} GPIO_PinState;

#define GPIO_NUMBER 16u

#define GPIOA_CRL    *(unsigned int *)(GPIOA_BASE+0x00)//����ǿ������ת���Ǹ���ϵͳ����һ����ַ
#define GPIOA_CRH    *(unsigned int *)(GPIOA_BASE+0x04)
#define GPIOA_IDR    *(unsigned int *)(GPIOA_BASE+0x08)
#define GPIOA_ODR    *(unsigned int *)(GPIOA_BASE+0x0c)
#define GPIOA_BSRR   *(unsigned int *)(GPIOA_BASE+0x10)
#define GPIOA_BRR    *(unsigned int *)(GPIOA_BASE+0x14)
#define GPIOA_CLKR   *(unsigned int *)(GPIOA_BASE+0x18)

#define GPIO_pin_0   ((uint16_t)0x0001)  /* ѡ��pin0  */
#define GPIO_pin_1   ((uint16_t)0x0002)  /* ѡ��pin1  */   
#define GPIO_pin_2   ((uint16_t)0x0004)  /* ѡ��pin2  */     
#define GPIO_pin_3   ((uint16_t)0x0008)  /* ѡ��pin3  */      
#define GPIO_pin_4   ((uint16_t)0x0010)  /* ѡ��pin4  */      
#define GPIO_pin_5   ((uint16_t)0x0020)  /* ѡ��pin5  */      
#define GPIO_pin_6   ((uint16_t)0x0040)  /* ѡ��pin6  */      
#define GPIO_pin_7   ((uint16_t)0x0080)  /* ѡ��pin7  */      
#define GPIO_pin_8   ((uint16_t)0x0100)  /* ѡ��pin8  */      
#define GPIO_pin_9   ((uint16_t)0x0200)  /* ѡ��pin9  */      
#define GPIO_pin_10  ((uint16_t)0x0400)  /* ѡ��pin10 */     
#define GPIO_pin_11  ((uint16_t)0x0800)  /* ѡ��pin11 */     
#define GPIO_pin_12  ((uint16_t)0x1000)  /* ѡ��pin12 */     
#define GPIO_pin_13  ((uint16_t)0x2000)  /* ѡ��pin13 */     
#define GPIO_pin_14  ((uint16_t)0x4000)  /* ѡ��pin14 */     
#define GPIO_pin_15  ((uint16_t)0x8000)  /* ѡ��pin15 */     
#define GPIO_pin_A11 ((uint16_t)0xFFFF)  /* ѡ��ȫ������*/   //(11111111 11111111)b


typedef enum
{
    GPIO_Speed_10MHz = 1,   //10MHZ   (01)
    GPIO_Speed_2MHz,        //2MHZ    (10)
    GPIO_Speed_50MHz        //50MHZ   (11)

}GPIOSpeed_TypeDef;

typedef enum
{
    GPIO_Mode_AIN = 0x0,            //ģ������        (0000 0000)
    GPIO_Mode_IN_FLOATING = 0x04,   //��������        (0000 0000)
    GPIO_Mode_IPD = 0x28,           //��������        (0010 1000)
    GPIO_Mode_IPU = 0x48,           //��������        (0100 1000)
    GPIO_Mode_Out_OD = 0x14,        //��©���        (0001 0100)
    GPIO_Mode_Out_PP = 0x10,        //�������        (0001 0000)
    GPIO_Mode_AF_OD = 0x1C,         //���ÿ�©���    (0001 1100)
    GPIO_Mode_AF_PP = 0x18          //�����������    (0001 1000)
}GPIOMode_TypeDef;


typedef struct
{
    uint16_t GPIO_Pin;           /* ѡ��Ҫ���õ� GPIO ���ſ����� GPIO_Pin_ ����ĺ� */
    GPIOSpeed_TypeDef GPIO_Speed; /* ѡ��GPIO ���ŵ�����ֻ�ܸ�ֵGPIOSpeed_TypeDef �����ö��ֵ*/
    GPIOMode_TypeDef GPIO_Mode; /*  ѡ��GPIO ���ŵĹ���ģʽ�ܸ�ֵGPIOMode_TypeDef �����ö��ֵ*/
}GPIO_InitTypeDef;


void HAL_GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);

void HAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
void HAL_GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void Hal_GPIO_Mode_Selection(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOMode_TypeDef Mode);

#endif /* __GPIO_H__ */
