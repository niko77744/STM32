#include "Com_RTC.h"

void Com_RTC_Init(void) {
    /* 1. ��ʱ��  PWR  BKP */
    RCC->APB1ENR |= (RCC_APB1ENR_PWREN | RCC_APB1ENR_BKPEN);
    /* 2. �򿪱��������дʹ�� */
    PWR->CR |= PWR_CR_DBP;
    /* 3. ����LSE�ⲿ����ʱ��  ��ΪRTC��ϵͳʱ�� */
    // 3.1 ����LSE�ⲿ����ʱ��
    RCC->BDCR |= RCC_BDCR_LSEON;
    while ((RCC->BDCR & RCC_BDCR_LSERDY) == 0);
    // 3.2 ѡ���ⲿ����ʱ����ΪRTCϵͳʱ��
    RCC->BDCR |= RCC_BDCR_RTCSEL_0;
    RCC->BDCR &= ~RCC_BDCR_RTCSEL_1;
    // 3.3 ����RTCʱ��
    RCC->BDCR |= RCC_BDCR_RTCEN;

    /* 4. ����RTC���� => ������  ��Ҫ����Ԥ��Ƶϵ�� */
    // 4.1 ��ѯRTOFFλ��ֱ��RTOFF��ֵ��Ϊ1
    while ((RTC->CRL & RTC_CRL_RTOFF) == 0);
    // 4.2 ��CNFֵΪ1����������ģʽ
    RTC->CRL |= RTC_CRL_CNF;
    // 4.3 ��һ������RTC�Ĵ�������д���� 
    // ��Ҫ�޸�Ԥ��Ƶϵ��  PRL  ����Ƶ�� = rtcclk(32768) / (prl + 1)
    RTC->PRLL = 0x7FFF;
    // 4.4 ���CNF��־λ���˳�����ģʽ
    RTC->CRL &= ~RTC_CRL_CNF;

    // 4.5 ��ѯRTOFF��ֱ��RTOFFλ��Ϊ1��ȷ��д�����Ѿ���ɡ�
    while ((RTC->CRL & RTC_CRL_RTOFF) == 0);
}
void Com_RTC_SetTime(uint32_t UnixTimestamp) {
    // ��ʱ���ת��Ϊ������ʱ���  +8h
    UnixTimestamp += 28800;

    /* ��timestamp���뵽CNT�� */
    // 1. ��ѯRTOFFλ��ֱ��RTOFF��ֵ��Ϊ1
    while ((RTC->CRL & RTC_CRL_RTOFF) == 0);
    // 2. ��CNFֵΪ1����������ģʽ
    RTC->CRL |= RTC_CRL_CNF;

    // 3. ��һ������RTC�Ĵ�������д���� 
    // 3.1 �ȴ����־
    while ((RTC->CRL & RTC_CRL_SECF) == 0);
    // 3.2 ��timpstampд�뵽CNT��
    RTC->CNTH = (UnixTimestamp) >> 16;
    RTC->CNTL = (UnixTimestamp & 0xFFFF) >> 0;

    // 4. ���CNF��־λ���˳�����ģʽ
    RTC->CRL &= ~RTC_CRL_CNF;

    // 5. ��ѯRTOFF��ֱ��RTOFFλ��Ϊ1��ȷ��д�����Ѿ���ɡ�
    while ((RTC->CRL & RTC_CRL_RTOFF) == 0);
}

void Com_RTC_GetTime(RTC_TimeTypeDef* datetime) {
    // 1. �ȵ��Ĵ���ͬ��  ���ڶ�ȡRTC�Ĵ���ʱ��RTC��APB1�ӿ��������ڽ�ֹ״̬����������ȱ���ȴ�RTC_CRL�Ĵ����е�RSFλ(�Ĵ���ͬ����־)��Ӳ����1��
    while ((RTC->CRL & RTC_CRL_RSF) == 0);

    // 2. ����CNT��ֵ Ҳ���ǵ�ǰʱ���
    uint32_t Current_timestamp = (RTC->CNTH << 16) | (RTC->CNTL);

    // 3. ��CNT��ֵת��Ϊ������ʱ����  ����ֵstruct tm*
    struct tm* datetime_tm = localtime(&Current_timestamp);

    datetime->second = datetime_tm->tm_sec;
    datetime->mintue = datetime_tm->tm_min;
    datetime->hour = datetime_tm->tm_hour;
    datetime->day = datetime_tm->tm_mday;
    datetime->week = datetime_tm->tm_wday;
    datetime->month = datetime_tm->tm_mon + 1;  //��0�¿�ʼ
    datetime->year = datetime_tm->tm_year + 1900;
    sprintf((char*)datetime->now, "%04d��-%02d��-%02d��-����%d %02dʱ:%02d��:%02d��", datetime->year, datetime->month, datetime->day, datetime->week, datetime->hour, datetime->mintue, datetime->second);
}

