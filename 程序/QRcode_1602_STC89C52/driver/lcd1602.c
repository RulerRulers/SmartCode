#include "reg52.h"
#include "stdio.h"
#include "intrins.h"
#include "delay.h"
#include "lcd1602.h"

sbit lcdrs  = P0^7;	//Һ�����Ŷ���
sbit led_cs = P0^6;
sbit lcden  = P0^5;

/*��ʱ����*/
void delay(unsigned int xms)
{
	unsigned int i,j; 
	for(i=xms;i>0;i--)
	for(j=110;j>0;j--);
}
/*1602Һ��*/
void write_com(unsigned char com)//д����
{
	lcdrs=0;
	lcden=0;
	P2=com;
	delay(5);
	lcden=1;
	delay(5);
	lcden=0;
}
void write_data(unsigned char date)//д����
{
	lcdrs=1;
	lcden=0;
	P2=date;
	delay(5);
	lcden=1;
	delay(5);
	lcden=0;
}
void write_by_xy(unsigned char x,unsigned char y)//���궨λ
{
	unsigned char address;
	if(y==0) 
	address=0x80+x;//y=0,д��һ��
	else 
	address=0xc0+x;//y=1,д�ڶ���
	write_com(address); 
}
/*void write_char(unsigned char x,unsigned char y,unsigned char date)//���궨λ��ʾ
{
	write_by_xy(x,y);//�ȶ�λ 
	write_data(date);//��д��
}*/

void write_string(unsigned char x,unsigned char y,unsigned char *s,unsigned char len)//д�ַ���
{
	write_by_xy(x,y);//�趨��ʾλ�� 
	while(len--)//write character
	{
			P2=*s;
			write_data(*s); 
			s++;
	}
}

void init_1602()//��ʼ��
{
	led_cs=0;
	write_com(0x38);
	write_com(0x0c);
	write_com(0x06);
	write_com(0x01);
}