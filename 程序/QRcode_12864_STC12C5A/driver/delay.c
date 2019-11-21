#include "reg52.h"
#include "delay.h"
#include "intrins.h"

sbit BEEP = P3^6;

void Delay1ms()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	i = 2;
	j = 199;
	do
	{
		while (--j);
	} while (--i);
}

void delay_us(nus)//us 延时 不是很准确
{
  while(nus--)
	{
			_nop_();
  }
}


void delay_ms(unsigned int ums)
{
  while(ums--)
	{
     Delay1ms();
  }

}

void Beep()
{
  BEEP = 0;
	delay_ms(20);
	BEEP = 1;
}
