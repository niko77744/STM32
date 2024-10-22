#include "Driver_USART.h"
#include "Driver_AdvancedTimer.h"
#include "Driver_ADC.h"
uint16_t buffer[1] = { 0 };
uint8_t timfinsh = 0;
int main(int argc, char const* argv[])
{
    Driver_USARTx_Init(USART1);
    Driver_USARTx_Init(USART2);
    printf("hello\n");
    AdvancedTimer_Count_Init(TIM1);
    AdvancedTimer_Start(TIM1);
    ADCx_Init(ADC1);
    ADCx_Start(ADC1, (uint32_t)buffer, 1);

    while (1) {
        if (timfinsh == 1)
        {
            timfinsh = 0;
            printf("buffer = %.2lf\n", (buffer[0] * (3.3 / 4095.0)));
        }
    }
}

void TIM1_UP_IRQHandler(void) {
    if ((TIM1->SR & TIM_SR_UIF) != 0)
    {
        TIM1->SR &= ~TIM_SR_UIF;
        timfinsh = 1;
    }
}
