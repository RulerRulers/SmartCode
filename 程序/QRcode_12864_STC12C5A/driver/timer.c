#include <STC12C5A60S2.H>
#include "intrins.h"
#include "timer.h"
#include "stdio.h"
#include "adc.h"
#include "TOF10120.h"


unsigned char count = 0;//���������
unsigned char get_adc_ok=0;//ADC�ɼ���ɱ�־λ
unsigned char bits = 0;//
unsigned char adc_result,adc_result1;


unsigned char T_500ms = 0;//�ձ�����ʱ�������
unsigned char tuobei_switch= 0;//�ձ�����ʱ���������

unsigned char T_500ms_flag =0;//��������ʱ�������
unsigned char jiuzuo_switch = 0;//��������ʱ���������

unsigned char zuowai_count = 0;//����ʱ�������
unsigned char zuowai_switch=0;//�����ж����ش�

void Timer0Init(void)		//50����@12.000MHz
{
	AUXR &= 0x7F;		//��ʱ��ʱ��12Tģʽ
	TMOD &= 0xF0;		//���ö�ʱ��ģʽ
	TL0 = 0xB0;		//���ö�ʱ��ֵ
	TH0 = 0x3C;		//���ö�ʱ��ֵ
	TF0 = 0;		//���TF0��־
	
	count = 0;
	ET0 = 1;
	EA = 1;//������ʱ���ж�
	TR0 = 1;//��ʱ��0��ʼ��ʱ
}

void tm0_isr() interrupt 1
{  
	count++;
  if (count== 100) //50ms*10=500ms
  {
     count = 0;  //reset counter 
		
		 if(T_500ms_flag == 0)
		 T_500ms_flag = 1;//500ms ��־λ
		
     if(tuobei_switch == 1)//�ձ��������ش� ��Ҫ�ۼ��ձ�����ʱ����
		 {
       T_500ms++;//500ms��־λ
     } 	
		 if(zuowai_switch == 1)//����������ش�
		 {
       zuowai_count++;
     }
		 if(bits < 5)
		 {      
			 //adc_result = GetADCResult(0);
       //adc_result1 = GetADCResult(1); 
			 //adcResult[bits++]= DistanDiffer(adc_result,adc_result1); //����ѹ����ֵ;
			 bits++;
     }
		 else
		 {
			 get_adc_ok = 1;
     }	 
  }
}



