#include "config.h"
#include "delay.h"
#include "uart.h"
#include "stdio.h"

#define S2RI  0x01          //S2CON.0
#define S2TI  0x02          //S2CON.1

unsigned char xdata Receive_Data[30];//��������
unsigned char uart_len = 0;//���ڽ����ֽ�����
unsigned char receive_ok = 0;//������ɱ�־λ

#ifdef USE_UART1
 void USART1_Init()//����1��ʼ�� 115200bps ���Դ���
{
	PCON &= 0x7F;		//�����ʲ�����
	SCON |= 0x50;		//8λ����,�ɱ䲨����
	AUXR |= 0x40;		//��ʱ��1ʱ��ΪFosc,��1T
	AUXR &= 0xFE;		//����1ѡ��ʱ��1Ϊ�����ʷ�����
	TMOD |= 0x20;		//�趨��ʱ��1Ϊ8λ�Զ���װ��ʽ        
  TH1 = TL1 = -(FOSC/32/BAUD1); //Set auto-reload vaule
  TR1 = 1;   //Timer1 start run	
	ET1 = 0;		//��ֹ��ʱ��1�ж�
	TR1 = 1;		//������ʱ��1
	
	TI = 1;       //�����жϱ��λ���������� ��������Ϊ��ʹ��printf���� �����ʹ��printf���� �����ȥ��
	EA = 1;				//�����ж�
	//ES = 1;				//�������ж�
	//EA��ES��1�����д��ڽ��ջ��߷��ͣ������ִ�д����жϷ������void USART_Interrupt(void)  interrupt 4	 
}	  


char putchar (char c) //printf�����ض���
{
  while (!TI);
  TI = 0;
  return (SBUF = c);
}
#endif

/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////����2��ʼ������/////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
#ifdef USE_UART2
void USART2_Init()//����2��ʼ�� 115200bps 
{
	  S2CON |= 0x50;           //8-bit variable UART
    BRT = -(FOSC/32/BAUD2);  //Set auto-reload vaule of baudrate generator
    AUXR |= 0x14;            //Baudrate generator work in 1T mode
    IE2 = 0x01;             //Enable UART2 interrupt
    EA = 1;                 //Open master interrupt switch
}	 
/*********************************************************************************************************
** �������� ������һ���ַ�
** ��ڲ��� ��d�������͵��ַ�
** ���ڲ��� ����
*********************************************************************************************************/
// void UART2_SendOneByte(unsigned char d)
// {
// 	S2BUF = d;
// 	while(!(S2CON&S2TI));	//��������ɣ���TI�Զ���1��������ѭ����ִ�н����������
// 	S2CON&=~S2TI;		// �������,TI����������㣬�´η��͵�ʱ���Ӳ���ſ��Խ�����һ��Ϊ�жϷ�����ɵ�����
// }		
#endif
/*********************************************************************************************************
** �������� ������2�жϷ������
** ��ڲ��� ����
** ���ڲ��� ����
*********************************************************************************************************/
void USART2_Interrupt(void)  interrupt 8	 
{
   	if(S2CON&S2RI) 			//�����ж�RI(�����жϱ�־)�Ƿ�Ϊ1
    {
    	S2CON&=~S2RI;
			
			if((uart_len<30) && (receive_ok==0))
			{
         Receive_Data[uart_len++]=S2BUF;//���մ�������
      }		
    }
}

//�жϴ����Ƿ������һ֡����
void Is_Receive_Ok(unsigned char *len)
{
	unsigned char rxlen=uart_len;
	unsigned char i=0;
	*len=0;				//Ĭ��Ϊ0
	 delay_ms(10);		//�ȴ�10ms,��������10msû�н��յ�һ������,����Ϊ���ս��� 
	if(rxlen==uart_len&&rxlen)//���յ�������,�ҽ��������
	{
		*len=uart_len;	//��¼�������ݳ���
		uart_len=0;		  //����
		receive_ok = 1;//������� 
	}
}

