#include "reg52.h"
#include "stdio.h"
#include "uart.h"
#include "intrins.h"
#include "delay.h"
#include "lcd1602.h"

sbit LED = P1^0;//LED
sbit Voice = P1^1;
sbit BEEP = P3^6 ;   //������
unsigned char  rxlengh = 0; 
unsigned char  Count1,Count2,flag;
void Timer0_init();

void main()
{
	 unsigned char i = 0;
   UartInit();//115200
	 init_1602();//��ʼ��LCD1602
	 Timer0_init();
	 write_string(0,0,"QR code:",8);
	 while(1)
	 {
     Is_Receive_Ok(&rxlengh);//�жϴ����Ƿ�������
		 if(rxlengh !=0)
		 {
			 if(rxlengh <= 20) 
			 {
			   write_string(0,1,Receive_Data,16);//����Ļ����ʾ����������
				 Voice = 0; 
				 delay_us(10);
				 Voice = 1; 	
			 }				 
			 else
			 {  				 
				 write_string(0,1,"QRcode too large",16);//��̫�� �޷���ʾ
			 }
			 TR0 = 1;
			 delay_ms(30);
			 TR0 = 0;       		 
			 receive_ok = 0;
			 uart_len = 0;//��־λ��0 ������һ�ν���
     }
		 LED = !LED; //LED��˸ ��ʾϵͳ��������
		 
   }
}

void Timer0_init()
{
   TMOD=0x01; 
   TH0=0xfc; 
   TL0=0x66;      //1ms��ʱ 
   EA=1; 
   ET0=1; 
}


/*********************************************************
  Time0�жϺ���
**********************************************************/
void Time0(void) interrupt 1 using 0
{
   TH0=0xfc;               //1ms��ʱ
   TL0=0x66;
   BEEP=~BEEP;  	 
}
