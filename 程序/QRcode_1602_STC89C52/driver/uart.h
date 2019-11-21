#ifndef UART_H
#define UART_H

extern unsigned char xdata Receive_Data[100];//缓冲数组
extern unsigned char uart_len;//串口接收字节数量
extern unsigned char receive_ok;//接受完成标志位

void UartInit(void);		//115200bps@11.0592MHz
void UART1_SendOneByte(unsigned char c);
void Is_Receive_Ok(unsigned char *len);


#endif



