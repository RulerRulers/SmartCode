#ifndef UART_H
#define UART_H

extern unsigned char xdata Receive_Data[100];//��������
extern unsigned char uart_len;//���ڽ����ֽ�����
extern unsigned char receive_ok;//������ɱ�־λ

void UartInit(void);		//115200bps@11.0592MHz
void UART1_SendOneByte(unsigned char c);
void Is_Receive_Ok(unsigned char *len);


#endif



