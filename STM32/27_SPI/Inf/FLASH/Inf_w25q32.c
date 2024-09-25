#include "Inf_w25q32.h"

/*  存储大小：
4M = 2^12Kb = 2^22b = 4096Kb;   1M = 2^10Kb = 2^20b = 1024Kb;   64Kb = 2^6Kb = 2^16b
        4M--->64块(Block:64KB)--->64*16段(Sector:4Kb)--->64*16*16页(Page:256b)
    用24位来表示地址:
        block块:    64Kb = 2^16b = 0xFFFF(1个F=4位)
            实际8位块号，24-16  理论来说6位表示64块足够
        Sector段:   4Kb =  2^12b = 0xFFF(1个F=4位)
            实际4位段号，16-12  理论来说4位表示16个段刚好
        Page页：    256b = 2^8b  = 0xFF(1个F=4位)
            实际4位页号，12-8   理论来说4位表示16个页刚好
*/



void Inf_W25Q32_Init(void) {
    Driver_SPI_Init();
}

void Inf_W25Q32_ReadId(uint8_t* mid, uint16_t* did) {
    // Driver_SPI_Start();

    // // 2.发送读取ID指令
    // Driver_SPI_SwapByte(0x9f);

    // *mid = Driver_SPI_SwapByte(0xFF);
    // *did = 0;
    // *did |= (Driver_SPI_SwapByte(0xff) << 8);
    // *did |= (Driver_SPI_SwapByte(0xff) << 0);

    // Driver_SPI_Stop();
        // 1.片选信号拉低
    CS_LOW;

    // 2.发送读取ID指令
    Driver_SPI_SwapByte(0x9f);

    // 3.封装返回值结果
    *mid = Driver_SPI_SwapByte(0xff);
    *did = 0;
    *did |= (Driver_SPI_SwapByte(0xff) << 8);
    *did |= (Driver_SPI_SwapByte(0xff) << 0);

    // 4.片选信号拉高
    CS_HIGH;
}

void Inf_W25Q32_WriteEnable(void);

void Inf_W25Q32_WriteDisable(void);

void Inf_W25Q32_WaitNotBusy(void);

void Inf_W25Q32_EraseSector(uint8_t block, uint8_t sector);

void Inf_W25Q32_PageWrite(uint8_t block, uint8_t sector, uint8_t page, uint8_t innerAddr, uint8_t* data, uint16_t dataLen);

void Inf_W25Q32_Read(uint8_t block, uint8_t sector, uint8_t page, uint8_t innerAddr, uint8_t* buffer, uint16_t dataLen);
