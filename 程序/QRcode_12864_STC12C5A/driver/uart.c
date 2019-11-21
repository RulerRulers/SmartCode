#include "reg52.h"
#include "delay.h"
#include "uart.h"
#include "stdio.h"

unsigned char xdata Receive_Data[100];//��������
unsigned char uart_len = 0;//���ڽ����ֽ�����
unsigned char receive_ok = 0;//������ɱ�־λ

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
	
	 ES = 1;			 //�����ж�ʹ��
	 TI = 1;			 //�����жϱ��λ���������� ��������Ϊ��ʹ��printf���� �����ʹ��printf���� �����ȥ��
	 EA = 1;    //�������ж�
}

/****************���п�1����****************/  
void UART1_SendOneByte(unsigned char c)  
{  
    SBUF = c;  
    while(!TI);    //��TI=0���ڴ˵ȴ�  
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

//�жϴ����Ƿ������һ֡����
void Is_Receive_Ok(unsigned char *len)
{
	unsigned char rxlen=uart_len;
	unsigned char i=0;
	*len=0;				//Ĭ��Ϊ0
	 delay_ms(1);		//�ȴ�10ms,��������10msû�н��յ�һ������,����Ϊ���ս��� 
	if(rxlen==uart_len&&rxlen)//���յ�������,�ҽ��������
	{
		*len=uart_len;	//��¼�������ݳ���
		uart_len=0;		  //����
		receive_ok = 1;//������� 
	}
}

void UART_Receive() interrupt 4
{
 if(RI==1)//RIΪ�����жϱ�־�������Ƿ��Ͳ������ж�
 {
  ES=0;     //�ش����ж�
  RI=0;//�����жϱ�־������� 
	if(receive_ok == 0)
	{
			if(uart_len>=50) 
			{
        ES=1;     //�������ж�	
        uart_len =0;	
	   		return;
			}				
			Receive_Data[uart_len++]=SBUF;//���������ݷ���Ԥ������ 
	}
	ES=1;     //�������ж�
 } 
}
