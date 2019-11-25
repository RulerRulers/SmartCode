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

unsigned char  rxlengh = 0;//串口接收数据长度
unsigned char flag_waitPay = 0;//等待支付才可以按键操作
unsigned char keyValue = 0;//键值

//语音播放控制脚
sbit Voice = P1^1;
void Voice_player(void);

void main()
{
	 unsigned char i = 0;
	 USART2_Init();//串口2 115200 二维码模块串口
	 Timer0Init();//定时器初始化
	 LCD12864_init();//LCD12864 初始化
	 LcdDiplay_MainWindow();
 
	 while(1)
	 {
     Is_Receive_Ok(&rxlengh);//判断串口是否接收完成
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
       flag_waitPay = 1;//进入等待支付状态			 
			 receive_ok = 0;
			 memset(Receive_Data,0,sizeof(Receive_Data));
			 uart_len = 0;//标志位清0 开启下一次接收
     }
		 keyValue = GetKey();
		 if(keyValue == 1 && flag_waitPay==1)//支付键按下 S4
		 {
         LcdDiplay_PayWindow();
			   flag_waitPay = 0;
			   keyValue = 0;
     }
		 else if(keyValue == 4 && flag_waitPay==1)//取消支付键按下  s1
		 {
         LcdDiplay_CancelWindow();//取消支付
			   flag_waitPay = 0;
			   keyValue = 0;
     }
   }
}


//语音播放
void Voice_player()
{
	 Voice = 0; 
	 delay_us(10);
	 Voice = 1; 
}
