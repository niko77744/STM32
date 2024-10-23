#ifndef __Int_Key_H__
#define __Int_Key_H__

#include "./Com/Com_Util.h"
#define SW1 P42
#define SW2 P43
#define SW3 P32
#define SW4 P33

/**
 * @brief ��ⰴ���Ƿ��£����·���1�����򷵻�0
 */
bit Int_Key_IsSw1Pressed(void);
bit Int_Key_IsSw2Pressed(void);
bit Int_Key_IsSw3Pressed(void);
bit Int_Key_IsSw4Pressed(void);

#endif /* __Int_Key_H__ */
