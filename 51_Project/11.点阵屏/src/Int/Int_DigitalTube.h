#ifndef __Int_DigitalTube__
#define __Int_DigitalTube__

#include "Com_Util.h"

// 初始化
void Int_DigitalTube_Init(void);

// 静态显示
void Int_DigitalTube_StaticDisplay(u8);

// 控制位选和段选 将结果输入到CU 真正的显示函数 通过控制P1控制38译码器重新选择
void Int_DigitalTube_Single(u8, u8);

// 向Buffer数组写入数据 将十进制的数字每一位拆下来放的 段选 在buffer数组最后
void Int_DigitalTube_SetBuffer(u32);

// 负数显示
void Int_DigitalTube_SetNegativeBuffer(float);

// 遍历buffer数组
void Int_DigitalTube_Refresh(void);

#endif /* __Int_DigitalTube__ */
