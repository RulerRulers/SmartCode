#include "config.h"
#include "stdio.h"
#include "string.h"
#include "uart.h"
#include "intrins.h"
#include "delay.h"
#include "lcd12864.h"
#include "timer.h"
#include "QRcoder.h"
#include "key.h"

unsigned char  rxlengh = 0;//���ڽ������ݳ���
unsigned char flag_waitPay = 0;//�ȴ�֧���ſ��԰�������
unsigned char keyValue = 0;//��ֵ

//�������ſ��ƽ�
sbit Voice = P1^1;
void Voice_player(void);

void main()
{
	 unsigned char i = 0;
	 USART2_Init();//����2 115200 ��ά��ģ�鴮��
	 Timer0Init();//��ʱ����ʼ��
	 LCD12864_init();//LCD12864 ��ʼ��
	 LcdDiplay_MainWindow();
 
	 while(1)
	 {
     Is_Receive_Ok(&rxlengh);//�жϴ����Ƿ�������
		 if(rxlengh !=0)
		 {
			 if(strstr(Receive_Data,"0001")!=NULL)
			 {
          LcdDispy_productInfo(&productInfo[0]);
       }
			 else if(strstr(Receive_Data,"0002")!=NULL)
			 {
          LcdDispy_productInfo(&productInfo[1]);  
       }
			  else if(strstr(Receive_Data,"0003")!=NULL)
			 {
          LcdDispy_productInfo(&productInfo[2]);
       }
			 else if(strstr(Receive_Data,"0004")!=NULL)
			 {
          LcdDispy_productInfo(&productInfo[3]);
       }
			 else if(strstr(Receive_Data,"0005")!=NULL)
			 {
          LcdDispy_productInfo(&productInfo[4]);
       }
		
       Voice_player();	
       flag_waitPay = 1;//����ȴ�֧��״̬			 
			 receive_ok = 0;
			 memset(Receive_Data,0,sizeof(Receive_Data));
			 uart_len = 0;//��־λ��0 ������һ�ν���
     }
		 keyValue = GetKey();
		 if(keyValue == 1 && flag_waitPay==1)//֧�������� S4
		 {
         LcdDiplay_PayWindow();
			   flag_waitPay = 0;
			   keyValue = 0;
     }
		 else if(keyValue == 4 && flag_waitPay==1)//ȡ��֧��������  s1
		 {
         LcdDiplay_CancelWindow();//ȡ��֧��
			   flag_waitPay = 0;
			   keyValue = 0;
     }
   }
}


//��������
void Voice_player()
{
	 Voice = 0; 
	 delay_us(10);
	 Voice = 1; 
}
