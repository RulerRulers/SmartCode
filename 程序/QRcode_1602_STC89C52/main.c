#include "reg52.h"
#include "stdio.h"
#include "uart.h"
#include "intrins.h"
#include "delay.h"
#include "lcd1602.h"

sbit LED = P1^0;//LED
sbit Voice = P1^1;
sbit BEEP = P3^6 ;   //蜂鸣器
unsigned char  rxlengh = 0; 
unsigned char  Count1,Count2,flag;
void Timer0_init();

void main()
{
	 unsigned char i = 0;
   UartInit();//115200
	 init_1602();//初始化LCD1602
	 Timer0_init();
	 write_string(0,0,"QR code:",8);
	 while(1)
	 {
     Is_Receive_Ok(&rxlengh);//判断串口是否接收完成
		 if(rxlengh !=0)
		 {
			 if(rxlengh <= 20) 
			 {
			   write_string(0,1,Receive_Data,16);//在屏幕上显示解码后的数据
				 Voice = 0; 
				 delay_us(10);
				 Voice = 1; 	
			 }				 
			 else
			 {  				 
				 write_string(0,1,"QRcode too large",16);//码太长 无法显示
			 }
			 TR0 = 1;
			 delay_ms(30);
			 TR0 = 0;       		 
			 receive_ok = 0;
			 uart_len = 0;//标志位清0 开启下一次接收
     }
		 LED = !LED; //LED闪烁 表示系统正在运行
		 
   }
}

void Timer0_init()
{
   TMOD=0x01; 
   TH0=0xfc; 
   TL0=0x66;      //1ms定时 
   EA=1; 
   ET0=1; 
}


/*********************************************************
  Time0中断函数
**********************************************************/
void Time0(void) interrupt 1 using 0
{
   TH0=0xfc;               //1ms定时
   TL0=0x66;
   BEEP=~BEEP;  	 
}
