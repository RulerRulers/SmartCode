#include "config.h"
#include "lcd12864.h"
#include "QRcoder.h"
#include "stdio.h"
#include "string.h"
#include "uart.h"
#include "delay.h"


	
//��Ʒ��Ϣ
ProductDef code productInfo[]=
{
  {"8641983220190001","�����",3},
  {"8641983220190002","���",3},
  {"8641983220190003","ֽ��",1},
  {"8641983220190004","��ˢ",5},
  {"8641983220190005","ϴ��ˮ",15}, 
};

void LcdDiplay_MainWindow()
{
  Lcd_Clear(0);	//�����ʾ�������趨��ַָ��Ϊ00H
  LcdShow_string(0,0,"====��ӭʹ��====");
	LcdShow_string(1,1,"����ɨ���豸");
	LcdShow_string(0,2,"----��ɨ��----");
	LcdShow_string(0,3,"Design  By  XXX");
}

//��ʾ��Ʒ��Ϣ
void LcdDispy_productInfo(ProductDef* proInfo)
{
	unsigned char dest[12];
	Lcd_Clear(0);	//�����ʾ�������趨��ַָ��Ϊ00H
	strncpy(dest,proInfo->QR,12);
	LcdShow_string(0,0,"QR:");
	LcdShow_string(2,0,dest);//��һ����ʾ��ά��
	
	LcdShow_string(0,1,"Ʒ��:");
	LcdShow_string(3,1,proInfo->name);//�ڶ�����ʾ��Ʒ����
	
	LcdShow_string(0,2,"�۸�:");
	LcdShow_number(3,2,proInfo->price);//��������ʾ��Ʒ�۸�
	LcdShow_string(5,2,"Ԫ");
	
	LcdShow_string(0,3,"----��֧��----");
}

void LcdDiplay_PayWindow()
{
   Lcd_Clear(0);	//�����ʾ
   LcdShow_string(2,1,"֧���ɹ���");//�ڶ�����ʾ��Ʒ����
   LcdShow_string(0,3,"3 ����Զ�����");//�ڶ�����ʾ��Ʒ����
	 delay_ms(3000);
   LcdDiplay_MainWindow();
}

void LcdDiplay_CancelWindow()
{
   Lcd_Clear(0);	//�����ʾ
   LcdShow_string(2,1,"ȡ��֧��");//�ڶ�����ʾ��Ʒ����
   LcdShow_string(0,3,"2 ����Զ�����");//�ڶ�����ʾ��Ʒ����
	 delay_ms(2000);
   LcdDiplay_MainWindow();
}
