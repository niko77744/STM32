#include "./Com_Util.h"
#include "./Int_DigitalTube.h"

void main()
{
    char i = 100;
    unsigned int n = 2000;
    // �ر���ˮ��
    P34 = 0;
    // �������
    P36 = 0;

    while (1) {
        if (0 == i)
        {
            DigitalTube_SetBuffer(n);
            i = 100;
            n++;
        }

        DigitalTube_Refresh();
        i--;
    }
}


