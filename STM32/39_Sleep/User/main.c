#include "Driver_USART.h"
#include "Com_Delay.h"
#include "Driver_LED.h"
#include "Driver_Key.h"

typedef struct
{
    uint32_t System_Clock;
    uint32_t AHB_Clock;
    uint32_t APB1_Clock;
    uint32_t APB2_Clock;
}Clock;
Clock system_clock;


void HAL_PWR_EnterSLEEPMode(void);
void HAL_PWR_EnterSTOPMode(void);
void SystemClock_Config(void);
void Get_SystemClock_Config(void);

int main(int argc, char const* argv[]) {
    Driver_USART_Init();
    Driver_LED_Init();
    Driver_KEY_Init();
    printf("hello\n");
    Driver_LED_On(LED2);

    // Get_SystemClock_Config();
    // printf("1: System_Clock = %d, AHB_Clock = %d, APB1_Clock = %d, APB2_Clock = %d\n", system_clock.System_Clock, system_clock.AHB_Clock, system_clock.APB1_Clock, system_clock.APB2_Clock);


    while (1) {
        printf("6s�����˯��ģʽ\n");
        Delay_s(3);
        // HAL_PWR_EnterSLEEPMode();
        HAL_PWR_EnterSTOPMode();

        /* ����ϵͳʱ���� */
        SystemClock_Config();
        Get_SystemClock_Config();
        Delay_ms(1000);
        printf("1: System_Clock = %d, AHB_Clock = %d, APB1_Clock = %d, APB2_Clock = %d\n", system_clock.System_Clock, system_clock.AHB_Clock, system_clock.APB1_Clock, system_clock.APB2_Clock);
        printf("������\n");
    }
}


void HAL_PWR_EnterSLEEPMode(void) {
    Delay_s(3);
    SCB->SCR &= ~SCB_SCR_SLEEPDEEP;
    __WFI();
}


void HAL_PWR_EnterSTOPMode(void) {
    // Power PWR
    Delay_s(3);
    // ���� PWR ʱ��
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    // �����Դ�������е�PDDSλ ������˯��ʱ������ͣ��ģʽ
    PWR->CR &= ~PWR_CR_PDDS;
    // ���õ�ѹ��������ģʽ 0����ѹ���������� 1����ѹ���������ڵ͹���ģʽ
    PWR->CR &= ~PWR_CR_LPDS;
    // ϵͳ���ƼĴ��������˯��ģʽ
    SCB->SCR |= SCB_SCR_SLEEPDEEP;
    __WFI();
}


void SystemClock_Config(void) {
    /* 1. ʹ��HSE ���ȴ����� */
    /* 2. ʹ��PLL ���ȴ����� */
    /* 3.ѡ�� PLL ��Ϊϵͳʱ��Դ CFGR_SW λ����  ���ȴ� PLL ��ѡΪϵͳʱ��Դ */
    RCC->CR |= RCC_CR_HSEON;
    while ((RCC->CR & RCC_CR_HSERDY) == 0); //1���ⲿ4-16MHz����������

    RCC->CR |= RCC_CR_PLLON;
    while ((RCC->CR & RCC_CR_PLLRDY)); //1��PLL����

    // ϵͳʱ���л� (System clock switch)  10��PLL�����Ϊϵͳʱ��
    RCC->CFGR |= RCC_CFGR_SW_1;
    RCC->CFGR &= ~RCC_CFGR_SW_0;
    while ((RCC->CR & RCC_CFGR_SWS) == 0); //1��PLL����
}

void Get_SystemClock_Config(void) {
    /* ----------------System_Clock-------------------- */
    uint32_t system_clock_source = (RCC->CFGR & RCC_CFGR_SWS);
    if (system_clock_source == RCC_CFGR_SWS_HSE)
    {
        system_clock.System_Clock = HSE_Value;
    }
    else if (system_clock_source == RCC_CFGR_SWS_HSI)
    {
        system_clock.System_Clock = HSI_Value;
    }
    else if (system_clock_source == RCC_CFGR_SWS_PLL)
    {
        /* Ĭ�����PLLʱ��HSE��9��Ƶ */
        // PLL multiplication factor PLL��Ƶϵ��
        uint32_t mul = ((RCC->CFGR & RCC_CFGR_PLLMULL) >> 18) + 2;
        system_clock.System_Clock = HSE_Value * mul;
    }


    /* ----------------AHB_Clock-------------------- */
    // ��ȡAHB����ʱ��Ƶ�� Ĭ�����AHB����ϵͳƵ��
    uint32_t hpre = (RCC->CR & RCC_CFGR_HPRE) >> 4;

    /* ���λ��1 �з�Ƶ */
    (hpre & 0x08) == 0 ? (system_clock.AHB_Clock = system_clock.System_Clock) : (system_clock.AHB_Clock = system_clock.System_Clock >> ((hpre & 0x07) + 1));

    /* ----------------APB1_Clock-------------------- */
    // APB1��Ƶ�� Ĭ���� ϵͳƵ��2��Ƶ
    uint32_t ppre1 = (RCC->CFGR & RCC_CFGR_PPRE1) >> 8;
    (ppre1 & 0x04) == 0 ? (system_clock.APB1_Clock = system_clock.AHB_Clock) : (system_clock.APB1_Clock = system_clock.AHB_Clock >> ((ppre1 & 0x03) + 1));


    /* ----------------APB2_Clock-------------------- */
    uint32_t ppre2 = (RCC->CFGR & RCC_CFGR_PPRE1) >> 11;
    (ppre2 & 0x04) == 0 ? (system_clock.APB2_Clock = system_clock.AHB_Clock) : (system_clock.APB2_Clock = system_clock.AHB_Clock >> ((ppre2 & 0x03) + 1));
}
