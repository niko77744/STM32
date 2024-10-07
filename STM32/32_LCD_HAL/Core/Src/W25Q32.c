#include "W25Q32.h"

#define WriterEnable 0x06
#define WriterDisable 0x04
#define ReadID 0x9F
#define ReadData 0x03
#define PageWrite 0x02
#define SectorErase 0x20
#define BlockHalfErase 0x52
#define BlockErase 0xD8
#define IsBusy 0x05   //数据手册13页， Statue Register-1  最低位为BUSY 忙=1  不忙=0

#define PAGE_SIZE	256		//页大小256字节
#define SECTOR_SIZE	4096	//扇区大小4096字节
#define START_ADDR	(uint32_t)0x000000		//起始地址
#define END_ADDR	(uint32_t)0x400000		//结束地址


void W25Q32_WriteEnable(void) {
    SPI_Start();
    SPI_Swap(WriterEnable);
    SPI_Stop();
}
void W25Q32_WriteDisable(void) {
    SPI_Start();
    SPI_Swap(WriterDisable);
    SPI_Stop();
}
void W25Q32_WaitNotBusy(void) {
    W25Q32_WriteEnable();
    SPI_Swap(IsBusy);

    while ((SPI_Swap(0xFF) & 0x01) == 0);

    W25Q32_WriteDisable();
}


void W25Q32_ReadData(uint32_t addr, uint8_t* data, uint32_t size) {

    uint8_t* pData = data;
    W25Q32_WaitNotBusy();
    SPI_Start();
    SPI_Swap(0x03);//读数据指令
    SPI_Swap((addr & 0xFF0000) >> 16);//发送24位地址
    SPI_Swap((addr & 0xFF00) >> 8);
    SPI_Swap((addr & 0xFF));
    while (size--)
    {
        *pData = SPI_Swap(0xFF);//保存数据
        pData++;
    }
    SPI_Stop();
}

void W25Q32_SectorErase(uint32_t addr) {
    W25Q32_WaitNotBusy();

    W25Q32_WriteEnable();
    SPI_Start();

    SPI_Swap(SectorErase);
    SPI_Swap((0xFF0000 & addr) >> 16);
    SPI_Swap((0x00FF00 & addr) >> 8);
    SPI_Swap((0x0000FF & addr) >> 0);

    SPI_Stop();
    W25Q32_WriteDisable();
}
void W25Q32_BlockErase(uint32_t addr) {
    W25Q32_WaitNotBusy();

    W25Q32_WriteEnable();
    SPI_Start();

    SPI_Swap(BlockErase);
    SPI_Swap((0xFF0000 & addr) >> 16);
    SPI_Swap((0x00FF00 & addr) >> 8);
    SPI_Swap((0x0000FF & addr) >> 0);

    SPI_Stop();
    W25Q32_WriteDisable();
}


void W25Q32_WriteToPage(uint32_t addr, uint8_t* data, uint32_t size) {
    if (size + addr > END_ADDR) return;

    W25Q32_WaitNotBusy();

    W25Q32_WriteEnable();
    SPI_Start();

    uint8_t* pData = data;
    SPI_Swap(PageWrite);
    SPI_Swap((0xFF0000 & addr) >> 16);
    SPI_Swap((0x00FF00 & addr) >> 8);
    SPI_Swap((0x0000FF & addr) >> 0);

    while (size--)
    {
        SPI_Swap(*pData);
        pData++;
    }

    SPI_Stop();
    W25Q32_WriteDisable();
}


/*
    \brief：	可跨页写数据（不考虑擦除，认为写入的地址都为0xFF）
    \param：	addr：要写入的地址
                data：写入的数据
                size：数据的数量（字节数）
    \retval：	none
*/
void W25Q32_StepOverPageWrite(uint32_t addr, uint8_t* data, uint32_t size) {
    uint32_t addr_remain = 256 - addr % 256;//当前页地址剩余
    uint8_t* pData = data;

    if (size <= addr_remain)
    {
        addr_remain = size;
    }

    while (1) {
        W25Q32_WriteToPage(addr, pData, addr_remain);
        if (addr_remain == size) break;

        pData += addr_remain;
        addr += addr_remain;
        size -= addr_remain;
        addr_remain = 256; // 写入一页数据
        if (size <= addr_remain)
        {
            addr_remain = size;
        }
    }
}
