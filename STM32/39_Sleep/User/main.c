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


void HAL_PWR_EnterSLEEPMode(void);
void HAL_PWR_EnterSTOPMode(void);
void HAL_PWR_EnterSTANDBYMode(void);
void SystemClock_Config(void);
Clock Get_SystemClock_Config(void);

int main(int argc, char const* argv[]) {
    Driver_USART_Init();
    Driver_LED_Init();
    Driver_KEY_Init();
    printf("hello\n");
    Driver_LED_On(LED2);

    /* 案例三：待机模式 */
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;

    if ((PWR->CSR & PWR_CSR_WUF) != 0)  //唤醒标志
    {
        // CSBF：清除待机位  CWUF：清除唤醒位
        PWR->CR |= (PWR_CR_CSBF | PWR_CR_CWUF);
        printf("从待机模式唤醒\n");
    }
    else {
        printf("复位键唤醒\n");
    }


    while (1) {
        printf("6s后进入睡眠模式\n");
        Delay_s(3);
        HAL_PWR_EnterSTANDBYMode();


        /* 案例一: 睡眠模式
        // HAL_PWR_EnterSLEEPMode(); */


        /* 案例二: 停机模式
        HAL_PWR_EnterSTOPMode();
        Clock ck1 = Get_SystemClock_Config();
        //设置系统时钟树
        SystemClock_Config();
        Clock ck2 = Get_SystemClock_Config();
        printf("设置系统时钟树前: System_Clock = %d, AHB_Clock = %d, APB1_Clock = %d, APB2_Clock = %d\n", ck1.System_Clock / 1000000, ck1.AHB_Clock / 1000000, ck1.APB1_Clock / 1000000, ck1.APB2_Clock / 1000000);
        printf("设置系统时钟树后: System_Clock = %d, AHB_Clock = %d, APB1_Clock = %d, APB2_Clock = %d\n", ck2.System_Clock / 1000000, ck2.AHB_Clock / 1000000, ck2.APB1_Clock / 1000000, ck2.APB2_Clock / 1000000); */
        printf("被唤醒\n");
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
    // 开启 PWR 时钟
    RCC->APB1ENR |= RCC_APB1ENR_PWREN;
    // 清除电源控制器中的PDDS位 进入深睡眠时，进入停机模式
    PWR->CR &= ~PWR_CR_PDDS;  // PDDS：掉电深睡眠  调压器的状态
    // 设置电压调节器的模式 0：电压调节器开启 1：电压调节器处于低功耗模式
    PWR->CR &= ~PWR_CR_LPDS;
    /*
    PDDS：掉电深睡眠   0：当CPU进入深睡眠时进入停机模式，调压器的状态由LPDS位控制。   1：CPU进入深睡眠时进入待机模式
    LPDS：深睡眠下的低功耗  PDDS=0时，与PDDS位协同操作  0：在停机模式下电压调压器开启  1：在停机模式下电压调压器处于低功耗模式
    */
    // 系统控制寄存器的深度睡眠模式
    SCB->SCR |= SCB_SCR_SLEEPDEEP;
    __WFI();
}

void HAL_PWR_EnterSTANDBYMode(void) {
    // 开启PWR的RCC时钟需要提前进行  因为待机模式每次从头执行代码
    PWR->CR |= PWR_CR_PDDS;
    PWR->CSR |= PWR_CSR_EWUP;

    SCB->SCR |= SCB_SCR_SLEEPDEEP;
    __WFI();
}

void SystemClock_Config(void) {
    /* 1. 使能HSE 并等待就绪 */
    /* 2. 使能PLL 并等待就绪 */
    /* 3.选择 PLL 作为系统时钟源 CFGR_SW 位控制  并等待 PLL 被选为系统时钟源 */
    RCC->CR |= RCC_CR_HSEON;
    while ((RCC->CR & RCC_CR_HSERDY) == 0); //1：外部4-16MHz振荡器就绪。

    RCC->CR |= RCC_CR_PLLON;
    while ((RCC->CR & RCC_CR_PLLRDY) == 0); //1：PLL锁定

    // 系统时钟切换 (System clock switch)  10：PLL输出作为系统时钟
    RCC->CFGR |= RCC_CFGR_SW_1;
    RCC->CFGR &= ~RCC_CFGR_SW_0;
    while ((RCC->CFGR & RCC_CFGR_SWS) == 0); //1：PLL锁定
}

Clock Get_SystemClock_Config(void) {
    Clock system_clock;
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
        /* 默认情况PLL时用HSE的9倍频 */
        // PLL multiplication factor PLL倍频系数
        uint32_t mul = ((RCC->CFGR & RCC_CFGR_PLLMULL) >> 18) + 2;
        system_clock.System_Clock = HSE_Value * mul;
    }


    /* ----------------AHB_Clock-------------------- */
    // 获取AHB总线时钟频率 默认情况AHB等于系统频率
    uint32_t hpre = (RCC->CFGR & RCC_CFGR_HPRE) >> 4;

    /* 最高位是1 有分频 */
    (hpre & 0x08) == 0 ? (system_clock.AHB_Clock = system_clock.System_Clock) : (system_clock.AHB_Clock = system_clock.System_Clock >> ((hpre & 0x07) + 1));

    /* ----------------APB1_Clock-------------------- */
    // APB1的频率 默认是 系统频率2分频
    uint32_t ppre1 = (RCC->CFGR & RCC_CFGR_PPRE1) >> 8;
    (ppre1 & 0x04) == 0 ? (system_clock.APB1_Clock = system_clock.AHB_Clock) : (system_clock.APB1_Clock = system_clock.AHB_Clock >> ((ppre1 & 0x03) + 1));


    /* ----------------APB2_Clock-------------------- */
    uint32_t ppre2 = (RCC->CFGR & RCC_CFGR_PPRE1) >> 11;
    (ppre2 & 0x04) == 0 ? (system_clock.APB2_Clock = system_clock.AHB_Clock) : (system_clock.APB2_Clock = system_clock.AHB_Clock >> ((ppre2 & 0x03) + 1));

    return system_clock;
}
