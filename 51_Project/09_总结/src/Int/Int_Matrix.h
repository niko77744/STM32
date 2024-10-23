#ifndef __Int_Matrix_H__
#define __Int_Matrix_H__
#include "./Com/Com_Util.h"


//     P24 P25 P26 P27
// P20 -|---|---|---|-
// P21 -|---|---|---|-
// P22 -|---|---|---|-
// P23 -|---|---|---|-

// P20-P23控制行，只能有一个是0，P24-P27控制列，全是1，按键按下会有一瞬间变为0


/**
 * @brief 检测矩阵按键中哪个按键被按下
 *
 * @return u8 按键编号
 */
u8 Int_Matrix_CheckKey(void);

#endif /* __Int_Matrix_H__ */
