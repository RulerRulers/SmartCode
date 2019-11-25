#include "lcd12864.h"
#include "intrins.h"
#include "stdio.h"

void delay(unsigned int t)
{
	unsigned int i;
	while(t--)
		for(i=0;i<110;i++);
}
 
bit busy()  //��æ
{
	bit result;
	LCD_DAT=0X00; 
	RS=0;			//����/����ѡ��,Ϊ0ʱѡ������    
	RW=1;			//��/дѡ��Ϊ1ʱѡ���
	E=1;			//ʹ��
	delay(1);
	result = (bit)(LCD_DAT&0x80); //��æ��־λ���ȴ���־λΪ0������ʾд�����
	E=0;			//�رն�д 
	return (result);
}
 
void wcode(unsigned char cmd)   //��lcdдһ����
{
	while(busy());  					 //��æ
	RS=0;							 //����/����ѡ��,Ϊ0ʱѡ������ 
	RW=0;							 //��/дѡ��Ϊ0ʱѡ��д
	E=0;
	_nop_();
  _nop_(); 
	LCD_DAT=cmd;				 //��������
	delay(1);				//�ȴ�
	E=1;							
	delay(1);
	E=0;
}
 
void wdata(unsigned char dat) 	//��LCDдһ����
{
	while(busy());
	RS=1;            //HΪ����
	RW=0;
	E=0;
	LCD_DAT=dat;
	delay(1);
	E=1;
	delay(1);
	E=0;
}
 
void LCD12864_init()    //LCD��ʼ��
{
	PSB=1;     //����Ϊ8BIT���ڹ���ģʽ  H���� L����
	delay(10);
	wcode(0x34);
	delay(5);
	wcode(0x30);  //ѡ�����ָ�
	delay(5);
	wcode(0x0c);  //����ʾ�����α�
	delay(5);
	wcode(0x01);	//�����ʾ�������趨��ַָ��Ϊ00H
	delay(5);
	wcode(0x06);	//ָ�������ϵĶ�ȡ��д��ʱ���趨�α���ƶ�����ָ����ʾ����λ
	
}

void Lcd_Clear(unsigned char mode)//LCD ���� mode=0 �ַ�ģʽ������  mpode=1 ��ͼģʽ������
{
   if(mode==0)
	 {
      //wcode(0x01);	//�����ʾ�������趨��ַָ��Ϊ00H
		  LCD12864_init();
   }
}
 
void LcdShow_string(unsigned char x,unsigned char y,unsigned char  *s)  //����λ����ʾ�ַ���
{                         //xΪ�����꣬yλ�����꣬*s��ʾָ�룬Ϊ���ݵ��׵�ַ
	switch(y)    						//ѡ��������
	{
		case 0:wcode(0x80+x);break;  //��һ��
		case 1:wcode(0x90+x);break;	 //�ڶ���
		case 2:wcode(0x88+x);break;  //������
		case 3:wcode(0x98+x);break;  //������
		default:break;
	}
	while(*s>0)										 //д�����ݣ�ֱ������Ϊ��
	{
		wdata(*s);									 //д����
		delay(10);									//��һ�ַ�
		s++;
	}
}  
void LcdShow_number(unsigned char x,unsigned char y, unsigned int n)  //lcd��ʾһ������
{
	char s[6];
	sprintf(s,"%d",n);
	LcdShow_string(x,y,s);	
}
