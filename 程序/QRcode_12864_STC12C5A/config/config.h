/*
*�ļ�����config.h
*��Ȩ��Copyright 2019 All Rights Reserved.
*���������������ļ�  
*�޸��ˣ�xie ze xiong
*�޸�ʱ�䣺2019-11-23
*�޸����ݣ�����
*/
#ifndef _CONFIG_H
#define _CONFIG_H

/****************ϵͳ����*****************/
#define MCU_STC12CXX    //оƬϵ��  STC89CXX 
#define FOSC 11059200L  //��ʱ��

#ifdef MCU_STC12CXX
#include <STC12C5A60S2.H>
#elif MCU_STC89CXX
#include <Reg52.H>
#else 
#error ��ָ��һ��MCUϵ��
#endif


/****************��������*****************/
//#define USE_UART1
#define BAUD1  115200 

#ifdef MCU_STC12CXX
#define USE_UART2    //����2 TxD=P1.3   RxD=P1.2 
#define BAUD2  115200
#endif

/****************��ʱ������*****************/
/*1Tģʽ�����ʱ5ms  12Tģʽ�����ʱ65ms*/ 

//#define MODE1T    //��ʱ��1T ���� 12Tģʽ
#define T_MS   10  //��ʱʱ�� ms  

#ifdef MODE1T
#define timer0_init_val (65536-FOSC/(1000/T_MS))  //1ms timer calculation method in 1T mode
#else
#define timer0_init_val (65536-FOSC/12/(1000/T_MS))   //1ms timer calculation method in 12T mode
#endif










#endif





