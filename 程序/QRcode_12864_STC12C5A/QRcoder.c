#include "config.h"
#include "lcd12864.h"
#include "QRcoder.h"
#include "stdio.h"
#include "string.h"
#include "uart.h"
#include "delay.h"


	
//商品信息
ProductDef code productInfo[]=
{
  {"8641983220190001","冰红茶",3},
  {"8641983220190002","面包",3},
  {"8641983220190003","纸巾",1},
  {"8641983220190004","牙刷",5},
  {"8641983220190005","洗发水",15}, 
};

void LcdDiplay_MainWindow()
{
  Lcd_Clear(0);	//清除显示，并且设定地址指针为00H
  LcdShow_string(0,0,"====欢迎使用====");
	LcdShow_string(1,1,"智能扫码设备");
	LcdShow_string(0,2,"----请扫码----");
	LcdShow_string(0,3,"Design  By  XXX");
}

//显示商品信息
void LcdDispy_productInfo(ProductDef* proInfo)
{
	unsigned char dest[12];
	Lcd_Clear(0);	//清除显示，并且设定地址指针为00H
	strncpy(dest,proInfo->QR,12);
	LcdShow_string(0,0,"QR:");
	LcdShow_string(2,0,dest);//第一行显示二维码
	
	LcdShow_string(0,1,"品名:");
	LcdShow_string(3,1,proInfo->name);//第二行显示商品名称
	
	LcdShow_string(0,2,"价格:");
	LcdShow_number(3,2,proInfo->price);//第三行显示商品价格
	LcdShow_string(5,2,"元");
	
	LcdShow_string(0,3,"----请支付----");
}

void LcdDiplay_PayWindow()
{
   Lcd_Clear(0);	//清除显示
   LcdShow_string(2,1,"支付成功！");//第二行显示商品名称
   LcdShow_string(0,3,"3 秒后自动返回");//第二行显示商品名称
	 delay_ms(3000);
   LcdDiplay_MainWindow();
}

void LcdDiplay_CancelWindow()
{
   Lcd_Clear(0);	//清除显示
   LcdShow_string(2,1,"取消支付");//第二行显示商品名称
   LcdShow_string(0,3,"2 秒后自动返回");//第二行显示商品名称
	 delay_ms(2000);
   LcdDiplay_MainWindow();
}
