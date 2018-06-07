//Last Write Time: 2015-07-28  16:19:42
#include "GUIcustom.h"

extern s8 index_FirstItermInPage;

extern s32 Para16s[Iterm_TOTAL];


char ParaNames[Iterm_TOTAL][ItermNameLengthMax+1]=
{
"AD_FL_Max",
"AD_L_Max",
"AD_M_Max",
"AD_R_Max",
"AD_FR_Max",
"AD_FL_Min",
"AD_L_Min",
"AD_M_Min",
"AD_R_Min",
"AD_FR_Min",
"AD_FL0",
"AD_L0",
"AD_M0",
"AD_R0",
"AD_FR0",
"AD_FL1",
"AD_L1",
"AD_M1",
"AD_R1",
"AD_FR1",
"e",
"e_Heng",
"e_Shu",
"Henadd",
"Shuadd",
"ZD_Count",
"WD_Count",
"ZDL_Count",
"WDL_Count",
"SZ_Count",
"RealSpd",
"Set_Spd",
"HMI_err_I",
"ZD_Spd",
"WD_Spd",
"Mo_IntMax",
"ZD_Ser_P",
"ZD_Ser_D",
"WD_Ser_P",
"WD_Ser_D",
"Motor_P",
"Motor_I",
"ServoPWM",
"SerDbg_EN",
"SerMid",
"Servo_EN",
"MtrDbg_EN",
"OC_ZD_Spd",
"OC_WD_Spd",
"0C_RlSpd",
"e(R-L)",
"CellVotg",
"AutoStart",
"StartTime",
"StartFlag",
"NotChange",
"T-Run_EN",
"T-Run_s",
"T-RunTime",
"T-RunFlag",
"Distance",
"OC_Distc",
"HCSR04_0",
"HCSR04_1",
"GyroY_Off",
"AcelX_Off",
"AcelZ_Off",
"GyroY",
"Accel_X",
"Accel_Z",
"Q_angle",
"Q_gyro",
"R_angle",
"dt",
"Angle_Y",
"AgY_off",
"Ramp_EN",
"RampPos",
"RampUp",
"RampDown",
"CSB_EN",
"DeteD_EN",
"Car_Cmd"
};

const s32 ParaSteps[Iterm_TOTAL]=
{
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
10,
1,
10,
10,
100,
5,
5,
5,
5,
5,
1,
1,
1,
2,
1,
1,
10,
10,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
10,
10,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1,
1
};

const s32 ParaMax[Iterm_TOTAL]=
{
1200,
1200,
1200,
1200,
1200,
1200,
1200,
1200,
1200,
1200,
5000,
5000,
5000,
5000,
5000,
5200,
5200,
5200,
5200,
5200,
1200,
1200,
1200,
3000,
3000,
10000,
10000,
10000,
10000,
1180,
1500,
1500,
5000,
4000,
4000,
50000,
1000,
1000,
1000,
1000,
4000,
4000,
4000,
1,
10000,
1,
1,
4000,
4000,
1500,
4000,
10000,
1,
10000,
1,
10000,
1,
9990,
10000,
1,
50000,
50000,
60000,
60000,
30000,
30000,
30000,
30000,
30000,
30000,
30000,
30000,
30000,
30000,
33333,
33333,
1,
1,
1,
1,
1,
1,
100
};

const s32 ParaMin[Iterm_TOTAL]=
{
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
-374,
-500,
-500,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0
};

void Panel_LoadParas(u8 index)
{
	if(index != 0)
		Para16s[0] = F_FL_MAX;
	if(index != 1)
		Para16s[1] = F_L_MAX;
	if(index != 2)
		Para16s[2] = F_M_MAX;
	if(index != 3)
		Para16s[3] = F_R_MAX;
	if(index != 4)
		Para16s[4] = F_FR_MAX;
	if(index != 5)
		Para16s[5] = F_FL_OFF;
	if(index != 6)
		Para16s[6] = F_L_OFF;
	if(index != 7)
		Para16s[7] = F_M_OFF;
	if(index != 8)
		Para16s[8] = F_R_OFF;
	if(index != 9)
		Para16s[9] = F_FR_OFF;
	if(index != 10)
		Para16s[10] = AD_Value_F_FL0;
	if(index != 11)
		Para16s[11] = AD_Value_F_L0;
	if(index != 12)
		Para16s[12] = AD_Value_F_M0;
	if(index != 13)
		Para16s[13] = AD_Value_F_R0;
	if(index != 14)
		Para16s[14] = AD_Value_F_FR0;
	if(index != 15)
		Para16s[15] = AD_Value_F_FL;
	if(index != 16)
		Para16s[16] = AD_Value_F_L;
	if(index != 17)
		Para16s[17] = AD_Value_F_M;
	if(index != 18)
		Para16s[18] = AD_Value_F_R;
	if(index != 19)
		Para16s[19] = AD_Value_F_FR;
	if(index != 20)
		Para16s[20] = HMI_e;
	if(index != 21)
		Para16s[21] = HMI_e_Heng;
	if(index != 22)
		Para16s[22] = HMI_e_Shu;
	if(index != 23)
		Para16s[23] = F_L_M_add;
	if(index != 24)
		Para16s[24] = FL_FR_add;
	if(index != 25)
		Para16s[25] = ZD_count;
	if(index != 26)
		Para16s[26] = WD_count;
	if(index != 27)
		Para16s[27] = ZDLose_count;
	if(index != 28)
		Para16s[28] = WDLose_count;
	if(index != 29)
		Para16s[29] = SZ_count;
	if(index != 30)
		Para16s[30] = Real_Speed;
	if(index != 31)
		Para16s[31] = Set_Speed;
	if(index != 32)
		Para16s[32] = HMI_err_I;
	if(index != 33)
		Para16s[33] = ZhiDaoSpeed;
	if(index != 34)
		Para16s[34] = WanDaoSpeed;
	if(index != 35)
		Para16s[35] = ERR_I_MAX;
	if(index != 36)
		Para16s[36] = ZhiDao_Servo_P;
	if(index != 37)
		Para16s[37] = ZhiDao_Servo_D;
	if(index != 38)
		Para16s[38] = WanDao_Servo_P;
	if(index != 39)
		Para16s[39] = WanDao_Servo_D;
	if(index != 40)
		Para16s[40] = MOTOR_P;
	if(index != 41)
		Para16s[41] = MOTOR_I;
	if(index != 42)
		Para16s[42] = PWM_duoji;
	if(index != 43)
		Para16s[43] = Ser_Debug_Enable;
	if(index != 44)
		Para16s[44] = SerMid_Debug;
	if(index != 45)
		Para16s[45] = ServoEnable;
	if(index != 46)
		Para16s[46] = Mtr_Debug_Enable;
	if(index != 47)
		Para16s[47] = OtherCar_ZhiDaoSpeed;
	if(index != 48)
		Para16s[48] = OtherCar_WanDaoSpeed;
	if(index != 49)
		Para16s[49] = OtherCar_Real_Speed;
	if(index != 50)
		Para16s[50] = HMI_e_LR;
	if(index != 51)
		Para16s[51] = AD_Value_Cell;
	if(index != 52)
		Para16s[52] = AutoStart;
	if(index != 53)
		Para16s[53] = StartTime;
	if(index != 54)
		Para16s[54] = StartFlag;
	if(index != 55)
		Para16s[55] = NotChange;
	if(index != 56)
		Para16s[56] = TimerRun_EN;
	if(index != 57)
		Para16s[57] = TimerRun_s;
	if(index != 58)
		Para16s[58] = TimerRun_Time;
	if(index != 59)
		Para16s[59] = TimerRun_Flag;
	if(index != 60)
		Para16s[60] = Distance;
	if(index != 61)
		Para16s[61] = OC_Distance;
	if(index != 62)
		Para16s[62] = NB_DisCount0;
	if(index != 63)
		Para16s[63] = NB_DisCount1;
	if(index != 64)
		Para16s[64] = Gyro_Y_Offest;
	if(index != 65)
		Para16s[65] = Accel_X_Offest;
	if(index != 66)
		Para16s[66] = Accel_Z_Offest;
	if(index != 67)
		Para16s[67] = Gyro_Y;
	if(index != 68)
		Para16s[68] = Accel_X;
	if(index != 69)
		Para16s[69] = Accel_Z;
	if(index != 70)
		Para16s[70] = Q_angle_HMI;
	if(index != 71)
		Para16s[71] = Q_gyro_HMI;
	if(index != 72)
		Para16s[72] = R_angle_HMI;
	if(index != 73)
		Para16s[73] = dt_HMI;
	if(index != 74)
		Para16s[74] = Angle_Y;
	if(index != 75)
		Para16s[75] = Angle_ShuiPing;
	if(index != 76)
		Para16s[76] = Ramp_EN;
	if(index != 77)
		Para16s[77] = Ramp_possible_flag;
	if(index != 78)
		Para16s[78] = Ramp_up_flag;
	if(index != 79)
		Para16s[79] = Ramp_down_flag;
	if(index != 80)
		Para16s[80] = CSB_EN;
	if(index != 81)
		Para16s[81] = DetectD_EN;
	if(index != 82)
		Para16s[82] = Car_Cmd;
}
void Panel_SaveParas()
{
	F_FL_MAX = Para16s[0];
	F_L_MAX = Para16s[1];
	F_M_MAX = Para16s[2];
	F_R_MAX = Para16s[3];
	F_FR_MAX = Para16s[4];
	F_FL_OFF = Para16s[5];
	F_L_OFF = Para16s[6];
	F_M_OFF = Para16s[7];
	F_R_OFF = Para16s[8];
	F_FR_OFF = Para16s[9];
	AD_Value_F_FL0 = Para16s[10];
	AD_Value_F_L0 = Para16s[11];
	AD_Value_F_M0 = Para16s[12];
	AD_Value_F_R0 = Para16s[13];
	AD_Value_F_FR0 = Para16s[14];
	AD_Value_F_FL = Para16s[15];
	AD_Value_F_L = Para16s[16];
	AD_Value_F_M = Para16s[17];
	AD_Value_F_R = Para16s[18];
	AD_Value_F_FR = Para16s[19];
	HMI_e = Para16s[20];
	HMI_e_Heng = Para16s[21];
	HMI_e_Shu = Para16s[22];
	F_L_M_add = Para16s[23];
	FL_FR_add = Para16s[24];
	ZD_count = Para16s[25];
	WD_count = Para16s[26];
	ZDLose_count = Para16s[27];
	WDLose_count = Para16s[28];
	SZ_count = Para16s[29];
	Real_Speed = Para16s[30];
	Set_Speed = Para16s[31];
	HMI_err_I = Para16s[32];
	ZhiDaoSpeed = Para16s[33];
	WanDaoSpeed = Para16s[34];
	ERR_I_MAX = Para16s[35];
	ZhiDao_Servo_P = Para16s[36];
	ZhiDao_Servo_D = Para16s[37];
	WanDao_Servo_P = Para16s[38];
	WanDao_Servo_D = Para16s[39];
	MOTOR_P = Para16s[40];
	MOTOR_I = Para16s[41];
	PWM_duoji = Para16s[42];
	Ser_Debug_Enable = Para16s[43];
	SerMid_Debug = Para16s[44];
	ServoEnable = Para16s[45];
	Mtr_Debug_Enable = Para16s[46];
	OtherCar_ZhiDaoSpeed = Para16s[47];
	OtherCar_WanDaoSpeed = Para16s[48];
	OtherCar_Real_Speed = Para16s[49];
	HMI_e_LR = Para16s[50];
	AD_Value_Cell = Para16s[51];
	AutoStart = Para16s[52];
	StartTime = Para16s[53];
	StartFlag = Para16s[54];
	NotChange = Para16s[55];
	TimerRun_EN = Para16s[56];
	TimerRun_s = Para16s[57];
	TimerRun_Time = Para16s[58];
	TimerRun_Flag = Para16s[59];
	Distance = Para16s[60];
	OC_Distance = Para16s[61];
	NB_DisCount0 = Para16s[62];
	NB_DisCount1 = Para16s[63];
	Gyro_Y_Offest = Para16s[64];
	Accel_X_Offest = Para16s[65];
	Accel_Z_Offest = Para16s[66];
	Gyro_Y = Para16s[67];
	Accel_X = Para16s[68];
	Accel_Z = Para16s[69];
	Q_angle_HMI = Para16s[70];
	Q_gyro_HMI = Para16s[71];
	R_angle_HMI = Para16s[72];
	dt_HMI = Para16s[73];
	Angle_Y = Para16s[74];
	Angle_ShuiPing = Para16s[75];
	Ramp_EN = Para16s[76];
	Ramp_possible_flag = Para16s[77];
	Ramp_up_flag = Para16s[78];
	Ramp_down_flag = Para16s[79];
	CSB_EN = Para16s[80];
	DetectD_EN = Para16s[81];
	Car_Cmd = Para16s[82];
}


//函数指针
void (*pPannelCmd[Iterm_CMD_TOTAL])(void)=
{
GUI_Sleep,
All_Test,
All_Init,
Run,
Stop,
Save_All,
Config_All,
SpeedSelect_HIGH,
SpeedSelect_MEDIUM,
SpeedSelect_LOW,
Offest_Init,
Angle_ShuiPing_get,
TC_Game,
Timer20sRun,
Delay2sDepart
};

char CMDNames[Iterm_CMD_TOTAL][ItermCMDNameLengthMax+1]=
{
"Sleep",
"ALL_Test",
"All_Init",
"RUN",
"STOP",
"SaveAll",
"ConfigAll",
"SpdHIGH",
"SpdMEDIUM",
"SpdLOW",
"GyOffInit",
"AgY_Get",
"TC_Game",
"Run_20s",
"2sDepart"
};


