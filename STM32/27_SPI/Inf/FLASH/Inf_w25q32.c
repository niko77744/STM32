#include "Inf_w25q32.h"

/*  �洢��С��
4M = 2^12Kb = 2^22b = 4096Kb;   1M = 2^10Kb = 2^20b = 1024Kb;   64Kb = 2^6Kb = 2^16b
        4M--->64��(Block:64KB)--->64*16��(Sector:4Kb)--->64*16*16ҳ(Page:256b)
    ��24λ����ʾ��ַ:
        block��:    64Kb = 2^16b = 0xFFFF(1��F=4λ)
            ʵ��8λ��ţ�24-16  ������˵6λ��ʾ64���㹻
        Sector��:   4Kb =  2^12b = 0xFFF(1��F=4λ)
            ʵ��4λ�κţ�16-12  ������˵4λ��ʾ16���θպ�
        Pageҳ��    256b = 2^8b  = 0xFF(1��F=4λ)
            ʵ��4λҳ�ţ�12-8   ������˵4λ��ʾ16��ҳ�պ�
*/



void Inf_W25Q32_Init(void) {
    Driver_SPI_Init();
}

void Inf_W25Q32_ReadId(uint8_t* mid, uint16_t* did) {
    // Driver_SPI_Start();

    // // 2.���Ͷ�ȡIDָ��
    // Driver_SPI_SwapByte(0x9f);

    // *mid = Driver_SPI_SwapByte(0xFF);
    // *did = 0;
    // *did |= (Driver_SPI_SwapByte(0xff) << 8);
    // *did |= (Driver_SPI_SwapByte(0xff) << 0);

    // Driver_SPI_Stop();
        // 1.Ƭѡ�ź�����
    CS_LOW;

    // 2.���Ͷ�ȡIDָ��
    Driver_SPI_SwapByte(0x9f);

    // 3.��װ����ֵ���
    *mid = Driver_SPI_SwapByte(0xff);
    *did = 0;
    *did |= (Driver_SPI_SwapByte(0xff) << 8);
    *did |= (Driver_SPI_SwapByte(0xff) << 0);

    // 4.Ƭѡ�ź�����
    CS_HIGH;
}

void Inf_W25Q32_WriteEnable(void);

void Inf_W25Q32_WriteDisable(void);

void Inf_W25Q32_WaitNotBusy(void);

void Inf_W25Q32_EraseSector(uint8_t block, uint8_t sector);

void Inf_W25Q32_PageWrite(uint8_t block, uint8_t sector, uint8_t page, uint8_t innerAddr, uint8_t* data, uint16_t dataLen);

void Inf_W25Q32_Read(uint8_t block, uint8_t sector, uint8_t page, uint8_t innerAddr, uint8_t* buffer, uint16_t dataLen);
