#include "Com_Delay.h"
#include "Com_SysTick.h"
#include "Driver_Key.h"
#include "Driver_LED.h"
#include "Driver_USART.h"
#include "Driver_IIC_Hard.h"
#include "Driver_IIC_Soft.h"
#include "Driver_SPI.h"
#include "Driver_BaseTimer.h"
#include "Driver_GeneralTimer.h"
#include "Driver_AdvancedTimer.h"
#include "Driver_DMA.h"
#include "Driver_ADC.h"
#include "GPIO.h"
#include "Inf_EEPROM.h"
#include "Inf_w25q32.h"

uint8_t Manufacture_ID = 0;
uint16_t Device_Id = 0;
uint8_t temp[1040] = { 0 };

int main(int argc, char const* argv[])
{
    Driver_USART_Init();
    Inf_W25Q32_Init();

    Inf_W25Q32_ReadId(&Manufacture_ID, &Device_Id);

    // mid = 0xef       did = 0x4016
    printf("mid = %#x \t did = %#x\n", Manufacture_ID, Device_Id);

    // Inf_W25Q32_EraseSector(0, 0);

    // // 块最大64(0x40) 段最大16(0x40) 页最大16(0x10) 页内地址最大256(0x100) 0xFF=255
    // Inf_W25Q32_PageWrite(0, 0, 2, 246, "plagiarismm", 10);
    // Inf_W25Q32_PageWrite(0, 0, 3, 0, "laboriously", 11);
    // Inf_W25Q32_Read(0, 0, 2, 246, temp, 21);
    // printf("temp = %s\n", temp);


    const uint8_t block = 50;
    const uint8_t sector = 15;
    const uint8_t page = 6;
    const uint8_t innerAddr = 128;

    Inf_W25Q32_EraseSector(block, sector);


    Inf_W25Q32_SectorWrite(block, sector, page, innerAddr, "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz", 1040);

    Inf_W25Q32_Read(block, sector, page, innerAddr, temp, 1040);
    printf("temp = %s\n", temp);



    while (1);
}


