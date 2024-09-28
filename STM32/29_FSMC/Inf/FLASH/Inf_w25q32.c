#include "Inf_w25q32.h"

/*  Flash ROM 存储大小：
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


#define WriterEnable 0x06
#define WriterDisable 0x04
#define ReadID 0x9F
#define ReadData 0x03
#define PageWrite 0x02
#define SectorErase 0x20
#define BlockHalfErase 0x52
#define BlockErase 0xD8
#define IsBusy 0x05   //13页， Statue Register-1 最低位为BUSY 忙=1  不忙=0

void Inf_W25Q32_Init(void) {
    Driver_SPI_Init();
}

void Inf_W25Q32_ReadId(uint8_t* mid, uint16_t* did) {
    Driver_SPI_Start();

    // 2.发送读取ID指令
    Driver_SPI_SwapByte(0x9f);

    *mid = Driver_SPI_SwapByte(0xFF);
    *did = 0;
    *did |= (Driver_SPI_SwapByte(0xff) << 8);  //隐式转换为int作运算
    *did |= (Driver_SPI_SwapByte(0xff) << 0);

    Driver_SPI_Stop();
}

static void Inf_W25Q32_WriteEnable(void) {
    Driver_SPI_Start();

    // 发送指令开启写使能
    Driver_SPI_SwapByte(WriterEnable);

    Driver_SPI_Stop();
}

static void Inf_W25Q32_WriteDisable(void) {
    Driver_SPI_Start();

    // 发送指令关闭写使能
    Driver_SPI_SwapByte(WriterDisable);

    Driver_SPI_Stop();
}

static void Inf_W25Q32_WaitNotBusy(void) {
    Driver_SPI_Start();

    Driver_SPI_SwapByte(IsBusy);

    //等待Busy=0
    while ((Driver_SPI_SwapByte(0xFF)) & 0x01);

    Driver_SPI_Stop();
}

// 段擦除
void Inf_W25Q32_EraseSector(uint8_t block, uint8_t sector) {
    // 1.等待不忙
    Inf_W25Q32_WaitNotBusy();

    // 2.开启写使能
    Inf_W25Q32_WriteEnable();

    // 3.开始信号 片选拉低
    Driver_SPI_Start();

    // 4.发送擦除指令
    Driver_SPI_SwapByte(SectorErase);

    // 5.发送擦除地址
    Driver_SPI_SwapByte(block);
    Driver_SPI_SwapByte(sector << 4);
    Driver_SPI_SwapByte(0xFF);

    // 6.结束信号 片选拉高
    Driver_SPI_Stop();

    // 7.关闭写使能
    Inf_W25Q32_WriteDisable();
}

void Inf_W25Q32_PageWrite(uint8_t block, uint8_t sector, uint8_t page, uint8_t innerAddr, uint8_t* data, uint16_t dataLen) {
    // 1.等待不忙
    Inf_W25Q32_WaitNotBusy();

    // 2.开启写使能
    Inf_W25Q32_WriteEnable();

    // 3.开始信号 片选拉低
    Driver_SPI_Start();

    // 4.发送页写指令
    Driver_SPI_SwapByte(PageWrite);

    // 5.发送页写地址
    Driver_SPI_SwapByte(block);
    Driver_SPI_SwapByte((sector << 4) | page);
    Driver_SPI_SwapByte(innerAddr);

    // 6.循环发送数据
    for (uint16_t i = 0; i < dataLen; i++)
    {
        Driver_SPI_SwapByte(data[i]);
    }

    // 7.结束信号 片选拉高
    Driver_SPI_Stop();

    // 8.关闭写使能
    Inf_W25Q32_WriteDisable();
}

void Inf_W25Q32_SectorWrite(uint8_t block, uint8_t sector, uint8_t page, uint8_t innerAddr, uint8_t* data, uint16_t dataLen) {
    uint16_t page_remain = 0;
    while (dataLen > 0) {
        page_remain = 256 - innerAddr % 256;
        if (dataLen > page_remain)
        {
            Inf_W25Q32_PageWrite(block, sector, page, innerAddr, data, page_remain);
            dataLen -= page_remain;
            data += page_remain;
            // page += 1;
            (page == 15) ? (page = 0) : (page += 1);
            innerAddr += page_remain;
        }
        else if (dataLen <= page_remain)
        {
            Inf_W25Q32_PageWrite(block, sector, page, innerAddr, data, dataLen);
            dataLen = 0;
        }
    }
}

void Inf_W25Q32_Read(uint8_t block, uint8_t sector, uint8_t page, uint8_t innerAddr, uint8_t* buffer, uint16_t dataLen) {
    // 1.等待不忙
    Inf_W25Q32_WaitNotBusy();

    // 2.开始信号 片选拉低
    Driver_SPI_Start();

    // 3.发送读取指令
    Driver_SPI_SwapByte(ReadData);

    // 4.发送读取地址
    Driver_SPI_SwapByte(block);
    Driver_SPI_SwapByte((sector << 4) | page);
    Driver_SPI_SwapByte(innerAddr);

    // 5.循环接收数据
    for (uint16_t i = 0; i < dataLen; i++)
    {
        buffer[i] = Driver_SPI_SwapByte(0xFF);
    }

    // 6.结束信号 片选拉高
    Driver_SPI_Stop();
}



void Inf_W25Q32_RandomWrite(uint8_t* src, uint32_t addr)
{
    /* 1.准备阶段 计算待写入总长度 拆分地址 第一页写入长度  */
    // 1.1 计算待写入总长度
    uint32_t len = strlen((char*)src);
    // 1.2 拆分地址
    uint8_t block = (addr >> 16) & 0xff;
    uint8_t sector = (addr >> 12) & 0x0f;
    uint8_t page = (addr >> 8) & 0x0f;
    uint8_t innerAddr = (addr >> 0) & 0xff;
    // 1.3 第一页写入长度
    uint8_t page1Size = 256 - innerAddr;
    // 1.4 剩余长度
    len -= page1Size;
    // 1.5 写入第一页数据
    Inf_W25Q32_PageWrite(block, sector, page, innerAddr, src, page1Size);

    /* 2.计算待写入的页数 */
    uint8_t lastPageSize = len % (0xff + 1);
    uint32_t pageNum = len / 256;

    /* 3.循环分页写入 */
    for (size_t i = 0; i < pageNum; i++)
    {
        // 利用页判断是否跨段
        if (page == 15)
        {
            // 利用段判断是否跨块
            if (sector == 15)
            {
                block++;
                sector = 0;
                page = 0;
            }
            else
            {
                sector++;
                page = 0;
            }
        }
        else
        {
            page++;
        }
        Inf_W25Q32_PageWrite(block, sector, page, 0, src + page1Size + 256 * i, 256);
    }

    /* 4.最后一页数据 */
    if (lastPageSize > 0)
    {
        Inf_W25Q32_PageWrite(block, sector, page, 0, src + page1Size + 256 * pageNum, lastPageSize);
    }
}
