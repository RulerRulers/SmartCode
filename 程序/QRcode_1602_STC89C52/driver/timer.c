#include <STC12C5A60S2.H>
#include "intrins.h"
#include "timer.h"
#include "stdio.h"
#include "adc.h"
#include "TOF10120.h"


unsigned char count = 0;//软件计数器
unsigned char get_adc_ok=0;//ADC采集完成标志位
unsigned char bits = 0;//
unsigned char adc_result,adc_result1;


unsigned char T_500ms = 0;//驼背持续时间计数器
unsigned char tuobei_switch= 0;//驼背继续时间计数开关

unsigned char T_500ms_flag =0;//久坐持续时间计数器
unsigned char jiuzuo_switch = 0;//久坐持续时间计数开关

unsigned char zuowai_count = 0;//坐歪时间计数器
unsigned char zuowai_switch=0;//坐歪判定开关打开

void Timer0Init(void)		//50毫秒@12.000MHz
{
	AUXR &= 0x7F;		//定时器时钟12T模式
	TMOD &= 0xF0;		//设置定时器模式
	TL0 = 0xB0;		//设置定时初值
	TH0 = 0x3C;		//设置定时初值
	TF0 = 0;		//清除TF0标志
	
	count = 0;
	ET0 = 1;
	EA = 1;//启动定时器中断
	TR0 = 1;//定时器0开始计时
}

void tm0_isr() interrupt 1
{  
	count++;
  if (count== 100) //50ms*10=500ms
  {
     count = 0;  //reset counter 
		
		 if(T_500ms_flag == 0)
		 T_500ms_flag = 1;//500ms 标志位
		
     if(tuobei_switch == 1)//驼背计数开关打开 需要累计驼背持续时间了
		 {
       T_500ms++;//500ms标志位
     } 	
		 if(zuowai_switch == 1)//坐歪计数开关打开
		 {
       zuowai_count++;
     }
		 if(bits < 5)
		 {      
			 //adc_result = GetADCResult(0);
       //adc_result1 = GetADCResult(1); 
			 //adcResult[bits++]= DistanDiffer(adc_result,adc_result1); //计算压力差值;
			 bits++;
     }
		 else
		 {
			 get_adc_ok = 1;
     }	 
  }
}



