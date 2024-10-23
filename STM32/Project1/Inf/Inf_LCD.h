#ifndef __INF_LCD_H__
#define __INF_LCD_H__
#include "stm32f10x.h"
#include "Inf_LCD_font.h"
#include "Com_Debug.h"

#define __Index(ch) (ch - ' ')

/* 命令集合 */
#define     ColAddSet                0X2A
#define     RowAddSet                0X2B
#define     PageAddSet               0X2B
#define     WriteDataToMemory        0X2C


/* 参数集合 */
#define LCD_W 320
#define LCD_H 480

//LCD地址结构体
typedef struct
{
    vu16 LCD_Cmd;  // 0x6c0007fe
    vu16 LCD_Data; // 0x6c000800  (0x6c000800 - 0x6c0007fe = 2)
} LCD_TypeDef;
#define LCD_BASE        ((uint32_t)(0X6C000000 | 0x000007FE)) 
#define LCD             ((LCD_TypeDef *) LCD_BASE)
/*                   Y            N
末尾不能是奇数，是AHB要求，因为配置的是16位，所以最小访问需要2字节(2字节对齐)，所以不能8位访问
01101100000000000000 0 0000000000 0  //0X6C000000
00000000000000000000 0 1111111111 0  //0X000007FE
01101100000000000000 0 1111111111 0  //0X6C0007FE
01101100000000000000 1 0000000000 0  //0X6c000800
*/


/* 颜色集合 */
#define     BackgroundColor          Black
#define     FontColor                White
#define     BROWN 			         0XBC40 //棕色
#define     BRRED 			         0XFC07 //棕红色
#define     GRAY  			         0X8430 //灰色
#define     LightPink                0xFDB8 //浅粉红
#define     Pink                     0xFE19 //粉红
#define     Crimson                  0xD8A7 //猩红
#define     LavenderBlush            0xFF9E //脸红的淡紫色
#define     PaleVioletRed            0xDB92 //苍白的紫罗兰红色
#define     HotPink                  0xFB56 //热情的粉红
#define     DeepPink                 0xF8B2 //深粉色
#define     MediumVioletRed          0xC0B0 //适中的紫罗兰红色
#define     Orchid                   0xDB9A //兰花的紫色
#define     Thistle                  0xDDFB //蓟
#define     plum                     0xDD1B //李子
#define     Violet                   0xEC1D //紫罗兰
#define     Magenta                  0xF81F //洋红
#define     Fuchsia                  0xF81F //灯笼海棠(紫红色)
#define     DarkMagenta              0x8811 //深洋红色
#define     Purple                   0x8010 //紫色
#define     MediumOrchid             0xBABA //适中的兰花紫
#define     DarkVoilet               0xD81C //深紫罗兰色
#define     DarkOrchid               0x9999 //深兰花紫
#define     Indigo                   0x4810 //靛青
#define     BlueViolet               0x895C //深紫罗兰的蓝色
#define     MediumPurple             0x939B //适中的紫色
#define     MediumSlateBlue          0x7B5D //适中的板岩暗蓝灰色
#define     SlateBlue                0x6AD9 //板岩暗蓝灰色
#define     DarkSlateBlue            0x49F1 //深岩暗蓝灰色
#define     Lavender                 0xE73F //熏衣草花的淡紫色
#define     GhostWhite               0xFFDF //幽灵的白色
#define     Blue                     0x001F //纯蓝
#define     MediumBlue               0x0019 //适中的蓝色
#define     MidnightBlue             0x18CE //午夜的蓝色
#define     DarkBlue                 0x0011 //深蓝色
#define     Navy                     0x0010 //海军蓝
#define     RoyalBlue                0x435C //皇军蓝
#define     CornflowerBlue           0x64BD //矢车菊的蓝色
#define     LightSteelBlue           0xB63B //淡钢蓝
#define     LightSlateGray           0x7453 //浅石板灰
#define     SlateGray                0x7412 //石板灰
#define     DoderBlue                0xD700 //道奇蓝
#define     AliceBlue                0xF7DF //爱丽丝蓝
#define     SteelBlue                0x4416 //钢蓝
#define     LightSkyBlue             0x867F //淡蓝色
#define     SkyBlue                  0x867D //天蓝色
#define     DeepSkyBlue              0x05FF //深天蓝
#define     LightBLue                0xAEDC //淡蓝
#define     PowDerBlue               0xB71C //火药蓝
#define     CadetBlue                0x5CF4 //军校蓝
#define     Azure                    0xF7FF //蔚蓝色
#define     LightCyan                0xE7FF //淡青色
#define     PaleTurquoise            0xAF7D //苍白的绿宝石
#define     Cyan                     0x07FF //青色
#define     Aqua                     0x07FF //水绿色
#define     DarkTurquoise            0x067A //深绿宝石
#define     DarkSlateGray            0x2A69 //深石板灰
#define     DarkCyan                 0x0451 //深青色
#define     Teal                     0x0410 //水鸭色
#define     MediumTurquoise          0x4E99 //适中的绿宝石
#define     LightSeaGreen            0x2595 //浅海洋绿
#define     Turquoise                0x471A //绿宝石
#define     Auqamarin                0xA500 //绿玉\碧绿色
#define     MediumAquamarine         0x6675 //适中的碧绿色
#define     MediumSpringGreen        0x07D3 //适中的春天的绿色
#define     MintCream                0xF7FF //薄荷奶油
#define     SpringGreen              0x07EF //春天的绿色
#define     SeaGreen                 0x2C4A //海洋绿
#define     Honeydew                 0xF7FE //蜂蜜
#define     LightGreen               0x9772 //淡绿色
#define     PaleGreen                0x9FD3 //苍白的绿色
#define     DarkSeaGreen             0x8DF1 //深海洋绿
#define     LimeGreen                0x3666 //酸橙绿
#define     Lime                     0x07E0 //酸橙色
#define     ForestGreen              0x2444 //森林绿
#define     Green                    0x0400 //纯绿
#define     DarkGreen                0x0320 //深绿色
#define     Chartreuse               0x7FE0 //查特酒绿
#define     LawnGreen                0x7FE0 //草坪绿
#define     GreenYellow              0xAFE5 //绿黄色
#define     OliveDrab                0x6C64 //橄榄土褐色
#define     Beige                    0xF7BB //米色(浅褐色)
#define     LightGoldenrodYellow     0xFFDA //浅秋麒麟黄
#define     Ivory                    0xFFFE //象牙
#define     LightYellow              0xFFFC //浅黄色
#define     Yellow                   0xFFE0 //纯黄
#define     Olive                    0x8400 //橄榄
#define     DarkKhaki                0xBDAD //深卡其布
#define     LemonChiffon             0xFFD9 //柠檬薄纱
#define     PaleGodenrod             0xA060 //灰秋麒麟
#define     Khaki                    0xF731 //卡其布
#define     Gold                     0xFEA0 //金
#define     Cornislk                 0xC000 //玉米色
#define     GoldEnrod                0xDD24 //秋麒麟
#define     FloralWhite              0xFFDE //花的白色
#define     OldLace                  0xFFBC //老饰带
#define     Wheat                    0xF6F6 //小麦色
#define     Moccasin                 0xFF36 //鹿皮鞋
#define     Orange                   0xFD20 //橙色
#define     PapayaWhip               0xFF7A //番木瓜
#define     BlanchedAlmond           0xFF59 //漂白的杏仁
#define     NavajoWhite              0xFEF5 //Navajo白
#define     AntiqueWhite             0xFF5A //古代的白色
#define     Tan                      0xD5B1 //晒黑
#define     BrulyWood                0xB000 //结实的树
#define     Bisque                   0xFF38 //(浓汤)乳脂,番茄等
#define     DarkOrange               0xFC60 //深橙色
#define     Linen                    0xFF9C //亚麻布
#define     Peru                     0xCC27 //秘鲁
#define     PeachPuff                0xFED7 //桃色
#define     SandyBrown               0xF52C //沙棕色
#define     Chocolate                0xD343 //巧克力
#define     SaddleBrown              0x8A22 //马鞍棕色
#define     SeaShell                 0xFFBD //海贝壳
#define     Sienna                   0xA285 //黄土赭色
#define     LightSalmon              0xFD0F //浅鲜肉(鲑鱼)色
#define     Coral                    0xFBEA //珊瑚
#define     OrangeRed                0xFA20 //橙红色
#define     DarkSalmon               0xECAF //深鲜肉(鲑鱼)色
#define     Tomato                   0xFB08 //番茄
#define     MistyRose                0xFF3C //薄雾玫瑰
#define     Salmon                   0xFC0E //鲜肉(鲑鱼)色
#define     Snow                     0xFFDF //雪
#define     LightCoral               0xF410 //淡珊瑚色
#define     RosyBrown                0xBC71 //玫瑰棕色
#define     IndianRed                0xCAEB //印度红
#define     Red                      0xF800 //纯红
#define     Brown                    0xA145 //棕色
#define     FireBrick                0xB104 //耐火砖
#define     DarkRed                  0x8800 //深红色
#define     Maroon                   0x8000 //栗色
#define     White                    0xFFFF //纯白
#define     WhiteSmoke               0xF7BE //白烟
#define     Gainsboro                0xDEFB //Gainsboro
#define     LightGrey                0xD69A //浅灰色
#define     Silver                   0xC618 //银白色
#define     DarkGray                 0xAD55 //深灰色
#define     Gray                     0x8410 //灰色
#define     DimGray                  0x6B4D //暗淡的灰色
#define     Black                    0x0000 //黑色

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
