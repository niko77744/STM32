#include "Int_MatrixSW.h"

// �������в�������
static Int_MatrixSW_rows[4] = {0xFE, 0xFD, 0xFB, 0xF7};

u8 Int_MatrixSW_IsSWPressed()
{
    u8 i;
    // ���в��Ұ���
    for (i = 0; i < 4; i++)
    {
        P2 = Int_MatrixSW_rows[i];
        // ���в��Ұ����Ƿ񱻰���
        if (P24 == 0)
        {
            Delay1ms(10); // ��������
            while (P24 == 0)
                ; // �ȴ�����̧��
            return 5 + 4 * i;
        }
        if (P25 == 0)
        {
            Delay1ms(10); // ��������
            while (P25 == 0)
                ; // �ȴ�����̧��
            return 6 + 4 * i;
        }
        if (P26 == 0)
        {
            Delay1ms(10); // ��������
            while (P26 == 0)
                ; // �ȴ�����̧��
            return 7 + 4 * i;
        }
        if (P27 == 0)
        {
            Delay1ms(10); // ��������
            while (P27 == 0)
                ; // �ȴ�����̧��
            return 8 + 4 * i;
        }
    }
    return 0;
}