#include "Com_Util.h"

// 延时函数的定义
void Delay_1ms(u16 ms)
{
	unsigned char data i, j;

	// 循环 ms 次
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

// 延时10微秒
void Delay10us(void)	//@11.0592MHz
{
	unsigned char data i;

	i = 2;
	while (--i);
}

// 延时50微秒
void Delay50us(void)	//@11.0592MHz
{
	unsigned char data i;

	_nop_();
	i = 20;
	while (--i);
}

// 延时60微秒
void Delay60us(void)	//@11.0592MHz
{
	unsigned char data i;

	i = 25;
	while (--i);
}

// 延时480微秒
void Delay480us(void)	//@11.0592MHz
{
	unsigned char data i;

	_nop_();
	i = 218;
	while (--i);
}
