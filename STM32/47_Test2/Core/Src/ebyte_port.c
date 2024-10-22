/**
  **********************************************************************************
  * @file      ebyte_port.h
  * @brief     EBYTE�������Ӳ���ӿڲ� �ɿͻ��Լ��ṩIO�ӿ�
  * @details   ������μ� https://www.ebyte.com/
  * @author    JiangHeng
  * @date      2021-05-13
  * @version   1.0.0
  **********************************************************************************
  * @copyright BSD License
  *            �ɶ��ڰ��ص��ӿƼ����޹�˾
  *   ______   ____   __     __  _______   ______
  *  |  ____| |  _ \  \ \   / / |__   __| |  ____|
  *  | |__    | |_) |  \ \_/ /     | |    | |__
  *  |  __|   |  _ <    \   /      | |    |  __|
  *  | |____  | |_) |    | |       | |    | |____
  *  |______| |____/     |_|       |_|    |______|
  *
  **********************************************************************************
  */
#include "ebyte_port.h"


  /*= !!!����Ŀ��Ӳ��ƽ̨ͷ�ļ� =======================================*/
#include "spi.h"
/*==================================================================*/

/* !
 * @brief ����Ŀ��Ӳ��ƽ̨SPI�ӿ��շ�����
 *
 * @param send EBYTE�������ϲ������Ҫ��������� 1 Byte
 * @return SPI���յ����� 1 Byte
 * @note ��Ŀ��ƽ̨����Ӳ��SPI_NSSʱ�������� ebyte_conf.h�ļ� �ر���������������SPI_CS(NSS)
 *       ��Ŀ��ƽ̨�������SPI_NSSʱ������������� Ebyte_Port_SpiCsIoControl() ��������ĺ���˵��
 */
uint8e_t Ebyte_Port_SpiTransmitAndReceivce(uint8e_t send)
{
    uint8e_t result = 0;

    /* !�����ṩ: SPI�ӿ� */
    HAL_SPI_TransmitReceive(&hspi1, &send, &result, 1, HAL_MAX_DELAY);
    return result;
}

/* !
 * @brief (��ѡ)����Ŀ��Ӳ��ƽ̨SPI_CS(NSS)����
 *
 * @param cmd EBYTE�������ϲ������Ŀ���ָ��
 *            @arg 0: ����CS(NSS)��������͵�ƽ�߼��ź� EBYTEģ��SPI�ӿ�Ϊ�͵�ƽѡ��
 *            @arg 1: ����CS(NSS)��������ߵ�ƽ�߼��ź�
 * @note ��Ŀ��ƽ̨����Ӳ��SPI_NSSʱ���������ļ����� �˺�������Ч
 *       ��Ŀ��ƽ̨�������SPI_NSSʱ�������ô˺���
 */
void Ebyte_Port_SpiCsIoControl(uint8e_t cmd)
{
    if (cmd == 1)
    {
        /* !��ѡ: SPI CS���� E22xx�ߵ�ƽδѡ�� */
        HAL_GPIO_WritePin(LoRa_CS_GPIO_Port, LoRa_CS_Pin, GPIO_PIN_SET);
    }
    else
    {
        /* !��ѡ: SPI CS���� E22xx�͵�ƽѡ�� */
        HAL_GPIO_WritePin(LoRa_CS_GPIO_Port, LoRa_CS_Pin, GPIO_PIN_RESET);
    }
}

/* !
 * @brief ����Ŀ��Ӳ��ƽ̨��λ���� NRST ���ƺ���
 *
 * @param cmd EBYTE�������ϲ������Ŀ���ָ��
 *            @arg 0: ����NRST ��������͵�ƽ�߼��ź�
 *            @arg 1: ����NRST ��������ߵ�ƽ�߼��ź�
 * @note EBYTEģ��NRSTΪ�͵�ƽ��λ
 */
void Ebyte_Port_RstIoControl(uint8e_t cmd)
{
    if (cmd == 1)
    {
        /* !�����ṩ: NRST����IO ����ߵ�ƽ */
        HAL_GPIO_WritePin(LoRa_NRST_GPIO_Port, LoRa_NRST_Pin, GPIO_PIN_SET);
    }
    else
    {
        /* !�����ṩ: Ŀ��Ӳ����·��ӦNRST����IO ����͵�ƽ */
        HAL_GPIO_WritePin(LoRa_NRST_GPIO_Port, LoRa_NRST_Pin, GPIO_PIN_RESET);
    }
}

/* !
 * @brief (��ѡ)����Ŀ��Ӳ��ƽ̨����ʹ������ TXEN ���ƺ���
 *
 * @param cmd EBYTE�������ϲ������Ŀ���ָ��
 *            @arg 0: ����TXEN ��������͵�ƽ�߼��ź�
 *            @arg 1: ����TXEN ��������ߵ�ƽ�߼��ź�
 * @note EBYTEģ��TXENΪ�ߵ�ƽ��Ч
 *       ��Ŀ��ƽ̨����ģ��DIO2�Զ�����TXENʱ���˺�������Ч
 */
void Ebyte_Port_TxenIoControl(uint8e_t cmd)
{
    if (cmd == 1)
    {
        /* !��ѡ: Ŀ��Ӳ����·��ӦTXEN����IO ����ߵ�ƽ */
        HAL_GPIO_WritePin(LoRa_TxEN_GPIO_Port, LoRa_TxEN_Pin, GPIO_PIN_SET);
    }
    else
    {
        /* !��ѡ: Ŀ��Ӳ����·��ӦTXEN����IO ����͵�ƽ */
        HAL_GPIO_WritePin(LoRa_TxEN_GPIO_Port, LoRa_TxEN_Pin, GPIO_PIN_RESET);
    }
}

/* !
 * @brief ����Ŀ��Ӳ��ƽ̨����ʹ������ RXEN ���ƺ���
 *
 * @param cmd EBYTE�������ϲ������Ŀ���ָ��
 *            @arg 0: ����RXEN��������͵�ƽ�߼��ź�
 *            @arg 1: ����RXEN��������ߵ�ƽ�߼��ź�
 * @note EBYTEģ��RXENΪ�ߵ�ƽ��Ч
 */
void Ebyte_Port_RxenIoControl(uint8e_t cmd)
{
    if (cmd == 1)
    {
        /* !�����ṩ: Ŀ��Ӳ����·��ӦRXEN����IO ����ߵ�ƽ */
        HAL_GPIO_WritePin(LoRa_RxEN_GPIO_Port, LoRa_RxEN_Pin, GPIO_PIN_SET);

    }
    else
    {
        /* !�����ṩ: Ŀ��Ӳ����·��ӦRXEN����IO ����͵�ƽ */
        HAL_GPIO_WritePin(LoRa_RxEN_GPIO_Port, LoRa_RxEN_Pin, GPIO_PIN_RESET);

    }
}

/* !
 * @brief ����Ŀ��Ӳ��ƽ̨����ʹ������ BUSY ���ƺ���
 *
 * @note EBYTEģ��BUSYΪ�ߵ�ƽ��ʾæ
 */
uint8e_t Ebyte_Port_BusyIoRead(void)
{
    uint8e_t result = 0;

    /* !�����ṩ: Ŀ��Ӳ����·��ӦBUSY IO ״̬��ȡ */
    result = HAL_GPIO_ReadPin(LoRa_BUSY_GPIO_Port, LoRa_BUSY_Pin);
    return result;
}

/* !
 * @brief ����Ŀ��Ӳ��ƽ̨��ʱ����
 *
 * @param time ������ʱ����
 * @note ��ע��ʱ��ģ���ʼ��ʱ�����ô˺�������ע���ж��Ƿ��Ӱ�쵽�˺���
 */
void Ebyte_Port_DelayMs(uint16e_t time)
{
    /* !�����ṩ: ��ʱ���� */
    HAL_Delay(time);
}



