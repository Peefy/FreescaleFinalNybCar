#ifndef _MOTORCONTROL_H
#define _MOTORCOMTROL_H

#define MOTOR_Hz        10000   //���Ƶ��

//���ģ�������еĺ궨��
#define  M_E_NB  -200      //err����   
#define  M_E_NM  -140      //err����  
#define  M_E_NS  -60       //err��С  
#define  M_E_ZO  0         //err��
#define  M_E_PS  60        //err��С
#define  M_E_PM  140       //err����
#define  M_E_PB  200       //err����

#define  M_EC_NB  -40      //errc����
#define  M_EC_NM  -28       //errc����
#define  M_EC_NS  -16       //errc��С
#define  M_EC_ZO  0        //errc��
#define  M_EC_PS  16        //errc��С
#define  M_EC_PM  28        //errc����
#define  M_EC_PB  40       //errc����

extern uint8 Stop_CMD;  //����һ��ȫ�ֱ���
extern uint8 ShangWeiJiStop; 
extern uint8 ItStop;
extern uint8 Car_Cmd;
extern uint8 DetectD_EN;
extern uint16 Set_Speed;
extern uint16 Real_Speed;     //��⵽����ʵ�ٶ�
extern uint16 OtherCar_Real_Speed;
extern uint16 MaxSpeed;      //����ٶ�
extern uint16 MinSpeed;      //��С�ٶ�
extern uint16 ZhiDaoSpeed;   //ֱ���ٶ�
extern uint16 WanDaoSpeed;   //����ٶ�
extern uint16 OtherCar_ZhiDaoSpeed;   //��һ������ֱ���ٶ�
extern uint16 OtherCar_WanDaoSpeed;   //��һ����������ٶ�
extern uint16 MOTOR_P;   //������Ƶ�P
extern uint16 MOTOR_I;   //������Ƶ�I
extern uint16 MOTOR_D;   //������Ƶ�D
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

extern float abs_float(float data_s);   //�������ֵ����
extern void  Get_Real_Speed(void);
extern void  Motor_Zheng(float pwm);    //�����ת����
extern void  Motor_Fan(float pwm);      //�����ת����
extern void  Run(void);                 //С����������
extern void  Stop(void);                //С��ֹͣ����
extern void Stop_(void);                //С��ֹͣ����
extern void  Motor_PID(float v_set);    //���PID����
extern void  Motor_P(float v_set);     //���PID����������P��
extern void  Motor_Ctl(void);         //������ƺ���
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