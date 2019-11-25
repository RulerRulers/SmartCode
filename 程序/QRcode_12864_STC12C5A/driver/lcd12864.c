#include "lcd12864.h"
#include "intrins.h"
#include "stdio.h"

void delay(unsigned int t)
{
	unsigned int i;
	while(t--)
		for(i=0;i<110;i++);
}
 
bit busy()  //查忙
{
	bit result;
	LCD_DAT=0X00; 
	RS=0;			//命令/数据选择,为0时选择命令    
	RW=1;			//读/写选择，为1时选择读
	E=1;			//使能
	delay(1);
	result = (bit)(LCD_DAT&0x80); //查忙标志位，等待标志位为0，即表示写入完毕
	E=0;			//关闭读写 
	return (result);
}
 
void wcode(unsigned char cmd)   //向lcd写一命令
{
	while(busy());  					 //查忙
	RS=0;							 //命令/数据选择,为0时选择命令 
	RW=0;							 //读/写选择，为0时选择写
	E=0;
	_nop_();
  _nop_(); 
	LCD_DAT=cmd;				 //送入命令
	delay(1);				//等待
	E=1;							
	delay(1);
	E=0;
}
 
void wdata(unsigned char dat) 	//向LCD写一数据
{
	while(busy());
	RS=1;            //H为数据
	RW=0;
	E=0;
	LCD_DAT=dat;
	delay(1);
	E=1;
	delay(1);
	E=0;
}
 
void LCD12864_init()    //LCD初始化
{
	PSB=1;     //设置为8BIT并口工作模式  H并行 L串行
	delay(10);
	wcode(0x34);
	delay(5);
	wcode(0x30);  //选择基本指令集
	delay(5);
	wcode(0x0c);  //开显示，无游标
	delay(5);
	wcode(0x01);	//清除显示，并且设定地址指针为00H
	delay(5);
	wcode(0x06);	//指定在资料的读取及写入时，设定游标的移动方向及指定显示的移位
	
}

void Lcd_Clear(unsigned char mode)//LCD 清屏 mode=0 字符模式下清屏  mpode=1 绘图模式下清屏
{
   if(mode==0)
	 {
      //wcode(0x01);	//清除显示，并且设定地址指针为00H
		  LCD12864_init();
   }
}
 
void LcdShow_string(unsigned char x,unsigned char y,unsigned char  *s)  //任意位置显示字符串
{                         //x为横坐标，y位纵坐标，*s表示指针，为数据的首地址
	switch(y)    						//选择纵坐标
	{
		case 0:wcode(0x80+x);break;  //第一行
		case 1:wcode(0x90+x);break;	 //第二行
		case 2:wcode(0x88+x);break;  //第三行
		case 3:wcode(0x98+x);break;  //第四行
		default:break;
	}
	while(*s>0)										 //写入数据，直到数据为空
	{
		wdata(*s);									 //写数据
		delay(10);									//下一字符
		s++;
	}
}  
void LcdShow_number(unsigned char x,unsigned char y, unsigned int n)  //lcd显示一个数字
{
	char s[6];
	sprintf(s,"%d",n);
	LcdShow_string(x,y,s);	
}
