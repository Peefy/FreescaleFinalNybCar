/************************* (C) COPYRIGHT 2013 DZXH ************************
* ��  ��  ��      : KEY.C
* ��      ��      : DZXH@Dream Creater
* ��      ��      ��DZXH ������V2.1/V1.0��
* ��  ��  ��      : http://shop102062100.taobao.com/
* ��      ��      : V1.0
* ��      ��      : 2013/11
* ��  ��  MCU     : STM32F103VET6
* ��  ��  ��      : Keil ARM 4.54
* ��      ��      : ������ʼ��
**************************************************************************/

#include "Key.h"
#include "KeyCustom.h"


KEY_STATUS_e key_check(u8 key);              //���key״̬
void deal_key_event(void);                  //�����¼��������
u8 Panel_KeyScan(void);



u16 count=0;
///<summary>
///���������������������ŵĶ�Ӧ��ϵ
///<\summary>
u16 KEY_One[KEY_MAX+1] = {KEY_NONE,KEY_R, KEY_DOWNN, KEY_L, KEY_UPP, KEY_OK};


 /************************************************************************
* ��  ��  ��  : key_check
* ��      ��  : ���key״̬
* ��      ��  : ������ţ�1-KEY_MAX����ĿǰKEY_MAX=10
* ��      ��  : ��.
************************************************************************/
KEY_STATUS_e key_check(u8 key)
{
	if(Panel_KeyScan() == key)   //KEY_Ϊ����������
	{
		return KEY_DOWN;             //����������	
	}
	else
	{
		 return KEY_UP;
	}
}

//���尴��״̬�ṹ��
typedef enum
{
    KEY_MSG_EMPTY,      //û�а�����Ϣ
    KEY_MSG_NORMAL,     //�������а�����Ϣ��������
    KEY_MSG_FULL        //������Ϣ��
} key_msg_e;

#define KEY_MSG_FIFO_SIZE   20      //��� 255��������Ҫ�޸�key_msg_front/key_msg_rear����
KEY_MSG_t       key_msg[KEY_MSG_FIFO_SIZE];
volatile u8     key_msg_front = 0, key_msg_rear = 0; //����FIFO��ָ��
volatile u8     key_msg_flag = KEY_MSG_EMPTY;

 /************************************************************************
* ��  ��  ��  : send_key_msg
* ��      ��  : 
* ��      ��  : 
* ��      ��  : ��.
************************************************************************/
void send_key_msg(KEY_MSG_t keymsg)
{
    //������FIFO��
    if(key_msg_flag == KEY_MSG_FULL)
    {
        //����ֱ�Ӳ�����
        return ;
    }
    key_msg[key_msg_rear].key = keymsg.key;
    key_msg[key_msg_rear].status = keymsg.status;

    key_msg_rear++;

    if((key_msg_rear > KEY_MSG_FIFO_SIZE)||(key_msg_rear == KEY_MSG_FIFO_SIZE))
    {
        key_msg_rear = 0;                       //��ͷ��ʼ
    }

    if(key_msg_rear == key_msg_front)                   //׷��ƨ���ˣ�����
    {
        key_msg_flag = KEY_MSG_FULL;
    }
    else
    {
        key_msg_flag = KEY_MSG_NORMAL;
    }
}
 /************************************************************************
* ��  ��  ��  : get_key_msg
* ��      ��  : 
* ��      ��  : 
* ��      ��  : ��.
************************************************************************/
u8 get_key_msg(KEY_MSG_t *keymsg)
{
    if(key_msg_flag == KEY_MSG_EMPTY)   //�գ�ֱ�ӷ���0
    {
        return 0;
    }
    keymsg->key = key_msg[key_msg_front].key;
    keymsg->status = key_msg[key_msg_front].status;

    key_msg_front++;                //���ڷǿգ����Կ���ֱ�ӳ�����

    if((key_msg_front > KEY_MSG_FIFO_SIZE)||(key_msg_front == KEY_MSG_FIFO_SIZE))
    {
        key_msg_front = 0;          //��ͷ��ʼ
    }

    if(key_msg_front == key_msg_rear)       //׷��ƨ���ˣ����ն��п�
    {
        key_msg_flag = KEY_MSG_EMPTY;
    }
	
    return 1;
}
 /************************************************************************
* ��  ��  ��  : key_IRQHandler
* ��      ��  : ��ʱ���key״̬
* ��      ��  : ��.
* ��      ��  : ��.
************************************************************************/
void key_IRQHandler(void)
{
    static u8 irq_time=0;
    u8    keynum;
    static u8 keytime[KEY_MAX];
    KEY_MSG_t keymsg;
	//5�βɼ������ж�  
	irq_time++;
	if(irq_time>3)
	{
		deal_key_event();
		irq_time=0;
	}		

    for(keynum = 1 ; keynum <= KEY_MAX; keynum ++)
    {
        if(key_check(keynum)  == KEY_DOWN)
        {
            keytime[keynum]++;

            if(keytime[keynum] < KEY_DOWN_TIME)
            {
                continue;
            }
            else if(keytime[keynum] == (KEY_DOWN_TIME + 1) )        //��Ч����
            {
                keymsg.key = KEY_One[keynum];
                keymsg.status = KEY_DOWN;
                send_key_msg(keymsg);
            }
            else if(keytime[keynum] < KEY_HOLD_TIME)
            {                 
                continue;                
            }
            else if(keytime[keynum]  == KEY_HOLD_TIME)    //��Ч��ס
            {             
                keymsg.key = KEY_One[keynum];;
                keymsg.status = KEY_HOLD;
                
                send_key_msg(keymsg);
            }
            else
            {
                keytime[keynum] = KEY_DOWN_TIME + 1;   
            }
	        }
        else
        {
            if(keytime[keynum] > KEY_DOWN_TIME)
            {
                keymsg.key = KEY_One[keynum];;
                keymsg.status = KEY_UP;
                send_key_msg(keymsg);           //��������
            }
            keytime[keynum] = 0;
        }
    } 
}

//*****************************END**********************************

