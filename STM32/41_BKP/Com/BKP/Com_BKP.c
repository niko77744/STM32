#include "Com_BKP.h"

void Com_RTCEx_BKPInit(void) {
    // ��ʼ��RTC�ͺ󱸼Ĵ���
    /* 1. ʹ�� PWR ʱ�� */
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    /* 2.����дʹ�� */
    PWR->CR |= PWR_CR_DBP;
    /* 3. ʹ�� BKP ʱ�� */
    RCC->APB1ENR |= RCC_APB1ENR_BKPEN;
    /* 4. ����Ѿ��� DR1�Ĵ���д���ֵ��֤���������Ѿ���λ��������ֱ�ӷ����� */
    if (BKP->DR1) return;

    /* �л�RTCʱ�� �� ��λ���������� */

    /* 5. ��λ������ */
    RCC->BDCR |= RCC_BDCR_BDRST;
    /* 6. ���������λ */
    RCC->BDCR &= ~RCC_BDCR_BDRST;
    /* 7. ʹ�� RTC ʱ�� */
    RCC->BDCR |= RCC_BDCR_RTCEN;

    /* 8. ʹ�� LSE */
    RCC->BDCR |= RCC_BDCR_LSEON;
    while ((RCC->BDCR & RCC_BDCR_LSERDY) == 0);

    /* 9. ʹ�� LSE(�ⲿ����ʱ��) ��Ϊ RTC ʱ��  01��LSE������ΪRTCʱ�� */
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
