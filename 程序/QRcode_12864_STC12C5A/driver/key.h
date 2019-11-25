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
    KEY_NULL = 0x00,//�޼�����
    KEY_SURE = 0x01,//ȷ��̬
    KEY_UP   = 0x02,//̧��
    KEY_DOWN = 0x04,//����
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
    unsigned char KEY_SHIELD;       //��������0:���Σ�1:������
    unsigned char KEY_COUNT;        //������������
    unsigned char KEY_LEVEL;        //���⵱ǰIO��ƽ������1��̧��0
    unsigned char KEY_DOWN_LEVEL;   //����ʱIOʵ�ʵĵ�ƽ
    unsigned char KEY_STATUS;       //����״̬
    unsigned char KEY_EVENT;        //�����¼�
    unsigned char (*READ_PIN)(void);//��IO��ƽ����
}KEY_COMPONENTS;
extern KEY_COMPONENTS Key_Buf[KEY_NUM];


void Task_KEY_Scan(void);//��������
void ReadKeyStatus(void);  
unsigned char GetKey(void);




#endif