/**
  **********************************************************************************
  * @file      board_ebyte_E220xx.h
  * @brief     E220 ϵ�� ������     
  * @details   ������μ� https://www.ebyte.com/       
  * @author    JiangHeng     
  * @date      2021-05-08     
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
#include "ebyte_conf.h"
#include "ebyte_callback.h"

/**
 * �ز�����Ƶ�� 
 *
 * @note �й�-��ҵ����Ϣ����
 *
 * ���л����񹲺͹����ߵ�Ƶ�ʻ��ֹ涨��(��ҵ����Ϣ�������46���� 2018��7��1����ʩ��) 
 *  �涨�������ر���׼ISMӦ��Ƶ��( Sub-1G��Χ ):  
 *          6.765��6.795MHz ������Ƶ��6.780MHz��
 *         13.553��13.567MHz (����Ƶ��13.560MHz)
 *         26.957��27.283MHz (����Ƶ��27.120MHz)     
 *          40.66��40.7MHz   (����Ƶ��40.68MHz��   
 *
 * ��΢����(�̾���)���ߵ��豸�ļ���Ҫ�󡷣��Ų��ޡ�2005��423�ţ�(��ҵ����Ϣ������52���� 2019��)
 *  �涨��΢�������ߵ��豸Ӧ��Ƶ��( Sub-1G��Χ ):
 *  A��      9KHz��190KHz
 *  B��    1.7MHz��2.1MHz 
 *         2.2MHz��3.0MHz 
 *         3.1MHz��4.1MHz 
 *         4.2MHz��5.6MHz 
 *         5.7MHz��6.2MHz 
 *         7.3MHz��8.3MHz 
 *         8.4MHz��9.9MHz 
 *  C��  6.765MHz��6.795MHz 
 *      13.553MHz��13.567MHz 
 *      26.957MHz��27.283MHz 
 *  D��    315kHz��30MHz 
 *  E��  40.66MHz��40.7MHz
 *  ------------------------- 
 *      26.975MHz��27.255MHz    ģ�͡����: ����/��ģ
 *       40.61MHz��40.75MHz     ģ�͡����: ����/��ģ
 *       40.77MHz��40.85MHz     ģ�͡����: ��ģ
 *          45MHz��45.475MHz    ģ��ʽ�绰��: ������
 *          48MHz��48.475MHz    ģ��ʽ�绰��: �ֻ���
 *       72.13MHz��72.84MHz     ģ�͡����: ��ģ
 *        75.4MHz��76.0MHz      �������估�����Ǳ�
 *          84MHz��87MHz        �������估�����Ǳ�
 *          87MHz��108MHz       �������估�����Ǳ�
 *         174MHz��216MHz       ����ҽѧ�豸 
 *       189.9MHz��223.0MHz     �������估�����Ǳ�
 *         223MHz��224MHz       ���ӵ���ר��
 *         224MHz��231MHz       �������ݴ����豸
 *         314MHz��316MHz       �����豸����
 *         407MHz��425MHz       ����ҽѧ�豸
 *      409.75MHz��409.9875MHz  ���ڶԽ���
 *     419.950MHz��419.275MHz   ��ҵ������ң���豸
 *         430MHz��432MHz       �����豸����
 *         433MHz��434.79MHz    �����豸����
 *    450.0125MHz��450.2125MHz  �����豸����
 *         470MHz��510MHz       ���ü����豸
 *         470MHz��566MHz       ͨ������ң���豸
 *         608MHz��630MHz       ����ҽѧ�豸
 *         614MHz��787MHz       ͨ������ң���豸
 *                
 * @note ���Ϲ�-���ʵ�������-���ߵ�ͨ�Ų���(ITU-R)
 * 
 * ��Report ITU-R SM.2180: Impact of Industrial, Scientific and Medical (ISM) Equipment on Radiocommunication Services��(2011��1��)
 *  SM.2180����ָ�������ر���׼��ISMӦ��Ƶ��( Sub-1G��Χ ): 
 *          6.765��6.795MHz ������Ƶ��6.780MHz��
 *         13.553��13.567MHz (����Ƶ��13.560MHz)
 *         26.957��27.283MHz (����Ƶ��27.120MHz)   
 *          40.66��40.7MHz   (����Ƶ��40.68MHz��      
 *         433.05��434.79MHz (����Ƶ��433.92MHz��   ������ITU 1��ʹ�� (ŷ�޺ͷ����Լ��ɹš�ԭ�����Ա��ĵ�����ŷ�ޡ�����������ԭ�����������������)
 *            902��928MHz    (����Ƶ��915MHz��      ������ITU 2��ʹ�� (�ϡ������޺�������)       
 *  �й���ITU 3��(���ޡ������޺������������������)
 * 
 * @note ŷ��
 *  ��COMMISSION DECISION of 9 November 2006 - on harmonisation of the radio spectrum for use by short-range devices��(2006/771/EC)
 *   ŷ�����ߵ翪��Ƶ���еģ������ر���׼Ƶ�λ������У�
 *          868.0��869.25MHz 
 *
 *   ����CE��֤�����˽�ŷ�������豸ָ��RED 2014/53/EU 
 *
 * @note ���� 
 *  ��47 CFR Part 18 - INDUSTRIAL, SCIENTIFIC, AND MEDICAL EQUIPMENT��
 *   FCC��18���ֹ���涨��ISMƵ�� 
 *
 *   ����FCC��֤�����˽� 47 CFR Part 15
 */

/* EBYTE_E220_400M22S ģ�����ͨ��Ƶ��  */
#if defined(EBYTE_E220_400M22S)
#define RF_FREQUENCY_START                          410125000 // Hz ��ʼƵ��
#define RF_FREQUENCY_CH_STEP                        1000000   // Hz Ƶ�ʼ��㲽��      
#define RF_FREQUENCY_CH                             23        // Hz Ƶ�ʼ���ͨ��(������)     �趨Ƶ�� 410.125 + 23 * 1 = 433.125MHz

/* EBYTE_E220_900M22S ģ�����ͨ��Ƶ��  */
#elif defined(EBYTE_E220_900M22S) 
#define RF_FREQUENCY_START                          902125000 // Hz ��ʼƵ��
#define RF_FREQUENCY_CH_STEP                        1000000   // Hz Ƶ�ʼ��㲽��      
#define RF_FREQUENCY_CH                             13        // Hz Ƶ�ʼ���ͨ��(������)     �趨Ƶ�� 902.125 + 13 * 1 = 915.125MHz

#endif

/* ���书�� */
#define RF_TX_OUTPUT_POWER                          22        // dBm

/**
 * ���ν������ݰ���������
 * ���ڲ����������� 256-Byte ) �����ճ��ȴ��ڸ�ֵʱ��Ӧ�ò�����������ô����ݰ�
 */    
#define RF_RX_BUFFER_SIZE                           255 

/* �źŵ��Ʒ�ʽ */   
#define RF_TX_RX_MODE                               0         // 0=LoRa  1=FSK
   
/**
 * LoRa ���ݰ�ͬ����
 * ע�⣺�����ģ���ͬ���ֲ���ͬʱ������֮���޷�ͨ��
 */   
#define LORA_MAC_PUBLIC_SYNCWORD                    0x5B4A    // 0x3444
   
/* LoRaģʽ ����(bps)����  */
#define RF_LORA_AIR_BPS                             2         // 0=0.3k  1=1.2k  2=2.4k  3=4.8k  4=9.6k  5=19.5k  6=38.4k  7=62.5k       

/* FSKģʽ ǰ���볤��*/    
#define FSK_PREAMBLE_LENGTH                         20   
    
/* FSKģʽ ͬ���� ���8 Byte ��Ҫָ������*/
#define FSK_MAC_PUBLIC_SYNCWORD_LENGTH              2 
#define FSK_MAC_PUBLIC_SYNCWORD_7                   0x57
#define FSK_MAC_PUBLIC_SYNCWORD_6                   0x4B
#define FSK_MAC_PUBLIC_SYNCWORD_5                   0x00
#define FSK_MAC_PUBLIC_SYNCWORD_4                   0x00                  
#define FSK_MAC_PUBLIC_SYNCWORD_3                   0x00 
#define FSK_MAC_PUBLIC_SYNCWORD_2                   0x00 
#define FSK_MAC_PUBLIC_SYNCWORD_1                   0x00    
#define FSK_MAC_PUBLIC_SYNCWORD_0                   0x00    
      
/**
 * ���ù�ϵ��
 * 
 *   DataRate          FrenquencyDeviation        BW
 *    4.8kbps                16KHz                31KHz
 *    9.6kbps                20KHz                31KHz
 *     20kbps                30KHz                50KHz
 *     40kbps                40KHz              62.5KHz
 *    100kbps               100KHz               166KHz
 */                                                               
/* FSKģʽ ����  */
#define RF_FSK_DATA_RATE                            4800     // 4.8kbps  
/* FSKģʽ Ƶ��  */
#define RF_FSK_FREQUENCY_DEVIATION                  16000    // 16k    
/* FSKģʽ Ƶ��  */
#define RF_FSK_BANDWIDTH                            31000    // 31k   

   
void Ebyte_E220x_Init( void );
void Ebyte_E220x_SetRfFrequency( uint32e_t frequency );
void Ebyte_E220x_SetRx( uint32e_t timeout );
void Ebyte_E220x_SendPayload( uint8e_t *payload, uint8e_t size, uint32e_t timeout );
void Ebyte_E220x_ClearIrqStatus( uint16e_t irq );
void Ebyte_E220x_ClearDeviceErrors( void );
void Ebyte_E220x_SendPayload( uint8e_t *payload, uint8e_t size, uint32e_t timeout );
void Ebyte_E220x_IntOrPollTask( void );
void Ebyte_E220x_InterruptTrigger(void);
void Ebyte_E220x_SetSleep( uint8e_t  cmd );
uint32e_t Ebyte_E220x_GetName(void);
uint8e_t Ebyte_E220x_GetDriverVersion(void);
