#ifndef __INF_LCD_H__
#define __INF_LCD_H__
#include "stm32f10x.h"
#include "Inf_LCD_font.h"
#include "Com_Debug.h"

#define __Index(ch) (ch - ' ')

/* ����� */
#define     ColAddSet                0X2A
#define     RowAddSet                0X2B
#define     PageAddSet               0X2B
#define     WriteDataToMemory        0X2C


/* �������� */
#define LCD_W 320
#define LCD_H 480

//LCD��ַ�ṹ��
typedef struct
{
    vu16 LCD_Cmd;  // 0x6c0007fe
    vu16 LCD_Data; // 0x6c000800  (0x6c000800 - 0x6c0007fe = 2)
} LCD_TypeDef;
#define LCD_BASE        ((uint32_t)(0X6C000000 | 0x000007FE)) 
#define LCD             ((LCD_TypeDef *) LCD_BASE)
/*                   Y            N
ĩβ��������������AHBҪ����Ϊ���õ���16λ��������С������Ҫ2�ֽ�(2�ֽڶ���)�����Բ���8λ����
01101100000000000000 0 0000000000 0  //0X6C000000
00000000000000000000 0 1111111111 0  //0X000007FE
01101100000000000000 0 1111111111 0  //0X6C0007FE
01101100000000000000 1 0000000000 0  //0X6c000800
*/


/* ��ɫ���� */
#define     BackgroundColor          Black
#define     FontColor                White
#define     BROWN 			         0XBC40 //��ɫ
#define     BRRED 			         0XFC07 //�غ�ɫ
#define     GRAY  			         0X8430 //��ɫ
#define     LightPink                0xFDB8 //ǳ�ۺ�
#define     Pink                     0xFE19 //�ۺ�
#define     Crimson                  0xD8A7 //�ɺ�
#define     LavenderBlush            0xFF9E //����ĵ���ɫ
#define     PaleVioletRed            0xDB92 //�԰׵���������ɫ
#define     HotPink                  0xFB56 //����ķۺ�
#define     DeepPink                 0xF8B2 //���ɫ
#define     MediumVioletRed          0xC0B0 //���е���������ɫ
#define     Orchid                   0xDB9A //��������ɫ
#define     Thistle                  0xDDFB //��
#define     plum                     0xDD1B //����
#define     Violet                   0xEC1D //������
#define     Magenta                  0xF81F //���
#define     Fuchsia                  0xF81F //��������(�Ϻ�ɫ)
#define     DarkMagenta              0x8811 //�����ɫ
#define     Purple                   0x8010 //��ɫ
#define     MediumOrchid             0xBABA //���е�������
#define     DarkVoilet               0xD81C //��������ɫ
#define     DarkOrchid               0x9999 //��������
#define     Indigo                   0x4810 //����
#define     BlueViolet               0x895C //������������ɫ
#define     MediumPurple             0x939B //���е���ɫ
#define     MediumSlateBlue          0x7B5D //���еİ��Ұ�����ɫ
#define     SlateBlue                0x6AD9 //���Ұ�����ɫ
#define     DarkSlateBlue            0x49F1 //���Ұ�����ɫ
#define     Lavender                 0xE73F //Ѭ�²ݻ��ĵ���ɫ
#define     GhostWhite               0xFFDF //����İ�ɫ
#define     Blue                     0x001F //����
#define     MediumBlue               0x0019 //���е���ɫ
#define     MidnightBlue             0x18CE //��ҹ����ɫ
#define     DarkBlue                 0x0011 //����ɫ
#define     Navy                     0x0010 //������
#define     RoyalBlue                0x435C //�ʾ���
#define     CornflowerBlue           0x64BD //ʸ���յ���ɫ
#define     LightSteelBlue           0xB63B //������
#define     LightSlateGray           0x7453 //ǳʯ���
#define     SlateGray                0x7412 //ʯ���
#define     DoderBlue                0xD700 //������
#define     AliceBlue                0xF7DF //����˿��
#define     SteelBlue                0x4416 //����
#define     LightSkyBlue             0x867F //����ɫ
#define     SkyBlue                  0x867D //����ɫ
#define     DeepSkyBlue              0x05FF //������
#define     LightBLue                0xAEDC //����
#define     PowDerBlue               0xB71C //��ҩ��
#define     CadetBlue                0x5CF4 //��У��
#define     Azure                    0xF7FF //ε��ɫ
#define     LightCyan                0xE7FF //����ɫ
#define     PaleTurquoise            0xAF7D //�԰׵��̱�ʯ
#define     Cyan                     0x07FF //��ɫ
#define     Aqua                     0x07FF //ˮ��ɫ
#define     DarkTurquoise            0x067A //���̱�ʯ
#define     DarkSlateGray            0x2A69 //��ʯ���
#define     DarkCyan                 0x0451 //����ɫ
#define     Teal                     0x0410 //ˮѼɫ
#define     MediumTurquoise          0x4E99 //���е��̱�ʯ
#define     LightSeaGreen            0x2595 //ǳ������
#define     Turquoise                0x471A //�̱�ʯ
#define     Auqamarin                0xA500 //����\����ɫ
#define     MediumAquamarine         0x6675 //���еı���ɫ
#define     MediumSpringGreen        0x07D3 //���еĴ������ɫ
#define     MintCream                0xF7FF //��������
#define     SpringGreen              0x07EF //�������ɫ
#define     SeaGreen                 0x2C4A //������
#define     Honeydew                 0xF7FE //����
#define     LightGreen               0x9772 //����ɫ
#define     PaleGreen                0x9FD3 //�԰׵���ɫ
#define     DarkSeaGreen             0x8DF1 //�����
#define     LimeGreen                0x3666 //�����
#define     Lime                     0x07E0 //���ɫ
#define     ForestGreen              0x2444 //ɭ����
#define     Green                    0x0400 //����
#define     DarkGreen                0x0320 //����ɫ
#define     Chartreuse               0x7FE0 //���ؾ���
#define     LawnGreen                0x7FE0 //��ƺ��
#define     GreenYellow              0xAFE5 //�̻�ɫ
#define     OliveDrab                0x6C64 //�������ɫ
#define     Beige                    0xF7BB //��ɫ(ǳ��ɫ)
#define     LightGoldenrodYellow     0xFFDA //ǳ�������
#define     Ivory                    0xFFFE //����
#define     LightYellow              0xFFFC //ǳ��ɫ
#define     Yellow                   0xFFE0 //����
#define     Olive                    0x8400 //���
#define     DarkKhaki                0xBDAD //��䲼
#define     LemonChiffon             0xFFD9 //���ʱ�ɴ
#define     PaleGodenrod             0xA060 //��������
#define     Khaki                    0xF731 //���䲼
#define     Gold                     0xFEA0 //��
#define     Cornislk                 0xC000 //����ɫ
#define     GoldEnrod                0xDD24 //������
#define     FloralWhite              0xFFDE //���İ�ɫ
#define     OldLace                  0xFFBC //���δ�
#define     Wheat                    0xF6F6 //С��ɫ
#define     Moccasin                 0xFF36 //¹ƤЬ
#define     Orange                   0xFD20 //��ɫ
#define     PapayaWhip               0xFF7A //��ľ��
#define     BlanchedAlmond           0xFF59 //Ư�׵�����
#define     NavajoWhite              0xFEF5 //Navajo��
#define     AntiqueWhite             0xFF5A //�Ŵ��İ�ɫ
#define     Tan                      0xD5B1 //ɹ��
#define     BrulyWood                0xB000 //��ʵ����
#define     Bisque                   0xFF38 //(Ũ��)��֬,���ѵ�
#define     DarkOrange               0xFC60 //���ɫ
#define     Linen                    0xFF9C //���鲼
#define     Peru                     0xCC27 //��³
#define     PeachPuff                0xFED7 //��ɫ
#define     SandyBrown               0xF52C //ɳ��ɫ
#define     Chocolate                0xD343 //�ɿ���
#define     SaddleBrown              0x8A22 //����ɫ
#define     SeaShell                 0xFFBD //������
#define     Sienna                   0xA285 //������ɫ
#define     LightSalmon              0xFD0F //ǳ����(����)ɫ
#define     Coral                    0xFBEA //ɺ��
#define     OrangeRed                0xFA20 //�Ⱥ�ɫ
#define     DarkSalmon               0xECAF //������(����)ɫ
#define     Tomato                   0xFB08 //����
#define     MistyRose                0xFF3C //����õ��
#define     Salmon                   0xFC0E //����(����)ɫ
#define     Snow                     0xFFDF //ѩ
#define     LightCoral               0xF410 //��ɺ��ɫ
#define     RosyBrown                0xBC71 //õ����ɫ
#define     IndianRed                0xCAEB //ӡ�Ⱥ�
#define     Red                      0xF800 //����
#define     Brown                    0xA145 //��ɫ
#define     FireBrick                0xB104 //�ͻ�ש
#define     DarkRed                  0x8800 //���ɫ
#define     Maroon                   0x8000 //��ɫ
#define     White                    0xFFFF //����
#define     WhiteSmoke               0xF7BE //����
#define     Gainsboro                0xDEFB //Gainsboro
#define     LightGrey                0xD69A //ǳ��ɫ
#define     Silver                   0xC618 //����ɫ
#define     DarkGray                 0xAD55 //���ɫ
#define     Gray                     0x8410 //��ɫ
#define     DimGray                  0x6B4D //�����Ļ�ɫ
#define     Black                    0x0000 //��ɫ

#include "stm32f10x.h"
#include "Driver_Fsmc.h"
#include "Com_Gpio.h"
#include "Com_Delay.h"

void Inf_LCD_Init(void);
void Inf_LCD_Clear(void);
void Inf_LCD_DisplayChar(uint16_t x, uint16_t y, uint8_t ch, uint8_t fontsize);
void Inf_LCD_DisplayString(uint16_t x, uint16_t y, uint8_t* str, uint8_t fontsize);
void Inf_LCD_DisplayChineseTitle(uint16_t x, uint16_t y);
void Inf_LCD_DisplayLogo(uint16_t x, uint16_t y);
#endif /* __INF_LCD_H__ */
