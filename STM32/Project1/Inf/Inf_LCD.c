#include "Inf_LCD.h"



void Inf_LCD_Init(void) {
    Driver_FSMC_Init();
    Inf_LCD_Reset();
    Inf_LCD_BKOpen();
    Inf_LCD_RegConfig();
}

void Inf_LCD_SetArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h) {
    Inf_LCD_WriteCmd(ColAddSet);  //�� x
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
    uint16_t SIZE = (size * size / 8);    //�����ֽ���
    // ���size = 16����ʾ�����ַ��� LCD ���� 16x16 �ĵ�����ʽ��ʾ������һ�� 16x16 �ĵ����ܹ���16 * 16 = 256���㣬����ÿ���ֽڿ��Դ洢 8 �������Ϣ����Ϊһ���ֽ��� 8 λ��������Ҫ256/8 = 32�ֽ����洢��� 16x16 ����������ַ���Ϣ�������SIZE��ֵ��
    uint16_t y0 = y;//��¼��һ����ʾ�ĳ�ʼλ��
    uint16_t x1 = x;//��¼��ʾ�ĳ�ʼλ��
    uint16_t y1 = y;
    uint16_t i, j;
    uint32_t Addr_offset;//���ֵ�ƫ�Ƶ�ַ
    uint8_t* pBuff = malloc(SIZE);//��̬����ռ�
    while (*pFont != '\0')
    {
        /*
        �� GB2312 �����У�ÿ�������ַ��������ֽڱ�ʾ������Ҫ��ʾ���� ���С����� GB2312 �����£����С� �ֵı����� 0xD6D0��
        ��ִ��GBKH = *pFont++;ʱ��GBKH������ֵΪ 0xD6��Ȼ��ִ��GBKL = *pFont++;��GBKL������ֵΪ 0xD0��
        ��Щ�ֽڽ����ڼ���ú����ڴ洢�е�ƫ�Ƶ�ַ�Ȳ��������ݴ����еļ��㷽ʽAddr_offset = ((GBKH - 0x81)*190 + GBKL - 0x40)*(size * 2);���Ը��ݻ�ȡ����GBKH��GBKL������ڴ洢�� ���С� �ֵĵ������ݵ�ƫ�Ƶ�ַ
        */
        //���㺺�ֵ�ƫ�Ƶ�ַ
        GBKH = *pFont++;//���ֽ�
        GBKL = *pFont++;//���ֽ�
        if (GBKL < 0x7F)
        {
            Addr_offset = ((GBKH - 0x81) * 190 + GBKL - 0x40) * (size * 2);
            //����Ϊ�� Addr_offset��0x3929 * 32 = 0x3929 * 0x20 = 0x72520
        }
        else
        {
            Addr_offset = ((GBKH - 0x81) * 190 + GBKL - 0x41) * (size * 2);
        }
        //��flash��ȡ��һ������
        switch (size)
        {
        case 16:Inf_W25q32_ReadData(Addr_offset, pBuff, SIZE);break;
        default:Inf_W25q32_ReadData(Addr_offset, pBuff, SIZE);break;
        }
        //��ʾһ������
        for (i = 0;i < SIZE;i++)
        {
            tmp = *(pBuff + i);
            y = y0; //����ʼ����һ�����ֽ�ʱ����Ҫ��y��������Ϊy0������Ϊ�ڴ�����һ���ֽڵ� 8 λʱ��y�����Ѿ������� 8 �Σ���Ӧ 8 λ��
            for (j = 0;j < 8;j++)
            {
                if (tmp & 0x80)	//��λ�ȷ�
                {
                    Inf_LCD_DisplayPonit(x, y, 1, FontColor);
                }
                tmp <<= 1;
                y++;
            }
            x++;
            // ����ʾһ�����ֵ�ѭ�������У�x��ֵ��������  
            // һ�������ڲ��Ļ����߼�
            if (x - x1 == size)
            {
                x = x1;
                y0 += 8;
            }
        }
        //һ��������ʾ��ɣ�Ϊ��һ��������ʾ��׼��
        x += size;

        if (LCD_W - x < size)//�����Ƿ���Ҫ����
        {
            y1 += size + 4;
            x = 0;
        }
        x1 = x;
        y0 = y1;
    }
    free(pBuff);//�ͷſռ�
}

void Inf_LCD_DisplayLogo(uint16_t x, uint16_t y) {
    Inf_LCD_SetArea(x, y, Img.w, Img.h);
    for (uint32_t i = 0; i < Img.w * Img.h * 2; i += 2)
    {
        Inf_LCD_WriteData(Img.Data[i] << 8 | Img.Data[i + 1]);
    }
}


void Inf_LCD_Reset(void) {
    // PG15���ͼ�Ϊ����
    HAL_GPIO_WritePin(GPIOG, GPIO_pin_15, GPIO_PIN_RESET);
    Delay_ms(5);
    HAL_GPIO_WritePin(GPIOG, GPIO_pin_15, GPIO_PIN_SET);
}
void Inf_LCD_BKOpen(void) {
    // PB0 ����
    HAL_GPIO_WritePin(GPIOB, GPIO_pin_0, GPIO_PIN_SET);
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
