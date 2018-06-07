/************************* (C) COPYRIGHT 2013 DZXH ************************
* 文  件  名      : KEY.H
* 作      者      : DZXH@Dream Creater
* 适      用      ：DZXH 开发板V2.1/V1.0。
* 淘  宝  店      : http://shop102062100.taobao.com/
* 版      本      : V1.0
* 日      期      : 2013/11
* 主  控  MCU     : STM32F103VET6
* 编  译  器      : Keil ARM 4.54
* 描      述      : 按键初始化头文件
**************************************************************************/
#ifndef __KEY_H__
#define __KEY_H__
#include "include.h"

//下面是定义按键的时间，单位为 ： 10ms
#define KEY_DOWN_TIME   1
#define KEY_HOLD_TIME   100         //最多253，否则需要修改keytime的类型


//按键端口的枚举
typedef enum  //后面的数据等于几都无所谓，随便定义
{             //除了最后那个KEY_MAX
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



//key状态宏定义
typedef enum
{
    KEY_DOWN  =   0,         //按键按下时对应电平
    KEY_UP    =   1,         //按键弹起时对应电平
    KEY_HOLD
} KEY_STATUS_e;

//按键及其状态结构体
typedef struct
{
    unsigned int    key;
    KEY_STATUS_e    status;
} KEY_MSG_t;


uint8 get_key_msg(KEY_MSG_t *keymsg);          //获取按键消息，返回1表示有按键消息，0为无按键消息

//定时扫描按键
void key_IRQHandler(void);                      // u16 absi(s16 data_s);

#endif 
//*****************************END**********************************

