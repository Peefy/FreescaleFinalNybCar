#ifndef _MOTORCONTROL_H
#define _MOTORCOMTROL_H

#define MOTOR_Hz        10000   //电机频率

//电机模糊控制中的宏定义
#define  M_E_NB  -200      //err负大   
#define  M_E_NM  -140      //err负中  
#define  M_E_NS  -60       //err负小  
#define  M_E_ZO  0         //err零
#define  M_E_PS  60        //err正小
#define  M_E_PM  140       //err正中
#define  M_E_PB  200       //err正大

#define  M_EC_NB  -40      //errc负大
#define  M_EC_NM  -28       //errc负中
#define  M_EC_NS  -16       //errc负小
#define  M_EC_ZO  0        //errc零
#define  M_EC_PS  16        //errc正小
#define  M_EC_PM  28        //errc正中
#define  M_EC_PB  40       //errc正大

extern uint8 Stop_CMD;  //声明一下全局变量
extern uint8 ShangWeiJiStop; 
extern uint8 ItStop;
extern uint8 Car_Cmd;
extern uint8 DetectD_EN;
extern uint16 Set_Speed;
extern uint16 Real_Speed;     //检测到的真实速度
extern uint16 OtherCar_Real_Speed;
extern uint16 MaxSpeed;      //最大速度
extern uint16 MinSpeed;      //最小速度
extern uint16 ZhiDaoSpeed;   //直道速度
extern uint16 WanDaoSpeed;   //弯道速度
extern uint16 OtherCar_ZhiDaoSpeed;   //另一个车的直道速度
extern uint16 OtherCar_WanDaoSpeed;   //另一个车的弯道速度
extern uint16 MOTOR_P;   //电机控制的P
extern uint16 MOTOR_I;   //电机控制的I
extern uint16 MOTOR_D;   //电机控制的D
extern uint8  Mtr_Debug_Enable;
extern uint16 KeepDis;

extern uint8 AutoStart;
extern uint8 StartFlag;
extern uint16 StartTime;

extern uint8 TimerRun_s;
extern uint8 TimerRun_Flag;
extern uint16 TimerRun_Time;
extern uint8 TimerRun_EN;

extern uint16 OC_Distance;
extern uint16 Distance;
extern float fDistance;
extern uint16 OC_Stop;

extern int16 OutofRangeCount; 
extern uint8 OutofRangeFlag;
extern int16 MotorOverloadCount;
extern uint8 MotorOverloadFlag;
extern uint8 SpeedingFlag;
extern uint16 BeeCount;

extern float abs_float(float data_s);   //浮点绝对值函数
extern void  Get_Real_Speed(void);
extern void  Motor_Zheng(float pwm);    //电机正转函数
extern void  Motor_Fan(float pwm);      //电机反转函数
extern void  Run(void);                 //小车启动函数
extern void  Stop(void);                //小车停止函数
extern void Stop_(void);                //小车停止函数
extern void  Motor_PID(float v_set);    //电机PID函数
extern void  Motor_P(float v_set);     //电机PID函数（二次P）
extern void  Motor_Ctl(void);         //电机控制函数
extern void  Motor_ExpertFuzzyPID(float);
extern void  Motor_LearningPID(float);
extern void  Start(void);
extern void  DectectStartLine(void);
extern void TimerRun(void);
extern void Delay2sDepart(void);
extern void Timer20sRun(void);

//#define  Motor_Normal_PID_Enable  1
#define  Motor_ExpertFuzzy_PID_Enable  1 
//#define  Motor_Learning_PID_Enable  1

#define Motor_EN 1
#define Encoder_EN 1
#define DetectDanger_EN 1

#endif