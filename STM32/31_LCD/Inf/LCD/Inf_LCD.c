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

void Inf_LCD_DisplayChar(uint16_t x, uint16_t y, uint16_t FontSize, uint8_t ch, uint16_t fontColor, uint16_t bgc) {
    uint16_t FontWidth = 0;
    uint16_t FontHeight = 0;
    switch (FontSize)
    {
    case SS:
        FontHeight = 12;
        FontWidth = 6;
        break;
    case SL:
        FontHeight = 16;
        FontWidth = 8;
        break;
    case LS:
        FontHeight = 24;
        FontWidth = 12;
        break;
    case LL:
        FontHeight = 32;
        FontWidth = 16;
        break;

    default:
        break;
    }
    // 1.设置待写区域
    Inf_LCD_Address_Set(x, y, FontWidth, FontHeight);
    // 2.计算出当前字符在二维数组中的角标
    uint8_t index = __GetIndex(ch);
    // 3.发送写数据指令
    Inf_LCD_WriteCmd(WriteDataToMemory);


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


/*
    typedef void (*WriteFunc)(uint16_t, uint16_t, uint8_t);
    WriteFunc writeFuncs[] = {writeSS, writeSL, writeLS, writeLL};
    writeFuncs[FontSize](fontColor, bgc, byte);
*/
