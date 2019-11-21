#include <STC12C5A60S2.H>
#include "key.h"
#include "stdio.h"




static unsigned char KEY0_ReadPin(void)
{
    return _KEY0;
}

static unsigned char KEY1_ReadPin(void)
{
    return _KEY1;
}

static unsigned char KEY2_ReadPin(void)
{
    return _KEY2;
}

static unsigned char KEY3_ReadPin(void)
{
    return _KEY3;
}


KEY_COMPONENTS Key_Buf[KEY_NUM] = {
{1,0,0,0,KEY_NULL,KEY_NULL,KEY0_ReadPin},
{1,0,0,0,KEY_NULL,KEY_NULL,KEY1_ReadPin},
{1,0,0,0,KEY_NULL,KEY_NULL,KEY2_ReadPin},
{1,0,0,0,KEY_NULL,KEY_NULL,KEY3_ReadPin},
};//第四个参数KEY_DOWN_LEVEL表示按键按下时IO口的电平  0：低电平  1：高电平  我的电路按键按下是低电平 所以这里设置为0

//轮询每个按键的电平 并赋值给对应的虚拟电平  
static void Get_Key_Level(void)
{
    unsigned char i;
    
    for(i = 0;i < KEY_NUM;i++)
    {
        if(Key_Buf[i].KEY_SHIELD == 0)
            continue;
        if(Key_Buf[i].READ_PIN() == Key_Buf[i].KEY_DOWN_LEVEL)
            Key_Buf[i].KEY_LEVEL = 1;//虚拟电平 1：按下 0：抬起
        else
            Key_Buf[i].KEY_LEVEL = 0;
    }
}

void ReadKeyStatus(void)
{
    unsigned char i;
    
    Get_Key_Level();
    
    for(i = 0;i < KEY_NUM;i++)
    {
        switch(Key_Buf[i].KEY_STATUS)
        {
            //状态0：没有按键按下
            case KEY_NULL:
                if(Key_Buf[i].KEY_LEVEL == 1)//有按键按下
                {
                    Key_Buf[i].KEY_STATUS = KEY_SURE;//转入状态1
                    Key_Buf[i].KEY_EVENT = KEY_NULL;//空事件
                }
                else
                {
                    Key_Buf[i].KEY_EVENT = KEY_NULL;//空事件
                }
                break;
            //状态1：按键按下确认
            case KEY_SURE:
                if(Key_Buf[i].KEY_LEVEL == 1)//确认和上次相同
                {
                    Key_Buf[i].KEY_STATUS = KEY_DOWN;//转入状态2
                    Key_Buf[i].KEY_EVENT = KEY_DOWN;//按下事件
                    Key_Buf[i].KEY_COUNT = 0;//计数器清零
									  
                }
                else
                {
                    Key_Buf[i].KEY_STATUS = KEY_NULL;//转入状态0
                    Key_Buf[i].KEY_EVENT = KEY_NULL;//空事件
                }
                break;
            //状态2：按键按下
            case KEY_DOWN:
                if(Key_Buf[i].KEY_LEVEL != 1)//按键释放，端口高电平
                {
                    Key_Buf[i].KEY_STATUS = KEY_NULL;//转入状态0
                    Key_Buf[i].KEY_EVENT = KEY_NULL;//空事件
                }
                else if((Key_Buf[i].KEY_LEVEL == 1))//超过255没有释放
                {
//                     Key_Buf[i].KEY_STATUS = KEY_NULL;//转入状态3
//                     Key_Buf[i].KEY_EVENT = KEY_NULL;//长按事件
//                     Key_Buf[i].KEY_COUNT = 0;//计数器清零
									      
									    while(Key_Buf[i].READ_PIN()==0);//等待按键释放
									    Key_Buf[i].KEY_STATUS = KEY_NULL;//转入状态0
                      Key_Buf[i].KEY_EVENT = KEY_NULL;//空事件
                }
                else
                {
                    Key_Buf[i].KEY_EVENT = KEY_NULL;//空事件
                }
                break;
            //状态3：按键连续按下
//             case KEY_LONG:
//                 if(Key_Buf[i].KEY_LEVEL != 1)//按键释放，端口高电平
//                 {
//                     Key_Buf[i].KEY_STATUS = KEY_NULL;//转入状态0
//                     Key_Buf[i].KEY_EVENT = KEY_UP;//松开事件
//                     Key_Buf[i].KEY_EVENT = KEY_NULL;
//                 }
//                 else if((Key_Buf[i].KEY_LEVEL == 1) 
//                 && (++Key_Buf[i].KEY_COUNT >= KEY_LONG_DOWN_DELAY)) //超过KEY_LONG_DOWN_DELAY没有释放
//                 {
//                     Key_Buf[i].KEY_EVENT = KEY_LONG;//长按事件
//                     Key_Buf[i].KEY_COUNT = 0;//计数器清零
//                 }
//                 else
//                 {
//                     Key_Buf[i].KEY_EVENT = KEY_NULL;//空事件
//                 }
//                 break;
        }
    }
}


//按键测试函数
// void Task_KEY_Scan(void)
// {
//     ReadKeyStatus();
//     
//     if(Key_Buf[KEY0].KEY_EVENT == KEY_DOWN)
//     {
//         printf("SW3 Down\n");
//     }
//     
//     if(Key_Buf[KEY1].KEY_EVENT == KEY_DOWN)
//     {
//         printf("SW4 Down\n");
//     }
//     
//     if(Key_Buf[KEY2].KEY_EVENT == KEY_DOWN)
//     {
//         printf("SW5 Down\n");
//     }
// 		if(Key_Buf[KEY3].KEY_EVENT == KEY_DOWN)
//     {
//         printf("SW6 Down\n");
//     }

// }

unsigned char GetKey()
{
     ReadKeyStatus();  
    if(Key_Buf[KEY0].KEY_EVENT == KEY_DOWN)
    {
       return 1;
    }
    
    else if(Key_Buf[KEY1].KEY_EVENT == KEY_DOWN)
    {
        return 2;
    }
    
    else if(Key_Buf[KEY2].KEY_EVENT == KEY_DOWN)
    {
        return 3;
    }
		else if(Key_Buf[KEY3].KEY_EVENT == KEY_DOWN)
    {
        return 4;
    }
		else
		{
        return 0;
    }

}



