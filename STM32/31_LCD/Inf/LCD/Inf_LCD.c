#include "Inf_LCD.h"
#include "inf_lcd_font.h"

void Inf_LCD_Init(void) {
    /* 1.FSMCģ���ʼ�� */
    Driver_FSMC_LCD_Init();

    /* 2.����LCD */
    Inf_LCD_Reset();

    /* 3.�������� */
    Inf_LCD_BGOn();

    /* 4.�����ڲ��Ĵ��� */
    Inf_LCD_RegConfig();
}


// ����LCD  PG15
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
    /* 1. ���ûҽ׵�ѹ�Ե���TFT����٤�����ԣ� ��У׼��һ����������ú��� */
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

    /* 2. ���ûҽ׵�ѹ�Ե���TFT����٤�����ԣ���У׼ */
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

   /* 4. ��Դ����1*/
    Inf_LCD_WriteCmd(0xC0);
    Inf_LCD_WriteData(0x11); /* ��٤���ѹ */
    Inf_LCD_WriteData(0x09); /* ��٤���ѹ */

    /* 5. ��Դ����2 */
    Inf_LCD_WriteCmd(0xC1);
    Inf_LCD_WriteData(0x02);
    Inf_LCD_WriteData(0x03);

    /* 6. VCOM���� */
    Inf_LCD_WriteCmd(0XC5);
    Inf_LCD_WriteData(0x00);
    Inf_LCD_WriteData(0x0A);
    Inf_LCD_WriteData(0x80);

    /* 7. Frame Rate Control (In Normal Mode/Full Colors) (B1h) */
    Inf_LCD_WriteCmd(0xB1);
    Inf_LCD_WriteData(0xB0);
    Inf_LCD_WriteData(0x11);

    /* 8.  Display Inversion Control (B4h) ��������ѹ��ת�����ٵ�Ÿ��ţ�*/
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

    /* 13. Sleep Out (11h) �ر�����ģʽ */
    Inf_LCD_WriteCmd(0x11);

    /* 14. ������Ļ�����RGB */
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
    vu16 data;			//��ֹ���Ż� volatile
    data = LCD->LCD_Data;
    return data;
}

/* 2.���Զ�ȡID */
uint32_t Inf_LCD_ReadID(void) {
    uint32_t ID = 0;
    Inf_LCD_WriteCmd(0x04);
    Inf_LCD_ReadData();
    ID |= ((Inf_LCD_ReadData() & 0xff) << 16);
    ID |= ((Inf_LCD_ReadData() & 0xff) << 8);
    ID |= ((Inf_LCD_ReadData() & 0xff) << 0);
    return ID;
}

/* 3.����Ļ��ʾ�����Ϣ */
/* ����2A--->�������е�ַ��Χ--->����2B--->�������е�ַ��Χ--->����2C--->�������������--->��������(ifneeded).....*/
void Inf_LCD_Address_Set(uint16_t x, uint16_t y, uint16_t width, uint16_t hight) {
    Inf_LCD_WriteCmd(ColAddSet); // �����е�ַ
    Inf_LCD_WriteData((x >> 8) & 0xFF);  // SC[15:8] ֻ��8λһ�����ȷ���ʼ��ַ��λ
    Inf_LCD_WriteData((x >> 0) & 0xFF);  // SC[7:0] ��ʼ��ַ��λ
    Inf_LCD_WriteData(((x + width - 1) >> 8) & 0xFF);  // EC[15:8] ֻ��8λһ�����ȷ�������ַ��λ
    Inf_LCD_WriteData(((x + width - 1) >> 0) & 0xFF);  // EC[7:0] ������ַ��λ
    Inf_LCD_WriteCmd(PageAddSet); // �����е�ַ
    Inf_LCD_WriteData((y >> 8) & 0xFF);  // SC[15:8] 
    Inf_LCD_WriteData((y >> 0) & 0xFF);  // SC[7:0] 
    Inf_LCD_WriteData(((y + hight - 1) >> 8) & 0xFF);  // EC[15:8] 
    Inf_LCD_WriteData(((y + hight - 1) >> 0) & 0xFF);  // EC[7:0] 
}
void Inf_LCD_Clear(uint16_t bgc) {
    // 1.���ô�д����Ϊȫ��
    Inf_LCD_Address_Set(0, 0, LCD_W, LCD_H);

    // 2.������ָ���ŵ�������д����(16λ��ɫ����)
    Inf_LCD_WriteCmd(WriteDataToMemory);
    for (uint32_t i = 0; i < LCD_W * LCD_H; i++)
    {
        Inf_LCD_WriteData(bgc);
    }
}


void Inf_LCD_FillBgc(uint16_t x, uint16_t y, uint16_t width, uint16_t hight, uint16_t bgc) {
    // 1.���ô�д����Ϊȫ��
    Inf_LCD_Address_Set(x, y, width, hight);

    // 2.������ָ���ŵ�������д����(16λ��ɫ����)
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

    // 1.���ô�д����
    Inf_LCD_Address_Set(x, y, FontWidth, FontHeight);
    // 2.�������ǰ�ַ��ڶ�ά�����еĽǱ�
    uint8_t index = __GetIndex(ch);
    // 3.����д����ָ��
    Inf_LCD_WriteCmd(WriteDataToMemory);


    /*
        typedef void (*WriteFunc)(uint16_t, uint16_t, uint8_t);
        WriteFunc writeFuncs[] = {writeSS, writeSL, writeLS, writeLL};
        writeFuncs[FontSize](fontColor, bgc, byte);
    */
    switch (FontSize) {
    case SS: //12�ֽڱ�ʾһ���ַ�
        for (uint16_t i = 0; i < FontHeight; i++) {
            uint8_t byte = ascii_1206[index][i];
            for (uint8_t j = 0; j < FontWidth; j++)  //��Ȼ������8λ�������ֿ�ֻ��6λ
            {
                // �����ǵ�λ��ǰ��ȡģ��ʽ, ���Դӵ�λȡ���ݿ�ʼд
                ((byte >> j) & 0x01) == 0 ? Inf_LCD_WriteData(bgc) : Inf_LCD_WriteData(fontColor);
            }
        }
        break;
    case SL: //16�ֽڱ�ʾһ���ַ�
        for (uint16_t i = 0; i < FontHeight; i++) {
            uint8_t byte = ascii_1608[index][i];
            for (uint8_t j = 0; j < FontWidth; j++)  //��Ȼ������8λ�������ֿ�ֻ��6λ
            {
                // �����ǵ�λ��ǰ��ȡģ��ʽ,���Դӵ�λȡ���ݿ�ʼд
                ((byte >> j) & 0x01) == 0 ? Inf_LCD_WriteData(bgc) : Inf_LCD_WriteData(fontColor);
            }
        }
        break;
    case LS: //48�ֽڱ�ʾһ���ַ� ������Ҫ2(1.5)���ֽڱ�ʾһ��
        for (uint16_t i = 0; i < FontHeight * 2; i++) {
            uint8_t byte = ascii_2412[index][i];
            uint8_t line = (i % 2) == 0 ? 8 : 4;
            for (uint8_t j = 0; j < line; j++)  //��Ȼ������8λ�������ֿ�ֻ��6λ
            {
                // �����ǵ�λ��ǰ��ȡģ��ʽ,���Դӵ�λȡ���ݿ�ʼд
                ((byte >> j) & 0x01) == 0 ? Inf_LCD_WriteData(bgc) : Inf_LCD_WriteData(fontColor);
            }
        }
        break;
    case LL: //64 �ֽڱ�ʾһ���ַ� ������Ҫ2���ֽڱ�ʾһ��
        for (uint16_t i = 0; i < FontHeight * 2; i++) {
            uint8_t byte = ascii_3216[index][i];
            for (uint8_t j = 0; j < (FontWidth / 2); j++)  //��Ȼ������8λ�������ֿ�ֻ��6λ
            {
                // �����ǵ�λ��ǰ��ȡģ��ʽ,���Դӵ�λȡ���ݿ�ʼд
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
        // ����
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


void Inf_LCD_DispalyPicture(uint16_t x, uint16_t y)
{
    // 1.������ʾ����
    Inf_LCD_Address_Set(x, y, 265, 480);

    // 2.����д��������
    Inf_LCD_WriteCmd(WriteDataToMemory);

    // 3.������ǰҪ��ʾͼƬ���ַ�����  ÿ����һ�����
    for (uint32_t i = 0; i < 10; i += 2)  //i < ͼƬ����Ĵ�С
    {
        // ƴ��ɫ������ 16λ  ��λ��ǰ
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



