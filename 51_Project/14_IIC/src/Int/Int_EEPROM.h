#ifndef __INT_EEPROM_H__
#define __INT_EEPROM_H__

#include "Com_Util.h"
#include "Dri_IIC.h"

#define EEPROM_Address 0xA0  // 1010 + E2、E1、E0三个引脚的输入 + 读写标记 最低位默认0表示写
#define PAGE_SIZE 0x10


/**
 * @brief 指定内容指定长度，写入EEPROM指定位置
 *
 * @param u8 addr 要写入位置（EEPROM内部地址）
 * @param u8 *bytes 要写入的内容
 * @param u8 len 要写入的字节个数（bytes的长度）
 *
 * @return bit 0表示所有步骤的应答信号都是0,1表示步骤中至少有一次的应答信号是1
 */
bit Int_EEPROM_WriteBytes(u8 addr, u8* bytes, u8 len);

/**
 * @brief 读取指定地址指定长度的内容，写入第二个参数中
 *
 * @param u8 addr 要读取位置（EEPROM内部地址）
 * @param u8 *bytes 将接收的内容写入该地址
 * @param u8 len 要读取的字节个数
 *
 * @return bit 0表示所有步骤的应答信号都是0,1表示步骤中至少有一次的应答信号是1
 */
bit Int_EEPROM_ReadBytes(u8 addr, u8* bytes, u8 len);

#endif /* __INT_EEPROM_H__ */
