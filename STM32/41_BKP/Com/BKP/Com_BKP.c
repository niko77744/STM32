#include "Com_BKP.h"

void Com_RTCEx_BKPInit(void) {
    // 初始化RTC和后备寄存器
    /* 1. 使能 PWR 时钟 */
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    /* 2.开启写使能 */
    PWR->CR |= PWR_CR_DBP;
    /* 3. 使能 BKP 时钟 */
    RCC->APB1ENR |= RCC_APB1ENR_BKPEN;
    /* 4. 如果已经向 DR1寄存器写入过值，证明备份域已经复位过。可以直接返回了 */
    if (BKP->DR1) return;

    /* 切换RTC时钟 和 复位整个备份域 */

    /* 5. 复位备份域 */
    RCC->BDCR |= RCC_BDCR_BDRST;
    /* 6. 解除备份域复位 */
    RCC->BDCR &= ~RCC_BDCR_BDRST;
    /* 7. 使能 RTC 时钟 */
    RCC->BDCR |= RCC_BDCR_RTCEN;

    /* 8. 使能 LSE */
    RCC->BDCR |= RCC_BDCR_LSEON;
    while ((RCC->BDCR & RCC_BDCR_LSERDY) == 0);

    /* 9. 使用 LSE(外部低俗时钟) 作为 RTC 时钟  01：LSE振荡器作为RTC时钟 */
    RCC->BDCR |= RCC_BDCR_RTCSEL_0;
    RCC->BDCR &= ~RCC_BDCR_RTCSEL_1;
}


uint32_t Com_RTCEx_BPKRead(uint32_t BackupRegister) {
    uint32_t backupregister = 0U;
    uint32_t pvalue = 0U;

    assert_param(IS_RTC_BKP(BackupRegister));

    backupregister = (uint32_t)BKP_BASE;
    backupregister += (BackupRegister * 4U);

    pvalue = (*(__IO uint32_t*)(backupregister)) & BKP_DR1_D;

    return pvalue;
}

void Com_RTCEx_BKPWrite(uint32_t BackupRegister, uint32_t Data) {
    uint32_t tmp = 0U;

    /* Check the parameters */
    assert_param(IS_RTC_BKP(BackupRegister));

    tmp = (uint32_t)BKP_BASE;
    tmp += (BackupRegister * 4U);

    *(__IO uint32_t*) tmp = (Data & BKP_DR1_D);
}
