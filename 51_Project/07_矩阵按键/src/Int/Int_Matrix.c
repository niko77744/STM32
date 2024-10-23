#include "Int_Matrix.h"


u8 Int_Matrix_CheckKey() {
    u8 i;
    for (i = 0; i < 4; i++)
    {
        P2 = lines[i];
        if (P24 == 0)
        {
            Delay_1ms(10);
            if (P24 == 0)
            {
                while (P24 == 0);
                return 5 + 4 * i;
            }
        }
    }
    return 0;
}