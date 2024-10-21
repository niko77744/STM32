#include "Com_IWDG.h"

#define IWDG_Start 0xCCCC
#define IWDG_WriteEnable 0x5555
#define IWDG_Refresh 0xAAAA

void Com_IWDG_Init(void) {
    // �������Ź�
    IWDG->KR = IWDG_Start;
    IWDG->KR = IWDG_WriteEnable;

    // Ԥ��Ƶϵ��  4 = 0b100 = 64��Ƶ      40KHz / 64 = 625Hz = 0.0016s = 1.6ms
    IWDG->PR = 4;
    // ��װ��ֵ
    IWDG->RLR = 2500 - 1;  //2500 * 1.6ms = 4s

    IWDG->KR = IWDG_Refresh;
}
void Com_IWDG_Refresh(void) {
    IWDG->KR = IWDG_Refresh;
}
