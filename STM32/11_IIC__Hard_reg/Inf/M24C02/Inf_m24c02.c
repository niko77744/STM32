#include "Inf_m24c02.h"
#include "Driver_usart .h"

void Inf_EEPROM_Init(void) {
    Driver_I2C_Init();
}
uint8_t Inf_EEPROM_Readbyte(uint8_t InsideAddr) {
    uint8_t byte = 0;
    /* 1.发送开始信号 */
    Driver_I2C_Start();
    /* 2.发送写地址 */
    Driver_I2C_SendAddr(EEP_ADDR_W);
    /* 3.发送内部地址 */
    Driver_I2C_Sendbyte(InsideAddr);
    /* 4.发送开始信号 */
    Driver_I2C_Start();
    /* 5.发送读地址 */
    Driver_I2C_SendAddr(EEP_ADDR_W + 1);
    /* 6.配置在接受完成后产生一个NAck */
    Driver_I2C_SendNAck();
    /* 7.配置在接受完成后产生结束信号 */
    Driver_I2C_Stop();
    /* 8.读取一个字节的数据 */
    byte = Driver_I2C_Receivebyte();
    /* 9.返回读取到的数据 */
    return byte;
}
void Inf_EEPROM_Readbytes(uint8_t* bytes, uint8_t len, uint8_t InsideAddr) {
    Driver_I2C_Start();
    Driver_I2C_SendAddr(EEP_ADDR_W);

    Driver_I2C_Sendbyte(InsideAddr);

    Driver_I2C_Start();
    Driver_I2C_SendAddr(EEP_ADDR_W + 1);

    for (uint8_t i = 0; i < len; i++)
    {
        if (i < (len - 1))
        {
            Driver_I2C_SendAck();
        }
        else
        {
            Driver_I2C_SendNAck();
            Driver_I2C_Stop();
        }

        bytes[i] = Driver_I2C_Receivebyte();
    }
}

void Inf_EEPROM_Writebyte(uint8_t byte, uint8_t InsideAddr) {

    Driver_I2C_Start();
    Driver_I2C_SendAddr(EEP_ADDR_W);

    Driver_I2C_Sendbyte(InsideAddr);

    Driver_I2C_Sendbyte(byte);

    Driver_I2C_Stop();
    Delay_ms(5);
}

void Inf_EEPROM_WritePage(uint8_t* bytes, uint8_t len, uint8_t InsideAddr) {

    Driver_I2C_Start();
    Driver_I2C_SendAddr(EEP_ADDR_W);

    Driver_I2C_Sendbyte(InsideAddr);


    for (uint8_t i = 0; i < len; i++)
    {
        Driver_I2C_Sendbyte(bytes[i]);
    }
    Driver_I2C_Stop();
    Delay_ms(5);
}
void Inf_EEPROM_Writebytes(uint8_t* bytes, uint8_t len, uint8_t InsideAddr) {
    uint8_t page_remain;
    // printf("111\n");
    while (len > 0)
    {
        page_remain = 16 - InsideAddr % 16;
        if (len > page_remain)
        {
            // printf("222\n");
            Inf_EEPROM_WritePage(bytes, page_remain, InsideAddr);
            bytes += page_remain;
            len -= page_remain;
            InsideAddr += page_remain;
        }
        else
        {
            // printf("333\n");
            Inf_EEPROM_WritePage(bytes, len, InsideAddr);
            len = 0;
        }
        Delay_ms(5);
    }
    // printf("444\n");
}
