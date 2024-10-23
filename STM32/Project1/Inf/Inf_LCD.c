#include "Inf_LCD.h"



void Inf_LCD_Init(void) {
    Driver_FSMC_Init();
    Inf_LCD_Reset();
    Inf_LCD_BKOpen();
    Inf_LCD_RegConfig();
}

void Inf_LCD_SetArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
    Inf_LCD_WriteCmd(ColAddSet);  //列 x
    Inf_LCD_WriteData(x >> 8);
    Inf_LCD_WriteData(x & 0x00FF);
    Inf_LCD_WriteData((x + w - 1) >> 8);
    Inf_LCD_WriteData((x + w - 1) & 0x00FF);

    Inf_LCD_WriteCmd(RowAddSet);
    Inf_LCD_WriteData(y >> 8);
    Inf_LCD_WriteData(y & 0x00FF);
    Inf_LCD_WriteData((y + h - 1) >> 8);
    Inf_LCD_WriteData((y + h - 1) & 0x00FF);

    Inf_LCD_WriteCmd(WriteDataToMemory);
}


void Inf_LCD_Clear(void) {
    Inf_LCD_SetArea(0, 0, LCD_W, LCD_H);
    for (uint32_t i = 0; i < LCD_W * LCD_H; i++)
    {
        Inf_LCD_WriteData(BackgroundColor);
    }
}


void Inf_LCD_DisplayChar(uint16_t x, uint16_t y, uint8_t ch, uint8_t fontsize) {
    Inf_LCD_SetArea(x, y, fontsize / 2, fontsize);
    uint8_t index = __Index(ch);
    if (fontsize == 32)
    {
        for (uint8_t i = 0; i < 64; i++)
        {
            uint8_t byte = ascii_3216[index][i];
            for (uint8_t j = 0; j < 8; j++)
            {
                (byte & 0x01) == 0 ? (Inf_LCD_WriteData(BackgroundColor)) : (Inf_LCD_WriteData(FontColor));
                byte >>= 1;
            }
        }
    }
    else if (fontsize == 16)
    {
        for (uint8_t i = 0; i < 16; i++)
        {
            uint8_t byte = ascii_1608[index][i];
            for (uint8_t j = 0; j < 8; j++)
            {
                (byte & 0x01) == 0 ? (Inf_LCD_WriteData(BackgroundColor)) : (Inf_LCD_WriteData(FontColor));
                byte >>= 1;
            }
        }
    }
}

void Inf_LCD_DisplayString(uint16_t x, uint16_t y, uint8_t* str, uint8_t fontsize) {
    uint8_t i = 0;
    while (str[i] != '\0')
    {
        if ((x + (fontsize / 2)) >= LCD_W)
        {
            x = 0;
            y += fontsize;
        }

        Inf_LCD_DisplayChar(x, y, str[i], fontsize);
        i++;
        x += fontsize / 2;
    }
}

void Inf_LCD_DisplayChineseTitle(uint16_t x, uint16_t y) {
    for (uint8_t k = 0; k < (sizeof(chinese) / sizeof(chinese[0])); k++)
    {
        if (x + 32 > LCD_W)
        {
            x = 0;
            y += 32;
        }
        Inf_LCD_SetArea(x, y, 32, 32);
        for (uint8_t i = 0; i < 128; i++)
        {
            uint8_t byte = chinese[k][i];
            for (uint8_t j = 0; j < 8; j++)
            {
                ((byte & 0x01) == 0) ? Inf_LCD_WriteData(BackgroundColor) : Inf_LCD_WriteData(FontColor);
                byte >>= 1;
            }
        }
        x += 32;
    }
}

void Inf_LCD_DisplayPonit(uint16_t x, uint16_t y, uint16_t LineWidth, uint16_t LineColor) {
    Inf_LCD_SetArea(x, y, LineWidth, LineWidth);
    Inf_LCD_WriteCmd(WriteDataToMemory);

    for (uint32_t i = 0; i < LineWidth * LineWidth; i++)
    {
        Inf_LCD_WriteData(LineColor);
    }
}
void Inf_LCD_DisplayChinese(uint16_t x, uint16_t y, uint16_t size, char* Font) {
    char* pFont = Font;
    uint8_t GBKL, GBKH, tmp;
    uint16_t SIZE = (size * size / 8);    //计算字节数
    // 如果size = 16，表示中文字符在 LCD 上以 16x16 的点阵形式显示。对于一个 16x16 的点阵，总共有16 * 16 = 256个点，由于每个字节可以存储 8 个点的信息（因为一个字节有 8 位）所以需要256/8 = 32字节来存储这个 16x16 点阵的中文字符信息，这就是SIZE的值。
    uint16_t y0 = y;//记录第一行显示的初始位置
    uint16_t x1 = x;//记录显示的初始位置
    uint16_t y1 = y;
    uint16_t i, j;
    uint32_t Addr_offset;//汉字的偏移地址
    uint8_t* pBuff = malloc(SIZE);//动态分配空间
    while (*pFont != '\0')
    {
        /*
        在 GB2312 编码中，每个中文字符由两个字节表示。例如要显示汉字 “中”，在 GB2312 编码下，“中” 字的编码是 0xD6D0。
        当执行GBKH = *pFont++;时，GBKH将被赋值为 0xD6。然后执行GBKL = *pFont++;，GBKL将被赋值为 0xD0。
        这些字节将用于计算该汉字在存储中的偏移地址等操作。根据代码中的计算方式Addr_offset = ((GBKH - 0x81)*190 + GBKL - 0x40)*(size * 2);可以根据获取到的GBKH和GBKL计算出在存储中 “中” 字的点阵数据的偏移地址
        */
        //计算汉字的偏移地址
        GBKH = *pFont++;//高字节
        GBKL = *pFont++;//低字节
        if (GBKL < 0x7F)
        {
            Addr_offset = ((GBKH - 0x81) * 190 + GBKL - 0x40) * (size * 2);
            //中字为例 Addr_offset：0x3929 * 32 = 0x3929 * 0x20 = 0x72520
        }
        else
        {
            Addr_offset = ((GBKH - 0x81) * 190 + GBKL - 0x41) * (size * 2);
        }
        //从flash中取出一个汉字
        switch (size)
        {
        case 16:Inf_W25q32_ReadData(Addr_offset, pBuff, SIZE);break;
        default:Inf_W25q32_ReadData(Addr_offset, pBuff, SIZE);break;
        }
        //显示一个汉字
        for (i = 0;i < SIZE;i++)
        {
            tmp = *(pBuff + i);
            y = y0; //当开始处理一个新字节时，需要将y坐标重置为y0，是因为在处理上一个字节的 8 位时，y坐标已经递增了 8 次（对应 8 位）
            for (j = 0;j < 8;j++)
            {
                if (tmp & 0x80)	//高位先发
                {
                    Inf_LCD_DisplayPonit(x, y, 1, FontColor);
                }
                tmp <<= 1;
                y++;
            }
            x++;
            // 在显示一个汉字的循环过程中，x的值会逐步增加  
            // 一个汉字内部的换行逻辑
            if (x - x1 == size)
            {
                x = x1;
                y0 += 8;
            }
        }
        //一个汉字显示完成，为下一个汉字显示做准备
        x += size;

        if (LCD_W - x < size)//考虑是否需要换行
        {
            y1 += size + 4;
            x = 0;
        }
        x1 = x;
        y0 = y1;
    }
    free(pBuff);//释放空间
}

void Inf_LCD_DisplayLogo(uint16_t x, uint16_t y) {
    Inf_LCD_SetArea(x, y, Img.w, Img.h);
    for (uint32_t i = 0; i < Img.w * Img.h * 2; i += 2)
    {
        Inf_LCD_WriteData(Img.Data[i] << 8 | Img.Data[i + 1]);
    }
}


void Inf_LCD_Reset(void) {
    // PG15拉低即为重置
    HAL_GPIO_WritePin(GPIOG, GPIO_pin_15, GPIO_PIN_RESET);
    Delay_ms(5);
    HAL_GPIO_WritePin(GPIOG, GPIO_pin_15, GPIO_PIN_SET);
}
void Inf_LCD_BKOpen(void) {
    // PB0 背光
    HAL_GPIO_WritePin(GPIOB, GPIO_pin_0, GPIO_PIN_SET);
}

void Inf_LCD_RegConfig(void) {
    /* 1. 设置灰阶电压以调整TFT面板的伽马特性， 正校准。一般出厂就设置好了 */
    Inf_LCD_WriteCmd(0xE0);
    Inf_LCD_WriteData(0x00);
    Inf_LCD_WriteData(0x07);
    Inf_LCD_WriteData(0x10);
    Inf_LCD_WriteData(0x09);
    Inf_LCD_WriteData(0x17);
    Inf_LCD_WriteData(0x0B);
    Inf_LCD_WriteData(0x41);
    Inf_LCD_WriteData(0x89);
    Inf_LCD_WriteData(0x4B);
    Inf_LCD_WriteData(0x0A);
    Inf_LCD_WriteData(0x0C);
    Inf_LCD_WriteData(0x0E);
    Inf_LCD_WriteData(0x18);
    Inf_LCD_WriteData(0x1B);
    Inf_LCD_WriteData(0x0F);

    /* 2. 设置灰阶电压以调整TFT面板的伽马特性，负校准 */
    Inf_LCD_WriteCmd(0XE1);
    Inf_LCD_WriteData(0x00);
    Inf_LCD_WriteData(0x17);
    Inf_LCD_WriteData(0x1A);
    Inf_LCD_WriteData(0x04);
    Inf_LCD_WriteData(0x0E);
    Inf_LCD_WriteData(0x06);
    Inf_LCD_WriteData(0x2F);
    Inf_LCD_WriteData(0x45);
    Inf_LCD_WriteData(0x43);
    Inf_LCD_WriteData(0x02);
    Inf_LCD_WriteData(0x0A);
    Inf_LCD_WriteData(0x09);
    Inf_LCD_WriteData(0x32);
    Inf_LCD_WriteData(0x36);
    Inf_LCD_WriteData(0x0F);

    /* 3.  Adjust Control 3 (F7h)  */
    /*LCD_WriteCmd(0XF7);
   Inf_LCD_WriteData(0xA9);
   Inf_LCD_WriteData(0x51);
   Inf_LCD_WriteData(0x2C);
   Inf_LCD_WriteData(0x82);*/
   /* DSI write DCS command, use loose packet RGB 666 */

   /* 4. 电源控制1*/
    Inf_LCD_WriteCmd(0xC0);
    Inf_LCD_WriteData(0x11); /* 正伽马电压 */
    Inf_LCD_WriteData(0x09); /* 负伽马电压 */

    /* 5. 电源控制2 */
    Inf_LCD_WriteCmd(0xC1);
    Inf_LCD_WriteData(0x02);
    Inf_LCD_WriteData(0x03);

    /* 6. VCOM控制 */
    Inf_LCD_WriteCmd(0XC5);
    Inf_LCD_WriteData(0x00);
    Inf_LCD_WriteData(0x0A);
    Inf_LCD_WriteData(0x80);

    /* 7. Frame Rate Control (In Normal Mode/Full Colors) (B1h) */
    Inf_LCD_WriteCmd(0xB1);
    Inf_LCD_WriteData(0xB0);
    Inf_LCD_WriteData(0x11);

    /* 8.  Display Inversion Control (B4h) （正负电压反转，减少电磁干扰）*/
    Inf_LCD_WriteCmd(0xB4);
    Inf_LCD_WriteData(0x02);

    /* 9.  Display Function Control (B6h)  */
    Inf_LCD_WriteCmd(0xB6);
    Inf_LCD_WriteData(0x0A);
    Inf_LCD_WriteData(0xA2);

    /* 10. Entry Mode Set (B7h)  */
    Inf_LCD_WriteCmd(0xB7);
    Inf_LCD_WriteData(0xc6);

    /* 11. HS Lanes Control (BEh) */
    Inf_LCD_WriteCmd(0xBE);
    Inf_LCD_WriteData(0x00);
    Inf_LCD_WriteData(0x04);

    /* 12.  Interface Pixel Format (3Ah) */
    Inf_LCD_WriteCmd(0x3A);
    Inf_LCD_WriteData(0x55); /* 0x55 : 16 bits/pixel  */

    /* 13. Sleep Out (11h) 关闭休眠模式 */
    Inf_LCD_WriteCmd(0x11);

    /* 14. 设置屏幕方向和RGB */
    Inf_LCD_WriteCmd(0x36);
    Inf_LCD_WriteData(0x08);

    Delay_ms(120);

    /* 14. display on */
    Inf_LCD_WriteCmd(0x29);
}
void Inf_LCD_WriteCmd(uint16_t cmd) {
    LCD->LCD_Cmd = cmd;
}
void Inf_LCD_WriteData(uint16_t data) {
    LCD->LCD_Data = data;
}
