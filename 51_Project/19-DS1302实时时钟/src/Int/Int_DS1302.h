#ifndef __INT_DS1302_H__
#define __INT_DS1302_H__

#include "Dri_3Wire.h"

//����ṹ�� ��ʾ����ʱ��
typedef struct
{
    u8 year;
    u8 month;
    u8 day_of_month;
    u8 day_of_week;
    u8 hour;
    u8 minute;
    u8 second;
} Struct_Date;

/**
 * @brief ��ʼ��
 *
 */
void Int_DS1302_Init();

/**
 * @brief ��ָ������ʱ�����õ�DS1302�ļĴ�����
 *
 * @param p_st_date ����ʱ��
 */
void Int_DS1302_SetDate(Struct_Date* p_st_date);


/**
 * @brief ��ȡDS1302�Ĵ����е����ں�ʱ��
 *
 * @return ����ʱ��
 */
Struct_Date Int_DS1302_GetDate();


#endif /* __INT_DS1302_H__ */