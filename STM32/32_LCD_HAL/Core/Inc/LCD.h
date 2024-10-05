#ifndef __LCD_H__
#define __LCD_H__

#include "fsmc.h"
#include "usart.h"
#include "W25Q32.h"



#define     LCD_W                    320
#define     LCD_H                    480

#define     LCD_BASE                 ((uint32_t)(0X6C000000 | 0x000007FE)) 
#define     LCD                      ((LCD_TypeDef *) LCD_BASE)
#define     SRAM_BANK1_4             0X6C000000
#define     LCD_ADDR_CMD             (uint16_t *)(SRAM_BANK1_4 &~ (1 << 11))
#define     LCD_ADDR_DATA            (uint16_t *)(SRAM_BANK1_4 |  (1 << 11))

#define     ColAddSet                0X2A
#define     RowAddSet                0X2B
#define     PageAddSet               0X2B
#define     WriteDataToMemory        0X2C

#define     BROWN 			         0XBC40 //×ØÉ«
#define     BRRED 			         0XFC07 //×ØºìÉ«
#define     GRAY  			         0X8430 //»ÒÉ«
#define     LightPink                0xFDB8 //Ç³·Ûºì
#define     Pink                     0xFE19 //·Ûºì
#define     Crimson                  0xD8A7 //ÐÉºì
#define     LavenderBlush            0xFF9E //Á³ºìµÄµ­×ÏÉ«
#define     PaleVioletRed            0xDB92 //²Ô°×µÄ×ÏÂÞÀ¼ºìÉ«
#define     HotPink                  0xFB56 //ÈÈÇéµÄ·Ûºì
#define     DeepPink                 0xF8B2 //Éî·ÛÉ«
#define     MediumVioletRed          0xC0B0 //ÊÊÖÐµÄ×ÏÂÞÀ¼ºìÉ«
#define     Orchid                   0xDB9A //À¼»¨µÄ×ÏÉ«
#define     Thistle                  0xDDFB //¼»
#define     plum                     0xDD1B //Àî×Ó
#define     Violet                   0xEC1D //×ÏÂÞÀ¼
#define     Magenta                  0xF81F //Ñóºì
#define     Fuchsia                  0xF81F //µÆÁýº£ÌÄ(×ÏºìÉ«)
#define     DarkMagenta              0x8811 //ÉîÑóºìÉ«
#define     Purple                   0x8010 //×ÏÉ«
#define     MediumOrchid             0xBABA //ÊÊÖÐµÄÀ¼»¨×Ï
#define     DarkVoilet               0xD81C //Éî×ÏÂÞÀ¼É«
#define     DarkOrchid               0x9999 //ÉîÀ¼»¨×Ï
#define     Indigo                   0x4810 //µåÇà
#define     BlueViolet               0x895C //Éî×ÏÂÞÀ¼µÄÀ¶É«
#define     MediumPurple             0x939B //ÊÊÖÐµÄ×ÏÉ«
#define     MediumSlateBlue          0x7B5D //ÊÊÖÐµÄ°åÑÒ°µÀ¶»ÒÉ«
#define     SlateBlue                0x6AD9 //°åÑÒ°µÀ¶»ÒÉ«
#define     DarkSlateBlue            0x49F1 //ÉîÑÒ°µÀ¶»ÒÉ«
#define     Lavender                 0xE73F //Ñ¬ÒÂ²Ý»¨µÄµ­×ÏÉ«
#define     GhostWhite               0xFFDF //ÓÄÁéµÄ°×É«
#define     Blue                     0x001F //´¿À¶
#define     MediumBlue               0x0019 //ÊÊÖÐµÄÀ¶É«
#define     MidnightBlue             0x18CE //ÎçÒ¹µÄÀ¶É«
#define     DarkBlue                 0x0011 //ÉîÀ¶É«
#define     Navy                     0x0010 //º£¾üÀ¶
#define     RoyalBlue                0x435C //»Ê¾üÀ¶
#define     CornflowerBlue           0x64BD //Ê¸³µ¾ÕµÄÀ¶É«
#define     LightSteelBlue           0xB63B //µ­¸ÖÀ¶
#define     LightSlateGray           0x7453 //Ç³Ê¯°å»Ò
#define     SlateGray                0x7412 //Ê¯°å»Ò
#define     DoderBlue                0xD700 //µÀÆæÀ¶
#define     AliceBlue                0xF7DF //°®ÀöË¿À¶
#define     SteelBlue                0x4416 //¸ÖÀ¶
#define     LightSkyBlue             0x867F //µ­À¶É«
#define     SkyBlue                  0x867D //ÌìÀ¶É«
#define     DeepSkyBlue              0x05FF //ÉîÌìÀ¶
#define     LightBLue                0xAEDC //µ­À¶
#define     PowDerBlue               0xB71C //»ðÒ©À¶
#define     CadetBlue                0x5CF4 //¾üÐ£À¶
#define     Azure                    0xF7FF //ÎµÀ¶É«
#define     LightCyan                0xE7FF //µ­ÇàÉ«
#define     PaleTurquoise            0xAF7D //²Ô°×µÄÂÌ±¦Ê¯
#define     Cyan                     0x07FF //ÇàÉ«
#define     Aqua                     0x07FF //Ë®ÂÌÉ«
#define     DarkTurquoise            0x067A //ÉîÂÌ±¦Ê¯
#define     DarkSlateGray            0x2A69 //ÉîÊ¯°å»Ò
#define     DarkCyan                 0x0451 //ÉîÇàÉ«
#define     Teal                     0x0410 //Ë®Ñ¼É«
#define     MediumTurquoise          0x4E99 //ÊÊÖÐµÄÂÌ±¦Ê¯
#define     LightSeaGreen            0x2595 //Ç³º£ÑóÂÌ
#define     Turquoise                0x471A //ÂÌ±¦Ê¯
#define     Auqamarin                0xA500 //ÂÌÓñ\±ÌÂÌÉ«
#define     MediumAquamarine         0x6675 //ÊÊÖÐµÄ±ÌÂÌÉ«
#define     MediumSpringGreen        0x07D3 //ÊÊÖÐµÄ´ºÌìµÄÂÌÉ«
#define     MintCream                0xF7FF //±¡ºÉÄÌÓÍ
#define     SpringGreen              0x07EF //´ºÌìµÄÂÌÉ«
#define     SeaGreen                 0x2C4A //º£ÑóÂÌ
#define     Honeydew                 0xF7FE //·äÃÛ
#define     LightGreen               0x9772 //µ­ÂÌÉ«
#define     PaleGreen                0x9FD3 //²Ô°×µÄÂÌÉ«
#define     DarkSeaGreen             0x8DF1 //Éîº£ÑóÂÌ
#define     LimeGreen                0x3666 //Ëá³ÈÂÌ
#define     Lime                     0x07E0 //Ëá³ÈÉ«
#define     ForestGreen              0x2444 //É­ÁÖÂÌ
#define     Green                    0x0400 //´¿ÂÌ
#define     DarkGreen                0x0320 //ÉîÂÌÉ«
#define     Chartreuse               0x7FE0 //²éÌØ¾ÆÂÌ
#define     LawnGreen                0x7FE0 //²ÝÆºÂÌ
#define     GreenYellow              0xAFE5 //ÂÌ»ÆÉ«
#define     OliveDrab                0x6C64 //éÏé­ÍÁºÖÉ«
#define     Beige                    0xF7BB //Ã×É«(Ç³ºÖÉ«)
#define     LightGoldenrodYellow     0xFFDA //Ç³Çï÷è÷ë»Æ
#define     Ivory                    0xFFFE //ÏóÑÀ
#define     LightYellow              0xFFFC //Ç³»ÆÉ«
#define     Yellow                   0xFFE0 //´¿»Æ
#define     Olive                    0x8400 //éÏé­
#define     DarkKhaki                0xBDAD //Éî¿¨Æä²¼
#define     LemonChiffon             0xFFD9 //ÄûÃÊ±¡É´
#define     PaleGodenrod             0xA060 //»ÒÇï÷è÷ë
#define     Khaki                    0xF731 //¿¨Æä²¼
#define     Gold                     0xFEA0 //½ð
#define     Cornislk                 0xC000 //ÓñÃ×É«
#define     GoldEnrod                0xDD24 //Çï÷è÷ë
#define     FloralWhite              0xFFDE //»¨µÄ°×É«
#define     OldLace                  0xFFBC //ÀÏÊÎ´ø
#define     Wheat                    0xF6F6 //Ð¡ÂóÉ«
#define     Moccasin                 0xFF36 //Â¹Æ¤Ð¬
#define     Orange                   0xFD20 //³ÈÉ«
#define     PapayaWhip               0xFF7A //·¬Ä¾¹Ï
#define     BlanchedAlmond           0xFF59 //Æ¯°×µÄÐÓÈÊ
#define     NavajoWhite              0xFEF5 //Navajo°×
#define     AntiqueWhite             0xFF5A //¹Å´úµÄ°×É«
#define     Tan                      0xD5B1 //É¹ºÚ
#define     BrulyWood                0xB000 //½áÊµµÄÊ÷
#define     Bisque                   0xFF38 //(Å¨ÌÀ)ÈéÖ¬,·¬ÇÑµÈ
#define     DarkOrange               0xFC60 //Éî³ÈÉ«
#define     Linen                    0xFF9C //ÑÇÂé²¼
#define     Peru                     0xCC27 //ÃØÂ³
#define     PeachPuff                0xFED7 //ÌÒÉ«
#define     SandyBrown               0xF52C //É³×ØÉ«
#define     Chocolate                0xD343 //ÇÉ¿ËÁ¦
#define     SaddleBrown              0x8A22 //Âí°°×ØÉ«
#define     SeaShell                 0xFFBD //º£±´¿Ç
#define     Sienna                   0xA285 //»ÆÍÁô÷É«
#define     LightSalmon              0xFD0F //Ç³ÏÊÈâ(öÙÓã)É«
#define     Coral                    0xFBEA //Éºº÷
#define     OrangeRed                0xFA20 //³ÈºìÉ«
#define     DarkSalmon               0xECAF //ÉîÏÊÈâ(öÙÓã)É«
#define     Tomato                   0xFB08 //·¬ÇÑ
#define     MistyRose                0xFF3C //±¡ÎíÃµ¹å
#define     Salmon                   0xFC0E //ÏÊÈâ(öÙÓã)É«
#define     Snow                     0xFFDF //Ñ©
#define     LightCoral               0xF410 //µ­Éºº÷É«
#define     RosyBrown                0xBC71 //Ãµ¹å×ØÉ«
#define     IndianRed                0xCAEB //Ó¡¶Èºì
#define     Red                      0xF800 //´¿ºì
#define     Brown                    0xA145 //×ØÉ«
#define     FireBrick                0xB104 //ÄÍ»ð×©
#define     DarkRed                  0x8800 //ÉîºìÉ«
#define     Maroon                   0x8000 //ÀõÉ«
#define     White                    0xFFFF //´¿°×
#define     WhiteSmoke               0xF7BE //°×ÑÌ
#define     Gainsboro                0xDEFB //Gainsboro
#define     LightGrey                0xD69A //Ç³»ÒÉ«
#define     Silver                   0xC618 //Òø°×É«
#define     DarkGray                 0xAD55 //Éî»ÒÉ«
#define     Gray                     0x8410 //»ÒÉ«
#define     DimGray                  0x6B4D //°µµ­µÄ»ÒÉ«
#define     Black                    0x0000 //ºÚÉ«

typedef struct
{
    uint16_t LCD_Cmd;  // (0X6C000000 | 0x000007FE)
    uint16_t LCD_Data;
} LCD_TypeDef;

typedef enum {
    SS = 0u,
    SL,
    LS,
    LL,
}LCD_FontSize;

void LCD_Init(void);
void LCD_Clear(uint8_t bgColor);
void Inf_LCD_WriteCmd(uint16_t cmd);
void Inf_LCD_WriteData(uint16_t data);
void LCD_DisplayChar(uint8_t x, uint8_t y, uint8_t ch, uint16_t fontColor, uint16_t bgColor);
void LCD_DisplayString(uint8_t x, uint8_t y, uint8_t* str, uint16_t fontColor, uint16_t bgColor);
void LCD_DisplayChinese(uint8_t x, uint8_t y, uint8_t* str, uint16_t fontColor, uint16_t bgColor);

#endif /* __LCD_H__ */
