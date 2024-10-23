#include "Inf_W25q32.h"


void Inf_W25q32_Init(void) {
    Driver_SPI_Init();
}

void Inf_W25q32_ReadID(uint8_t* mid, uint16_t* did) {
    Driver_SPI_CS_Start();

    // 2.���Ͷ�ȡIDָ��
    Driver_SPI_SwapData(0x9f);

    *mid = Driver_SPI_SwapData(0xFF);
    *did = 0;
    *did |= (Driver_SPI_SwapData(0xFF) << 8);  //��ʽת��Ϊint������
    *did |= (Driver_SPI_SwapData(0xFF) << 0);

    Driver_SPI_CS_Stop();
}

void Inf_W25q32_WaitNotBusy(void) {
    // ���λΪBUSY æ=1  ��æ=0
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
    Inf_W25q32_WaitNotBusy();//�ȴ�æ����
    Driver_SPI_CS_Start();

    Driver_SPI_SwapData(ReadData);//������ָ��
    Driver_SPI_SwapData((addr & 0xFF0000) >> 16);
    Driver_SPI_SwapData((addr & 0xFF00) >> 8);
    Driver_SPI_SwapData((addr & 0xFF) >> 0);
    while (size--)
    {
        *pData = Driver_SPI_SwapData(0xFF);//��������
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
    \brief��	�ɿ�ҳд���ݣ������ǲ�������Ϊд��ĵ�ַ��Ϊ0xFF��
    \param��	addr��Ҫд��ĵ�ַ
                data��д�������
                size�����ݵ��������ֽ�����
    \retval��	none
*/
void Inf_W25q32_StepOverPageWrite(uint32_t addr, uint8_t* data, uint32_t size) {
    if (addr <= W25Q32_FontLibrary) return;
    uint32_t addr_remain = 256 - addr % 256;//��ǰҳ��ַʣ��
    uint8_t* pData = data;
    if (size <= addr_remain)
    {
        addr_remain = size;
    }
    while (1)
    {
        Inf_W25q32_PageWrite(addr, pData, addr_remain);
        if (addr_remain == size) break;		//����ȫ��д��
        pData += addr_remain;	//���ݵ�ַƫ��
        addr += addr_remain;	//��ַƫ��
        size -= addr_remain;	//����ʣ������
        addr_remain = 256;//д��һҳ����
        if (size <= addr_remain)	//���㵱ǰҳ�Ƿ�д��ʣ������
        {
            addr_remain = size;
        }
    }
}


/*
    \brief��	�ɿ�ҳд���ݣ����ǲ�����ԭ�����ݣ�
    \param��	addr��Ҫд��ĵ�ַ
                data��д�������
                size�����ݵ��������ֽ�����
    \retval��	none
*/
uint8_t sector_data[W25Q32_SECTOR_SIZE];
void Inf_W25q32_WriteData(uint32_t addr, uint8_t* data, uint32_t size) {
    if (addr <= W25Q32_FontLibrary) return;

    uint16_t sector_offset = addr % 4096;	//���㵱ǰ�����ĵ�ַƫ��
    uint16_t sector_remain = 4096 - sector_offset;	//���㵱ǰ����ʣ��
    uint32_t sector_addr = addr - sector_offset;	//���㵱ǰ��������ʼ��ַ
    uint8_t* pData = data;
    uint32_t i;
    if (size <= sector_remain)
    {
        sector_remain = (uint16_t)size;
    }
    while (1)
    {
        Inf_W25q32_ReadData(addr, sector_data, sector_remain);//��ȡҪд���ַ������
        for (i = 0;i < sector_remain;i++)
        {
            if (sector_data[i] != 0xFF) break;
        }
        if (i != sector_remain)//�ж��Ƿ���Ҫ��������
        {
            //����ǰ���浱ǰ����ǰһ������
            Inf_W25q32_ReadData(sector_addr, sector_data, sector_offset);
            //����ǰ���浱ǰ������һ������
            Inf_W25q32_ReadData(addr + sector_remain, sector_data + (sector_offset + sector_remain), W25Q32_SECTOR_SIZE - (sector_offset + sector_remain));
            Inf_W25q32_SectorErase(sector_addr);//��������
            //��Ҫд������ݲ��뻺����
            for (i = 0;i < sector_remain;i++)
            {
                sector_data[sector_offset + i] = pData[i];
            }
            Inf_W25q32_StepOverPageWrite(sector_addr, sector_data, W25Q32_SECTOR_SIZE);
            sector_offset = 0;
        }
        else
        {
            Inf_W25q32_StepOverPageWrite(addr, pData, sector_remain);//��ǰ����д������
        }
        if (sector_remain == size) break;//ȫ��������ȫд��

        pData += sector_remain;	//���ݵ�ַƫ��
        addr += sector_remain;	//flash��ַƫ��
        sector_addr = addr;		//��ǰ������ʼ��ַ
        size -= sector_remain;	//����������
        sector_remain = W25Q32_SECTOR_SIZE;//��ǰ����ʣ��
        if (size <= W25Q32_SECTOR_SIZE)//���㵱ǰ�����Ƿ�д��ʣ������
        {
            sector_remain = size;
        }
    }
}
