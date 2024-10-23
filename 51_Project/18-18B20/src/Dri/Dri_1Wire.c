#include "Dri_1Wire.h"
#define DQ P44

/**
 * @brief 初始化
 *
 * @return bit 返回从设备的应答信号
 */
bit Dri_1Wire_Init()
{
    bit result;

    // 发送复位脉冲
    DQ = 0;
    // 持续480μs
    Delay480us();

    // 释放DQ
    DQ = 1;

    // 15~60微秒后，获取DQ的值
    Delay60us();
    result = DQ;

    // 从DQ释放开始，至少延迟480微妙，再进行后续操作
    Delay480us();

    return result;
}

/**
 * @brief 发送1个字节的数据
 *
 * @param byte 要发送的字节
 */
void Dri_1Wire_SendByte(u8 byte)
{
    u8 i;
    // 逐比特发送，循环
    for (i = 0; i < 8; i++)
    {
        // 先拉低总线，表示要发送数据
        DQ = 0;

        // 需要在15微妙之内，向DQ发送数据； 所以，10微秒后修改DQ的值
        Delay10us();
        DQ = byte >> i;

        /*
        abcdefgh >> 0
        abcdefgh >> 1
        abcdefgh >> 2
        ...
        abcdefgh >> 7
        */

        // 持续50微妙
        Delay50us();

        // 释放总线
        DQ = 1;
    }
}

/**
 * @brief 接收1个字节的数据
 *
 * @return 返回接收的字节
 */
u8 Dri_1Wire_ReceiveByte()
{
    u8 i;
    // 定义变量保存读到的字节 0000 0000
    u8 byte = 0x00;

    // 循环读取8次，逐比特读取
    for (i = 0; i < 8; i++)
    {
        // 主设备拉低DQ 保持1微妙
        DQ = 0;
        // 主设备释放DQ
        DQ = 1;

        // 10微妙之后从总线采样  先收到低位
        Delay10us();
        // byte <<= 1;
        // byte = DQ;

        if (DQ == 1)
        {
            byte = byte | (1 << i);
        }

        /*
        00000000

        第一次接收1： 00000000 | (1 << 0), 变为 00000001
        第二次接收0： 条件不成立            变为 00000001
        第三次接收1： 00000001 | (1 << 2)   变为 00000101

        */

        // 再延时50us，凑够60us
        Delay50us();
    }

    return byte;
}