#include "Dri_1Wire.h"
#define DQ P44
#include "MATH.H"

/**
 * @brief 初始化
 *
 * @return bit 返回从设备的应答信号
 */
bit Dri_1Wire_Init() {
    bit result;
    //1.主设备拉低总线至少480us
    DQ = 0;
    Delay480us();
    //2.主设备释放总线以让从设备在15-60us内回应,前15us是确保DQ回到高电平
    DQ = 1;
    // 确保从设备回应完毕
    Delay60us();

    // 采集数据，0表示回应成功 从设备会拉低总线表示回应
    DQ = result;

    // 从设备拉低总线保持60-240us后拉高总线，还要延迟时间以满足最小时长480us
    Delay480us();

    return result;
}


/**
 * @brief 发送1个字节的数据
 *
 * @param byte 要发送的字节
 */
void Dri_1Wire_SendByte(u8 byte) {
    u8 i;
    u8 temp = 0x01;

    // 1-wire是低位先发，只有IIC是高位先发
    // 一定要在15us内改变状态,所以不要进行多位位运算
    for (i = 0; i < 8; i++)
    {
        // 拉低总线表示要发送数据
        DQ = 0;
        // 在15us内改变总线状态
        Delay10us();
        // 将byte低位取出赋给DQ
        DQ = ((byte & temp) == 0 ? 0 : 1);
        temp <<= 1;

        // DQ = byte & 1;
        // byte >>= 1;   
        // DQ = (byte >> i) & 1;   // 该指令花费时间过长，导致无法在15微秒改变DQ状态

        // 延时以满足整个周期60us
        Delay50us();

        // 拉高总线以便下次拉低同时以标识1bit发送完成
        DQ = 1;
    }
}

/**
 * @brief 接收1个字节的数据
 *
 * @return 返回接收的字节
 */
u8 Dri_1Wire_ReceiveByte() {
    u8 i;
    u8 byte = 0x00;
    bit temp;
    for (i = 0; i < 8; i++)
    {
        // 拉低马上拉高以表示读取
        DQ = 0;
        DQ = 1;
        // 等待从设备改变总线状态 15us内改变
        Delay10us();
        temp = DQ;
        // 将DQ一位一位放入byte，低位先接收
        byte += (temp * (1 << i));

        /*
        DQ = 1100 1010
        byte = 0 * 2^0   +   1 * 2^1    +   0 * 2^2    +   1 * 2^3
        */

        // if (DQ == 1)
        // {
        //     byte = byte | (1 << i);
        // }

        /*
        00000000

        第一次接收1： 00000000 | (1 << 0), 变为 00000001
        第二次接收0： 条件不成立            变为 00000001
        第三次接收1： 00000001 | (1 << 2)   变为 00000101

        */

        // 延时以满足整个周期60us  从设备会自动拉高释放总线
        Delay50us();
    }


    return byte;
}