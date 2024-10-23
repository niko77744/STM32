#include "Int_18B20.h"

#define SkipROM 0xCC
#define measure_temperature 0x44
#define read_temperature 0xBE


/**
 * @brief ��ȡ��18B20��õ��¶�
 *
 * @return char ��ʾ���¶�
 */
char Int_18B20_GetTemperature() {
    u8 ls_byte;
    u8 ms_byte;

    // ��һ�� ���Ͳ������� ------------------------------------
    // ��ʼ��
    Dri_1Wire_Init();
    // ����Ѱַ�����豸��
    Dri_1Wire_SendByte(SkipROM);
    // ��18B20���Ͳ�������, ����֮���洢�ݴ���
    Dri_1Wire_SendByte(measure_temperature);


    // �ڶ��� ��ȡ18B20�ݴ����е���ֵ -------------------------
    // ��ʼ��  18b20�涨����Ҫ�ٴγ�ʼ��
    Dri_1Wire_Init();
    Dri_1Wire_SendByte(SkipROM);
    Dri_1Wire_SendByte(read_temperature);


    // ������ �����ȡ�������� --------------------------------
    /*
        ls_byte:  1011xxxx
        ms_byte:  xxxx0010

        ls_byte >> 4:  00001011
        ms_byte << 4:  00100000
    */
    ls_byte = Dri_1Wire_ReceiveByte();
    ms_byte = Dri_1Wire_ReceiveByte();
    // ��ls�ĸ���λ��ms�ĵ���λƴ����  
    return (ls_byte >> 4) + (ms_byte << 4);  // (ls_byte >> 4) | (ms_byte << 4)
}


/**
 * @brief ��ȡ��18B20��õ��¶�
 *
 * @return float ��ʾ���¶�
 */
float Int_18B20_GetTemperatureFloat() {
    u8 ls_byte;
    u8 ms_byte;

    // ��һ�� ���Ͳ������� ------------------------------------
    // ��ʼ��
    Dri_1Wire_Init();
    // ����Ѱַ�����豸��
    Dri_1Wire_SendByte(SkipROM);
    // ��18B20���Ͳ�������, ����֮���洢�ݴ���
    Dri_1Wire_SendByte(measure_temperature);


    // �ڶ��� ��ȡ18B20�ݴ����е���ֵ -------------------------
    // ��ʼ��  18b20�涨����Ҫ�ٴγ�ʼ��
    Dri_1Wire_Init();
    Dri_1Wire_SendByte(SkipROM);
    Dri_1Wire_SendByte(read_temperature);

    // ������ �����ȡ�������� --------------------------------
    /*
        С�����֣�
        ls_byte ȡ�����4λ���Ѹ�4λ��Ϊ0�� &00001111
    */
    // �������� + С������

    ls_byte = Dri_1Wire_ReceiveByte();
    ms_byte = Dri_1Wire_ReceiveByte();
    // ��ls�ĸ���λ��ms�ĵ���λƴ����  
    return (ls_byte >> 4) + (ms_byte << 4) + (ls_byte & 0x0F) * 0.0625;
}
