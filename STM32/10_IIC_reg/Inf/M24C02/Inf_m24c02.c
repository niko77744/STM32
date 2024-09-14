#include "Inf_m24c02.h"

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

    Driver_I2C_Sendbyte(EEP_ADDR_W + 1);
    Driver_I2C_ReceiveAck();

    byte = Driver_I2C_Receivebyte();
    Driver_I2C_SendNAck();

    Driver_I2C_Stop();
}
void Inf_EEPROM_Readbytes(uint8_t* byte, uint8_t InsideAddr) {
    
}

void Inf_EEPROM_Writebyte(uint8_t byte, uint8_t InsideAddr);
void Inf_EEPROM_Writebytes(uint8_t*, uint8_t len, uint8_t InsideAddr);