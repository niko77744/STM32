#include "Int_EEPROM.h"

static bit WriteToPage(u8 addr, u8* bytes, u8 len) {
    bit ack;
    u8 i;
    // 发送一个起始信号，起始和结束不需要接收ack
    Dri_IIC_Start();

    // !!!忘记发送从设备地址+写标记; 并接收EEPROM的应答信号
    Dri_IIC_SendByte(EEPROM_Address);
    ack |= Dri_IIC_ReceiveAck();

    // 发送写入位置(EEPROM的内部地址)，并接收EEPROM的应答信号
    Dri_IIC_SendByte(addr);
    ack |= Dri_IIC_ReceiveAck();

    // 向 EEPROM 发送数据; 逐字节发送并确认应答信号
    for (i = 0; i < len; i++)
    {
        Dri_IIC_SendByte(bytes[i]);
        ack |= Dri_IIC_ReceiveAck();
    }

    // !!! 忘记发送停止信号
    Dri_IIC_Stop();
    return ack;
}

/**
 * @brief 指定内容指定长度，写入EEPROM指定位置
 *
 * @param u8 addr 要写入位置（EEPROM内部地址）
 * @param u8 *bytes 要写入的内容
 * @param u8 len 要写入的字节个数（bytes的长度）
 *
 * @return bit 0表示所有步骤的应答信号都是0,1表示步骤中至少有一次的应答信号是1
 */
bit Int_EEPROM_WriteBytes(u8 addr, u8* bytes, u8 len) {
    bit ack;

    // 定义变量 记录当前页剩余容量
    u8 page_remain;


    // !!!这里一定是len > 0，不能写len，因为不是--
    while (len > 0)
    {
        // 计算当前页的剩余容量  !!!忘记 PAGE_SIZE -
        page_remain = PAGE_SIZE - addr % PAGE_SIZE;
        if (len > page_remain)
        {
            // 当前页余量不足，需要写入多页 -----------------
            // 写满当前页
            ack |= WriteToPage(addr, bytes, page_remain);

            // 待写入地址后移，移到下一页  所以要后移page_remain位到下一行
            addr += page_remain;   //下一行的地址

            //因为一次是写入1行，1个page，一次已经写了page_remain个字节，所以下一次写入在+page_remain个字节
            bytes += page_remain;

            // 总长度减掉已写入的长度
            len -= page_remain;
        }
        else if (len <= page_remain)
        {
            // 当前页余量充足，足以写下要写入的数据 ----------
            ack |= WriteToPage(addr, bytes, len);

            // !!!忘记 len = 0
            len = 0;
        }
        // 写入有页周期
        Delay_1ms(5);
    }
    return ack;
}

/**
 * @brief 读取指定地址指定长度的内容，写入第二个参数中
 *
 * @param u8 addr 要读取位置（EEPROM内部地址）
 * @param u8 *bytes 将接收的内容写入该地址
 * @param u8 len 要读取的字节个数
 *
 * @return bit 0表示所有步骤的应答信号都是0,1表示步骤中至少有一次的应答信号是1
 */
bit Int_EEPROM_ReadBytes(u8 addr, u8* bytes, u8 len) {
    u8 i;
    bit ack;

    // 1.伪写，设置地址寄存器中的地址 --------------------------------
    // 发送起始信号
    Dri_IIC_Start();

    // 发送EEPROM地址和写标记；并接收应答
    Dri_IIC_SendByte(EEPROM_Address);  //默认写操作 进行一次伪写
    ack |= Dri_IIC_ReceiveAck();

    // 发送地址（EEPROM的内部地址，会被EEPROM写入地址寄存器）;并接收应答信号
    Dri_IIC_SendByte(addr);  //默认写操作 进行一次伪写
    ack |= Dri_IIC_ReceiveAck();
    // 发送结束信号
    Dri_IIC_Stop();


    // 正式读 ------------------------------------------------------
    // 发送起始信号
    Dri_IIC_Start();

    // 发送EEPROM地址和读标记，并接收应答
    Dri_IIC_SendByte(0xA1);  // 也可以写EEPROM_Address+1
    ack |= Dri_IIC_ReceiveAck();

    // 逐字节接收读取到的EEPROM中的内容，并发送应答信号
    for (i = 0; i < len; i++)
    {
        // 接收到字节并存入bytes数组
        bytes[i] = Dri_IIC_ReceiveByte();

        // 发送应答信号 如果接收完最后一个字节，回复1，其他回复0
        Dri_IIC_SendAck(i == (len - 1) ? 1 : 0);
    }

    // 起始和接收都不需要接收ack

    // 发送结束信号
    Dri_IIC_Stop();
    return ack;
}