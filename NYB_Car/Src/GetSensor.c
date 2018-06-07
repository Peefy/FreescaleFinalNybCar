#include "Include.h"

#define ZuoMax   1
#define ZhongMax 2
#define YouMax   3
#define ZuoMin   4
#define ZhongMin 5
#define YouMin   6       //�൱��ö��������������  ��¼���������Сֵ���
/****************����ŷţ���������*****************/
uint16 ShiZiWanCount=0;        //ʮ�ּ�������
uint16 YiChangCount=0;         //�쳣��������
uint16 ZhiDaoCount=0;          //ֱ����������
uint16 WanDaoCount=0;          //�����������

uint8 BendOut_Flag=0;          //�����־
uint16 BendOutOver_Count=0;    //�������
uint8 LowFlag=0;               //���ٱ�־

uint16 ZD_count=0;             //ֱ������
uint16 WD_count=0;             //�������
uint16 SZ_count=0;             //ʮ�ּ���
uint16 PD_count=0;             //�µ�����
uint16 ZDLose_count=0;         //ֱ���G�߼���
uint16 WDLose_count=0;         //����G�߼���
uint16 Sharp_count=0;          //�������
uint16 NotChange=0;            //��ֹ·�������� �������

uint8 Heng_max;                //���е��ֵ���ֵ
uint8 Heng_min;                //���е��ֵ��Сֵ
int16  AD[5]={0};              //�����ֵ�������� ���� ��������
uint8  Max_AD_Num=0;           //���е��AD���ֵ���
uint8  Max_AD_Num_pre=0;       //ǰ�����е��AD���ֵ���
uint16 Max_AD_Value=0;         //���е��AD���ֵ
uint16 Max_Shu_Value=0;        //����е�AD���ֵ
uint16 Max_Heng_Value=0;       //���е�AD���ֵ
int16 RoadType_ShangWeiJi=1001;   //����λ�����͵�·������ 1001����ֱ�� 102������� 3����ʮ��  110����ֱ������ 119�����������
int16 RoadType_OtherCar=0;        //��һ������·��   1001����ֱ�� 102������� 3����ʮ��  110����ֱ������ 119�����������
int16  e_ShangWeiJi=0;            //С����λ��ƫ��
int16  e_Heng_ShangWeiJi=0;       //С���ĺ���λ��ƫ��
int16  e_Shu_ShangWeiJi=0;        //С���������λ��ƫ��

float  ePre=0;         //���ǰ�α�����С��� �˲���
float  e_HengPre=0;;   //���ǰ�α�����С��� �˲���
float  e_ShuPre=0;     //���ǰ�α�����С��� �˲���

float  max[3][3]={{1.0,1.0,1.0},{1.0,1.0,1.0},{1.0,1.0,1.0}};  // no use
//����һ������
  /*max[0] ���������ʱ �������е�ֵ
    max[1] ���е�����ʱ �������е�ֵ
    max[2] ���ҵ�����ʱ �������е�ֵ*/

enum ROADTYPE RoadType = ZhiDao;        //ö�ٶ���һ������ RoadType ��ʼ��ΪZhiDao
enum ROADTYPE RoadType_Pre = ZhiDao;    //ö�ٶ���һ������ ǰ��RoadType ��ʼ��ΪZhiDao
enum ROADTYPE RoadType_PPre = ZhiDao;   //ö�ٶ���һ������ ǰǰ��RoadType ��ʼ��ΪZhiDao  �����ж�

uint8 OC_Ramp_flag=0;
uint8 Ramp_flag=0;
uint8 Ramp_possible_flag=0;     //�µ���־ 
uint8 Ramp_up_flag=0;
uint8 Ramp_down_flag=0;
uint16 Ramp_way=0;
#ifdef NA_Car
uint8 Ramp_EN=1;
#endif
#ifdef NB_Car
uint8 Ramp_EN=0;
#endif 
uint8 RaceAu[3]={0,0,0};                  //·���жϸ�������    

float  e=0;	        //���
float  e_Heng=0;	//���   ����
float  e_Shu=0;	        //���   �����
float  eLM=0;	 //λ��ֵ    ����������  ����
float  eLR=0;	 //λ��ֵ    ����������  ���� 
float  eMR=0;	 //λ��ֵ    ����������  ����
float  e_nonfilter;   //û���˲���λ��ֵ
float  PianYi=0.0;    //e����ƫ����
float  e_array[50];   //�����������
float  e_total;       //50*5ms = 250ms �������ۻ�
//ADԭʼ����
int16 AD_Value_F_L0=0; 
int16 AD_Value_F_M0=0;
int16 AD_Value_F_R0=0;
int16 AD_Value_F_FL0=0;
int16 AD_Value_F_FR0=0;
int16 AD_Value_Cell0=0;
int16 AD_Value_Key0=0;
//AD��һ������  
int16 AD_Value_F_L=1;
int16 AD_Value_F_M=1;
int16 AD_Value_F_R=1;
int16 AD_Value_F_FL=1;
int16 AD_Value_F_FR=1;
int16 AD_Value_Cell=1; 
int16 AD_Value_Key=1;
//AD���ǰ������ 
int16 AD_Value_F_L_Pre=1;
int16 AD_Value_F_M_Pre=1;
int16 AD_Value_F_R_Pre=1;
int16 AD_Value_F_FL_Pre=1;
int16 AD_Value_F_FR_Pre=1;
//AD�˲��������
int16 AD_Filted_F_L=1;
int16 AD_Filted_F_M=1;
int16 AD_Filted_F_R=1;
int16 AD_Filted_F_FL=1;
int16 AD_Filted_F_FR=1;
//����AD��Сֵ ���뻯��ֵΪ0����1
uint16 F_L_OFF  = 10;
uint16 F_M_OFF  = 10;
uint16 F_R_OFF  = 10;
uint16 F_FL_OFF = 10;
uint16 F_FR_OFF = 10;
//����AD��Сֵ ��д�ֱ�ڵ��ߵ�ADֵ
uint16 F_L_MAX  = 100;
uint16 F_M_MAX  = 100;
uint16 F_R_MAX  = 100;
uint16 F_FL_MAX = 100;
uint16 F_FR_MAX = 100;
//OLED����״̬ ��Ϊ����������
uint8 OLED_Key_Status;   //1-UP;2-DOWN;3-LEFT;4-RIGHT;5-OK

int32 F_L_M_add;//��������ֵ�ĺ�
int32 FL_FR_add;//���������ֵ�ĺ�
int32 ALL_add;  //���е��ֵ�ĺ�
int32 FL_FR_dif; //����еĲ�
int16  HMI_e=0;	        //�˻�����λ��ֵ
int16  HMI_e_Heng=0;	//�˻�����λ��ֵ   ����
int16  HMI_e_Shu=0;	//�˻�����λ��ֵ   �����
int16  HMI_e_LR=0;      //�������Һ��м���������
float  LR_LM_nihe,LR_MR_nihe,LR_LR_nihe;   //���������У����������ң����������Ҳ�Ⱥ���ϵ�e

float absi(float data_s)       //16λ����ֵ����
{
    return data_s>=0?data_s:-data_s;
}

void Add_History_e(float now)   //Ŀ�����e���ۻ�
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
    AD_Value_F_L0  = adc_once(AD_L, ADC_10bit)&0x03FF;     //��ȡAD�ĵ�ǰֵ   ����  ��
    AD_Value_F_M0  = adc_once(AD_M, ADC_10bit)&0x03FF;     //��ȡAD�ĵ�ǰֵ   ����  ��
    AD_Value_F_R0  = adc_once(AD_R, ADC_10bit)&0x03FF;     //��ȡAD�ĵ�ǰֵ   ����  ��
    AD_Value_F_FL0 = adc_once(AD_FL, ADC_10bit)&0x03FF;    //��ȡAD�ĵ�ǰֵ   �����  ��
    AD_Value_F_FR0 = adc_once(AD_FR, ADC_10bit)&0x03FF;    //��ȡAD�ĵ�ǰֵ   �����  ��  
    AD_Value_Cell0 = adc_once(Cell_AD, ADC_10bit)&0x03FF;  //��ȡAD�ĵ�ǰֵ   ��ص��� 
    AD_Value_Key0  = adc_once(Key_AD, ADC_10bit)&0x03FF;   //��ȡAD�ĵ�ǰֵ   ��ֵ��ȡ    
    AD_Value_Cell  = (int)((long)(AD_Value_Cell0&0x03ff)*13370/1024);  //��ص���ADת��
    AD_Value_Key   = AD_Value_Key0;
    #ifdef  MyDisplay_Enable                 
    Judge_OLEDkey_Status();    //AD�����Ƿ���״̬�ж�     
    #endif
    #ifdef  KalmanFilter_Enable
    AD_F_KalmanFilter();       //����е�ADֵ���е����뵥����Ŀ������˲�
    Filted_AD_To_One();        //���˲���ĵ��ADֵ���й�һ��
    #else   
    AD_To_One();               //��һ��
    #endif
}

void AD_GetMaxValue(void)   //���ϲɼ�ˢ�µ��AD���ֵ
{
    AD_GetValue();           //��ȡADֵ
    
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
  
void Filted_AD_To_One(void)  //������ʽ ��һ�����ֵ=����ǰֵ-��Сֵ)/(���ֵ-��Сֵ)
{
       //���µ��AD��һ����1000Ϊ��׼��
    if(((AD_Filted_F_L&0x03ff)-F_L_OFF)>0)
    {  
         AD_Value_F_L=(int)(((long)((AD_Filted_F_L&0x03ff)-F_L_OFF)*1000)/(F_L_MAX-F_L_OFF));
    }
    else
    {
         AD_Value_F_L=1;
    }
    //���µ��AD��һ����1000Ϊ��׼��
    if(((AD_Filted_F_M&0x03ff)-F_M_OFF)>0)
    {  
         AD_Value_F_M=(int)(((long)((AD_Filted_F_M&0x03ff)-F_M_OFF)*1000)/(F_M_MAX-F_M_OFF));
    }
    else
    {
        AD_Value_F_M=1;
    }
    //���µ��AD��һ����1000Ϊ��׼��
    if(((AD_Filted_F_R&0x03ff)-F_R_OFF)>0)
    {  
       AD_Value_F_R=(int)(((long)((AD_Filted_F_R&0x03ff)-F_R_OFF)*1000)/(F_R_MAX-F_R_OFF));
    }
    else
    {
       AD_Value_F_R=1;
    }
    //���ϵ��AD��һ����1000Ϊ��׼��
    if(((AD_Filted_F_FL&0x03ff)-F_FL_OFF)>0)
    {  
       AD_Value_F_FL=(int)(((long)((AD_Filted_F_FL&0x03ff)-F_FL_OFF)*1000)/(F_FL_MAX-F_FL_OFF));
    }
    else
    {
       AD_Value_F_FL=1;
    }
    //���ϵ��AD��һ����1000Ϊ��׼��
    if(((AD_Filted_F_FR&0x03ff)-F_FR_OFF)>0)
    {  
       AD_Value_F_FR=(int)(((long)((AD_Filted_F_FR&0x03ff)-F_FR_OFF)*1000)/(F_FR_MAX-F_FR_OFF));
    }
    else
    {
       AD_Value_F_FR=1;
    }
    
    // �޷��˲� ��ֹ����
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
       //���µ��AD��һ����1000Ϊ��׼��
    if(((AD_Value_F_L0&0x03ff)-F_L_OFF)>0)
    {  
         AD_Value_F_L=(int)(((long)((AD_Value_F_L0&0x03ff)-F_L_OFF)*1000)/(F_L_MAX-F_L_OFF));
    }
    else
    {
         AD_Value_F_L=1;
    }
    //���µ��AD��һ����1000Ϊ��׼��
    if(((AD_Value_F_M0&0x03ff)-F_M_OFF)>0)
    {  
         AD_Value_F_M=(int)(((long)((AD_Value_F_M0&0x03ff)-F_M_OFF)*1000)/(F_M_MAX-F_M_OFF));
    }
    else
    {
        AD_Value_F_M=1;
    }
    //���µ��AD��һ����1000Ϊ��׼��
    if(((AD_Value_F_R0&0x03ff)-F_R_OFF)>0)
    {  
      AD_Value_F_R=(int)(((long)((AD_Value_F_R0&0x03ff)-F_R_OFF)*1000)/(F_R_MAX-F_R_OFF));
    }
    else
    {
      AD_Value_F_R=1;
    }
    //���ϵ��AD��һ����1000Ϊ��׼��
    if(((AD_Value_F_FL0&0x03ff)-F_FL_OFF)>0)
    {  
      AD_Value_F_FL=(int)(((long)((AD_Value_F_FL0&0x03ff)-F_FL_OFF)*1000)/(F_FL_MAX-F_FL_OFF));
    }
    else
    {
      AD_Value_F_FL=1;
    }
    //���ϵ��AD��һ����1000Ϊ��׼��
    if(((AD_Value_F_FR0&0x03ff)-F_FR_OFF)>0)
    {  
       AD_Value_F_FR=(int)(((long)((AD_Value_F_FR0&0x03ff)-F_FR_OFF)*1000)/(F_FR_MAX-F_FR_OFF));
    }
    else
    {
       AD_Value_F_FR=1;
    }
    
    // �޷��˲� ��ֹ����
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



void New_AnalysisDecision(void)  //��������
{  
   New_Cal_FtoE();                //�����ֵ��������
   New_Judge_RoadType();          //��������
   New_MakeDecision();            //������ ֱ�������������
}

void New_Cal_FtoE(void)
{  
   int i;
   AD[0]=AD_Value_F_L;     //���ֵ���
   AD[1]=AD_Value_F_M;
   AD[2]=AD_Value_F_R;
   AD[3]=AD_Value_F_FL;
   AD[4]=AD_Value_F_FR;
   for(i=0;i<4;i++)       //�������ֵ���
   {
     if(AD[Max_AD_Num]<AD[i]-1)
       Max_AD_Num=i;
   }
   Max_AD_Value=AD[Max_AD_Num]; //������ֵ
   Max_Shu_Value=(AD[3]>AD[4])?AD[3]:AD[4]; //��������ֵ
      //�ж��ĸ�������С����� �����ź�ֵ
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
   
   F_L_M_add = AD_Value_F_L+AD_Value_F_M+AD_Value_F_R;  //���еĺ�
   FL_FR_add = AD_Value_F_FL +AD_Value_F_FR;            //����еĺ�
   ALL_add    = F_L_M_add + FL_FR_add;                  //���е�еĺ�
   FL_FR_dif = AD_Value_F_FR - AD_Value_F_FL;           //����еĲ�
   //�޷���ֹ����
   if(F_L_M_add<1)  F_L_M_add=1;
   if(FL_FR_add<1)  FL_FR_add=1;
   if(ALL_add<1)    ALL_add=1;
   
   //(L-R)/(L+R)�������ƫ��  ��Ⱥͽ�����������ϳ�������  ͨ��EXCEL���Իع���ϵõ�
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
   e_Heng =  LR_LR_nihe;  //��������ϵ�ƽ��ֵ ��С���  ��ĺ��еĲ�
#endif 
   e_Heng = LR_LM_nihe/3 + LR_LR_nihe/3 + LR_MR_nihe/3;  //��������ϵ�ƽ��ֵ ��С���  ��ĺ��еĲ�
   //�޷��˲�
   if((e_Heng-e_HengPre)>500 || (e_Heng-e_HengPre)<-500 ||e_Heng>800)     
   {
        e_Heng=e_HengPre; 
   }
   e_HengPre=e_Heng;
  
   e_Shu =(float)((AD_Value_F_FR)-(AD_Value_F_FL))*200/((AD_Value_F_FR)+(AD_Value_F_FL));   //����еĲ�Ⱥ�
   //�޷��˲�
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
       if(NotChange>5)   //������  25MS�� �����������ı�RoadType ʱ��̫�� ̫�� ��������
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
              if((RaceAu[0]+RaceAu[1]+RaceAu[2])>=2)   //��������ߵ�ǿ�ж�
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
           switch (RoadType)   //�G��ǿ�жϷ��� ������ֱ�������ʱ
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
       if((absi(AD[3]-AD[4])>180)&&Max_Shu_Value>250&&(absi(e_Shu)>30)&&F_L_M_add<1796)  //ע������
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
       //e�޷�
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



