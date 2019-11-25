#include "config.h"
#include "delay.h"
#include "uart.h"
#include "stdio.h"

#define S2RI  0x01          //S2CON.0
#define S2TI  0x02          //S2CON.1

unsigned char xdata Receive_Data[30];//缓冲数组
unsigned char uart_len = 0;//串口接收字节数量
unsigned char receive_ok = 0;//接受完成标志位

#ifdef USE_UART1
 void USART1_Init()//串口1初始化 115200bps 调试串口
{
	PCON &= 0x7F;		//波特率不倍速
	SCON |= 0x50;		//8位数据,可变波特率
	AUXR |= 0x40;		//定时器1时钟为Fosc,即1T
	AUXR &= 0xFE;		//串口1选择定时器1为波特率发生器
	TMOD |= 0x20;		//设定定时器1为8位自动重装方式        
  TH1 = TL1 = -(FOSC/32/BAUD1); //Set auto-reload vaule
  TR1 = 1;   //Timer1 start run	
	ET1 = 0;		//禁止定时器1中断
	TR1 = 1;		//启动定时器1
	
	TI = 1;       //发送中断标记位，必须设置 这两句是为了使用printf函数 如果不使用printf函数 则可以去掉
	EA = 1;				//开总中断
	//ES = 1;				//开串行中断
	//EA、ES置1后，若有串口接收或者发送，则进入执行串口中断服务程序void USART_Interrupt(void)  interrupt 4	 
}	  


char putchar (char c) //printf函数重定向
{
  while (!TI);
  TI = 0;
  return (SBUF = c);
}
#endif

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////串口2初始化函数/////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
#ifdef USE_UART2
void USART2_Init()//串口2初始化 115200bps 
{
	  S2CON |= 0x50;           //8-bit variable UART
    BRT = -(FOSC/32/BAUD2);  //Set auto-reload vaule of baudrate generator
    AUXR |= 0x14;            //Baudrate generator work in 1T mode
    IE2 = 0x01;             //Enable UART2 interrupt
    EA = 1;                 //Open master interrupt switch
}	 
/*********************************************************************************************************
** 函数功能 ：发送一个字符
** 入口参数 ：d：待发送的字符
** 出口参数 ：无
*********************************************************************************************************/
// void UART2_SendOneByte(unsigned char d)
// {
// 	S2BUF = d;
// 	while(!(S2CON&S2TI));	//若发送完成，则TI自动置1，则跳出循环，执行接下来的语句
// 	S2CON&=~S2TI;		// 发送完成,TI必须软件置零，下次发送的时候才硬件才可以将它置一作为判断发送完成的依据
// }		
#endif
/*********************************************************************************************************
** 函数功能 ：串口2中断服务程序
** 入口参数 ：无
** 出口参数 ：无
*********************************************************************************************************/
void USART2_Interrupt(void)  interrupt 8	 
{
   	if(S2CON&S2RI) 			//必须判断RI(接收中断标志)是否为1
    {
    	S2CON&=~S2RI;
			
			if((uart_len<30) && (receive_ok==0))
			{
         Receive_Data[uart_len++]=S2BUF;//接收串口数据
      }		
    }
}

//判断串口是否接收完一帧数据
void Is_Receive_Ok(unsigned char *len)
{
	unsigned char rxlen=uart_len;
	unsigned char i=0;
	*len=0;				//默认为0
	 delay_ms(10);		//等待10ms,连续超过10ms没有接收到一个数据,则认为接收结束 
	if(rxlen==uart_len&&rxlen)//接收到了数据,且接收完成了
	{
		*len=uart_len;	//记录本次数据长度
		uart_len=0;		  //清零
		receive_ok = 1;//接收完成 
	}
}

