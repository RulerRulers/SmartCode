#ifndef _QRCODER_H
#define _QRCODER_H

typedef struct Product
{
  unsigned char QR[16];
	unsigned char name[8];
	unsigned char price;
}ProductDef;

extern ProductDef code productInfo[];

void LcdDiplay_MainWindow(void);//显示主界面
void LcdDispy_productInfo(ProductDef* proInfo);
void LcdDiplay_PayWindow(void);
void LcdDiplay_CancelWindow(void);

#endif

