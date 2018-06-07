/************************* (C) COPYRIGHT 2013 DZXH ************************
* ��  ��  ��      : KEY.H
* ��      ��      : DZXH@Dream Creater
* ��      ��      ��DZXH ������V2.1/V1.0��
* ��  ��  ��      : http://shop102062100.taobao.com/
* ��      ��      : V1.0
* ��      ��      : 2013/11
* ��  ��  MCU     : STM32F103VET6
* ��  ��  ��      : Keil ARM 4.54
* ��      ��      : ������ʼ��ͷ�ļ�
**************************************************************************/
#ifndef __KEY_H__
#define __KEY_H__
#include "include.h"

//�����Ƕ��尴����ʱ�䣬��λΪ �� 10ms
#define KEY_DOWN_TIME   1
#define KEY_HOLD_TIME   100         //���253��������Ҫ�޸�keytime������


//�����˿ڵ�ö��
typedef enum  //��������ݵ��ڼ�������ν����㶨��
{             //��������Ǹ�KEY_MAX
	KEY_NONE = 0,
    KEY_0=1000, 
    KEY_1=1365,
    KEY_2=1985,
    KEY_3=2730,
    KEY_4=3723,
  
    KEY_UPP=100,//+KEY_OFFSET, 
    KEY_OK =340,//+KEY_OFFSET,
    KEY_L=512,//+KEY_OFFSET,
    KEY_R=676,//+KEY_OFFSET,
    KEY_DOWNN =931,//+KEY_OFFSET,
    KEY_MAX=5
} KEY_e;



//key״̬�궨��
typedef enum
{
    KEY_DOWN  =   0,         //��������ʱ��Ӧ��ƽ
    KEY_UP    =   1,         //��������ʱ��Ӧ��ƽ
    KEY_HOLD
} KEY_STATUS_e;

//��������״̬�ṹ��
typedef struct
{
    unsigned int    key;
    KEY_STATUS_e    status;
} KEY_MSG_t;


uint8 get_key_msg(KEY_MSG_t *keymsg);          //��ȡ������Ϣ������1��ʾ�а�����Ϣ��0Ϊ�ް�����Ϣ

//��ʱɨ�谴��
void key_IRQHandler(void);                      // u16 absi(s16 data_s);

#endif 
//*****************************END**********************************

