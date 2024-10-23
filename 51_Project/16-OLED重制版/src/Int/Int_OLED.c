#include "Int_OLED.h"

// 注意宏定义不要写错了，最难排查
#define OLEDAddrWrite 0x78

// 注意：D/C#
#define OLED_Data 0x40
#define OLED_Command 0x00

#define SetAddMode 0x20
#define SetAdd_Horizontal 0x00
#define SetAdd_Page 0x02

#define SetColRemap 0xA1
#define SetRowRemap 0xC8

// 注意：写反了
#define SetDisplayOn 0xAF
#define SetDisplayOff 0xAE

#define SetPump 0x8D
#define SetPumpLevel 0x14

/**
 * 向OLED显示器发送字节数据
 *
 * @param bytes 要发送的数据字节数组
 * @param is_data 标记数据类型，1表示数据，0表示命令
 * @param len 要发送的字节数
 *
 * 本函数通过IIC通信协议向OLED显示器发送数据或命令字节
 * 首先启动IIC通信，发送OLED设备的写地址，并接收应答
 * 根据is_data参数，发送数据或命令标识符，并接收应答
 * 然后逐字节发送数据数组中的字节，并在每个字节后接收应答
 * 最后停止IIC通信
 */
static void Int_OLED_SendBytes(u8* bytes, bit is_data, u8 len) {
    u8 i;
    Dri_IIC_Start();

    Dri_IIC_SendByte(OLEDAddrWrite);
    Dri_IIC_ReceiveAck();

    if (is_data)
    {
        Dri_IIC_SendByte(OLED_Data);
    }
    else {
        Dri_IIC_SendByte(OLED_Command);
    }
    Dri_IIC_ReceiveAck();


    for (i = 0; i < len; i++)
    {
        Dri_IIC_SendByte(bytes[i]);
        Dri_IIC_ReceiveAck();
    }

    Dri_IIC_Stop();
}

static void Int_OLED_SendData(u8* bytes, u8 len) {
    Int_OLED_SendBytes(bytes, 1, len);
}

static void Int_OLED_SendCommand(u8* bytes, u8 len) {
    Int_OLED_SendBytes(bytes, 0, len);
}


void Int_OLED_Init() {
    u8 cmds[6] = { SetDisplayOff, SetColRemap,SetRowRemap,SetPump,SetPumpLevel,SetDisplayOn };
    Int_OLED_SendCommand(cmds, 6);
}


void Int_OLED_Clear() {
    u8 i;
    u8 ClearArr[16] = { 0x00 };
    u8 cmds[2] = { SetAddMode,SetAdd_Horizontal };
    Int_OLED_SendCommand(cmds, 2);

    for (i = 0; i < 64; i++)
    {
        Int_OLED_SendData(ClearArr, 16);
    }
}


/**
 * 在OLED显示屏上显示字符串
 *
 * 此函数负责将给定的字符数组显示在OLED显示屏上的指定位置
 * 它通过发送命令和数据到OLED控制器来实现显示功能
 *
 * 参数:
 * x - 字符串显示的起始列位置（0-15）
 * y - 字符串显示的起始页位置（0-7）
 * bytes - 指向要显示的字符数组的指针
 *
 * 注意:
 * 1. 该函数假设OLED显示屏为128x64像素，使用I2C通信
 * 2. 字符数组应包含可打印的ASCII字符（32-127）
 */
void Int_OLED_DisplayStr(u8 x, u8 y, u8* bytes) {
    u8 i = 0; // 用于遍历字符数组的索引
    u8 cmds[5]; // 命令数组，用于存储发送到OLED控制器的命令

    // 初始化命令数组，设置地址模式和页面模式
    cmds[0] = SetAddMode;
    cmds[1] = SetAdd_Page;
    cmds[2] = (y * 2) | 0xB0; // 设置页面地址
    cmds[3] = (x * 8) & 0x0F; // 设置列地址的低4位
    cmds[4] = ((x * 8) >> 4) | 0x10; // 设置列地址的高4位

    // 发送初始化命令到OLED控制器
    Int_OLED_SendCommand(cmds, 5);

    // 遍历字符数组，发送字符数据到OLED控制器
    while ((bytes[i] != '\0') && (x + i < 16)) {
        Int_OLED_SendData(s_fonts[bytes[i] - 32], 8);
        i++;
    }

    // 准备发送下一个页面的命令
    cmds[2] = (y * 2 + 1) | 0xB0; // 更新页面地址
    Int_OLED_SendCommand(cmds, 5); // 发送命令

    // 继续发送字符数据到OLED控制器
    while ((bytes[i] != '\0') && (x + i < 16)) {
        Int_OLED_SendData(s_fonts[bytes[i] - 32] + 8, 8);
        i++;
    }
}


void Int_OLED_DisplayNum(u8 x, u8 y, long num) {
    char str[17];
    sprintf(str, "%ld", num);
    Int_OLED_DisplayStr(x, y, str);
}

