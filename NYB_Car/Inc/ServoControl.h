#ifndef _SERVOCONTROL_H
#define _SERVOCOMTROL_H

#define SERVO_Hz        300      //舵机频率
#define SERVO_MID       5368.0   //舵机的参考中值
#define SERVO_RANGE_L   2000   
#define SERVO_RANGE_R   2000
#define SERVO_MAX_ANGLE 45.0
//舵机模糊控制中的宏定义
#define  S_E_NB_Z  -300      //e负大  直道
#define  S_E_NM_Z  -180      //e负中  
#define  S_E_NS_Z  -100       //e负小  
#define  S_E_ZO_Z   0         //e零
#define  S_E_PS_Z   100        //e正小
#define  S_E_PM_Z   180       //e正中
#define  S_E_PB_Z   300       //e正大

#define  S_EC_NB_Z  -140      //ec负大
#define  S_EC_NM_Z  -90      //ec负中
#define  S_EC_NS_Z  -50       //ec负小
#define  S_EC_ZO_Z  0        //ec零
#define  S_EC_PS_Z  50       //ec正小
#define  S_EC_PM_Z  90        //ec正中
#define  S_EC_PB_Z  140      //ec正大

#define  S_E_NB_W  -293      //e负大  弯道 
#define  S_E_NM_W  -190      //e负中  
#define  S_E_NS_W  -120       //e负小  
#define  S_E_ZO_W   0         //e零
#define  S_E_PS_W   120        //e正小
#define  S_E_PM_W   190       //e正中
#define  S_E_PB_W   293       //e正大

#define  S_EC_NB_W  -150      //ec负大
#define  S_EC_NM_W  -80       //ec负中
#define  S_EC_NS_W  -50       //ec负小
#define  S_EC_ZO_W  0        //ec零
#define  S_EC_PS_W  50        //ec正小
#define  S_EC_PM_W  80        //ec正中
#define  S_EC_PB_W  150       //ec正大

typedef enum
{
   PB=0,PM=1,PS=2,ZO=3,NS=4,NM=5,NB=6 
}FuzzyField;

typedef enum
{
   ClockWise,AntiClockWise  //赛道顺时针 赛道逆时针
}Direction;

extern Direction Race;
extern int16 ec_min;  
extern int16 ec_max;
extern int16 ec_retern;
extern uint16 PWM_duoji;
extern uint16 SerMid_Debug;
extern uint8 ServoEnable;
extern uint8 Ser_Debug_Enable;
extern float ServoAngle;
extern void Servo_Debug(void);
extern void Set_Servo_PWM(int value);
extern void Servo_PID(void);
extern void Servo_ExpertFuzzyPID(void);

extern uint16 Servo_D,Servo_P,ZhiDao_Servo_P,ZhiDao_Servo_D,WanDao_Servo_P,WanDao_Servo_D;
extern int P1;
extern int P2;
extern int P3;
extern int P4;
/****************舵机PID模式选择****************/
//#define  Servo_Normal_PID_Enable  1
#define  Servo_ExpertFuzzy_PID_Enable  1   

#define Servo_EN 1

#endif