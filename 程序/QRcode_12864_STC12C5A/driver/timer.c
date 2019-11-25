#include "config.h"
#include "intrins.h"
#include "timer.h"
#include "stdio.h"
#include "key.h"

unsigned int count = 0;//定时计数器
sbit LED1 = P1^0;

void Timer0Init(void)	
{
	#ifdef MODE1T
    AUXR |= 0x80;                    //timer0 work in 1T mode
  #endif
    TMOD |= 0x01;                    //set timer0 as mode1 (16-bit)
    TL0 = timer0_init_val;          //initial timer0 low byte
    TH0 = timer0_init_val >> 8;     //initial timer0 high byte
    TR0 = 1;                        //timer0 start running
    ET0 = 1;                        //enable timer0 interrupt
    EA = 1;                         //open global interrupt switch
}

void tm0_isr() interrupt 1
{  
    TL0 = timer0_init_val;          //initial timer0 low byte
    TH0 = timer0_init_val >> 8;     //initial timer0 high byte
	  count++;
	  //ReadKeyStatus();  
	  if(count == 20)//1s
		{
        count =0;
			  //printf("timer 1s \r\n");
			  //LED1 =!LED1;
    }
}



