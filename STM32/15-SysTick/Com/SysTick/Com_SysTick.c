#include "Com_SysTick.h"
uint32_t SysTick_Now = 0;



/**
 * @brief ���ò�����ϵͳ�δ�ʱ��(SysTick)
 *
 * ����������SysTick��ʱ�����Բ�����ʱ�жϣ�֧��ϵͳ�δ��ʱ���ӳٹ��ܡ�
 * SysTick��ʱ������Ϊʹ��AHBʱ��Դ�����õδ�����Ϊ1ms���������˶�ʱ����
*/
void Com_SysTick_Init() {
    // 1.����ʱ��ԴΪAHB 72MHz
    SysTick->CTRL |= SysTick_CTRL_CLKSOURCE;

    // 2.������װ��ֵ  72MHz = 72 000 000Hz  LoAD���Ϊ24M�����Բ���ֱ����1s����
    // ����1ms����һ��  72MHz/1000 - 1(�������һλ)   0 �� 71999���ܹ� 72000 ������ֵ
    SysTick->LOAD = 72000 - 1;

    // 3.�����ж� ���ȼ�Ĭ��15
    SysTick->CTRL |= SysTick_CTRL_TICKINT;

    // 4.��ʹ��
    SysTick->CTRL |= SysTick_CTRL_ENABLE;
}


/**
 * @brief ��ȡ��ǰϵͳ�δ���
 *
 * �˺������ڻ�ȡ��ǰϵͳ�ĵδ������Ա������ϵͳ����������ʱ�䣨�Եδ�Ϊ��λ����
 *
 * @return uint32_t ���ص�ǰ��ϵͳ�δ���
*/
static uint32_t SysTick_GetTick(void) {
    return SysTick_Now;
}


/**
 * @brief ��ʱ������ʹ��SysTick��ʱ��ʵ����ʱ
 *
 * �ú�����Ҫ�����ڳ�����ʵ��һ��ʱ�����ʱ����ʱ����صĲ����зǳ�����
 *
 * @param Delay ��ʱ�ĵ�λ�ǵδ�����ticks������ʱ�ľ�ȷʱ��ȡ����ϵͳ��ʱ��Ƶ��
*/
void SysTick_Delay(uint32_t Delay)
{
    // ��ȡ��ǰ�ĵδ�����Ϊ��ʼ��ʱ�Ĳο���
    uint32_t tickstart = SysTick_GetTick();
    // �������Delay����wait����ʾ��Ҫ��ʱ�ĵδ���
    uint32_t wait = Delay;
    // ��Ϊ��ʱ�ļ��㷽ʽ�Ǵ�0��ʼ�ۼӣ�������Ҫ��������һ���δ�����ȷ����ʱ��׼ȷ��
    wait += 1;

    // ѭ��ֱ��������ʱ��ﵽ�򳬹��������ʱʱ��
    while ((SysTick_GetTick() - tickstart) < wait);
}





/**
 * @brief SysTick�жϷ�������
 *
 * ÿ��SysTick��ʱ�������ж�ʱ���˺����ᱻ���á�
 * ������Ҫ�����ǵ���SysTick_Now����������ϵͳʱ��ļ�����
*/
void SysTick_Handler(void)
{
    // ����SysTick_Now��������ʾʱ���н�չ
    SysTick_Now++;
}
