#ifndef __Int_DIGITIAL_H__
#define __Int_DIGITIAL_H__

// �������飬����ÿ�����ֶ�Ӧ�Ķ�ѡ��Ϣ
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

// �������飬��ʾ���棬���������ÿ��λ��Ҫ��ʾ�����ֵĶ�ѡ��Ϣ
static u8 digital_buffer[8];

/**
 * @brief �������ָ��λ��ָ����ѡ��Ϣ
 *
 * @param pos λ�ã� ������������ 0 ~ 7
 * @param code ��ѡ��Ϣ
 */
void DigitalTube_Single(u8, u8);

/**
 * @brief ������ʾ����
 *
 * @param number Ҫ��ʾ�����������֣�ʮ���Ʊ�ʾ��
 */
void DigitalTube_SetBuffer(u32);

/**
 * @brief ����ʾ�����е�������ʾ�������
 */
void DigitalTube_Refresh();

#endif