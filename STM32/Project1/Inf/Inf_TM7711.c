#include "Inf_TM7711.h"


void Inf_TM7711_Init(void) {
    Driver_GPIO_TM7711_Init();
}


/**
 * @brief 读取水位传感器的值 测量24位，最高位是符号位 带正负号
 *  时序 最小0.2us  最大50us  高位先发 前24位为有效数据 25位为无效数据
 *
 * 考虑正负号的数据 范围        DATA存的数据是用补码存的  ->  转换为正数存储
 * 0x800000 - 0x7fffff
 *      ↓
 * 异或0x800000   同0异1
 *      ↓
 * 不考虑正负号
 * 0x000000 - 0xffffff
 * 
 * @return uint32_t
 */
uint32_t Inf_TM7711_ReadV(void) {
    uint32_t data = 0;
    TM7711_SCK_L;
    while ((TM7711_SDA_R) != 0); //等待数据线拉低

    for (uint8_t i = 0; i < 24; i++)
    {
        TM7711_SCK_H;
        Delay_us(5);

        TM7711_SCK_L;
        // 在下降沿时读取数据

        data <<= 1;
        if (TM7711_SDA_R)
        {
            data |= 0x01;
        }

        Delay_us(5);
    }

    // 使用第25个空时钟信号
    TM7711_SCK_H;
    Delay_us(5);
    TM7711_SCK_L;
    Delay_us(5);

    // 注意: 这里DATA存的数据是用补码存的  ->  转换为正数存储
    return data ^ 0x800000;
}
