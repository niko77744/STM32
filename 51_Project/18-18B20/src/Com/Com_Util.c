#include "Com_Util.h"

// ��ʱ�����Ķ���
void Delay_1ms(u16 ms)
{
	unsigned char data i, j;

	// ѭ�� ms ��
	for (; ms > 0; ms--)
	{

		_nop_();
		i = 2;
		j = 199;
		do
		{
			while (--j)
				;
		} while (--i);
	}
}

// ��ʱ10΢��
void Delay10us(void)	//@11.0592MHz
{
	unsigned char data i;

	i = 2;
	while (--i);
}

// ��ʱ50΢��
void Delay50us(void)	//@11.0592MHz
{
	unsigned char data i;

	_nop_();
	i = 20;
	while (--i);
}

// ��ʱ60΢��
void Delay60us(void)	//@11.0592MHz
{
	unsigned char data i;

	i = 25;
	while (--i);
}

// ��ʱ480΢��
void Delay480us(void)	//@11.0592MHz
{
	unsigned char data i;

	_nop_();
	i = 218;
	while (--i);
}
