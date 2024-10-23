#include "Int_DS1302.h"
#include "Dri_3Wire.h"

// ���üĴ�����ַ  Ĭ��д
#define SECOND 0x80
#define MINUTE 0x82
#define HOUR 0x84
#define DAY_OF_MONTH 0x86
#define MONTH 0x88
#define DAY_OF_WEEK 0x8A
#define YEAR 0x8C
#define WP 0x8E



static void Int_DS1302_SetRegister(u8 addr, u8 datas) {
    CE = 1;
    Dri_3Wire_SendByte(addr);
    Dri_3Wire_SendByte(datas);
    CE = 0;
}


static u8 Int_DS1302_GetRegister(u8 addr) {
    u8 byte;
    CE = 1;
    Dri_3Wire_SendByte(addr + 1);
    byte = Dri_3Wire_ReceiveByte();
    CE = 0;

    return byte;
}

/**
 * @brief ��ʼ��
 *
 */
void Int_DS1302_Init() {
    CE = 0;
    SCLK = 0;
    IO = 0;
}

/**
  * @brief ��ָ������ʱ�����õ�DS1302�ļĴ�����
  *
  * @param p_st_date ����ʱ��
  */
void Int_DS1302_SetDate(Struct_Date* p_st_date) {
    // �ر�д����
    Int_DS1302_SetRegister(WP, 0x00);
    Int_DS1302_SetRegister(SECOND, ((p_st_date->second / 10) << 4) + (p_st_date->second % 10));
    Int_DS1302_SetRegister(MINUTE, ((p_st_date->minute / 10) << 4) + (p_st_date->minute % 10));
    Int_DS1302_SetRegister(HOUR, ((p_st_date->hour / 10) << 4) + (p_st_date->hour % 10));
    Int_DS1302_SetRegister(DAY_OF_MONTH, ((p_st_date->day_of_month / 10) << 4) + (p_st_date->day_of_month % 10));
    Int_DS1302_SetRegister(MONTH, ((p_st_date->month / 10) << 4) + (p_st_date->month % 10));
    Int_DS1302_SetRegister(DAY_OF_WEEK, ((p_st_date->day_of_week / 10) << 4) + (p_st_date->day_of_week % 10));
    Int_DS1302_SetRegister(YEAR, ((p_st_date->year / 10) << 4) + (p_st_date->year % 10));
    // ����д����
    Int_DS1302_SetRegister(WP, 0x80);
}


/**
 * @brief ��ȡDS1302�Ĵ����е����ں�ʱ��
 *
 * @return ����ʱ��
 */
Struct_Date Int_DS1302_GetDate() {
    u8 temp;
    Struct_Date st_date;
    temp = Int_DS1302_GetRegister(SECOND);
    st_date.second = (temp & 0x0F) + (temp >> 4) * 10;

    // ��ȡ���ӼĴ���
    temp = Int_DS1302_GetRegister(MINUTE);
    st_date.minute = (temp >> 4) * 10 + (temp & 0x0F);

    // ��ȡСʱ�Ĵ���
    temp = Int_DS1302_GetRegister(HOUR);
    st_date.hour = (temp >> 4) * 10 + (temp & 0x0F);

    // ��ȡ�ռĴ���(ÿ��)
    temp = Int_DS1302_GetRegister(DAY_OF_MONTH);
    st_date.day_of_month = (temp >> 4) * 10 + (temp & 0x0F);

    // ��ȡ�ռĴ���(ÿ��)
    temp = Int_DS1302_GetRegister(DAY_OF_WEEK);
    st_date.day_of_week = temp;

    // ��ȡ�¼Ĵ���
    temp = Int_DS1302_GetRegister(MONTH);
    st_date.month = (temp >> 4) * 10 + (temp & 0x0F);

    // ��ȡ��Ĵ���
    temp = Int_DS1302_GetRegister(YEAR);
    st_date.year = (temp >> 4) * 10 + (temp & 0x0F);

    // ����
    return st_date;
}