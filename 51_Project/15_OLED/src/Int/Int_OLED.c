#include "Int_OLED.h"

// 设置
#define OLED_ADDR 0x78
#define OLED_Command 0x00
#define OLED_Data 0x40

#define SetDisplayOn 0xAF
#define SetDisplayOff 0xAE

#define SetDisplayPumpEnable 0x8D
#define ChargePumpModel 0x14

#define SetSegmentRemap 0xA1
#define SetComOutputScanDirection 0xC8


#define SetMemoryAddressingMode 0x20
#define PageAddressingMode 0x02
#define HorizontalAddressingMode 0x00

static u8 ClearOLEDArr[16] = { 0x00 };

/**
 * @brief 向OLED写入多个数据 分为命令和数据
 *
 * @param bytes 要写入的数据/命令集合
 * @param len  要写入长度
 * @param bit is_data 1表示数据 0表示命令
 */
static void Int_OLED_WriteBytes(u8* bytes, u8 len, bit is_data) {
    u8 i;
    // 发送启动信号
    Dri_IIC_Start();
    // 发送OLED地址和写标志，并接收应答引号
    Dri_IIC_SendByte(OLED_ADDR);
    Dri_IIC_ReceiveAck();

    // 发送控制字节，确定后续是数据还是命令; 都设置为连续发送
    if (is_data)
    {
        // 控制字节指定后续发的数据， 0100 0000
        Dri_IIC_SendByte(OLED_Data);
    }
    else {
        // 控制字节指定后续发的命令，0000 0000
        Dri_IIC_SendByte(OLED_Command);
    }
    Dri_IIC_ReceiveAck();

    // 依次发送 命令或数据
    for (i = 0; i < len; i++)
    {
        Dri_IIC_SendByte(bytes[i]);
        Dri_IIC_ReceiveAck();
    }

    // 发送结束信号
    Dri_IIC_Stop();
}

// 发送命令
static void Int_OLED_WriteCommand(u8* bytes, u8 len)
{
    Int_OLED_WriteBytes(bytes, len, 0);
}

// 发送数据
static void Int_OLED_WriteData(u8* bytes, u8 len)
{
    Int_OLED_WriteBytes(bytes, len, 1);
}

// 设置页地址和列地址 并发送命令; 两个参数分别是 页地址和列地址

static void Int_OLED_SetAddress(u8 page, u8 column) {
    // 定义数组
    u8 address_cmds[3];
    // page要设置成 1011 0xxx
    address_cmds[0] = page | 0xB0;
    // col要设置成：低4位 0000 xxxx    高3位 0001 0xxx
    address_cmds[1] = column & 0x0F;
    address_cmds[2] = (column >> 4) | 0x10;   // 0000 0xxx    0001 0000     0001 0xxx
    Int_OLED_WriteCommand(address_cmds, 3);
}

/**
 * @brief OLED 初始化
 *
 */
void Int_OLED_Init() {
    u8 cmds[6] = { SetDisplayOff,SetDisplayPumpEnable,ChargePumpModel,SetSegmentRemap,SetComOutputScanDirection,SetDisplayOn };
    Int_OLED_WriteCommand(cmds, 6);
}


/**
 * @brief OLED 清屏
 *
 */
void Int_OLED_Clear() {
    u8 i;
    // 先设置水平寻址方式
    u8 cmds[2] = { SetMemoryAddressingMode,HorizontalAddressingMode };
    // 发送命令
    Int_OLED_WriteCommand(cmds, 2);

    //每个page需要8次，一共8个page  每个字是 16x8  4行x16列
    //一个字存长16宽8  需要两个page
    //  向GDDRAM写入数据，循环 64 次，每次写入 16 个字节，可以写满整个 GDDRAM
    for (i = 0; i < 64; i++)
    {
        Int_OLED_WriteData(ClearOLEDArr, 16);
    }
}

void Int_OLED_ClearSpot(u8 x, u8 y) {
    // 先设置水平寻址方式
    u8 i = 0;
    u8 cmds[8];
    cmds[0] = SetMemoryAddressingMode;
    // 水平寻址
    cmds[1] = HorizontalAddressingMode;
    // 发送标识正在设置列
    cmds[2] = 0x21;
    // 列起始位置
    cmds[3] = x * 8;
    // 列结束位置
    cmds[4] = x * 8 + 8;
    // 发送标识正在设置行
    cmds[5] = 0x22;
    // 行起始位置
    cmds[6] = y * 2;
    // 行结束位置
    cmds[7] = y * 2 + 1;
    Int_OLED_WriteCommand(cmds, 8);

    for (i = 0; i < 1; i++)
    {
        Int_OLED_WriteData(ClearOLEDArr, 16);
    }
}

void Int_OLED_ClearSpotLine(u8 y) {
    u8 i;
    u8 cmds[5];
    // 先设置寻址方式
    cmds[0] = SetMemoryAddressingMode;
    cmds[1] = PageAddressingMode;
    // 设置page位置 B0~B7
    cmds[2] = (y * 2) | 0xB0;
    // 设置列起始位置 0x00~0x0F
    cmds[3] = 0x00;
    // 设置列结束位置 0x10~0x17
    cmds[4] = 0x10;

    // 向GDDRAM写入数据
    // 循环 8 次，每次写入 16 个字节，可以写满一整行
    Int_OLED_WriteCommand(cmds, 5);
    for (i = 0; i < 8; i++)
    {
        Int_OLED_WriteData(ClearOLEDArr, 16);
    }


    cmds[2] = (y * 2 + 1) | 0xB0;
    Int_OLED_WriteCommand(cmds, 5);
    for (i = 0; i < 8; i++)
    {
        Int_OLED_WriteData(ClearOLEDArr, 16);
    }
}


/**
 * @brief OLED 显示字符串
 *
 * @param x X坐标
 * @param y Y坐标
 * @param str 要写入的字符串
 */
void Int_OLED_DisplayStr(u8 x, u8 y, u8* str) {

    u8 i = 0;
    // 一个字存长16宽8  需要两个page
    u8 cmds[2] = { SetMemoryAddressingMode,PageAddressingMode };
    Int_OLED_WriteCommand(cmds, 2);

    Int_OLED_SetAddress(y * 2, x * 8);  //page行对应y  col列对应x
    while ((str[i] != 0) && (x + i < 16)) {
        Int_OLED_WriteData(s_fonts[str[i] - 32], 8);
        i++;
    };

    Int_OLED_SetAddress(y * 2 + 1, x * 8);
    for (i = 0; (str[i] != 0) && (x + i < 16); i++)
    {
        // 写入数据
        Int_OLED_WriteData(s_fonts[str[i] - 32] + 8, 8);
    }
}


/**
 * @brief OLED 显示数字
 *
 * @param x X坐标
 * @param y Y坐标
 * @param num 要写入的数字
 */
void Int_OLED_DisplayNum(u8 x, u8 y, long num)
{
    // 定义字符串 
    u8 str[12];
    // 将 num 转为字符串存入 str
    sprintf(str, "%ld", num);
    // 显示str
    Int_OLED_DisplayStr(x, y, str);
}