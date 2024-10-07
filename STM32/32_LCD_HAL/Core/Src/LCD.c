#include "lcd.h"
#include "Inf_LCD_font.h"

void Inf_LCD_WriteCmd(uint16_t cmd) {
    LCD->LCD_Cmd = cmd;
}
void Inf_LCD_WriteData(uint16_t data) {
    LCD->LCD_Data = data;
}
void LCD_Init(void) {
    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_15, GPIO_PIN_RESET);
    HAL_Delay(100);
    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_15, GPIO_PIN_SET);
    HAL_Delay(100);

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);

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

    HAL_Delay(120);

    /* 14. display on */
    Inf_LCD_WriteCmd(0x29);
}



void Inf_LCD_Address_Set(uint16_t x, uint16_t y, uint16_t width, uint16_t hight) {
    /* 命令2A--->参数：列地址范围--->命令2B--->参数：行地址范围--->命令2C--->连续传输的数据--->其它命令(ifneeded).....*/
    Inf_LCD_WriteCmd(ColAddSet); // 设置列地址
    Inf_LCD_WriteData(x >> 8); //SC[15:8] 只能8位一发，先发起始地址高位
    Inf_LCD_WriteData(x & 0x00FF);
    Inf_LCD_WriteData((x + width - 1) >> 8);
    Inf_LCD_WriteData((x + width - 1) & 0x00FF);
    Inf_LCD_WriteCmd(PageAddSet);
    Inf_LCD_WriteData(y >> 8); //SC[15:8] 只能8位一发，先发起始地址高位
    Inf_LCD_WriteData(y & 0x00FF);
    Inf_LCD_WriteData((y + hight - 1) >> 8);
    Inf_LCD_WriteData((y + hight - 1) & 0x00FF);
}

void LCD_Clear(uint16_t bgColor) {
    Inf_LCD_Address_Set(0, 0, LCD_W, LCD_H);
    Inf_LCD_WriteCmd(WriteDataToMemory);
    for (uint32_t i = 0; i < LCD_W * LCD_H; i++)
    {
        Inf_LCD_WriteData(bgColor);
    }
}
void LCD_DisplayChar(uint16_t x, uint16_t y, uint8_t ch, uint8_t fontHeight, uint16_t fontColor, uint16_t bgColor) {
    uint8_t fontWidth = fontHeight / 2;
    Inf_LCD_Address_Set(x, y, fontWidth, fontHeight);
    Inf_LCD_WriteCmd(WriteDataToMemory);
    uint8_t index = ch - ' ';
    if (fontHeight == 12)
    {
        for (uint8_t i = 0; i < 12; i++)
        {
            uint8_t byte = ascii_1206[index][i];
            for (uint8_t j = 0; j < 6; j++)
            {
                //先从低位开始取，因为低位在前
                (byte & 0x01) == 0 ? Inf_LCD_WriteData(bgColor) : Inf_LCD_WriteData(fontColor);
                byte >>= 1;
            }
        }
    }
    else if (fontHeight == 16)
    {
        for (uint8_t i = 0; i < 16; i++)
        {
            uint8_t byte = ascii_1608[index][i];
            for (uint8_t j = 0; j < 8; j++)
            {
                (byte & 0x01) == 0 ? Inf_LCD_WriteData(bgColor) : Inf_LCD_WriteData(fontColor);
                byte >>= 1;
            }
        }
    }
    else if (fontHeight == 24)
    {
        for (uint8_t i = 0; i < 48; i++)
        {
            uint8_t byte = ascii_2412[index][i];
            // 24x12 两个1组，但是一组中最后一个只要低四位
            uint8_t line = (i % 2) == 0 ? (8) : (4);
            for (uint8_t j = 0; j < line; j++)
            {
                (byte & 0x01) == 0 ? Inf_LCD_WriteData(bgColor) : Inf_LCD_WriteData(fontColor);
                byte >>= 1;
            }
        }
    }
    else if (fontHeight == 32)
    {
        for (uint16_t i = 0; i < 64; i++)
        {
            uint8_t byte = ascii_3216[index][i];
            // 32x16  一组2个一共32组
            for (uint8_t j = 0; j < 8; j++)
            {
                (byte & 0x01) == 0 ? Inf_LCD_WriteData(bgColor) : Inf_LCD_WriteData(fontColor);
                byte >>= 1;
            }
        }
    }
}
void LCD_DisplayString(uint16_t x, uint16_t y, uint8_t* str, uint8_t fontHeight, uint16_t fontColor, uint16_t bgColor) {
    uint32_t i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '\n')
        {
            x = 0;
            y += fontHeight;
            i++;
        }
        if ((x + fontHeight / 2) >= LCD_W)
        {
            x = 0;
            y += fontHeight;
        }
        LCD_DisplayChar(x, y, str[i], fontHeight, fontColor, bgColor);
        x += fontHeight / 2;
        i++;
    }
}


void Inf_LCD_DisplayPonit(uint16_t x, uint16_t y, uint16_t LineWidth, uint16_t LineColor) {
    Inf_LCD_Address_Set(x, y, LineWidth, LineWidth);
    Inf_LCD_WriteCmd(WriteDataToMemory);

    for (uint32_t i = 0; i < LineWidth * LineWidth; i++)
    {
        Inf_LCD_WriteData(LineColor);
    }
}
void Inf_LCD_DisplayChinese(uint16_t x, uint16_t y, uint16_t size, char* Font, uint16_t color)
{
    char* pFont = Font;
    uint8_t GBKL, GBKH, tmp;
    uint16_t SIZE = size * size / 8;//计算字节数
    uint16_t y0 = y;//记录第一行显示的初始位置
    uint16_t x1 = x;//记录显示的初始位置
    uint16_t y1 = y;
    uint16_t i, j;
    uint32_t Addr_offset;//汉字的偏移地址
    uint8_t* pBuff = malloc(SIZE);//动态分配空间
    while (*pFont != '\0')
    {
        //计算汉字的偏移地址
        GBKH = *pFont++;//高字节
        GBKL = *pFont++;//低字节
        if (GBKL < 0x7F)
        {
            Addr_offset = ((GBKH - 0x81) * 190 + GBKL - 0x40) * (size * 2);
        }
        else
        {
            Addr_offset = ((GBKH - 0x81) * 190 + GBKL - 0x41) * (size * 2);
        }
        //从flash中取出一个汉字
        switch (size)
        {
        case 16:W25Q32_ReadData(Addr_offset, pBuff, SIZE);break;
        default:W25Q32_ReadData(Addr_offset, pBuff, SIZE);break;
        }
        //显示一个汉字
        for (i = 0;i < SIZE;i++)
        {
            tmp = *(pBuff + i);
            y = y0;
            for (j = 0;j < 8;j++)
            {
                if (tmp & 0x80)	//高位先发
                {
                    Inf_LCD_DisplayPonit(x, y, 1, color);
                }
                tmp <<= 1;
                y++;
            }
            x++;
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
void Inf_LCD_DispalyPicture(uint16_t x, uint16_t y) {
    // 1.设置显示区域
    Inf_LCD_Address_Set(x, y, 265, 480);

    // 2.发送写数据命令
    Inf_LCD_WriteCmd(WriteDataToMemory);

    // 3.遍历当前要显示图片的字符数组  每两个一起遍历
    for (uint32_t i = 0; i < 254400; i += 2)  //i < 图片数组的大小
    {
        // 拼接色彩数据 16位  低位在前
        uint16_t byte = gImage_logo[i] + (gImage_logo[i + 1] << 8);
        Inf_LCD_WriteData(byte);
    }
}
