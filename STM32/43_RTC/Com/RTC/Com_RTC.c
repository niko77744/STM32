#include "Com_RTC.h"

void Com_RTC_Init(void) {
    /* 1. 打开时钟  PWR  BKP */
    RCC->APB1ENR |= (RCC_APB1ENR_PWREN | RCC_APB1ENR_BKPEN);
    /* 2. 打开备份区域的写使能 */
    PWR->CR |= PWR_CR_DBP;
    /* 3. 配置LSE外部低速时钟  作为RTC的系统时钟 */
    // 3.1 开启LSE外部低速时钟
    RCC->BDCR |= RCC_BDCR_LSEON;
    while ((RCC->BDCR & RCC_BDCR_LSERDY) == 0);
    // 3.2 选择外部低速时钟作为RTC系统时钟
    RCC->BDCR |= RCC_BDCR_RTCSEL_0;
    RCC->BDCR &= ~RCC_BDCR_RTCSEL_1;
    // 3.3 开启RTC时钟
    RCC->BDCR |= RCC_BDCR_RTCEN;

    /* 4. 配置RTC过程 => 计数器  主要配置预分频系数 */
    // 4.1 查询RTOFF位，直到RTOFF的值变为1
    while ((RTC->CRL & RTC_CRL_RTOFF) == 0);
    // 4.2 置CNF值为1，进入配置模式
    RTC->CRL |= RTC_CRL_CNF;
    // 4.3 对一个或多个RTC寄存器进行写操作 
    // 主要修改预分频系数  PRL  计算频率 = rtcclk(32768) / (prl + 1)
    RTC->PRLL = 0x7FFF;
    // 4.4 清除CNF标志位，退出配置模式
    RTC->CRL &= ~RTC_CRL_CNF;

    // 4.5 查询RTOFF，直至RTOFF位变为1以确认写操作已经完成。
    while ((RTC->CRL & RTC_CRL_RTOFF) == 0);
}
void Com_RTC_SetTime(uint32_t UnixTimestamp) {
    // 将时间戳转换为东八区时间戳  +8h
    UnixTimestamp += 28800;

    /* 将timestamp存入到CNT中 */
    // 1. 查询RTOFF位，直到RTOFF的值变为1
    while ((RTC->CRL & RTC_CRL_RTOFF) == 0);
    // 2. 置CNF值为1，进入配置模式
    RTC->CRL |= RTC_CRL_CNF;

    // 3. 对一个或多个RTC寄存器进行写操作 
    // 3.1 等待秒标志
    while ((RTC->CRL & RTC_CRL_SECF) == 0);
    // 3.2 将timpstamp写入到CNT中
    RTC->CNTH = (UnixTimestamp) >> 16;
    RTC->CNTL = (UnixTimestamp & 0xFFFF) >> 0;

    // 4. 清除CNF标志位，退出配置模式
    RTC->CRL &= ~RTC_CRL_CNF;

    // 5. 查询RTOFF，直至RTOFF位变为1以确认写操作已经完成。
    while ((RTC->CRL & RTC_CRL_RTOFF) == 0);
}

void Com_RTC_GetTime(RTC_TimeTypeDef* datetime) {
    // 1. 等到寄存器同步  若在读取RTC寄存器时，RTC的APB1接口曾经处于禁止状态，则软件首先必须等待RTC_CRL寄存器中的RSF位(寄存器同步标志)被硬件置1。
    while ((RTC->CRL & RTC_CRL_RSF) == 0);

    // 2. 读出CNT的值 也就是当前时间戳
    uint32_t Current_timestamp = (RTC->CNTH << 16) | (RTC->CNTL);

    // 3. 将CNT的值转换为年月日时分秒  返回值struct tm*
    struct tm* datetime_tm = localtime(&Current_timestamp);

    datetime->second = datetime_tm->tm_sec;
    datetime->mintue = datetime_tm->tm_min;
    datetime->hour = datetime_tm->tm_hour;
    datetime->day = datetime_tm->tm_mday;
    datetime->week = datetime_tm->tm_wday;
    datetime->month = datetime_tm->tm_mon + 1;  //从0月开始
    datetime->year = datetime_tm->tm_year + 1900;
    sprintf((char*)datetime->now, "%04d年-%02d月-%02d日-星期%d %02d时:%02d分:%02d秒", datetime->year, datetime->month, datetime->day, datetime->week, datetime->hour, datetime->mintue, datetime->second);
}

