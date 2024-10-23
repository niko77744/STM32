#include "Inf_W25q32.h"


void Inf_W25q32_Init(void) {
    Driver_SPI_Init();
}

void Inf_W25q32_ReadID(uint8_t* mid, uint16_t* did) {
    Driver_SPI_CS_Start();

    // 2.发送读取ID指令
    Driver_SPI_SwapData(0x9f);

    *mid = Driver_SPI_SwapData(0xFF);
    *did = 0;
    *did |= (Driver_SPI_SwapData(0xFF) << 8);  //隐式转换为int作运算
    *did |= (Driver_SPI_SwapData(0xFF) << 0);

    Driver_SPI_CS_Stop();
}

void Inf_W25q32_WaitNotBusy(void) {
    // 最低位为BUSY 忙=1  不忙=0
    Driver_SPI_CS_Start();

    Driver_SPI_SwapData(IsBusy);
    while (Driver_SPI_SwapData(0xFF) & 0x01);

    Driver_SPI_CS_Stop();
}

void Inf_W25q32_WriteENABLE(void) {
    Driver_SPI_CS_Start();

    Driver_SPI_SwapData(WriterEnable);

    Driver_SPI_CS_Stop();
}
void Inf_W25q32_WriteDisable(void) {
    Driver_SPI_CS_Start();

    Driver_SPI_SwapData(WriterDisable);

    Driver_SPI_CS_Stop();
}

void Inf_W25q32_SectorErase(uint32_t addr) {
    Inf_W25q32_WaitNotBusy();
    Inf_W25q32_WriteENABLE();
    Driver_SPI_CS_Start();

    Driver_SPI_SwapData(SectorErase);
    Driver_SPI_SwapData((addr & 0xFF0000) >> 16);
    Driver_SPI_SwapData((addr & 0xFF00) >> 8);
    Driver_SPI_SwapData((addr & 0xFF) >> 0);

    Driver_SPI_CS_Stop();
    Inf_W25q32_WriteDisable();
}
void Inf_W25q32_BlockErase(uint32_t addr) {
    Inf_W25q32_WaitNotBusy();
    Inf_W25q32_WriteENABLE();
    Driver_SPI_CS_Start();

    Driver_SPI_SwapData(BlockErase);
    Driver_SPI_SwapData((addr & 0xFF0000) >> 16);
    Driver_SPI_SwapData((addr & 0xFF00) >> 8);
    Driver_SPI_SwapData((addr & 0xFF) >> 0);

    Driver_SPI_CS_Stop();
    Inf_W25q32_WriteDisable();
}

void Inf_W25q32_ReadData(uint32_t addr, uint8_t* data, uint16_t size) {
    uint8_t* pData = data;
    Inf_W25q32_WaitNotBusy();//等待忙结束
    Driver_SPI_CS_Start();

    Driver_SPI_SwapData(ReadData);//读数据指令
    Driver_SPI_SwapData((addr & 0xFF0000) >> 16);
    Driver_SPI_SwapData((addr & 0xFF00) >> 8);
    Driver_SPI_SwapData((addr & 0xFF) >> 0);
    while (size--)
    {
        *pData = Driver_SPI_SwapData(0xFF);//保存数据
        pData++;
    }
    Driver_SPI_CS_Stop();
}
void Inf_W25q32_PageWrite(uint32_t addr, uint8_t* data, uint16_t size) {
    if (addr <= W25Q32_FontLibrary) return;
    uint8_t* pData = data;
    Inf_W25q32_WaitNotBusy();
    Inf_W25q32_WriteENABLE();
    Driver_SPI_CS_Start();

    Driver_SPI_SwapData(PageWrite);
    Driver_SPI_SwapData((addr >> 16) & 0xFF0000);
    Driver_SPI_SwapData((addr >> 8) & 0xFF00);
    Driver_SPI_SwapData((addr >> 0) & 0xFF);
    while (size--)
    {
        Driver_SPI_SwapData(*pData);
        pData++;
    }

    Driver_SPI_CS_Stop();
    Inf_W25q32_WriteDisable();
}


/*
    \brief：	可跨页写数据（不考虑擦除，认为写入的地址都为0xFF）
    \param：	addr：要写入的地址
                data：写入的数据
                size：数据的数量（字节数）
    \retval：	none
*/
void Inf_W25q32_StepOverPageWrite(uint32_t addr, uint8_t* data, uint32_t size) {
    if (addr <= W25Q32_FontLibrary) return;
    uint32_t addr_remain = 256 - addr % 256;//当前页地址剩余
    uint8_t* pData = data;
    if (size <= addr_remain)
    {
        addr_remain = size;
    }
    while (1)
    {
        Inf_W25q32_PageWrite(addr, pData, addr_remain);
        if (addr_remain == size) break;		//数据全部写入
        pData += addr_remain;	//数据地址偏移
        addr += addr_remain;	//地址偏移
        size -= addr_remain;	//计算剩余数据
        addr_remain = 256;//写入一页数据
        if (size <= addr_remain)	//计算当前页是否够写入剩余数据
        {
            addr_remain = size;
        }
    }
}


/*
    \brief：	可跨页写数据（考虑擦除和原有数据）
    \param：	addr：要写入的地址
                data：写入的数据
                size：数据的数量（字节数）
    \retval：	none
*/
uint8_t sector_data[W25Q32_SECTOR_SIZE];
void Inf_W25q32_WriteData(uint32_t addr, uint8_t* data, uint32_t size) {
    if (addr <= W25Q32_FontLibrary) return;

    uint16_t sector_offset = addr % 4096;	//计算当前扇区的地址偏移
    uint16_t sector_remain = 4096 - sector_offset;	//计算当前扇区剩余
    uint32_t sector_addr = addr - sector_offset;	//计算当前扇区的起始地址
    uint8_t* pData = data;
    uint32_t i;
    if (size <= sector_remain)
    {
        sector_remain = (uint16_t)size;
    }
    while (1)
    {
        Inf_W25q32_ReadData(addr, sector_data, sector_remain);//读取要写入地址的数据
        for (i = 0;i < sector_remain;i++)
        {
            if (sector_data[i] != 0xFF) break;
        }
        if (i != sector_remain)//判断是否需要擦除扇区
        {
            //擦除前保存当前扇区前一段数据
            Inf_W25q32_ReadData(sector_addr, sector_data, sector_offset);
            //擦除前保存当前扇区后一段数据
            Inf_W25q32_ReadData(addr + sector_remain, sector_data + (sector_offset + sector_remain), W25Q32_SECTOR_SIZE - (sector_offset + sector_remain));
            Inf_W25q32_SectorErase(sector_addr);//擦除扇区
            //将要写入的数据插入缓冲区
            for (i = 0;i < sector_remain;i++)
            {
                sector_data[sector_offset + i] = pData[i];
            }
            Inf_W25q32_StepOverPageWrite(sector_addr, sector_data, W25Q32_SECTOR_SIZE);
            sector_offset = 0;
        }
        else
        {
            Inf_W25q32_StepOverPageWrite(addr, pData, sector_remain);//向当前扇区写入数据
        }
        if (sector_remain == size) break;//全部数据完全写入

        pData += sector_remain;	//数据地址偏移
        addr += sector_remain;	//flash地址偏移
        sector_addr = addr;		//当前扇区起始地址
        size -= sector_remain;	//数据量减少
        sector_remain = W25Q32_SECTOR_SIZE;//当前扇区剩余
        if (size <= W25Q32_SECTOR_SIZE)//计算当前扇区是否够写入剩余数据
        {
            sector_remain = size;
        }
    }
}
