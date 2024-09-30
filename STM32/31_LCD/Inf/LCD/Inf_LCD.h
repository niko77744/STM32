#ifndef __INF_LCD_H__
#define __INF_LCD_H__

#include "Driver_FSMC.h"
#include "Driver_USART.h"
#include "Com_Delay.h"
#include "GPIO.h"

#define __GetIndex(index) (index - ' ')

typedef enum {
    SS = 0u,
    SL,
    LS,
    LL,
}LCD_FontSize;

//////////////////////////////////////////////////////////////////////////////////	 
//-----------------LCD�˿ڶ���---------------- 
//LCD��Ҫ������
#define LCD_W 320
#define LCD_H 480

//LCD��ַ�ṹ��
typedef struct
{
    vu16 LCD_Cmd;  // (0X6C000000 | 0x000007FE)
    vu16 LCD_Data; // 
} LCD_TypeDef;
//ʹ��NOR/SRAM�� Bank1.sector4,��ַλHADDR[27,26]=11 A10��Ϊ�������������� 
//ע������ʱSTM32�ڲ�������һλ����! 			    
#define LCD_BASE        ((uint32_t)(0X6C000000 | 0x000007FE)) 
#define LCD             ((LCD_TypeDef *) LCD_BASE)

#define SRAM_BANK1_4 0X6C000000
// #define LCD_ADDR_CMD  (uint16_t *)(SRAM_BANK1_4 | 0x000007FE)
// #define LCD_ADDR_DATA (uint16_t *)(SRAM_BANK1_4 | 0x00000FFE)

#define LCD_ADDR_CMD  (uint16_t *)(SRAM_BANK1_4 &~ (1 << 11))
#define LCD_ADDR_DATA (uint16_t *)(SRAM_BANK1_4 |  (1 << 11))

/*                   Y            N
01101100000000000000 0 0000000000 0  //0X6C000000
00000000000000000000 0 1111111111 0  //0X000007FE
01101100000000000000 0 1111111111 0  //0X6C0007FE
01101100000000000000 1 0000000000 0  //0X6c000800
*/
/*
LCD_Cmd = 6c0007fe  +2���ֽ�  011111111110
LCD_Data = 6c000800
LCD_ADDR_CMD = 6c000000
LCD_ADDR_DATA = 6c000800
*/

//////////////////////////////////////////////////////////////////////////////////
//������ɫ
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //��ɫ
#define BRRED 			 0XFC07 //�غ�ɫ
#define GRAY  			 0X8430 //��ɫ

//GUI��ɫ
#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
//������ɫΪPANEL����ɫ 

#define LIGHTGREEN     	 0X841F //ǳ��ɫ
//#define LIGHTGRAY        0XEF5B //ǳ��ɫ(PANNEL)
#define LGRAY 			 0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ

#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)

/* ����� */

#define ColAddSet 0X2A
#define RowAddSet 0X2B
#define PageAddSet 0X2B
#define WriteDataToMemory 0X2C


/* 1.�������� */
void Inf_LCD_Init(void);
void Inf_LCD_Reset(void);
void Inf_LCD_BGOn(void);
void Inf_LCD_BGOff(void);
void Inf_LCD_RegConfig(void);
void Inf_LCD_WriteCmd(uint16_t cmd);
void Inf_LCD_WriteData(uint16_t data);
uint16_t Inf_LCD_ReadData(void);

/* 2.���Զ�ȡID */
uint32_t Inf_LCD_ReadID(void);

/* 3.����Ļ��ʾ�����Ϣ */
void Inf_LCD_Address_Set(uint16_t x, uint16_t y, uint16_t width, uint16_t hight);
void Inf_LCD_Clear(uint16_t bgc);
void Inf_LCD_FillBgc(uint16_t x, uint16_t y, uint16_t width, uint16_t hight, uint16_t bgc);
void Inf_LCD_DisplayChar(uint16_t x, uint16_t y, uint16_t FontSize, uint8_t ch, uint16_t fontColor, uint16_t bgc);
void Inf_LCD_ShowAsciiChar(uint16_t x, uint16_t y, uint16_t h, uint8_t c, uint16_t fColor, uint16_t bgColor);


#endif /* __INF_LCD_H__ */
