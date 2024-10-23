#include "Int_18B20.h"

#define SkipROM 0xCC
#define measure_temperature 0x44
#define read_temperature 0xBE


/**
 * @brief 获取到18B20测得的温度
 *
 * @return char 表示的温度
 */
char Int_18B20_GetTemperature() {
    u8 ls_byte;
    u8 ms_byte;

    // 第一步 发送测温命令 ------------------------------------
    // 初始化
    Dri_1Wire_Init();
    // 跳过寻址（单设备）
    Dri_1Wire_SendByte(SkipROM);
    // 向18B20发送测温命令, 测温之后会存储暂存器
    Dri_1Wire_SendByte(measure_temperature);


    // 第二步 获取18B20暂存器中的数值 -------------------------
    // 初始化  18b20规定，需要再次初始化
    Dri_1Wire_Init();
    Dri_1Wire_SendByte(SkipROM);
    Dri_1Wire_SendByte(read_temperature);


    // 第三步 处理获取到的数据 --------------------------------
    /*
        ls_byte:  1011xxxx
        ms_byte:  xxxx0010

        ls_byte >> 4:  00001011
        ms_byte << 4:  00100000
    */
    ls_byte = Dri_1Wire_ReceiveByte();
    ms_byte = Dri_1Wire_ReceiveByte();
    // 将ls的高四位和ms的第四位拼起来  
    return (ls_byte >> 4) + (ms_byte << 4);  // (ls_byte >> 4) | (ms_byte << 4)
}


/**
 * @brief 获取到18B20测得的温度
 *
 * @return float 表示的温度
 */
float Int_18B20_GetTemperatureFloat() {
    u8 ls_byte;
    u8 ms_byte;

    // 第一步 发送测温命令 ------------------------------------
    // 初始化
    Dri_1Wire_Init();
    // 跳过寻址（单设备）
    Dri_1Wire_SendByte(SkipROM);
    // 向18B20发送测温命令, 测温之后会存储暂存器
    Dri_1Wire_SendByte(measure_temperature);


    // 第二步 获取18B20暂存器中的数值 -------------------------
    // 初始化  18b20规定，需要再次初始化
    Dri_1Wire_Init();
    Dri_1Wire_SendByte(SkipROM);
    Dri_1Wire_SendByte(read_temperature);

    // 第三步 处理获取到的数据 --------------------------------
    /*
        小数部分：
        ls_byte 取出最低4位，把高4位变为0， &00001111
    */
    // 整数部分 + 小数部分

    ls_byte = Dri_1Wire_ReceiveByte();
    ms_byte = Dri_1Wire_ReceiveByte();
    // 将ls的高四位和ms的第四位拼起来  
    return (ls_byte >> 4) + (ms_byte << 4) + (ls_byte & 0x0F) * 0.0625;
}
