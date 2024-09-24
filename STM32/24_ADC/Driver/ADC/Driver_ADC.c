#include "Driver_ADC.h"

// ADC1 的 CH10
// 规则通道最多为16通道(IN0-In15)，数据寄存器只有一个
// 注入通道最多为4通道，但是数据寄存器有4个
void Driver_ADC1_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_ADC1EN;
    // 10：PCLK2 6分频后作为ADC时钟  2 4 6 8  00-11
    RCC->CFGR |= RCC_CFGR_ADCPRE_1;
    RCC->CFGR &= ~RCC_CFGR_ADCPRE_0;

    // 配置GPIO  模拟输入 MODE=CNF=00  PC0
    GPIOC->CRL &= ~(GPIO_CRL_MODE0 | GPIO_CRL_CNF0);

    ADC1->CR1 &= ~ADC_CR1_SCAN; //关闭扫描(只转换通道组的第一个通道)  多通道顺序扫描挨个转换
    ADC1->CR2 |= ADC_CR2_CONT; // 开启连续 
    ADC1->CR2 &= ~ADC_CR2_ALIGN; //0右对齐

    //配置采样时间 001 7.5个周期  一共18个通道 0 - 17
    ADC1->SMPR1 |= ADC_SMPR1_SMP10_0; //001 7.5周期 每个通道的采样时间
    ADC1->SMPR1 &= ~(ADC_SMPR1_SMP10_1 | ADC_SMPR1_SMP10_2);

    ADC1->SQR1 &= ~ADC_SQR1_L; // 0000 1个转换 定义在规则通道转换序列中的通道数目
    ADC1->SQR3 &= ~ADC_SQR3_SQ1; //先清空该位，避免默认值可能是1导致错误
    // 这些位由软件定义转换序列中的第16个转换通道的编号(0~17) 5位
    ADC1->SQR3 |= (10 << 0);  // 将10号通道配置在最后5位,表示组中第一个通道为10号通道

    // ADC1->CR2 |= ADC_CR2_EXTSEL; //选择启动规则通道组转换的外部事件  111软件
    // ADC1->CR2 |= ADC_CR2_EXTTRIG; //1：使用外部事件启动转换。
}
void Driver_ADC1_Start(void) {
    // 上电唤醒 写1唤醒 再写1启动转换  0进入断电模式并关闭AD转换和校准
    ADC1->CR2 |= ADC_CR2_ADON;

    //RSTCAL 是用于复位校准状态，为新的校准做准备；而 CAL 则是直接启动 ADC 的校准过程，以获取准确的转换误差修正值，提高 ADC 的转换精度。
    ADC1->CR2 |= ADC_CR2_RSTCAL;
    while (ADC1->CR2 & ADC_CR2_RSTCAL); //等到rstcal=0完成校准
    // A/D校准 相当于校准天平
    ADC1->CR2 |= ADC_CR2_CAL;
    while (ADC1->CR2 & ADC_CR2_CAL); //等到cal=0完成校准

    // 延迟一段时间后再写1 替代ADC_CR2_EXTSEL和ADC_CR2_EXTTRIG和ADC_CR2_SWSTART
    ADC1->CR2 |= ADC_CR2_ADON;
    // ADC1->CR2 |= ADC_CR2_SWSTART; //1：开始转换规则通道。如果在EXTSEL[2:0]位中选择了SWSTART为触发事件，该位用于启动一组规则通道的转换，
    while (!(ADC1->SR & ADC_SR_EOC));
}
double Driver_ADC1_GetValue(void) {
    return (ADC1->DR * 3.3) / 4095;  //ADC分辨率为12位，4096-1
}

