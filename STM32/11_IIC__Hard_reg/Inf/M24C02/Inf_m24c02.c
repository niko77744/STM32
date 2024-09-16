#include "Inf_m24c02.h"
#include "Driver_usart .h"

void Inf_EEPROM_Init(void) {
    Driver_I2C_Init();
}
uint8_t Inf_EEPROM_Readbyte(uint8_t InsideAddr) {
    uint8_t byte = 0;
    Driver_I2C_Start();
    Driver_I2C_Sendbyte(EEP_ADDR_W);
    Driver_I2C_ReceiveAck();

    Driver_I2C_Sendbyte(InsideAddr);
    Driver_I2C_ReceiveAck();

    Driver_I2C_Start();
    Driver_I2C_Sendbyte(EEP_ADDR_W + 1);
    Driver_I2C_ReceiveAck();


    byte = Driver_I2C_Receivebyte();
    Driver_I2C_SendNAck();

    Driver_I2C_Stop();
    return byte;
}
void Inf_EEPROM_Readbytes(uint8_t* bytes, uint8_t len, uint8_t InsideAddr) {
    Driver_I2C_Start();
    Driver_I2C_Sendbyte(EEP_ADDR_W);
    Driver_I2C_ReceiveAck();

    Driver_I2C_Sendbyte(InsideAddr);
    Driver_I2C_ReceiveAck();

    Driver_I2C_Start();
    Driver_I2C_Sendbyte(EEP_ADDR_W + 1);
    Driver_I2C_ReceiveAck();

    for (uint8_t i = 0; i < len; i++)
    {
        bytes[i] = Driver_I2C_Receivebyte();
        // (len == (i - 1)) ? (Driver_I2C_SendNAck()) : (Driver_I2C_SendAck());
        /* 10.判断是否为最后一个数据,来决定返回ACK还是NAck */
        if (i < len - 1)
        {
            Driver_I2C_SendAck();
        }
        else
        {
            Driver_I2C_SendNAck();
        }
    }
    Driver_I2C_Stop();
}

void Inf_EEPROM_Writebyte(uint8_t byte, uint8_t InsideAddr) {

    Driver_I2C_Start();
    Driver_I2C_Sendbyte(EEP_ADDR_W);
    Driver_I2C_ReceiveAck();

    Driver_I2C_Sendbyte(InsideAddr);
    Driver_I2C_ReceiveAck();

    Driver_I2C_Sendbyte(byte);
    Driver_I2C_ReceiveAck();

    Driver_I2C_Stop();
    Delay_ms(5);
}

void Inf_EEPROM_WritePage(uint8_t* bytes, uint8_t len, uint8_t InsideAddr) {

    Driver_I2C_Start();
    Driver_I2C_Sendbyte(EEP_ADDR_W);
    Driver_I2C_ReceiveAck();

    Driver_I2C_Sendbyte(InsideAddr);
    Driver_I2C_ReceiveAck();

    for (uint8_t i = 0; i < len; i++)
    {
        Driver_I2C_Sendbyte(bytes[i]);
        Driver_I2C_ReceiveAck();
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
