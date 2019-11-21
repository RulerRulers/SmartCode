#ifndef KEY_H
#define KEY_H

#define _KEY0 (P3&(1<<2))
#define _KEY1 (P3&(1<<3))
#define _KEY2 (P3&(1<<4))
#define _KEY3 (P3&(1<<5))

#define KEY_ENTER  1
#define LEFT 2
#define RIGHT 3
#define KEY_RETURN 4


typedef enum _KEY_STATUS_LIST
{
    KEY_NULL = 0x00,//无键按下
    KEY_SURE = 0x01,//确认态
    KEY_UP   = 0x02,//抬起
    KEY_DOWN = 0x04,//按下
}KEY_STATUS_LIST;

typedef enum _KEY_LIST
{
    KEY0=0,
    KEY1,
    KEY2,
	  KEY3,
    KEY_NUM,
}KEY_LIST;

typedef struct _KEY_COMPONENTS
{
    unsigned char KEY_SHIELD;       //按键屏蔽0:屏蔽，1:不屏蔽
    unsigned char KEY_COUNT;        //按键长按计数
    unsigned char KEY_LEVEL;        //虚拟当前IO电平，按下1，抬起0
    unsigned char KEY_DOWN_LEVEL;   //按下时IO实际的电平
    unsigned char KEY_STATUS;       //按键状态
    unsigned char KEY_EVENT;        //按键事件
    unsigned char (*READ_PIN)(void);//读IO电平函数
}KEY_COMPONENTS;
extern KEY_COMPONENTS Key_Buf[KEY_NUM];


void Task_KEY_Scan(void);//按键测试
unsigned char GetKey();




#endif