#include "Inf_LCD.h"



static void Inf_LCD_Reset(void);
static void Inf_LCD_BKOpen(void);
static void Inf_LCD_RegConfig(void);
static void Inf_LCD_WriteCmd(uint16_t cmd);
static void Inf_LCD_WriteData(uint16_t data);

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

void Inf_LCD_DisplayLogo(uint16_t x, uint16_t y) {
    Inf_LCD_SetArea(x, y, Img.w, Img.h);
    for (uint32_t i = 0; i < Img.w * Img.h * 2; i += 2)
    {
        Inf_LCD_WriteData(Img.Data[i] << 8 | Img.Data[i + 1]);
    }
}


static void Inf_LCD_Reset(void) {
    // PG15拉低即为重置
    HAL_GPIO_WritePin(GPIOG, GPIO_pin_15, GPIO_PIN_RESET);
    Delay_ms(5);
    HAL_GPIO_WritePin(GPIOG, GPIO_pin_15, GPIO_PIN_SET);
}
static void Inf_LCD_BKOpen(void) {
    // PB0 背光
    HAL_GPIO_WritePin(GPIOB, GPIO_pin_0, GPIO_PIN_SET);
}

static void Inf_LCD_RegConfig(void) {
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
static void Inf_LCD_WriteCmd(uint16_t cmd) {
    LCD->LCD_Cmd = cmd;
}
static void Inf_LCD_WriteData(uint16_t data) {
    LCD->LCD_Data = data;
}
