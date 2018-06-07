/*******************************************************************
#include "GUIcustom.h"
Last Write Time: 2015-07-28  16:19:42
*******************************************************************/

#ifndef GUI_CUSTOM_H
#define GUI_CUSTOM_H

#include "include.h"

///类型重定义
typedef uint8 u8;
typedef uint16 u16 ;
typedef uint32 u32;
typedef  int8 s8;
typedef int16 s16;
typedef int32 s32;

///配置宏定义
#define ItermNameLengthMax     9
#define Iterm_TOTAL            83
#define ItemNum_MAX            5
#define ItermCMDNameLengthMax  10
#define Iterm_CMD_TOTAL        15

#define LCD_X_NAME  6
#define LCD_X_DATA  69
#define LCD_X_X     62

#define SHOW_PAGE_NUM


///函数宏定义
#define LCD_CLEAR(value) LCD_CLS(value)
#define LCD_PrintString(X,Y,STR) LCD_P6x8Str(X,Y,STR)
#define LCD_PrintParaNameString(X,Y,STR) LCD_P6x8Str(X,Y,STR)
#define LCD_PrintParaDataString(X,Y,STR) LCD_P6x8Str(X,Y,STR)
#define LCD_PrintCMDNameString(X,Y,STR) LCD_P6x8Str(X,Y,STR)
//#define PANNEL_SEND_DATA(value) PannelWrite(value)


///Iterms
extern u16 F_FL_MAX;
extern u16 F_L_MAX;
extern u16 F_M_MAX;
extern u16 F_R_MAX;
extern u16 F_FR_MAX;
extern u16 F_FL_OFF;
extern u16 F_L_OFF;
extern u16 F_M_OFF;
extern u16 F_R_OFF;
extern u16 F_FR_OFF;
extern s16 AD_Value_F_FL0;
extern s16 AD_Value_F_L0;
extern s16 AD_Value_F_M0;
extern s16 AD_Value_F_R0;
extern s16 AD_Value_F_FR0;
extern s16 AD_Value_F_FL;
extern s16 AD_Value_F_L;
extern s16 AD_Value_F_M;
extern s16 AD_Value_F_R;
extern s16 AD_Value_F_FR;
extern s16 HMI_e;
extern s16 HMI_e_Heng;
extern s16 HMI_e_Shu;
extern s32 F_L_M_add;
extern s32 FL_FR_add;
extern u16 ZD_count;
extern u16 WD_count;
extern u16 ZDLose_count;
extern u16 WDLose_count;
extern u16 SZ_count;
extern u16 Real_Speed;
extern u16 Set_Speed;
extern u16 HMI_err_I;
extern u16 ZhiDaoSpeed;
extern u16 WanDaoSpeed;
extern u16 ERR_I_MAX;
extern u16 ZhiDao_Servo_P;
extern u16 ZhiDao_Servo_D;
extern u16 WanDao_Servo_P;
extern u16 WanDao_Servo_D;
extern u16 MOTOR_P;
extern u16 MOTOR_I;
extern u16 PWM_duoji;
extern u8 Ser_Debug_Enable;
extern u16 SerMid_Debug;
extern u8 ServoEnable;
extern u8 Mtr_Debug_Enable;
extern u16 OtherCar_ZhiDaoSpeed;
extern u16 OtherCar_WanDaoSpeed;
extern u16 OtherCar_Real_Speed;
extern s16 HMI_e_LR;
extern s16 AD_Value_Cell;
extern u8 AutoStart;
extern u16 StartTime;
extern u8 StartFlag;
extern u16 NotChange;
extern u8 TimerRun_EN;
extern u8 TimerRun_s;
extern u16 TimerRun_Time;
extern u8 TimerRun_Flag;
extern u16 Distance;
extern u16 OC_Distance;
extern u16 NB_DisCount0;
extern u16 NB_DisCount1;
extern s16 Gyro_Y_Offest;
extern s16 Accel_X_Offest;
extern s16 Accel_Z_Offest;
extern s32 Gyro_Y;
extern s32 Accel_X;
extern s32 Accel_Z;
extern u16 Q_angle_HMI;
extern u16 Q_gyro_HMI;
extern u16 R_angle_HMI;
extern u16 dt_HMI;
extern s16 Angle_Y;
extern s32 Angle_ShuiPing;
extern u8 Ramp_EN;
//extern u8 Ramp_possible_flag;
//extern u8 Ramp_up_flag;
//extern u8 Ramp_down_flag;
extern u8 CSB_EN;
extern u8 DetectD_EN;
extern u8 Car_Cmd;

void GUI_Sleep(void);
void All_Test(void);
void All_Init(void);
void Run(void);
void Stop(void);
void Save_All(void);
void Config_All(void);
void SpeedSelect_HIGH(void);
void SpeedSelect_MEDIUM(void);
void SpeedSelect_LOW(void);
void Offest_Init(void);
void Angle_ShuiPing_get(void);
void TC_Game(void);
void Timer20sRun(void);
void Delay2sDepart(void);

#endif

