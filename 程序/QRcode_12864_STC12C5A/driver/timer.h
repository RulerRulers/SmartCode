#ifndef _TIMER_H
#define _TIMER_H

extern unsigned char get_adc_ok;//ADC采集完成标志位
extern unsigned char bits;//

extern unsigned char adc_result,adc_result1;

extern unsigned char T_500ms;//驼背持续时间计数器
extern unsigned char tuobei_switch;//驼背继续时间计数开关

extern unsigned char zuowai_count ;//坐歪时间计数器
extern unsigned char zuowai_switch;//坐歪判定开关打开


extern unsigned char T_500ms_flag;//久坐持续时间计数器

void Timer0Init(void);		//50毫秒@12.000MHz



#endif

