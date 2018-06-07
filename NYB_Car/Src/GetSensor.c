#include "Include.h"

#define ZuoMax   1
#define ZhongMax 2
#define YouMax   3
#define ZuoMin   4
#define ZhongMin 5
#define YouMin   6       //相当于枚举了六个常变量  记录横电感最大最小值标号
/****************电感排放：三横两竖*****************/
uint16 ShiZiWanCount=0;        //十字计数变量
uint16 YiChangCount=0;         //异常计数变量
uint16 ZhiDaoCount=0;          //直道计数变量
uint16 WanDaoCount=0;          //弯道计数变量

uint8 BendOut_Flag=0;          //出弯标志
uint16 BendOutOver_Count=0;    //出弯结束
uint8 LowFlag=0;               //减速标志

uint16 ZD_count=0;             //直道计数
uint16 WD_count=0;             //弯道计数
uint16 SZ_count=0;             //十字计数
uint16 PD_count=0;             //坡道计数
uint16 ZDLose_count=0;         //直道丟线计数
uint16 WDLose_count=0;         //弯道丟线计数
uint16 Sharp_count=0;          //急弯计数
uint16 NotChange=0;            //防止路况的跳变 缓冲变量

uint8 Heng_max;                //横电感电感值最大值
uint8 Heng_min;                //横电感电感值最小值
int16  AD[5]={0};              //将电感值赋给数组 方便 处理数据
uint8  Max_AD_Num=0;           //所有电感AD最大值标号
uint8  Max_AD_Num_pre=0;       //前次所有电感AD最大值标号
uint16 Max_AD_Value=0;         //所有电感AD最大值
uint16 Max_Shu_Value=0;        //竖电感的AD最大值
uint16 Max_Heng_Value=0;       //横电感的AD最大值
int16 RoadType_ShangWeiJi=1001;   //往上位机发送的路况类型 1001代表直道 102代表弯道 3代表十字  110代表直道丢线 119代表弯道丢线
int16 RoadType_OtherCar=0;        //另一个车的路况   1001代表直道 102代表弯道 3代表十字  110代表直道丢线 119代表弯道丢线
int16  e_ShangWeiJi=0;            //小车的位置偏差
int16  e_Heng_ShangWeiJi=0;       //小车的横电感位置偏差
int16  e_Shu_ShangWeiJi=0;        //小车的竖电感位置偏差

float  ePre=0;         //拟合前次变量减小误差 滤波用
float  e_HengPre=0;;   //拟合前次变量减小误差 滤波用
float  e_ShuPre=0;     //拟合前次变量减小误差 滤波用

float  max[3][3]={{1.0,1.0,1.0},{1.0,1.0,1.0},{1.0,1.0,1.0}};  // no use
//定义一个数组
  /*max[0] 下左电感最大时 三个横电感的值
    max[1] 下中电感最大时 三个横电感的值
    max[2] 下右电感最大时 三个横电感的值*/

enum ROADTYPE RoadType = ZhiDao;        //枚举定义一个变量 RoadType 初始化为ZhiDao
enum ROADTYPE RoadType_Pre = ZhiDao;    //枚举定义一个变量 前次RoadType 初始化为ZhiDao
enum ROADTYPE RoadType_PPre = ZhiDao;   //枚举定义一个变量 前前次RoadType 初始化为ZhiDao  辅助判断

uint8 OC_Ramp_flag=0;
uint8 Ramp_flag=0;
uint8 Ramp_possible_flag=0;     //坡道标志 
uint8 Ramp_up_flag=0;
uint8 Ramp_down_flag=0;
uint16 Ramp_way=0;
#ifdef NA_Car
uint8 Ramp_EN=1;
#endif
#ifdef NB_Car
uint8 Ramp_EN=0;
#endif 
uint8 RaceAu[3]={0,0,0};                  //路况判断辅助变量    

float  e=0;	        //误差
float  e_Heng=0;	//误差   横电感
float  e_Shu=0;	        //误差   竖电感
float  eLM=0;	 //位移值    下左与下中  横电感
float  eLR=0;	 //位移值    下左与下右  横电感 
float  eMR=0;	 //位移值    下中与下右  横电感
float  e_nonfilter;   //没有滤波的位移值
float  PianYi=0.0;    //e补偿偏移量
float  e_array[50];   //定义误差数组
float  e_total;       //50*5ms = 250ms 内误差的累积
//AD原始数据
int16 AD_Value_F_L0=0; 
int16 AD_Value_F_M0=0;
int16 AD_Value_F_R0=0;
int16 AD_Value_F_FL0=0;
int16 AD_Value_F_FR0=0;
int16 AD_Value_Cell0=0;
int16 AD_Value_Key0=0;
//AD归一化数据  
int16 AD_Value_F_L=1;
int16 AD_Value_F_M=1;
int16 AD_Value_F_R=1;
int16 AD_Value_F_FL=1;
int16 AD_Value_F_FR=1;
int16 AD_Value_Cell=1; 
int16 AD_Value_Key=1;
//AD拟合前次数据 
int16 AD_Value_F_L_Pre=1;
int16 AD_Value_F_M_Pre=1;
int16 AD_Value_F_R_Pre=1;
int16 AD_Value_F_FL_Pre=1;
int16 AD_Value_F_FR_Pre=1;
//AD滤波后的数据
int16 AD_Filted_F_L=1;
int16 AD_Filted_F_M=1;
int16 AD_Filted_F_R=1;
int16 AD_Filted_F_FL=1;
int16 AD_Filted_F_FR=1;
//赛道AD最小值 理想化的值为0或者1
uint16 F_L_OFF  = 10;
uint16 F_M_OFF  = 10;
uint16 F_R_OFF  = 10;
uint16 F_FL_OFF = 10;
uint16 F_FR_OFF = 10;
//赛道AD最小值 电感垂直于导线的AD值
uint16 F_L_MAX  = 100;
uint16 F_M_MAX  = 100;
uint16 F_R_MAX  = 100;
uint16 F_FL_MAX = 100;
uint16 F_FR_MAX = 100;
//OLED按键状态 分为上下左右中
uint8 OLED_Key_Status;   //1-UP;2-DOWN;3-LEFT;4-RIGHT;5-OK

int32 F_L_M_add;//三个横电感值的和
int32 FL_FR_add;//两个竖电感值的和
int32 ALL_add;  //所有电感值的和
int32 FL_FR_dif; //竖电感的差
int16  HMI_e=0;	        //人机交互位移值
int16  HMI_e_Heng=0;	//人机交互位移值   横电感
int16  HMI_e_Shu=0;	//人机交互位移值   竖电感
int16  HMI_e_LR=0;      //仅由左右横电感计算出的误差
float  LR_LM_nihe,LR_MR_nihe,LR_LR_nihe;   //下左与下中，下左与下右，下中与下右差比和拟合的e

float absi(float data_s)       //16位绝对值函数
{
    return data_s>=0?data_s:-data_s;
}

void Add_History_e(float now)   //目标计算e的累积
{   
    uint8 Old; 
    e_array[49]=now;
    e_total=0;
    for(Old=0;Old<49;Old++)
      e_array[Old]=e_array[Old+1];
    for(Old=0;Old<49;Old++)
      e_total+=e_array[Old];
}

void AD_GetValue(void) 
{    
    AD_Value_F_L0  = adc_once(AD_L, ADC_10bit)&0x03FF;     //获取AD的当前值   横电感  左
    AD_Value_F_M0  = adc_once(AD_M, ADC_10bit)&0x03FF;     //获取AD的当前值   横电感  中
    AD_Value_F_R0  = adc_once(AD_R, ADC_10bit)&0x03FF;     //获取AD的当前值   横电感  右
    AD_Value_F_FL0 = adc_once(AD_FL, ADC_10bit)&0x03FF;    //获取AD的当前值   竖电感  左
    AD_Value_F_FR0 = adc_once(AD_FR, ADC_10bit)&0x03FF;    //获取AD的当前值   竖电感  右  
    AD_Value_Cell0 = adc_once(Cell_AD, ADC_10bit)&0x03FF;  //获取AD的当前值   电池电量 
    AD_Value_Key0  = adc_once(Key_AD, ADC_10bit)&0x03FF;   //获取AD的当前值   键值获取    
    AD_Value_Cell  = (int)((long)(AD_Value_Cell0&0x03ff)*13370/1024);  //电池电量AD转换
    AD_Value_Key   = AD_Value_Key0;
    #ifdef  MyDisplay_Enable                 
    Judge_OLEDkey_Status();    //AD按键是否按下状态判断     
    #endif
    #ifdef  KalmanFilter_Enable
    AD_F_KalmanFilter();       //将电感的AD值进行单输入单输出的卡尔曼滤波
    Filted_AD_To_One();        //将滤波后的电感AD值进行归一化
    #else   
    AD_To_One();               //归一化
    #endif
}

void AD_GetMaxValue(void)   //不断采集刷新电感AD最大值
{
    AD_GetValue();           //获取AD值
    
    if(F_L_MAX<AD_Value_F_L0)    
       F_L_MAX=AD_Value_F_L0;  
    
    if(F_M_MAX<AD_Value_F_M0)
       F_M_MAX=AD_Value_F_M0;
    
    if(F_R_MAX<AD_Value_F_R0)
       F_R_MAX=AD_Value_F_R0;
  
    if(F_FL_MAX<AD_Value_F_FL0)
       F_FL_MAX=AD_Value_F_FL0;
  
    if(F_FR_MAX<AD_Value_F_FR0)
       F_FR_MAX=AD_Value_F_FR0; 
}
  
void Filted_AD_To_One(void)  //基本公式 归一化后的值=（当前值-最小值)/(最大值-最小值)
{
       //左下电感AD归一化（1000为基准）
    if(((AD_Filted_F_L&0x03ff)-F_L_OFF)>0)
    {  
         AD_Value_F_L=(int)(((long)((AD_Filted_F_L&0x03ff)-F_L_OFF)*1000)/(F_L_MAX-F_L_OFF));
    }
    else
    {
         AD_Value_F_L=1;
    }
    //中下电感AD归一化（1000为基准）
    if(((AD_Filted_F_M&0x03ff)-F_M_OFF)>0)
    {  
         AD_Value_F_M=(int)(((long)((AD_Filted_F_M&0x03ff)-F_M_OFF)*1000)/(F_M_MAX-F_M_OFF));
    }
    else
    {
        AD_Value_F_M=1;
    }
    //右下电感AD归一化（1000为基准）
    if(((AD_Filted_F_R&0x03ff)-F_R_OFF)>0)
    {  
       AD_Value_F_R=(int)(((long)((AD_Filted_F_R&0x03ff)-F_R_OFF)*1000)/(F_R_MAX-F_R_OFF));
    }
    else
    {
       AD_Value_F_R=1;
    }
    //左上电感AD归一化（1000为基准）
    if(((AD_Filted_F_FL&0x03ff)-F_FL_OFF)>0)
    {  
       AD_Value_F_FL=(int)(((long)((AD_Filted_F_FL&0x03ff)-F_FL_OFF)*1000)/(F_FL_MAX-F_FL_OFF));
    }
    else
    {
       AD_Value_F_FL=1;
    }
    //右上电感AD归一化（1000为基准）
    if(((AD_Filted_F_FR&0x03ff)-F_FR_OFF)>0)
    {  
       AD_Value_F_FR=(int)(((long)((AD_Filted_F_FR&0x03ff)-F_FR_OFF)*1000)/(F_FR_MAX-F_FR_OFF));
    }
    else
    {
       AD_Value_F_FR=1;
    }
    
    // 限幅滤波 防止跳变
    if (absi(AD_Filted_F_L-AD_Value_F_L_Pre)>800)   AD_Value_F_L=AD_Value_F_L_Pre;   
    if (absi(AD_Filted_F_M-AD_Value_F_M_Pre)>800)   AD_Value_F_M=AD_Value_F_M_Pre;
    if (absi(AD_Filted_F_R-AD_Value_F_R_Pre)>800)   AD_Value_F_R=AD_Value_F_R_Pre;
    if (absi(AD_Filted_F_FL-AD_Value_F_FL_Pre)>800) AD_Value_F_L=AD_Value_F_FL_Pre;
    if (absi(AD_Filted_F_FR-AD_Value_F_FR_Pre)>800) AD_Value_F_L=AD_Value_F_FR_Pre;
    
    AD_Value_F_L_Pre=AD_Filted_F_L;
    AD_Value_F_M_Pre=AD_Filted_F_M;
    AD_Value_F_R_Pre=AD_Filted_F_R;
    AD_Value_F_FL_Pre=AD_Filted_F_FL;
    AD_Value_F_FR_Pre=AD_Filted_F_FR; 
}

void AD_To_One(void)
{
       //左下电感AD归一化（1000为基准）
    if(((AD_Value_F_L0&0x03ff)-F_L_OFF)>0)
    {  
         AD_Value_F_L=(int)(((long)((AD_Value_F_L0&0x03ff)-F_L_OFF)*1000)/(F_L_MAX-F_L_OFF));
    }
    else
    {
         AD_Value_F_L=1;
    }
    //中下电感AD归一化（1000为基准）
    if(((AD_Value_F_M0&0x03ff)-F_M_OFF)>0)
    {  
         AD_Value_F_M=(int)(((long)((AD_Value_F_M0&0x03ff)-F_M_OFF)*1000)/(F_M_MAX-F_M_OFF));
    }
    else
    {
        AD_Value_F_M=1;
    }
    //右下电感AD归一化（1000为基准）
    if(((AD_Value_F_R0&0x03ff)-F_R_OFF)>0)
    {  
      AD_Value_F_R=(int)(((long)((AD_Value_F_R0&0x03ff)-F_R_OFF)*1000)/(F_R_MAX-F_R_OFF));
    }
    else
    {
      AD_Value_F_R=1;
    }
    //左上电感AD归一化（1000为基准）
    if(((AD_Value_F_FL0&0x03ff)-F_FL_OFF)>0)
    {  
      AD_Value_F_FL=(int)(((long)((AD_Value_F_FL0&0x03ff)-F_FL_OFF)*1000)/(F_FL_MAX-F_FL_OFF));
    }
    else
    {
      AD_Value_F_FL=1;
    }
    //右上电感AD归一化（1000为基准）
    if(((AD_Value_F_FR0&0x03ff)-F_FR_OFF)>0)
    {  
       AD_Value_F_FR=(int)(((long)((AD_Value_F_FR0&0x03ff)-F_FR_OFF)*1000)/(F_FR_MAX-F_FR_OFF));
    }
    else
    {
       AD_Value_F_FR=1;
    }
    
    // 限幅滤波 防止跳变
    if (absi(AD_Value_F_L-AD_Value_F_L_Pre)>800)   AD_Value_F_L=AD_Value_F_L_Pre;   
    if (absi(AD_Value_F_M-AD_Value_F_M_Pre)>800)   AD_Value_F_M=AD_Value_F_M_Pre;
    if (absi(AD_Value_F_R-AD_Value_F_R_Pre)>800)   AD_Value_F_R=AD_Value_F_R_Pre;
    if (absi(AD_Value_F_FL-AD_Value_F_FL_Pre)>800) AD_Value_F_L=AD_Value_F_FL_Pre;
    if (absi(AD_Value_F_FR-AD_Value_F_FR_Pre)>800) AD_Value_F_L=AD_Value_F_FR_Pre;
   
    AD_Value_F_L_Pre=AD_Value_F_L;
    AD_Value_F_M_Pre=AD_Value_F_M;
    AD_Value_F_R_Pre=AD_Value_F_R;
    AD_Value_F_FL_Pre=AD_Value_F_FL;
    AD_Value_F_FR_Pre=AD_Value_F_FR; 
}



void New_AnalysisDecision(void)  //分析赛道
{  
   New_Cal_FtoE();                //将电感值计算成误差
   New_Judge_RoadType();          //分析赛道
   New_MakeDecision();            //误差调整 直道弯道参数调整
}

void New_Cal_FtoE(void)
{  
   int i;
   AD[0]=AD_Value_F_L;     //电感值编号
   AD[1]=AD_Value_F_M;
   AD[2]=AD_Value_F_R;
   AD[3]=AD_Value_F_FL;
   AD[4]=AD_Value_F_FR;
   for(i=0;i<4;i++)       //求电感最大值标号
   {
     if(AD[Max_AD_Num]<AD[i]-1)
       Max_AD_Num=i;
   }
   Max_AD_Value=AD[Max_AD_Num]; //电感最大值
   Max_Shu_Value=(AD[3]>AD[4])?AD[3]:AD[4]; //竖电感最大值
      //判断哪个横电感最小，最大 求其标号和值
   if(AD_Value_F_L>AD_Value_F_M && AD_Value_F_L>AD_Value_F_R)
   {
      Heng_max=ZuoMax;
      if(AD_Value_F_M>AD_Value_F_R)
      {
         Heng_min=YouMin;
      }
      else
      {
         Heng_min=ZhongMin;
      }
      Max_Heng_Value=AD_Value_F_L;
    }
    else if(AD_Value_F_M>AD_Value_F_L && AD_Value_F_M>AD_Value_F_R)
    {
         Heng_max=ZhongMax;
         if(AD_Value_F_L>AD_Value_F_R)
         {
            Heng_min=YouMin;
         }
         else
         {
            Heng_min=ZuoMin;
         }
         Max_Heng_Value=AD_Value_F_M;
    }
    else
    {
        Heng_max=YouMax;
        if(AD_Value_F_M>AD_Value_F_L)
        {
           Heng_min=ZuoMin;
        }
        else
        {
           Heng_min=ZhongMin;
        }
        Max_Heng_Value=AD_Value_F_R;
   }    
   
   F_L_M_add = AD_Value_F_L+AD_Value_F_M+AD_Value_F_R;  //横电感的和
   FL_FR_add = AD_Value_F_FL +AD_Value_F_FR;            //竖电感的和
   ALL_add    = F_L_M_add + FL_FR_add;                  //所有电感的和
   FL_FR_dif = AD_Value_F_FR - AD_Value_F_FL;           //竖电感的差
   //限幅防止出错
   if(F_L_M_add<1)  F_L_M_add=1;
   if(FL_FR_add<1)  FL_FR_add=1;
   if(ALL_add<1)    ALL_add=1;
   
   //(L-R)/(L+R)法求拟合偏差  差比和将非线性量拟合成线性量  通过EXCEL线性回归拟合得到
#ifdef  NA_Car    
   eLM=(float)((AD_Value_F_L)-(AD_Value_F_M))*1000/((AD_Value_F_L)+(AD_Value_F_M));
   LR_LM_nihe = -0.5953*eLM -90.996;
  
   eLR=(float)((AD_Value_F_L)-(AD_Value_F_R))*1000/((AD_Value_F_L)+(AD_Value_F_R));
   LR_LR_nihe = -0.289*eLR +0.1365;
  
   eMR=(float)((AD_Value_F_M)-(AD_Value_F_R))*1000/((AD_Value_F_M)+(AD_Value_F_R));
   LR_MR_nihe = -0.4397*eMR +65.115;
   
#endif 
#ifdef  NB_Car    
   eLM=(float)((AD_Value_F_L)-(AD_Value_F_M))*1000/((AD_Value_F_L)+(AD_Value_F_M));
   LR_LM_nihe = -0.4101*eLM - 77.148;

   eLR=(float)((AD_Value_F_L)-(AD_Value_F_R))*1000/((AD_Value_F_L)+(AD_Value_F_R));
   LR_LR_nihe = -0.2455*eLR + 7.3208;

   eMR=(float)((AD_Value_F_M)-(AD_Value_F_R))*1000/((AD_Value_F_M)+(AD_Value_F_R));
   LR_MR_nihe = -0.3837*eMR + 86.265;
   e_Heng =  LR_LR_nihe;  //求三个拟合的平均值 减小误差  求的横电感的差
#endif 
   e_Heng = LR_LM_nihe/3 + LR_LR_nihe/3 + LR_MR_nihe/3;  //求三个拟合的平均值 减小误差  求的横电感的差
   //限幅滤波
   if((e_Heng-e_HengPre)>500 || (e_Heng-e_HengPre)<-500 ||e_Heng>800)     
   {
        e_Heng=e_HengPre; 
   }
   e_HengPre=e_Heng;
  
   e_Shu =(float)((AD_Value_F_FR)-(AD_Value_F_FL))*200/((AD_Value_F_FR)+(AD_Value_F_FL));   //竖电感的差比和
   //限幅滤波
   if((e_Shu-e_ShuPre)>700 || (e_Shu-e_ShuPre)<-700 ||e_Shu>800)
   {
       e_Shu=e_ShuPre;
   }
   e_ShuPre=e_Shu;  
}

void New_Judge_RoadType(void)
{
    if(Mtr_Debug_Enable==0)
    {  
       if(NotChange>5)   //防跳变  25MS内 不允许连续改变RoadType 时间太长 太短 都会误判
       {
          if(RoadType_Pre == ZhiDao)
          {
              if(((AD_Value_F_FL>718)||(AD_Value_F_FR>718))&&F_L_M_add>1300)
              {
                 RoadType=ShiZiWan;
              }
              else if(ALL_add>4400)
              {
                  RoadType=ShiZiWan; 
              }
              else if((Ramp_EN>=1)&&(AD_Value_F_M>1800||(AD_Value_F_L>1199&&AD_Value_F_R>1199)))
              {   
                  RoadType=PoDao;
              }
              else if(F_L_M_add<688&&FL_FR_add<200)
              {   
                  RoadType=ZD_Lose;
              }
              else if(F_L_M_add<899&&FL_FR_add<666)
              {
                  RoadType=ZD_Lose;
              }
              else if(((AD_Value_F_FL>120)||(AD_Value_F_FR>120)))
              {
                  RoadType=WanDao;
              }
              else 
                  RoadType=ZhiDao;
          }
          else if(RoadType_Pre == WanDao)
          {
              if(ALL_add>4400)
              {
                 RoadType=ShiZiWan; 
              }
              else if(((AD_Value_F_FL>880)||(AD_Value_F_FR>880))&&F_L_M_add>1000&&absi(FL_FR_dif)<170)
              {
                  RoadType=ShiZiWan;
              }
              /*else if(((AD_Value_F_FL>720)||(AD_Value_F_FR>720))&&F_L_M_add>1700&&absi(FL_FR_dif)<150)
              {
                  RoadType=ShiZiWan;
              }*/
#ifdef NA_Car
              else if(Max_AD_Value<330||Max_Heng_Value<330||F_L_M_add<1149)
#endif
#ifdef NB_Car
              else if(Max_AD_Value<330||Max_Heng_Value<330||F_L_M_add<1009)  
#endif
              {
                  RoadType=WD_Lose;
              }
              /*else if(Heng_max!=ZhongMax)
              {
                  if(Max_Heng_Value<800)
                    RoadType=WD_Lose;
              }*/
              else if(Max_Shu_Value>700&&F_L_M_add<1645&&(absi(e_Shu)>30))
              {
                   RoadType=SharpWan; 
              }                
              else if((absi(AD[3]-AD[4])>160)&&Max_Shu_Value>400&&(absi(e_Shu)>30)&&(F_L_M_add<1650))
              {
                  RoadType=SharpWan;
              }
              else if(((AD_Value_F_FL>124)||(AD_Value_F_FR>124)))
              {
                  RoadType=WanDao;
              }                      
              else if((FL_FR_add<350)&&(absi(e)<145)&&(AD_Value_F_L>200||AD_Value_F_R>200)&&F_L_M_add>1200)
              {
                  RoadType=ZhiDao;
              }            
              else   
                  RoadType=WanDao;          
          }
          else if(RoadType_Pre == ShiZiWan)
          {    
              if(ALL_add>6600)
              {
                   RoadType=ShiZiWan; 
              } 
              else if((Ramp_EN>=1)&&(AD_Value_F_M>1800||(AD_Value_F_L>1199&&AD_Value_F_R>1199)))
              {   
                      RoadType=PoDao;
              }
              else if(((AD_Value_F_FL>738)||(AD_Value_F_FR>738))&&F_L_M_add>1300)
              {
                   RoadType=ShiZiWan;
              }    
              else 
                   RoadType=ZhiDao;
           }
           else if(RoadType_Pre == SharpWan)
           {  
              if(ALL_add>4400)
              {
                 RoadType=ShiZiWan; 
              }
              else if(((AD_Value_F_FL>880)||(AD_Value_F_FR>880))&&F_L_M_add>1000&&absi(FL_FR_dif)<170)
              {
                  RoadType=ShiZiWan;
              }
              else if(F_L_M_add<988)
              {
                 RoadType=WD_Lose;
              }
              else if(Max_AD_Value<400||F_L_M_add<1000)
              {
                 RoadType=SharpWan; 
              }
              else if((absi(AD[3]-AD[4])>150)&&Max_Shu_Value>380&&(absi(e_Shu)>25)&&(F_L_M_add<1800))
              {
                  RoadType=SharpWan;
              }
              else if(absi(AD[3]-AD[4])>321)
              {
                  RoadType=SharpWan;  
              }
              else if((absi(e)<300)&&(AD_Value_F_L>200||AD_Value_F_R>200)&&F_L_M_add>1500)
              {
                  RoadType=ZhiDao;
              }
              else if(F_L_M_add>1500)
              {
                  RoadType=WanDao;
              }
              else
                  RoadType=SharpWan;
           }
           else if(RoadType_Pre == ZD_Lose)
           {  
              if(F_L_M_add>999)
              { 
                  RoadType=ZhiDao;
              }
              else
              {
              if((RaceAu[0]+RaceAu[1]+RaceAu[2])>=2)   //对弯道丢线的强判断
                 RoadType=WD_Lose;
              else
                 RoadType=ZD_Lose;
              }
          }
          else if(RoadType_Pre == WD_Lose)
          {
               if(F_L_M_add>1100)
               { 
                   RoadType=WanDao;
               }
               else
                   RoadType=WD_Lose;
               }
          } 
          else if(RoadType_Pre == PoDao)
          {
               if(Ramp_EN>=1)
               {    
                    RoadType=PoDao;
               }
          }
          /*else if(RoadType_Pre==YiChang)
          {
              if((AD_Value_F_L+AD_Value_F_M+AD_Value_F_M+AD_Value_F_R+AD_Value_F_FR)<8&&Real_Speed<6)
                
              else
                RoadType=YiChang;  
          }
          else if((AD_Value_F_L+AD_Value_F_M+AD_Value_F_M+AD_Value_F_R+AD_Value_F_FR)<8&&Real_Speed<6)
              RoadType=YiChang;*/
       }
       else
          RoadType=ZhiDao;
       if(ShangWeiJiStop==1)
       {  
          if(RoadType == ZhiDao && RoadType_Pre == ZhiDao && RoadType_PPre == ZhiDao)
          {
               ZD_count++;              
                //if(Race==ClockWise)
                // PianYi=-ZD_count/8.0;
                // else
                //PianYi= ZD_count/8.0;
               if(ZD_count>1000)
               {
                  ZD_count=0;
                  PianYi=0.0;
               }
          }
          else
          {
              ZD_count=0;
              PianYi=0.0;              
          }
         if(RoadType==WanDao&&RoadType_Pre==WanDao) 
         {   
             WD_count++; 
             if(WD_count>10000)
             {   
                WD_count=0;
             }
         }
         else 
         {
              LowFlag=0;
              WD_count=0;            
         }
         if((RoadType==WD_Lose&&RoadType_Pre==WD_Lose))
         {    
              WDLose_count++;
              if(WDLose_count>10000)
                WDLose_count=0;
         }
         else
         {
              WDLose_count=0;
         }
         if((RoadType==ZD_Lose&&RoadType_Pre==ZD_Lose))
         {    
              ZDLose_count++; 
              if(ZDLose_count>10000)
                ZDLose_count=0;
         }
         else
         {
              ZDLose_count=0;
         }
         if((RoadType==ShiZiWan&&RoadType_Pre==ShiZiWan))
         { 
              SZ_count++; 
              if(SZ_count>10000)
                SZ_count=0;
         }
         else
         {
                           
         }
         if(RoadType_Pre==SharpWan&&RoadType==SharpWan)
         { 
             Sharp_count++;
             if(Sharp_count>10000)
                Sharp_count=0;
         }
         else
         {
               
         }
         if(RoadType_Pre==PoDao&&RoadType==PoDao)
         { 
             PD_count++;
             if(PD_count>10000)
                PD_count=0;
             Ramp_flag=1;
             if(PD_count>666)
             {   
                 RoadType=ZhiDao;
                 
             }
         }
         else
         {
             Ramp_flag=0;
             PD_count=0;
         }
         if((RoadType_Pre==SharpWan||RoadType_Pre==WanDao)&&RoadType==ZhiDao)
         {
           BendOut_Flag=1;         
         }
         if(BendOut_Flag==1)
            BendOutOver_Count++;
         if(BendOutOver_Count>180)
         {
            BendOut_Flag=0;
            BendOutOver_Count=0;
         }
       }
       else
       {   
           PD_count=0;
           WD_count=0;
           ZD_count=0;
           SZ_count=0;
           ZDLose_count=0;
           WDLose_count=0;
           Sharp_count=0;
           BendOut_Flag=0;
           BendOutOver_Count=0;
       }           
     if(RoadType_Pre==RoadType)  
     {
           NotChange++;
           if(NotChange>10000)
              NotChange=0;
           switch (RoadType)   //丟线强判断分析 仅考虑直道变弯道时
           {    
           case ZhiDao  : RaceAu[0]=0;break;
           case WanDao  : RaceAu[0]=2;break;
           case ShiZiWan: RaceAu[0]=2;break;
           case SharpWan: RaceAu[0]=2;break;
           case YiChang : ;break;
           case PoDao   : ;break;
           case ZD_Lose : RaceAu[0]=0;break;
           case WD_Lose : RaceAu[0]=2;break;  
           }
     } 
     else
     {
           NotChange=0;
           RaceAu[2]=RaceAu[1];
           RaceAu[1]=RaceAu[0];
           RaceAu[0]=0;
     }
     RoadType_PPre = RoadType_Pre;
     RoadType_Pre = RoadType;   
}

void New_MakeDecision(void)
{
    if(RoadType == ZhiDao)
    {
       e=e_Heng-PianYi;
       e = 0.2 * e + 0.8 * ePre;
       ePre=e;
       RoadType_ShangWeiJi=1001;
       Servo_D=ZhiDao_Servo_D;
       Servo_P=ZhiDao_Servo_P;
       
    }
    else if(RoadType == ShiZiWan)
    {    
         e=e_Heng-PianYi; 
         e = 0.2 * e + 0.8 * ePre;
         ePre=e;
         Servo_D=ZhiDao_Servo_D;
         Servo_P=ZhiDao_Servo_P;
    }
    else if(RoadType == WanDao)
    {        
       if((absi(AD[3]-AD[4])>180)&&Max_Shu_Value>250&&(absi(e_Shu)>30)&&F_L_M_add<1796)  //注意这里
       {
          if(e_Shu>10&&absi(e_Heng<180))
          {
            e_Heng=(e_Heng>0)?e_Heng:-e_Heng;
            // e=0.120*e_Heng-PianYi+1.5*e_Shu;
            //if(F_L_M_add<=2000&&F_L_M_add>1444)
            if(F_L_M_add<=2000)
               e=0.550*e_Heng-PianYi+1.2*e_Shu+HengWanDao_Deta*2000.0/F_L_M_add;
            //else if(F_L_M_add<=1444)
               //e=0.550*e_Heng-PianYi+1.2*e_Shu+HengWanDao_Deta2*2000.0/F_L_M_add; 
            else
               e=0.550*e_Heng-PianYi+1.2*e_Shu;
          } 
          else if(e_Shu<-10&&absi(e_Heng<180))            
          {
            e_Heng=(e_Heng<0)?e_Heng:-e_Heng; 
            //e=0.120*e_Heng-PianYi+1.5*e_Shu;
            //if(F_L_M_add<=2000&&F_L_M_add>1444)
            if(F_L_M_add<=2000)
            e=0.550*e_Heng-PianYi+1.2*e_Shu-HengWanDao_Deta*2000.0/F_L_M_add;
            //else if(F_L_M_add<=1444)
               //e=0.550*e_Heng-PianYi+1.2*e_Shu-HengWanDao_Deta2*2000.0/F_L_M_add;
            else
               e=0.550*e_Heng-PianYi+1.2*e_Shu;
          }
          else if(e_Heng>0)
          {   
           e_Shu=(e_Shu>0)?e_Shu:-e_Shu; 
           e=1.1*e_Heng-PianYi;
          }
          else if(e_Heng<0)
          {   
           e_Shu=(e_Shu<0)?e_Shu:-e_Shu;
           e=1.1*e_Heng-PianYi;
          }   
       }
       else 
          e=e_Heng-PianYi;
       e = 0.2 * e + 0.8 * ePre;
       ePre=e;      
       RoadType_ShangWeiJi=102; 
       Servo_D=WanDao_Servo_D;
       Servo_P=WanDao_Servo_P;              
    }
    else if(RoadType == ZD_Lose)
    {    
        if(e> 20&&e<= 180)    e= 180;         
        if(e<-20&&e>=-180)    e=-180;
        e = 0.2 * e + 0.8 * ePre;
        ePre=e;
        Servo_D=ZhiDao_Servo_D+30;
        Servo_P=ZhiDao_Servo_P*2-15;
    }
    else if(RoadType == WD_Lose)
    {   
        if(e> 50&&e<= 210)   e= 210;         
        if(e<-50&&e>=-210)   e=-210;
        if(absi(e)<=50)
        {
            if(e_total<0)
              e=-180;
            else
              e=180;
        }
        e = 0.2 * e + 0.8 * ePre;
        ePre=e;
        Servo_D=WanDao_Servo_D+60;
        Servo_P=WanDao_Servo_P+50;
    } 
    else if(RoadType == SharpWan)      
    {           
          if(e_Shu>10&&absi(e_Heng<100))
          {
            e_Heng=(e_Heng>0)?e_Heng:-e_Heng;
            // e=0.120*e_Heng-PianYi+1.5*e_Shu;
            //if(F_L_M_add<=2000&&F_L_M_add>1444)
            if(F_L_M_add<=2000)
               e=0.750*e_Heng-PianYi+1.2*e_Shu+HengWanDao_Deta*2000.0/F_L_M_add;
            //else if(F_L_M_add<=1444)
               //e=0.550*e_Heng-PianYi+1.2*e_Shu+HengWanDao_Deta2*2000.0/F_L_M_add; 
            else
               e=0.750*e_Heng-PianYi+1.2*e_Shu;
          } 
          else if(e_Shu<-10&&absi(e_Heng<100))            
          {
            e_Heng=(e_Heng<0)?e_Heng:-e_Heng; 
            //e=0.120*e_Heng-PianYi+1.5*e_Shu;
            //if(F_L_M_add<=2000&&F_L_M_add>1444)
            if(F_L_M_add<=2000)
            e=0.750*e_Heng-PianYi+1.2*e_Shu-18*2000.0/F_L_M_add;
            //else if(F_L_M_add<=1444)
               //e=0.550*e_Heng-PianYi+1.2*e_Shu-HengWanDao_Deta2*2000.0/F_L_M_add;
            else
               e=0.550*e_Heng-PianYi+1.2*e_Shu;
          }
          else if(e_Heng>0)
          {   
           e_Shu=(e_Shu>0)?e_Shu:-e_Shu; 
           e=0.650*e_Heng-PianYi+1.2*e_Shu;
          }
          else if(e_Heng<0)
          {   
           e_Shu=(e_Shu<0)?e_Shu:-e_Shu;
           e=0.650*e_Heng-PianYi+1.2*e_Shu;
          }   
       
        else 
           e=e_Heng-PianYi;
        e = 0.2 * e + 0.8 * ePre;
        ePre=e;  
#ifdef NA_Car
        Servo_D=WanDao_Servo_D+100;
        Servo_P=WanDao_Servo_P+44;
#endif
#ifdef NB_Car
        Servo_D=WanDao_Servo_D;
        Servo_P=WanDao_Servo_P; 
#endif 
    }
    else if(RoadType == PoDao)
    {   
        e=LR_LR_nihe-PianYi;
        e = 0.2 * e + 0.8 * ePre;
        ePre=e;
        Servo_D=ZhiDao_Servo_D-40;
        Servo_P=ZhiDao_Servo_P-40;
    }
       //e限幅
    if(e>e_pRefine) e=e_pRefine;
    if(e<e_dRefine) e=e_dRefine;
          
    HMI_e=(int)e;	        
    HMI_e_Heng=(int)e_Heng;	
    HMI_e_Shu=(int)e_Shu;
    HMI_e_LR=(int)LR_LR_nihe;
    e_Heng_ShangWeiJi=(int)e_Heng;
    e_Shu_ShangWeiJi = (int)e_Shu;
    e_ShangWeiJi=(int)e;
    Add_History_e(e);
}



