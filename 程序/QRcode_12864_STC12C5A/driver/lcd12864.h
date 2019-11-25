#ifndef __LCD12864_H
#define __LCD12864_H
#include <STC12C5A60S2.H>

sbit RS  =  P0^7;     //命令/数据选择       
sbit RW  =  P0^6;     //读写口 
sbit E  =   P0^5;      //使能端       
sbit PSB =  P0^4;     //串并选择  
sbit RST =  P0^3;		 //复位端
#define LCD_DAT  P2

void LCD12864_init(void);//LCD初始化
void Lcd_Clear(unsigned char mode);//LCD 清屏 mode=0 字符模式下清屏  mpode=1 绘图模式下清屏
void LcdShow_string(unsigned char x,unsigned char y,unsigned char *s);  //任意位置显示字符串
void LcdShow_number(unsigned char x,unsigned char y, unsigned int n);  //lcd显示一个数字

#endif
