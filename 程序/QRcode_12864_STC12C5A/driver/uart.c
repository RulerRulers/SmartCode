#include "reg52.h"
#include "delay.h"
#include "uart.h"
#include "stdio.h"

unsigned char xdata Receive_Data[100];//缓冲数组
unsigned char uart_len = 0;//串口接收字节数量
unsigned char receive_ok = 0;//接受完成标志位

void UartInit(void)		//115200bps@11.0592MHz
{
	 SCON=0x50;   
   TH2=0xFF;           
   TL2=0xFD;   
   RCAP2H=0xFF;   
   RCAP2L=0xFD; 

/*****************/
   TCLK=1;   
   RCLK=1;   
   C_T2=0;   
   EXEN2=0;

/*****************/
   TR2=1 ;
	
	 ES = 1;			 //串口中断使能
	 TI = 1;			 //发送中断标记位，必须设置 这两句是为了使用printf函数 如果不使用printf函数 则可以去掉
	 EA = 1;    //开放总中断
}

/****************串行口1发送****************/  
void UART1_SendOneByte(unsigned char c)  
{  
    SBUF = c;  
    while(!TI);    //若TI=0，在此等待  
    TI = 0;    
}  

/*
 * putchar (mini version): outputs charcter only
 */
char putchar (char c) 
{
  while (!TI);
  TI = 0;
  return (SBUF = c);
}

//判断串口是否接收完一帧数据
void Is_Receive_Ok(unsigned char *len)
{
	unsigned char rxlen=uart_len;
	unsigned char i=0;
	*len=0;				//默认为0
	 delay_ms(1);		//等待10ms,连续超过10ms没有接收到一个数据,则认为接收结束 
	if(rxlen==uart_len&&rxlen)//接收到了数据,且接收完成了
	{
		*len=uart_len;	//记录本次数据长度
		uart_len=0;		  //清零
		receive_ok = 1;//接收完成 
	}
}

void UART_Receive() interrupt 4
{
 if(RI==1)//RI为接受中断标志，可能是发送产生的中断
 {
  ES=0;     //关串口中断
  RI=0;//接受中断标志软件清零 
	if(receive_ok == 0)
	{
			if(uart_len>=50) 
			{
        ES=1;     //开串口中断	
        uart_len =0;	
	   		return;
			}				
			Receive_Data[uart_len++]=SBUF;//将接受数据放入预置数组 
	}
	ES=1;     //开串口中断
 } 
}
