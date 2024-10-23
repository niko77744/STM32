#ifndef __INT_EEPROM_H__
#define __INT_EEPROM_H__

#include "Com_Util.h"
#include "Dri_IIC.h"

#define EEPROM_Address 0xA0  // 1010 + E2��E1��E0�������ŵ����� + ��д��� ���λĬ��0��ʾд
#define PAGE_SIZE 0x10


/**
 * @brief ָ������ָ�����ȣ�д��EEPROMָ��λ��
 *
 * @param u8 addr Ҫд��λ�ã�EEPROM�ڲ���ַ��
 * @param u8 *bytes Ҫд�������
 * @param u8 len Ҫд����ֽڸ�����bytes�ĳ��ȣ�
 *
 * @return bit 0��ʾ���в����Ӧ���źŶ���0,1��ʾ������������һ�ε�Ӧ���ź���1
 */
bit Int_EEPROM_WriteBytes(u8 addr, u8* bytes, u8 len);

/**
 * @brief ��ȡָ����ַָ�����ȵ����ݣ�д��ڶ���������
 *
 * @param u8 addr Ҫ��ȡλ�ã�EEPROM�ڲ���ַ��
 * @param u8 *bytes �����յ�����д��õ�ַ
 * @param u8 len Ҫ��ȡ���ֽڸ���
 *
 * @return bit 0��ʾ���в����Ӧ���źŶ���0,1��ʾ������������һ�ε�Ӧ���ź���1
 */
bit Int_EEPROM_ReadBytes(u8 addr, u8* bytes, u8 len);

#endif /* __INT_EEPROM_H__ */
