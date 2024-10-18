#ifndef __COM_BKP_H__
#define __COM_BKP_H__

#include "stm32f10x.h"
#include <time.h>

typedef struct
{
    uint16_t year;
    uint8_t month;
    uint8_t week;
    uint8_t day;
    uint8_t hour;
    uint8_t mintue;
    uint8_t second;
    uint8_t now[32];
} RTC_TimeTypeDef;

#define RTC_BKP_NUMBER 42
#define assert_param(expr) ((void)0U)
#define IS_RTC_BKP(BKP)  (((BKP) <= (uint32_t)RTC_BKP_DR10) || (((BKP) >= (uint32_t)RTC_BKP_DR11) && ((BKP) <= (uint32_t)RTC_BKP_DR42)))

#if RTC_BKP_NUMBER > 0U
#define RTC_BKP_DR1                         0x00000001U
#define RTC_BKP_DR2                         0x00000002U
#define RTC_BKP_DR3                         0x00000003U
#define RTC_BKP_DR4                         0x00000004U
#define RTC_BKP_DR5                         0x00000005U
#define RTC_BKP_DR6                         0x00000006U
#define RTC_BKP_DR7                         0x00000007U
#define RTC_BKP_DR8                         0x00000008U
#define RTC_BKP_DR9                         0x00000009U
#define RTC_BKP_DR10                        0x0000000AU
#endif /* RTC_BKP_NUMBER > 0 */

#if RTC_BKP_NUMBER > 10U
#define RTC_BKP_DR11                        0x00000010U
#define RTC_BKP_DR12                        0x00000011U
#define RTC_BKP_DR13                        0x00000012U
#define RTC_BKP_DR14                        0x00000013U
#define RTC_BKP_DR15                        0x00000014U
#define RTC_BKP_DR16                        0x00000015U
#define RTC_BKP_DR17                        0x00000016U
#define RTC_BKP_DR18                        0x00000017U
#define RTC_BKP_DR19                        0x00000018U
#define RTC_BKP_DR20                        0x00000019U
#define RTC_BKP_DR21                        0x0000001AU
#define RTC_BKP_DR22                        0x0000001BU
#define RTC_BKP_DR23                        0x0000001CU
#define RTC_BKP_DR24                        0x0000001DU
#define RTC_BKP_DR25                        0x0000001EU
#define RTC_BKP_DR26                        0x0000001FU
#define RTC_BKP_DR27                        0x00000020U
#define RTC_BKP_DR28                        0x00000021U
#define RTC_BKP_DR29                        0x00000022U
#define RTC_BKP_DR30                        0x00000023U
#define RTC_BKP_DR31                        0x00000024U
#define RTC_BKP_DR32                        0x00000025U
#define RTC_BKP_DR33                        0x00000026U
#define RTC_BKP_DR34                        0x00000027U
#define RTC_BKP_DR35                        0x00000028U
#define RTC_BKP_DR36                        0x00000029U
#define RTC_BKP_DR37                        0x0000002AU
#define RTC_BKP_DR38                        0x0000002BU
#define RTC_BKP_DR39                        0x0000002CU
#define RTC_BKP_DR40                        0x0000002DU
#define RTC_BKP_DR41                        0x0000002EU
#define RTC_BKP_DR42                        0x0000002FU
#endif /* RTC_BKP_NUMBER > 10 */

void Com_RTCEx_BKPInit(void);
void Com_RTCEx_BKPWrite(uint32_t BackupRegister, uint32_t Data);
uint32_t Com_RTCEx_BPKRead(uint32_t BackupRegister);


void Com_RTC_Init(void);
void Com_RTC_SetTime(uint32_t UnixTimestamp);
void Com_RTC_GetTime(RTC_TimeTypeDef* datatime);
#endif /* __COM_BKP_H__ */
