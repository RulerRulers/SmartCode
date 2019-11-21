#include "reg52.h"
#include "stdio.h"
#include "intrins.h"
#include "delay.h"
#include "lcd1602.h"

sbit lcdrs  = P0^7;	//液晶引脚定义
sbit led_cs = P0^6;
sbit lcden  = P0^5;

/*延时函数*/
void delay(unsigned int xms)
{
	unsigned int i,j; 
	for(i=xms;i>0;i--)
	for(j=110;j>0;j--);
}
/*1602液晶*/
void write_com(unsigned char com)//写命令
{
	lcdrs=0;
	lcden=0;
	P2=com;
	delay(5);
	lcden=1;
	delay(5);
	lcden=0;
}
void write_data(unsigned char date)//写数据
{
	lcdrs=1;
	lcden=0;
	P2=date;
	delay(5);
	lcden=1;
	delay(5);
	lcden=0;
}
void write_by_xy(unsigned char x,unsigned char y)//坐标定位
{
	unsigned char address;
	if(y==0) 
	address=0x80+x;//y=0,写第一行
	else 
	address=0xc0+x;//y=1,写第二行
	write_com(address); 
}
/*void write_char(unsigned char x,unsigned char y,unsigned char date)//坐标定位显示
{
	write_by_xy(x,y);//先定位 
	write_data(date);//后写数
}*/

void write_string(unsigned char x,unsigned char y,unsigned char *s,unsigned char len)//写字符串
{
	write_by_xy(x,y);//设定显示位置 
	while(len--)//write character
	{
			P2=*s;
			write_data(*s); 
			s++;
	}
}

void init_1602()//初始化
{
	led_cs=0;
	write_com(0x38);
	write_com(0x0c);
	write_com(0x06);
	write_com(0x01);
}