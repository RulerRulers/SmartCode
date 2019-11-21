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
};//���ĸ�����KEY_DOWN_LEVEL��ʾ��������ʱIO�ڵĵ�ƽ  0���͵�ƽ  1���ߵ�ƽ  �ҵĵ�·���������ǵ͵�ƽ ������������Ϊ0

//��ѯÿ�������ĵ�ƽ ����ֵ����Ӧ�������ƽ  
static void Get_Key_Level(void)
{
    unsigned char i;
    
    for(i = 0;i < KEY_NUM;i++)
    {
        if(Key_Buf[i].KEY_SHIELD == 0)
            continue;
        if(Key_Buf[i].READ_PIN() == Key_Buf[i].KEY_DOWN_LEVEL)
            Key_Buf[i].KEY_LEVEL = 1;//�����ƽ 1������ 0��̧��
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
            //״̬0��û�а�������
            case KEY_NULL:
                if(Key_Buf[i].KEY_LEVEL == 1)//�а�������
                {
                    Key_Buf[i].KEY_STATUS = KEY_SURE;//ת��״̬1
                    Key_Buf[i].KEY_EVENT = KEY_NULL;//���¼�
                }
                else
                {
                    Key_Buf[i].KEY_EVENT = KEY_NULL;//���¼�
                }
                break;
            //״̬1����������ȷ��
            case KEY_SURE:
                if(Key_Buf[i].KEY_LEVEL == 1)//ȷ�Ϻ��ϴ���ͬ
                {
                    Key_Buf[i].KEY_STATUS = KEY_DOWN;//ת��״̬2
                    Key_Buf[i].KEY_EVENT = KEY_DOWN;//�����¼�
                    Key_Buf[i].KEY_COUNT = 0;//����������
									  
                }
                else
                {
                    Key_Buf[i].KEY_STATUS = KEY_NULL;//ת��״̬0
                    Key_Buf[i].KEY_EVENT = KEY_NULL;//���¼�
                }
                break;
            //״̬2����������
            case KEY_DOWN:
                if(Key_Buf[i].KEY_LEVEL != 1)//�����ͷţ��˿ڸߵ�ƽ
                {
                    Key_Buf[i].KEY_STATUS = KEY_NULL;//ת��״̬0
                    Key_Buf[i].KEY_EVENT = KEY_NULL;//���¼�
                }
                else if((Key_Buf[i].KEY_LEVEL == 1))//����255û���ͷ�
                {
//                     Key_Buf[i].KEY_STATUS = KEY_NULL;//ת��״̬3
//                     Key_Buf[i].KEY_EVENT = KEY_NULL;//�����¼�
//                     Key_Buf[i].KEY_COUNT = 0;//����������
									      
									    while(Key_Buf[i].READ_PIN()==0);//�ȴ������ͷ�
									    Key_Buf[i].KEY_STATUS = KEY_NULL;//ת��״̬0
                      Key_Buf[i].KEY_EVENT = KEY_NULL;//���¼�
                }
                else
                {
                    Key_Buf[i].KEY_EVENT = KEY_NULL;//���¼�
                }
                break;
            //״̬3��������������
//             case KEY_LONG:
//                 if(Key_Buf[i].KEY_LEVEL != 1)//�����ͷţ��˿ڸߵ�ƽ
//                 {
//                     Key_Buf[i].KEY_STATUS = KEY_NULL;//ת��״̬0
//                     Key_Buf[i].KEY_EVENT = KEY_UP;//�ɿ��¼�
//                     Key_Buf[i].KEY_EVENT = KEY_NULL;
//                 }
//                 else if((Key_Buf[i].KEY_LEVEL == 1) 
//                 && (++Key_Buf[i].KEY_COUNT >= KEY_LONG_DOWN_DELAY)) //����KEY_LONG_DOWN_DELAYû���ͷ�
//                 {
//                     Key_Buf[i].KEY_EVENT = KEY_LONG;//�����¼�
//                     Key_Buf[i].KEY_COUNT = 0;//����������
//                 }
//                 else
//                 {
//                     Key_Buf[i].KEY_EVENT = KEY_NULL;//���¼�
//                 }
//                 break;
        }
    }
}


//�������Ժ���
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



