#include "Inf_LCD.h"
#include "inf_lcd_font.h"

void Inf_LCD_Init(void) {
    /* 1.FSMC模块初始化 */
    Driver_FSMC_LCD_Init();

    /* 2.重置LCD */
    Inf_LCD_Reset();

    /* 3.开启背光 */
    Inf_LCD_BGOn();

    /* 4.配置内部寄存器 */
    Inf_LCD_RegConfig();
}


// 重置LCD  PG15
void Inf_LCD_Reset(void) {
    HAL_GPIO_WritePin(GPIOG, GPIO_pin_15, GPIO_PIN_RESET);
    Delay_ms(100);
    HAL_GPIO_WritePin(GPIOG, GPIO_pin_15, GPIO_PIN_SET);
    Delay_ms(100);
}


void Inf_LCD_BGOn(void) {
    HAL_GPIO_WritePin(GPIOB, GPIO_pin_0, GPIO_PIN_SET);
}
void Inf_LCD_BGOff(void) {
    HAL_GPIO_WritePin(GPIOB, GPIO_pin_0, GPIO_PIN_RESET);
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
uint16_t Inf_LCD_ReadData(void) {
    vu16 data;			//防止被优化 volatile
    data = LCD->LCD_Data;
    return data;
}

/* 2.测试读取ID */
uint32_t Inf_LCD_ReadID(void) {
    uint32_t ID = 0;
    Inf_LCD_WriteCmd(0x04);
    Inf_LCD_ReadData();
    ID |= ((Inf_LCD_ReadData() & 0xff) << 16);
    ID |= ((Inf_LCD_ReadData() & 0xff) << 8);
    ID |= ((Inf_LCD_ReadData() & 0xff) << 0);
    return ID;
}

/* 3.在屏幕显示相关信息 */
/* 命令2A--->参数：列地址范围--->命令2B--->参数：行地址范围--->命令2C--->连续传输的数据--->其它命令(ifneeded).....*/
void Inf_LCD_Address_Set(uint16_t x, uint16_t y, uint16_t width, uint16_t hight) {
    Inf_LCD_WriteCmd(ColAddSet); // 设置列地址
    Inf_LCD_WriteData((x >> 8) & 0xFF);  // SC[15:8] 只能8位一发，先发起始地址高位
    Inf_LCD_WriteData((x >> 0) & 0xFF);  // SC[7:0] 起始地址低位
    Inf_LCD_WriteData(((x + width - 1) >> 8) & 0xFF);  // EC[15:8] 只能8位一发，先发结束地址高位
    Inf_LCD_WriteData(((x + width - 1) >> 0) & 0xFF);  // EC[7:0] 结束地址低位
    Inf_LCD_WriteCmd(PageAddSet); // 设置行地址
    Inf_LCD_WriteData((y >> 8) & 0xFF);  // SC[15:8] 
    Inf_LCD_WriteData((y >> 0) & 0xFF);  // SC[7:0] 
    Inf_LCD_WriteData(((y + hight - 1) >> 8) & 0xFF);  // EC[15:8] 
    Inf_LCD_WriteData(((y + hight - 1) >> 0) & 0xFF);  // EC[7:0] 
}
void Inf_LCD_Clear(uint16_t bgc) {
    // 1.设置待写区域为全屏
    Inf_LCD_Address_Set(0, 0, LCD_W, LCD_H);

    // 2.依次向指定号的区域中写数据(16位颜色数据)
    Inf_LCD_WriteCmd(WriteDataToMemory);
    for (uint32_t i = 0; i < LCD_W * LCD_H; i++)
    {
        Inf_LCD_WriteData(bgc);
    }
}


void Inf_LCD_FillBgc(uint16_t x, uint16_t y, uint16_t width, uint16_t hight, uint16_t bgc) {
    // 1.设置待写区域为全屏
    Inf_LCD_Address_Set(x, y, width, hight);

    // 2.依次向指定号的区域中写数据(16位颜色数据)
    Inf_LCD_WriteCmd(WriteDataToMemory);
    for (uint32_t i = 0; i < width * hight; i++)
    {
        Inf_LCD_WriteData(bgc);
    }
}
Font_Style Inf_LCD_GetFontSize(uint16_t FontSize) {
    Font_Style font_style;
    font_style.FontHeight = 0;
    font_style.FontWidth = 0;
    switch (FontSize)
    {
    case SS:
        font_style.FontHeight = 12;
        font_style.FontWidth = 6;
        break;
    case SL:
        font_style.FontHeight = 16;
        font_style.FontWidth = 8;
        break;
    case LS:
        font_style.FontHeight = 24;
        font_style.FontWidth = 12;
        break;
    case LL:
        font_style.FontHeight = 32;
        font_style.FontWidth = 16;
        break;
    default:
        break;
    }
    return font_style;
}

void Inf_LCD_DisplayChar(uint16_t x, uint16_t y, uint16_t FontSize, uint8_t ch, uint16_t fontColor, uint16_t bgc) {
    uint16_t FontWidth = 0;
    uint16_t FontHeight = 0;
    Font_Style font_style = Inf_LCD_GetFontSize(FontSize);
    FontWidth = font_style.FontWidth;
    FontHeight = font_style.FontHeight;

    // 1.设置待写区域
    Inf_LCD_Address_Set(x, y, FontWidth, FontHeight);
    // 2.计算出当前字符在二维数组中的角标
    uint8_t index = __GetIndex(ch);
    // 3.发送写数据指令
    Inf_LCD_WriteCmd(WriteDataToMemory);


    /*
        typedef void (*WriteFunc)(uint16_t, uint16_t, uint8_t);
        WriteFunc writeFuncs[] = {writeSS, writeSL, writeLS, writeLL};
        writeFuncs[FontSize](fontColor, bgc, byte);
    */
    switch (FontSize) {
    case SS: //12字节表示一个字符
        for (uint16_t i = 0; i < FontHeight; i++) {
            uint8_t byte = ascii_1206[index][i];
            for (uint8_t j = 0; j < FontWidth; j++)  //虽然数据是8位，但是字宽只有6位
            {
                // 由于是低位在前的取模方式, 所以从低位取数据开始写
                ((byte >> j) & 0x01) == 0 ? Inf_LCD_WriteData(bgc) : Inf_LCD_WriteData(fontColor);
            }
        }
        break;
    case SL: //16字节表示一个字符
        for (uint16_t i = 0; i < FontHeight; i++) {
            uint8_t byte = ascii_1608[index][i];
            for (uint8_t j = 0; j < FontWidth; j++)  //虽然数据是8位，但是字宽只有6位
            {
                // 由于是低位在前的取模方式,所以从低位取数据开始写
                ((byte >> j) & 0x01) == 0 ? Inf_LCD_WriteData(bgc) : Inf_LCD_WriteData(fontColor);
            }
        }
        break;
    case LS: //48字节表示一个字符 所以需要2(1.5)个字节表示一行
        for (uint16_t i = 0; i < FontHeight * 2; i++) {
            uint8_t byte = ascii_2412[index][i];
            uint8_t line = (i % 2) == 0 ? 8 : 4;
            for (uint8_t j = 0; j < line; j++)  //虽然数据是8位，但是字宽只有6位
            {
                // 由于是低位在前的取模方式,所以从低位取数据开始写
                ((byte >> j) & 0x01) == 0 ? Inf_LCD_WriteData(bgc) : Inf_LCD_WriteData(fontColor);
            }
        }
        break;
    case LL: //64 字节表示一个字符 所以需要2个字节表示一行
        for (uint16_t i = 0; i < FontHeight * 2; i++) {
            uint8_t byte = ascii_3216[index][i];
            for (uint8_t j = 0; j < (FontWidth / 2); j++)  //虽然数据是8位，但是字宽只有6位
            {
                // 由于是低位在前的取模方式,所以从低位取数据开始写
                ((byte >> j) & 0x01) == 0 ? Inf_LCD_WriteData(bgc) : Inf_LCD_WriteData(fontColor);
            }
        }
        break;
    default:
        break;
    }
}



void Inf_LCD_DisplayString(uint16_t x, uint16_t y, uint16_t FontSize, uint8_t* str, uint16_t fontColor, uint16_t bgc) {
    uint16_t i = 0;
    uint16_t FontWidth = 0;
    uint16_t FontHeight = 0;
    Font_Style font_style = Inf_LCD_GetFontSize(FontSize);
    FontWidth = font_style.FontWidth;
    FontHeight = font_style.FontHeight;

    while (str[i] != '\0')
    {
        // 换行
        if ((x + FontWidth) > LCD_W)
        {
            x = 0;
            y += FontHeight;
        }
        if (str[i] == '\n')
        {
            x = 0;
            y += FontHeight;
            i++;
            continue;
        }
        Inf_LCD_DisplayChar(x, y, FontSize, str[i], fontColor, bgc);
        x += FontWidth;
        i++;
    }
}

void Inf_LCD_DispalySingleChinese(uint16_t x, uint16_t y, uint8_t index, uint16_t fColor, uint16_t bgColor) {
    Inf_LCD_Address_Set(x, y, 32, 32);
    Inf_LCD_WriteCmd(WriteDataToMemory);
    for (uint16_t i = 0; i < 128; i++)
    {
        // 每次取出一个字节
        uint8_t byte = chinese[index][i];
        for (uint8_t j = 0; j < 8; j++)
        {
            ((byte >> j) & 0x01) == 0 ? Inf_LCD_WriteData(bgColor) : Inf_LCD_WriteData(fColor);
        }
    }
}


void Inf_LCD_DispalyPicture(uint16_t x, uint16_t y)
{
    // 1.设置显示区域
    Inf_LCD_Address_Set(x, y, 265, 480);

    // 2.发送写数据命令
    Inf_LCD_WriteCmd(WriteDataToMemory);

    // 3.遍历当前要显示图片的字符数组  每两个一起遍历
    for (uint32_t i = 0; i < 10; i += 2)  //i < 图片数组的大小
    {
        // 拼接色彩数据 16位  低位在前
        uint16_t byte = gImage_logo[i] + (gImage_logo[i + 1] << 8);
        Inf_LCD_WriteData(byte);
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

void Inf_LCD_BouncingBall(void) {
    static uint16_t x = 100;
    static uint16_t y = 100;

    static uint8_t Xflag = 0;
    static  uint8_t Yflag = 0;

    static uint16_t last_x = 0;
    static uint16_t last_y = 0;

    Inf_LCD_FillBgc(last_x, last_y, 8, 8, White);
    Inf_LCD_DisplayPonit(x, y, 8, MediumVioletRed);

    last_x = x;
    last_y = y;

    if (x >= 320 || x <= 0)
    {
        Xflag = ~Xflag;
    }
    else if (y >= 480 || y <= 0)
    {
        Yflag = ~Yflag;
    }
    Xflag ? (x -= 1) : (x += 2);
    Yflag ? (y += 2) : (y -= 1);

    Delay_ms(10);
}


void Inf_LCD_DisplayLine(uint16_t SP_x, uint16_t SP_y, uint16_t EP_x, uint16_t EP_y, uint16_t LineWidth, uint16_t LineColor) {
    // y = k * x + b; k = (y2-y1)/(x2-x1); b = y1 - (k * x1);
    // y = k * x + b; k = (EP_y-SP_y)/(EP_x-SP_x); b = EP_y - (k * EP_x);
    if (EP_x == SP_x)
    {
        for (uint16_t y = SP_y; y <= EP_y; y += (uint16_t)(LineWidth / 2.0))
        {
            Inf_LCD_DisplayPonit(EP_x, y, LineWidth, LineColor);
        }
    }
    else {
        double k = 1.0 * (EP_y - SP_y) / (EP_x - SP_x);
        double b = EP_y - (k * EP_x);
        // 默认x2 > x1
        for (uint16_t x = SP_x; x < EP_x; x++)
        {
            uint16_t y = (uint16_t)(k * x + b);
            Inf_LCD_DisplayPonit(x, y, LineWidth, LineColor);
        }
    }
}


void Inf_LCD_DisplayCycle(uint16_t xCenter, uint16_t yCenter, uint16_t radius, uint16_t LineWidth, uint16_t LineColor) {
    // x = r * cos(theta);   y = r * sin(theta);
    uint16_t x = 0;
    uint16_t y = 0;
    for (uint8_t angle = 0; angle <= 90; angle++)
    {
        // 根据角度计算弧度值  要将角度60度转换为弧度=3/PI
        double theta = angle * 3.14 / 180;

        x = radius * cos(theta);
        y = radius * sin(theta);
        Inf_LCD_DisplayPonit(x + xCenter, y + yCenter, LineWidth, LineColor);
        Inf_LCD_DisplayPonit(-x + xCenter, y + yCenter, LineWidth, LineColor);
        Inf_LCD_DisplayPonit(x + xCenter, -y + yCenter, LineWidth, LineColor);
        Inf_LCD_DisplayPonit(-x + xCenter, -y + yCenter, LineWidth, LineColor);
    }
}


void Inf_LCD_DisplaySolidCycle(uint16_t xCenter, uint16_t yCenter, uint16_t radius, uint16_t LineWidth, uint16_t LineColor) {
    // x = r * cos(theta);   y = r * sin(theta);
    uint16_t x = 0;
    uint16_t y = 0;
    for (uint16_t angle = 0; angle <= 90; angle++)
    {
        // 根据角度计算弧度值  要将角度60度转换为弧度=3/PI
        double theta = angle * 3.14 / 180;

        x = radius * cos(theta);
        y = radius * sin(theta);
        Inf_LCD_DisplayLine(-x + xCenter, y + yCenter, x + xCenter, y + yCenter, LineWidth, LineColor);
        Inf_LCD_DisplayLine(-x + xCenter, -y + yCenter, x + xCenter, -y + yCenter, LineWidth, LineColor);
    }
}

void Inf_LCD_DisplayRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t LineWidth, uint16_t LineColor)
{
    Inf_LCD_DisplayLine(x1, y1, x2, y1, LineWidth, LineColor);
    Inf_LCD_DisplayLine(x2, y1, x2, y2, LineWidth, LineColor);
    Inf_LCD_DisplayLine(x1, y1, x1, y2, LineWidth, LineColor);
    Inf_LCD_DisplayLine(x1, y2, x2, y2, LineWidth, LineColor);
}

void Inf_LCD_DisplayChinese(uint16_t x, uint16_t y, uint16_t size, char* Font, uint16_t color)
{
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
        case 16:Inf_W25Q32_ReadData(Addr_offset, pBuff, SIZE);break;
        default:Inf_W25Q32_ReadData(Addr_offset, pBuff, SIZE);break;
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
                    Inf_LCD_DisplayPonit(x, y, 1, color);
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



