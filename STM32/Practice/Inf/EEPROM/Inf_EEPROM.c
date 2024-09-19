#include "Inf_EEPROM.h"


void Inf_EEPROM_Hard_Init(void) {
    Driver_I2C_Hard_Init();
}
void Inf_EEPROM_Hard_WriteByte(uint8_t byte, uint8_t InsiderAddr) {
    Driver_I2C_Hard_Start();
    Driver_I2C_Hard_SendAddr(EEPROM_ADDR_W);
    Driver_I2C_Hard_Sendbyte(InsiderAddr);
    Driver_I2C_Hard_Sendbyte(byte);
    Driver_I2C_Hard_Stop();
    Delay_ms(5);
}


static void Inf_EEPROM_Hard_WriteToPage(uint8_t* bytes, uint8_t len, uint8_t InsiderAddr) {
    Driver_I2C_Hard_Start();
    Driver_I2C_Hard_SendAddr(EEPROM_ADDR_W);
    Driver_I2C_Hard_Sendbyte(InsiderAddr);
    for (uint8_t i = 0; i < len; i++)
    {
        Driver_I2C_Hard_Sendbyte(bytes[i]);
    }
    // sendbyte ��־λBTF �������ȡSR1�Ĵ����󣬶����ݼĴ����Ķ���д�����������λ���ڴ����з���һ����ʼ��ֹͣ�����󣬻�PE=0ʱ����Ӳ�������λ��
    // ���һ��BTF��Stop���㣬ͬʱ��Stop��⵽BTF=1��TXE=1ʱ����ֹͣ�źţ���������stopд�ں��档
    Driver_I2C_Hard_Stop();
    Delay_ms(5);
}

void Inf_EEPROM_Hard_WriteBytes(uint8_t* bytes, uint8_t len, uint8_t InsiderAddr) {
    uint8_t page_remanin;
    while (len > 0)
    {
        page_remanin = 16 - InsiderAddr % 16;
        if (len > page_remanin) {
            Inf_EEPROM_Hard_WriteToPage(bytes, page_remanin, InsiderAddr);
            bytes += page_remanin;
            len -= page_remanin;
            InsiderAddr += page_remanin;
        }
        else {
            Inf_EEPROM_Hard_WriteToPage(bytes, len, InsiderAddr);
            len = 0;
        }
        Delay_ms(5);
    }
}

void Inf_EEPROM_Hard_ReadByte(uint8_t* byte, uint8_t InsiderAddr) {
    Driver_I2C_Hard_Start();
    Driver_I2C_Hard_SendAddr(EEPROM_ADDR_W);
    Driver_I2C_Hard_Sendbyte(InsiderAddr);

    Driver_I2C_Hard_Start();
    Driver_I2C_Hard_SendAddr(EEPROM_ADDR_R);

    Driver_I2C_Hard_SendNAck();
    // Receivebyte�ı�־λ��TXE�������ݼĴ����Ķ�д���������λ��Receivebyte���ý�����TXE�Ѿ�Ϊ0�ˣ����д�ں��棬Stop�ͼ�ⲻ��TXE=1�����޷�����ֹͣ�źţ�����stopҪд��ǰ�档
    Driver_I2C_Hard_Stop();

    *byte = Driver_I2C_Hard_Receivebyte();
}
void Inf_EEPROM_Hard_ReadBytes(uint8_t* bytes, uint8_t len, uint8_t InsiderAddr) {
    Driver_I2C_Hard_Start();
    Driver_I2C_Hard_SendAddr(EEPROM_ADDR_W);
    Driver_I2C_Hard_Sendbyte(InsiderAddr);

    Driver_I2C_Hard_Start();
    Driver_I2C_Hard_SendAddr(EEPROM_ADDR_R);

    for (uint8_t i = 0; i < len; i++)
    {
        if (i < (len - 1))
        {
            Driver_I2C_Hard_SendAck();
        }
        else {
            Driver_I2C_Hard_SendNAck();
            Driver_I2C_Hard_Stop();
        }
        bytes[i] = Driver_I2C_Hard_Receivebyte();
    }
}


void Inf_EEPROM_Soft_Init(void) {
    Driver_I2C_Soft_Init();
}
void Inf_EEPROM_Soft_WriteByte(uint8_t byte, uint8_t InsiderAddr) {
    Driver_I2C_Soft_Start();
    Driver_I2C_Soft_SendAddr(EEPROM_ADDR_W);
    Driver_I2C_Soft_ReceivAck();

    Driver_I2C_Soft_Sendbyte(InsiderAddr);
    Driver_I2C_Soft_ReceivAck();

    Driver_I2C_Soft_Sendbyte(byte);
    Driver_I2C_Soft_ReceivAck();

    Driver_I2C_Soft_Stop();
    Delay_ms(5);
}

void Inf_EEPROM_Soft_WriteToPage(uint8_t* bytes, uint8_t len, uint8_t InsiderAddr) {
    Driver_I2C_Soft_Start();
    Driver_I2C_Soft_SendAddr(EEPROM_ADDR_W);
    Driver_I2C_Soft_ReceivAck();

    Driver_I2C_Soft_Sendbyte(InsiderAddr);
    Driver_I2C_Soft_ReceivAck();

    for (uint8_t i = 0; i < len; i++)
    {
        Driver_I2C_Soft_Sendbyte(bytes[i]);
        Driver_I2C_Soft_ReceivAck();
    }

    Driver_I2C_Soft_Stop();
    Delay_ms(5);
}

void Inf_EEPROM_Soft_WriteBytes(uint8_t* bytes, uint8_t len, uint8_t InsiderAddr) {
    uint8_t page_remanin;
    while (len > 0)
    {
        page_remanin = 16 - InsiderAddr % 16;
        if (len > page_remanin) {
            Inf_EEPROM_Soft_WriteToPage(bytes, page_remanin, InsiderAddr);
            bytes += page_remanin;
            len -= page_remanin;
            InsiderAddr += page_remanin;
        }
        else {
            Inf_EEPROM_Soft_WriteToPage(bytes, len, InsiderAddr);
            len = 0;
        }
        Delay_ms(5);
    }
}

void Inf_EEPROM_Soft_ReadByte(uint8_t* byte, uint8_t InsiderAddr) {
    Driver_I2C_Soft_Start();
    Driver_I2C_Soft_SendAddr(EEPROM_ADDR_W);
    Driver_I2C_Soft_ReceivAck();

    Driver_I2C_Soft_Sendbyte(InsiderAddr);
    Driver_I2C_Soft_ReceivAck();

    Driver_I2C_Soft_Start();
    Driver_I2C_Soft_SendAddr(EEPROM_ADDR_R);
    Driver_I2C_Soft_ReceivAck();

    *byte = Driver_I2C_Soft_Receivebyte();
    Driver_I2C_Soft_SendNAck();

    Driver_I2C_Soft_Stop();
}
void Inf_EEPROM_Soft_ReadBytes(uint8_t* bytes, uint8_t len, uint8_t InsiderAddr) {
    Driver_I2C_Soft_Start();
    Driver_I2C_Soft_SendAddr(EEPROM_ADDR_W);
    Driver_I2C_Soft_ReceivAck();

    Driver_I2C_Soft_Sendbyte(InsiderAddr);
    Driver_I2C_Soft_ReceivAck();

    Driver_I2C_Soft_Start();
    Driver_I2C_Soft_SendAddr(EEPROM_ADDR_R);
    Driver_I2C_Soft_ReceivAck();

    for (uint8_t i = 0; i < len; i++)
    {
        bytes[i] = Driver_I2C_Soft_Receivebyte(); // д��ǰ��
        if (i < len - 1) {
            Driver_I2C_Soft_SendAck();
        }
        else {
            Driver_I2C_Soft_SendNAck();
        }
        // bytes[i] = Driver_I2C_Soft_Receivebyte();
    }

    Driver_I2C_Soft_Stop();
}
