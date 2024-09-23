#include "Driver_GeneralTimer.h"

// 用于LED1和LED2的呼吸灯  CH1控制LED1  CH2控制LED2
void Driver_GeneralTimer5_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM5EN;

    // 复用推挽输出 MODE=11  CNF=10
    GPIOA->CRL |= (GPIO_CRL_MODE0 | GPIO_CRL_MODE1 | GPIO_CRL_CNF0_1 | GPIO_CRL_CNF1_1);
    GPIOA->CRL &= ~(GPIO_CRL_CNF0_0 | GPIO_CRL_CNF1_0);

    TIM5->CR1 &= ~TIM_CR1_DIR;  // 0:计数器向上计数；
    // TIM5->CR1 |= TIM_CR1_URS;  // 更新请求源
    // TIM5->EGR |= TIM_EGR_UG;  // Update generation

    // capture/compare Mode register  捕获/比较2选择 (Capture/Compare 2 selection) 
    TIM5->CCMR1 &= ~(TIM_CCMR1_CC2S | TIM_CCMR1_CC1S);  // 00 输出   01：CC1通道被配置为输入，IC1映射在TI1上

    // Output compare 2 enable  110：PWM模式1－ 在向上计数时，一旦TIMx_CNT<TIMx_CCR1时通道1为有效电平，否则为无效电平
    TIM5->CCMR1 |= (TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC1M_2);
    TIM5->CCMR1 |= (TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC1M_1);
    TIM5->CCMR1 &= ~(TIM_CCMR1_OC2M_0 | TIM_CCMR1_OC1M_0);

    // 输入/捕获2输出极性 (Capture/Compare 2 output polarity) 
    TIM5->CCER &= ~(TIM_CCER_CC2P | TIM_CCER_CC1P);  //CC1通道配置为输出时 0：OC1高电平有效

    // 输入/捕获1输出使能 (Capture/Compare 1 output enable)
    TIM5->CCER |= (TIM_CCER_CC2E | TIM_CCER_CC1E); //CC1通道配置为输出时  1：开启OC1,信号输出到对应的输出引脚。

    // 预分频器 Prescaler  7199分频后为1MHz, 1000ns=0.001ms一个周期
    TIM5->PSC = 7199;

    // 自动重装载寄存器 auto reload register  99是为了好算占空比 直接/100
    TIM5->ARR = 99;

    // 比较寄存器的值  捕获/比较1的值 (Capture/Compare 1 value) 
    TIM5->CCR1 = 50;  //小于CCR1是有效电平
    TIM5->CCR2 = 77;

    TIM5->CR1 |= TIM_CR1_CEN;  // 使能计数器
}

//用Time4测量Tim5产生的PWM的频率 / 周期和占空比  需要用杜邦线将B6和A1连接起来  TIM4 - CH1   再利用CH2来测量占空比(下降沿)
void Driver_GeneralTimer4_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
    RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;

    // PB6为浮空输入  MODE=00 CNF=01
    GPIOB->CRL &= ~(GPIO_CRL_MODE6 | GPIO_CRL_CNF6_1);
    GPIOB->CRL |= GPIO_CRL_CNF6_0;

    // 设置计数方向向上  0
    TIM4->CR1 &= ~TIM_CR1_DIR;


    /* 4.配置TIM4的输入捕获部分 */
    // 4.1 配置通道1引脚直连TI1
    TIM4->CR2 &= ~TIM_CR2_TI1S; //-------------


    //!!!!!!!!!!!!!!!!!! DMA/中断使能寄存器  DIER
    // TIM4->DIER |= TIM_DIER_CC1IE; //允许捕获/比较中断(Capture / Compare 4 interrupt enable)  1允许

    // SMS[2:0]：从模式选择 (Slave mode selection)   100 复位模式
    TIM4->SMCR |= TIM_SMCR_SMS_2;
    TIM4->SMCR &= ~(TIM_SMCR_SMS_1 | TIM_SMCR_SMS_0);
    // TS[2:0]：触发选择 (Trigger selection)  101：滤波后的定时器输入1(TI1FP1) 
    TIM4->SMCR |= (TIM_SMCR_TS_2 | TIM_SMCR_TS_0);
    TIM4->SMCR &= ~TIM_SMCR_TS_1;


    // CC1S[1:0]：捕获/比较1 选择 (Capture/Compare 1 selection)  
    TIM4->CCMR1 |= TIM_CCMR1_CC1S_0; // 配置为01：CC1通道被配置为输入，IC1映射在TI1上；
    TIM4->CCMR1 &= ~TIM_CCMR1_CC1S_1;

    // !!!!IC2映射在TI1上  10
    TIM4->CCMR1 &= ~TIM_CCMR1_CC2S_0;
    TIM4->CCMR1 |= TIM_CCMR1_CC2S_1;

    //预分频器 IC1PSC[1:0]：输入/捕获1预分频器 (Input capture 1 prescaler) 00不分频
    TIM4->CCMR1 &= ~(TIM_CCMR1_IC1PSC | TIM_CCMR1_IC2PSC);

    // IC1F[3:0]：输入捕获1滤波器 (Input capture 1 filter)   00不滤波
    TIM4->CCMR1 &= ~(TIM_CCMR1_IC1F | TIM_CCMR1_IC2F);

    // 捕获/比较使能寄存器CCER  
    // CC1P：输入/捕获1输出极性 (Capture/Compare 1 output polarity) 
    // 作为输入时候 0：不反相：捕获发生在IC1的上升沿
    TIM4->CCER &= ~TIM_CCER_CC1P;
    TIM4->CCER |= TIM_CCER_CC2P;  //cc2p下降沿

    // CC1E：输入/捕获1输出使能 (Capture/Compare 1 output enable)  作为输入
    TIM4->CCER |= (TIM_CCER_CC1E | TIM_CCER_CC2E);

    // !!!!!3.1 预分频系数 72分频,时钟频率为1MHz,一次计数表示1us
    TIM4->PSC = 71;

    // 自动重装载
    TIM4->ARR = 65535;  //设置为最大

    // 使能计数
    TIM4->CR1 |= TIM_CR1_CEN;

    // NVIC_SetPriorityGrouping(3);
    // NVIC_SetPriority(TIM4_IRQn, 3);
    // NVIC_EnableIRQ(TIM4_IRQn);
}


void Driver_GeneralTimer5_LED1_SetDutyCycle(uint8_t DutyCycle) {
    TIM5->CCR1 = DutyCycle;
}
void Driver_GeneralTimer5_LED2_SetDutyCycle(uint8_t DutyCycle) {
    TIM5->CCR2 = DutyCycle;
}

// uint8_t PWM_count = 0;
// uint16_t PWM_cycle_time = 0;  //单位是us

// 返回PWM的周期 ms
double Driver_GeneralTimer4_GetCycle(void) {
    return TIM4->CCR1 / 1000.0;  // 计算周期 例如，5000 μs = 5000÷1000 = 5 ms。 5ms也是tim5的100分频后
}
double Driver_GeneralTimer4_GetFrequency(void) {
    return 1000000.0 / TIM4->CCR1; // 计算频率= 1/周期 = 1/(PWM_cycle_time/1000000)
}

double Driver_GeneralTimer4_GetDutyCycle(void) {
    return (TIM4->CCR2 * 1.0) / TIM4->CCR1; // 计算占空比= 高电平持续的时间/周期 
}

// 利用从模式替代中断对CNF置0
// void TIM4_IRQHandler(void) {
//     TIM4->SR &= ~TIM_SR_CC1IF;
//     TIM4->CNT = 0;
// }
