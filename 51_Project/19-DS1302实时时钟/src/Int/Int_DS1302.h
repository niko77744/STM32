#ifndef __INT_DS1302_H__
#define __INT_DS1302_H__

#include "Dri_3Wire.h"

//定义结构体 表示日期时间
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
 * @brief 初始化
 *
 */
void Int_DS1302_Init();

/**
 * @brief 将指定日期时间设置到DS1302的寄存器中
 *
 * @param p_st_date 日期时间
 */
void Int_DS1302_SetDate(Struct_Date* p_st_date);


/**
 * @brief 获取DS1302寄存器中的日期和时间
 *
 * @return 日期时间
 */
Struct_Date Int_DS1302_GetDate();


#endif /* __INT_DS1302_H__ */