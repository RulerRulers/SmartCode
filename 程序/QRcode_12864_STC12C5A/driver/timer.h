#ifndef _TIMER_H
#define _TIMER_H

extern unsigned char get_adc_ok;//ADC�ɼ���ɱ�־λ
extern unsigned char bits;//

extern unsigned char adc_result,adc_result1;

extern unsigned char T_500ms;//�ձ�����ʱ�������
extern unsigned char tuobei_switch;//�ձ�����ʱ���������

extern unsigned char zuowai_count ;//����ʱ�������
extern unsigned char zuowai_switch;//�����ж����ش�


extern unsigned char T_500ms_flag;//��������ʱ�������

void Timer0Init(void);		//50����@12.000MHz



#endif

