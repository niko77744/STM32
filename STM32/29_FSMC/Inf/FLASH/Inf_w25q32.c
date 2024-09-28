#include "Inf_w25q32.h"

/*  Flash ROM �洢��С��
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


#define WriterEnable 0x06
#define WriterDisable 0x04
#define ReadID 0x9F
#define ReadData 0x03
#define PageWrite 0x02
#define SectorErase 0x20
#define BlockHalfErase 0x52
#define BlockErase 0xD8
#define IsBusy 0x05   //13ҳ�� Statue Register-1 ���λΪBUSY æ=1  ��æ=0

void Inf_W25Q32_Init(void) {
    Driver_SPI_Init();
}

void Inf_W25Q32_ReadId(uint8_t* mid, uint16_t* did) {
    Driver_SPI_Start();

    // 2.���Ͷ�ȡIDָ��
    Driver_SPI_SwapByte(0x9f);

    *mid = Driver_SPI_SwapByte(0xFF);
    *did = 0;
    *did |= (Driver_SPI_SwapByte(0xff) << 8);  //��ʽת��Ϊint������
    *did |= (Driver_SPI_SwapByte(0xff) << 0);

    Driver_SPI_Stop();
}

static void Inf_W25Q32_WriteEnable(void) {
    Driver_SPI_Start();

    // ����ָ���дʹ��
    Driver_SPI_SwapByte(WriterEnable);

    Driver_SPI_Stop();
}

static void Inf_W25Q32_WriteDisable(void) {
    Driver_SPI_Start();

    // ����ָ��ر�дʹ��
    Driver_SPI_SwapByte(WriterDisable);

    Driver_SPI_Stop();
}

static void Inf_W25Q32_WaitNotBusy(void) {
    Driver_SPI_Start();

    Driver_SPI_SwapByte(IsBusy);

    //�ȴ�Busy=0
    while ((Driver_SPI_SwapByte(0xFF)) & 0x01);

    Driver_SPI_Stop();
}

// �β���
void Inf_W25Q32_EraseSector(uint8_t block, uint8_t sector) {
    // 1.�ȴ���æ
    Inf_W25Q32_WaitNotBusy();

    // 2.����дʹ��
    Inf_W25Q32_WriteEnable();

    // 3.��ʼ�ź� Ƭѡ����
    Driver_SPI_Start();

    // 4.���Ͳ���ָ��
    Driver_SPI_SwapByte(SectorErase);

    // 5.���Ͳ�����ַ
    Driver_SPI_SwapByte(block);
    Driver_SPI_SwapByte(sector << 4);
    Driver_SPI_SwapByte(0xFF);

    // 6.�����ź� Ƭѡ����
    Driver_SPI_Stop();

    // 7.�ر�дʹ��
    Inf_W25Q32_WriteDisable();
}

void Inf_W25Q32_PageWrite(uint8_t block, uint8_t sector, uint8_t page, uint8_t innerAddr, uint8_t* data, uint16_t dataLen) {
    // 1.�ȴ���æ
    Inf_W25Q32_WaitNotBusy();

    // 2.����дʹ��
    Inf_W25Q32_WriteEnable();

    // 3.��ʼ�ź� Ƭѡ����
    Driver_SPI_Start();

    // 4.����ҳдָ��
    Driver_SPI_SwapByte(PageWrite);

    // 5.����ҳд��ַ
    Driver_SPI_SwapByte(block);
    Driver_SPI_SwapByte((sector << 4) | page);
    Driver_SPI_SwapByte(innerAddr);

    // 6.ѭ����������
    for (uint16_t i = 0; i < dataLen; i++)
    {
        Driver_SPI_SwapByte(data[i]);
    }

    // 7.�����ź� Ƭѡ����
    Driver_SPI_Stop();

    // 8.�ر�дʹ��
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
    // 1.�ȴ���æ
    Inf_W25Q32_WaitNotBusy();

    // 2.��ʼ�ź� Ƭѡ����
    Driver_SPI_Start();

    // 3.���Ͷ�ȡָ��
    Driver_SPI_SwapByte(ReadData);

    // 4.���Ͷ�ȡ��ַ
    Driver_SPI_SwapByte(block);
    Driver_SPI_SwapByte((sector << 4) | page);
    Driver_SPI_SwapByte(innerAddr);

    // 5.ѭ����������
    for (uint16_t i = 0; i < dataLen; i++)
    {
        buffer[i] = Driver_SPI_SwapByte(0xFF);
    }

    // 6.�����ź� Ƭѡ����
    Driver_SPI_Stop();
}



void Inf_W25Q32_RandomWrite(uint8_t* src, uint32_t addr)
{
    /* 1.׼���׶� �����д���ܳ��� ��ֵ�ַ ��һҳд�볤��  */
    // 1.1 �����д���ܳ���
    uint32_t len = strlen((char*)src);
    // 1.2 ��ֵ�ַ
    uint8_t block = (addr >> 16) & 0xff;
    uint8_t sector = (addr >> 12) & 0x0f;
    uint8_t page = (addr >> 8) & 0x0f;
    uint8_t innerAddr = (addr >> 0) & 0xff;
    // 1.3 ��һҳд�볤��
    uint8_t page1Size = 256 - innerAddr;
    // 1.4 ʣ�೤��
    len -= page1Size;
    // 1.5 д���һҳ����
    Inf_W25Q32_PageWrite(block, sector, page, innerAddr, src, page1Size);

    /* 2.�����д���ҳ�� */
    uint8_t lastPageSize = len % (0xff + 1);
    uint32_t pageNum = len / 256;

    /* 3.ѭ����ҳд�� */
    for (size_t i = 0; i < pageNum; i++)
    {
        // ����ҳ�ж��Ƿ���
        if (page == 15)
        {
            // ���ö��ж��Ƿ���
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

    /* 4.���һҳ���� */
    if (lastPageSize > 0)
    {
        Inf_W25Q32_PageWrite(block, sector, page, 0, src + page1Size + 256 * pageNum, lastPageSize);
    }
}
