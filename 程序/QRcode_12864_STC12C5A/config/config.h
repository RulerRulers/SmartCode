/*
*文件名：config.h
*版权：Copyright 2019 All Rights Reserved.
*描述：顶层配置文件  
*修改人：xie ze xiong
*修改时间：2019-11-23
*修改内容：新增
*/
#ifndef _CONFIG_H
#define _CONFIG_H

/****************系统配置*****************/
#define MCU_STC12CXX    //芯片系列  STC89CXX 
#define FOSC 11059200L  //主时钟

#ifdef MCU_STC12CXX
#include <STC12C5A60S2.H>
#elif MCU_STC89CXX
#include <Reg52.H>
#else 
#error 请指定一个MCU系列
#endif


/****************串口配置*****************/
//#define USE_UART1
#define BAUD1  115200 

#ifdef MCU_STC12CXX
#define USE_UART2    //串口2 TxD=P1.3   RxD=P1.2 
#define BAUD2  115200
#endif

/****************定时器配置*****************/
/*1T模式下最大定时5ms  12T模式下最大定时65ms*/ 

//#define MODE1T    //定时器1T 或者 12T模式
#define T_MS   10  //定时时间 ms  

#ifdef MODE1T
#define timer0_init_val (65536-FOSC/(1000/T_MS))  //1ms timer calculation method in 1T mode
#else
#define timer0_init_val (65536-FOSC/12/(1000/T_MS))   //1ms timer calculation method in 12T mode
#endif










#endif





