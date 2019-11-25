#ifndef UART_H
#define UART_H

#define FOSC 11059200L      //System frequency
#define BAUD1 115200         //UART baudrate

#ifdef USE_UART2
#define BAUD2 115200
#endif


extern unsigned char xdata Receive_Data[30];//��������
extern unsigned char uart_len;//���ڽ����ֽ�����
extern unsigned char receive_ok;//������ɱ�־λ

void USART1_Init(void);		//115200bps@11.0592MHz
void USART2_Init(void);//����2��ʼ�� 115200bps 
void UART2_SendOneByte(unsigned char c);
void Is_Receive_Ok(unsigned char *len);


#endif



