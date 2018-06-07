#ifndef _GETSENSOR_H
#define _GETSENSOR_H

/*********AD按键各值宏定义*********/   
#define Key_UP_Value     92
#define Key_DOWN_Value   924
#define Key_LEFT_Value   511
#define Key_RIGHT_Value  672
#define Key_OK_Value     340
/*********AD按键状态标号宏定义*********/
#define  NO     0
#define  RIGHT  1
#define  DOWN   2
#define  LEFT   3
#define  UP     4
#define  OK     5

/**********函数外部声明**************/
extern void AD_GetValue(void);
extern void AD_GetMaxValue(void);
extern void AnalysisDecision(void); 
extern void New_AnalysisDecision(void);
extern float absi(float data_s);       //16位绝对值函数


void MakeDecision(void);
void Cal_FtoE(void);
void Judge_RoadType(void);
void New_Judge_RoadType(void);
void New_MakeDecision(void);
void New_Cal_FtoE(void);

void AD_To_One(void);
void Filted_AD_To_One(void);
void ADC0_IRQHandler(void);
/**************枚举路况类型*************/
enum ROADTYPE { 
  ZhiDao,                
  WanDao,                                            
  ShiZiWan,
  PoDao,
  YiChang,
  SharpWan,
  ZD_Lose,
  WD_Lose,   
};

extern int32 F_L_M_add;//三个横电感值的和
extern int32 FL_FR_add;//两个竖电感值的和
extern int32 ALL_add;  //所有电感值的和
extern uint16 ZhiDaoCount;      //直道计数  每进入一次变量+1
extern uint16 WanDaoCount;      //弯道计数
extern uint16 YiChangCount;     //异常计数
extern uint16 ShiZiWanCount;    //十字弯计数

extern int16 AD_Value_F_L0;
extern int16 AD_Value_F_M0;
extern int16 AD_Value_F_R0;
extern int16 AD_Value_F_FL0;
extern int16 AD_Value_F_FR0;
extern int16 AD_Value_Key0;

extern uint16 F_L_MAX  ;
extern uint16 F_M_MAX  ;
extern uint16 F_R_MAX  ;
extern uint16 F_FL_MAX ;
extern uint16 F_FR_MAX ;

extern uint16 F_L_OFF  ;
extern uint16 F_M_OFF  ;
extern uint16 F_R_OFF  ;
extern uint16 F_FL_OFF ;
extern uint16 F_FR_OFF ;

extern int16 AD_Filted_F_L;
extern int16 AD_Filted_F_M;
extern int16 AD_Filted_F_R;
extern int16 AD_Filted_F_FL;
extern int16 AD_Filted_F_FR;

extern int16 AD_Value_F_L;
extern int16 AD_Value_F_M;
extern int16 AD_Value_F_R;
extern int16 AD_Value_F_FL;
extern int16 AD_Value_F_FR;
extern int16 AD_Value_Cell; 
extern int16 AD_Value_Key;

extern uint16 ShiZiWanCount;
extern uint16 YiChangCount;
extern uint16 ZhiDaoCount;
extern uint16 WanDaoCount;

extern float  max[3][3];
extern float  e;                 //小车位置偏差
extern float  e_Heng;	//位移值   横电感
extern float  e_Shu;	        //位移值   竖电感
extern enum ROADTYPE RoadType;
extern enum ROADTYPE RoadType_Pre;  //前次路况
extern uint8 OLED_Key_Status;
extern uint8 BendOut_Flag;
extern uint8 LowFlag;
extern uint8 OC_Ramp_flag;
extern uint8 Ramp_flag;
extern uint8 Ramp_possible_flag;//坡道标志 
extern uint8 Ramp_up_flag;
extern uint8 Ramp_down_flag;
extern uint8 Ramp_EN;
extern uint16 Ramp_way;

#define HengWanDao_Deta 30
#define HengWanDao_Deta2 58
#define e_pRefine  350.0
#define e_dRefine -350.0

#endif