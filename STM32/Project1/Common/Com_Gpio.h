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

#define GPIOA_CRL    *(unsigned int *)(GPIOA_BASE+0x00)//这里强制类型转化是告诉系统这是一个地址
#define GPIOA_CRH    *(unsigned int *)(GPIOA_BASE+0x04)
#define GPIOA_IDR    *(unsigned int *)(GPIOA_BASE+0x08)
#define GPIOA_ODR    *(unsigned int *)(GPIOA_BASE+0x0c)
#define GPIOA_BSRR   *(unsigned int *)(GPIOA_BASE+0x10)
#define GPIOA_BRR    *(unsigned int *)(GPIOA_BASE+0x14)
#define GPIOA_CLKR   *(unsigned int *)(GPIOA_BASE+0x18)

#define GPIO_pin_0   ((uint16_t)0x0001)  /* 选择pin0  */
#define GPIO_pin_1   ((uint16_t)0x0002)  /* 选择pin1  */   
#define GPIO_pin_2   ((uint16_t)0x0004)  /* 选择pin2  */     
#define GPIO_pin_3   ((uint16_t)0x0008)  /* 选择pin3  */      
#define GPIO_pin_4   ((uint16_t)0x0010)  /* 选择pin4  */      
#define GPIO_pin_5   ((uint16_t)0x0020)  /* 选择pin5  */      
#define GPIO_pin_6   ((uint16_t)0x0040)  /* 选择pin6  */      
#define GPIO_pin_7   ((uint16_t)0x0080)  /* 选择pin7  */      
#define GPIO_pin_8   ((uint16_t)0x0100)  /* 选择pin8  */      
#define GPIO_pin_9   ((uint16_t)0x0200)  /* 选择pin9  */      
#define GPIO_pin_10  ((uint16_t)0x0400)  /* 选择pin10 */     
#define GPIO_pin_11  ((uint16_t)0x0800)  /* 选择pin11 */     
#define GPIO_pin_12  ((uint16_t)0x1000)  /* 选择pin12 */     
#define GPIO_pin_13  ((uint16_t)0x2000)  /* 选择pin13 */     
#define GPIO_pin_14  ((uint16_t)0x4000)  /* 选择pin14 */     
#define GPIO_pin_15  ((uint16_t)0x8000)  /* 选择pin15 */     
#define GPIO_pin_A11 ((uint16_t)0xFFFF)  /* 选择全部引脚*/   //(11111111 11111111)b


typedef enum
{
    GPIO_Speed_10MHz = 1,   //10MHZ   (01)
    GPIO_Speed_2MHz,        //2MHZ    (10)
    GPIO_Speed_50MHz        //50MHZ   (11)

}GPIOSpeed_TypeDef;

typedef enum
{
    GPIO_Mode_AIN = 0x0,            //模拟输入        (0000 0000)
    GPIO_Mode_IN_FLOATING = 0x04,   //浮空输入        (0000 0000)
    GPIO_Mode_IPD = 0x28,           //下拉输入        (0010 1000)
    GPIO_Mode_IPU = 0x48,           //上拉输入        (0100 1000)
    GPIO_Mode_Out_OD = 0x14,        //开漏输出        (0001 0100)
    GPIO_Mode_Out_PP = 0x10,        //推挽输出        (0001 0000)
    GPIO_Mode_AF_OD = 0x1C,         //复用开漏输出    (0001 1100)
    GPIO_Mode_AF_PP = 0x18          //复用推挽输出    (0001 1000)
}GPIOMode_TypeDef;


typedef struct
{
    uint16_t GPIO_Pin;           /* 选择要配置的 GPIO 引脚可输入 GPIO_Pin_ 定义的宏 */
    GPIOSpeed_TypeDef GPIO_Speed; /* 选择GPIO 引脚的速率只能赋值GPIOSpeed_TypeDef 定义的枚举值*/
    GPIOMode_TypeDef GPIO_Mode; /*  选择GPIO 引脚的工作模式能赋值GPIOMode_TypeDef 定义的枚举值*/
}GPIO_InitTypeDef;


void HAL_GPIO_Init(GPIO_TypeDef* GPIOx, GPIO_InitTypeDef* GPIO_InitStruct);

void HAL_GPIO_WritePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState);
void HAL_GPIO_TogglePin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void Hal_GPIO_Mode_Selection(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, GPIOMode_TypeDef Mode);

#endif /* __GPIO_H__ */
