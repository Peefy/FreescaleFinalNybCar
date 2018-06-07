#include "include.h"

#define  U32 unsigned long
#define  uint8 unsigned char
#define  uint16 unsigned int

#define FMQ_PIN  PTD7
#define FMQ      PTXn_T(FMQ_PIN,OUT)


char FMQ_Status=1;
void FMQ_TURN(void)
{
    if(FMQ_Status==1)
    {
     FMQ=0;
     FMQ_Status=0; 
    }
    else
    {
     FMQ=1;
     FMQ_Status=1; 
    }
    
}
void FMQ_OFF(void)
{
  FMQ=0;
  FMQ_Status =0; 
}
void FMQ_ON(void)
{
  FMQ=1;
  FMQ_Status =1; 
}
void sound_init(void)
{
  gpio_init  (FMQ_PIN, GPO, 1); 
}

void  delay_fmq(uint32  ms)
{

    U32  i, j;
    for(i = 0; i < ms; i++)
    {
        for(j = 400; j > 0; j--)
        {
            //_asm(nop);
        }
    }
}                                                                                                                                               


void kaiji_fmq(void)			 //开机音
{
	uint8 a;
	for(a=60;a>0;a--)
	 {
		FMQ_TURN() ;
		delay_fmq(60);
	 }
	for(a=100;a>0;a--)
	 {
	FMQ_TURN() ;
		delay_fmq(50);
	 }
	for(a=100;a>0;a--)
	 {
		FMQ_TURN() ;
		delay_fmq(20);
	 }
	FMQ_OFF() ;
}

void up_fmq(void)			 //开机音
{
	uint8 a;
	for(a=100;a>0;a--)
	 {
		FMQ_TURN() ;
		delay_fmq(6);
	 }
	for(a=100;a>0;a--)
	 {
		FMQ_TURN() ;
		delay_fmq(12);
	 }
	for(a=100;a>0;a--)
	 {
		FMQ_TURN() ;
		delay_fmq(6);
	 }
	FMQ_OFF() ;
}

void down_fmq(void)			 //开机音
{
	uint8 a;
	for(a=100;a>0;a--)
	 {
		FMQ_TURN() ;
		delay_fmq(20);
	 }
	for(a=100;a>0;a--)
	 {
		FMQ_TURN() ;
		delay_fmq(6);
	 }
	for(a=100;a>0;a--)
	 {
		FMQ_TURN() ;
		delay_fmq(15);
	 }
	FMQ_OFF() ;
}
void left_fmq(void)
{
    uint8 a;
    	for(a=100;a>0;a--)
	 {
		FMQ_TURN() ;
		delay_fmq(10);
	 }
	for(a=100;a>0;a--)
	 {
		FMQ_TURN() ;
		delay_fmq(16);
	 }
	for(a=100;a>0;a--)
	 {
		FMQ_TURN() ;
		delay_fmq(5);
	 }
	FMQ_OFF() ;
}

void right_fmq(void)
{
       uint8 a;
       for(a=100;a>0;a--)
       {
		FMQ_TURN() ;
		delay_fmq(15);
	 }
	for(a=100;a>0;a--)
	 {
		FMQ_TURN() ;
		delay_fmq(6);
	 }
	for(a=100;a>0;a--)
	 {
		FMQ_TURN() ;
		delay_fmq(12);
	 }
	FMQ_OFF() ;
}

void ok_fmq(void)			  //按键音
{
	uint8 a;
	for(a=100;a>0;a--)
	 {
		FMQ_TURN() ;
		delay_fmq(20);
	 }
	for(a=80;a>0;a--)
	 {
		FMQ_TURN() ;
		delay_fmq(30);
	 }

	FMQ_OFF() ;
}

void ok_hold_fmq(void)			  //按键音
{
	uint16 a;
	for(a=450;a>0;a--)
	 {
		FMQ_TURN() ;
		delay_fmq(10);
	 }
	FMQ_TURN() ;

	 delay_fmq(50);
	for(a=450;a>0;a--)
	 {
		FMQ_TURN() ;
		delay_fmq(10);
	 }
	FMQ_OFF() ;

}

void Warning_fmq(void)
{
    uint16 a;
    for(a=450;a>0;a--)
    {
	FMQ_TURN() ;
	delay_fmq(10);
    }
}
