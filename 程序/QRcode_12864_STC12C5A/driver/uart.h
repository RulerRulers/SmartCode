#ifndef UART_H
#define UART_H

#define FOSC 11059200L      //System frequency
#define BAUD1 115200         //UART baudrate

#ifdef USE_UART2
#define BAUD2 115200
#endif


extern unsigned char xdata Receive_Data[30];//缓冲数组
extern unsigned char uart_len;//串口接收字节数量
extern unsigned char receive_ok;//接受完成标志位

void USART1_Init(void);		//115200bps@11.0592MHz
void USART2_Init(void);//串口2初始化 115200bps 
void UART2_SendOneByte(unsigned char c);
void Is_Receive_Ok(unsigned char *len);


#endif



