#ifndef __Int_DIGITIAL_H__
#define __Int_DIGITIAL_H__

// 定义数组，保存每个数字对应的段选信息
static u8 number_codes[10] = {
    0x3F, // 0
    0x06, // 1
    0x5B, // 2
    0x4F, // 3
    0x66, // 4
    0x6D, // 5
    0x7D, // 6
    0x07, // 7
    0x7F, // 8
    0x6F  // 9
};

// 定义数组，显示缓存，保存数码管每个位置要显示的数字的段选信息
static u8 digital_buffer[8];

/**
 * @brief 给数码管指定位置指定段选信息
 *
 * @param pos 位置， 从左向右依次 0 ~ 7
 * @param code 段选信息
 */
void DigitalTube_Single(u8, u8);

/**
 * @brief 设置显示缓存
 *
 * @param number 要显示的完整的数字（十进制表示）
 */
void DigitalTube_SetBuffer(u32);

/**
 * @brief 将显示缓存中的数据显示到数码管
 */
void DigitalTube_Refresh();

#endif