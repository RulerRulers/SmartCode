#ifndef __LCD12864_H
#define __LCD12864_H
#include <STC12C5A60S2.H>

sbit RS  =  P0^7;     //����/����ѡ��       
sbit RW  =  P0^6;     //��д�� 
sbit E  =   P0^5;      //ʹ�ܶ�       
sbit PSB =  P0^4;     //����ѡ��  
sbit RST =  P0^3;		 //��λ��
#define LCD_DAT  P2

void LCD12864_init(void);//LCD��ʼ��
void Lcd_Clear(unsigned char mode);//LCD ���� mode=0 �ַ�ģʽ������  mpode=1 ��ͼģʽ������
void LcdShow_string(unsigned char x,unsigned char y,unsigned char *s);  //����λ����ʾ�ַ���
void LcdShow_number(unsigned char x,unsigned char y, unsigned int n);  //lcd��ʾһ������

#endif
