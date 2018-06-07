#include "Include.h"

#ifdef NA_Car
uint16 ZhiDao_Servo_P=225;            //ֱ�������P
uint16 ZhiDao_Servo_D=10;             //ֱ�������D
uint16 WanDao_Servo_P=259;            //��������P
uint16 WanDao_Servo_D=643;           //��������D
#endif

#ifdef NB_Car
uint16 ZhiDao_Servo_P=225;            //ֱ�������P
uint16 ZhiDao_Servo_D=10;            //ֱ�������D
uint16 WanDao_Servo_P=303;            //��������P
uint16 WanDao_Servo_D=808;            //��������D
#endif

#define kpc 0.01f
#define kpc_ 0.006f

uint16 Servo_P=225;                   //�����P,D
uint16 Servo_D=150;
uint8 ServoEnable=0;
uint8 Ser_Debug_Enable=0;
uint8 Ser_Flash_Saved=0;                //flash�������
uint8 Debug_Sccess=0;
uint16 SerMid_Debug = SERVO_MID;
uint16 PWM_duoji = SERVO_MID;          //��ʼ��Ϊ�������ֵ

int16 ec_min=0;  
int16 ec_max=0;
int16 ec_retern=0;

float Servo_PWM_abs = SERVO_MID;
float ServoAngle=0;
Direction Race=ClockWise;
#ifdef NA_Car
const float Servo_P_Deta_Z = 107.036;    //���ֱ��P����
const float Servo_D_Deta_Z = 3.518;      //���ֱ��D����
#endif 
#ifdef NB_Car
const float Servo_P_Deta_Z = 107.036;     //���ֱ��P����
const float Servo_D_Deta_Z = 53.518;      //���ֱ��D����
#endif
const float Servo_P_Deta_W = 35.259;    //������P����
const float Servo_D_Deta_W = 70.518;     //������D����
const float Servo_PID_RefineB = 320.0;  //���������
const float Servo_PID_RefineS = 170.0;  //С��������
const float S_BuffConstant     = 1.1;     //����ϵ��
const float S_DebuffConstant   = 0.9;     //����ϵ��
//PD������P��������,����С��λ��ƫ��e����������Ƶ�P����
int P1=0;
int P2=0;
int P3=0;
int P4=0;
uint8 ServoFuzzyJiance=0;              //���ר��ģ��PID ģ�����ּ�����
uint8 ServoExpertJiance=0;             //���ר��ģ��PID ר�Ҳ��ּ�����
                                                                     //kpģ�������
const float Servo_FuzzyCtlPID_ExP[7][7]=                            //           ec���仯��
{                                                                    //   e   NB NM NS ZO PS PM PB      
    { 0.895, 0.895, 0.667, 0.667, 0.333, 0.000, 0.000},              //  NB   PB PB PM PM PS ZO ZO
    { 0.895, 0.895, 0.667, 0.333, 0.333, 0.000, 0.333},              //  NM   PB PB PM PS PS ZO NS
    { 0.667, 0.667, 0.667, 0.333, 0.000, 0.333, 0.333},              //  NS   PM PM PM PS ZO NS NS 
    { 0.667, 0.667, 0.333, 0.000, 0.333, 0.667, 0.667},              //  ZO   PM PM PS ZO NS NM NM
    { 0.333, 0.333, 0.000, 0.333, 0.333, 0.667, 0.667},              //  PS   PS PS ZO NS NS NM NM
    { 0.333, 0.000, 0.333, 0.667, 0.667, 0.667, 0.895},              //  PM   PS ZO NS NM NM NM NB
    { 0.000, 0.000, 0.667, 0.667, 0.667, 0.895, 0.895},              //  PB   ZO ZO NM NM NM NB NB
};                                                                   //kiģ�������
const float Servo_FuzzyCtlPID_ExI[7][7]=                            //           ec���仯��
{                                                                    //    e   NB NM NS ZO PS PM PB
    {-0.895,-0.895,-0.667,-0.667,-0.333, 0.000, 0.000},              //   NB   NB NB NM NM NS ZO ZO
    {-0.895,-0.895,-0.667,-0.333,-0.333, 0.000, 0.000},              //   NM   NB NB NM NS NS ZO ZO
    {-0.895,-0.667,-0.333,-0.333, 0.000, 0.333, 0.333},              //   NS   NB NM NS NS ZO PS PS
    {-0.667,-0.667,-0.333, 0.000, 0.333, 0.667, 0.667},              //   ZO   NM NM NS ZO PS PM PM
    {-0.667,-0.333, 0.000, 0.333, 0.333, 0.667, 0.895},              //   PS   NM NS ZO PS PS PM PB
    { 0.000, 0.000, 0.333, 0.333, 0.667, 0.895, 0.895},              //   PM   ZO ZO PS PS PM PB PB
    { 0.000, 0.000, 0.333, 0.667, 0.667, 0.895, 0.895},              //   PB   ZO ZO PS PM PM PB PB
};                                                                   //kdģ�������
const float Servo_FuzzyCtlPID_ExD[7][7]=                            //           ec���仯��
{                                                                    //   e   NB NM NS ZO PS PM PB
    { 0.333, 0.333,-0.895, 0.895,-0.895, 0.667, 0.333},              //  NB   PS NS NB NB NB NM PS
    { 0.333, 0.333,-0.895, 0.667,-0.667, 0.333, 0.000},             //   NM   PS NS NB NM NM NS ZO
    { 0.000, 0.333,-0.667, 0.667,-0.333, 0.333, 0.000},             //   NS   ZO NS NM NM NS NS ZO
    { 0.000, 0.333,-0.333, 0.333,-0.333, 0.333, 0.000},             //   ZO   ZO NS NS NS NS NS ZO
    { 0.000, 0.000, 0.000, 0.667, 0.000, 0.000, 0.000},             //   PS   ZO ZO ZO ZO ZO ZO ZO
    { 0.895, 0.333, 0.333, 0.667, 0.333, 0.333, 0.895},             //   PM   PB NS PS PS PS PS PB
    { 0.895, 0.667, 0.667, 0.895, 0.333, 0.333, 0.895},             //   PB   PB PM PM PM PS PS PB
};                                       
//���PWM���� 
void Set_Servo_PWM(int value)             
{     
   PWM_duoji=SerMid_Debug+value;   
   if(PWM_duoji>SerMid_Debug+SERVO_RANGE_R)  PWM_duoji=SerMid_Debug+SERVO_RANGE_R; 
   if(PWM_duoji<SerMid_Debug-SERVO_RANGE_L)  PWM_duoji=SerMid_Debug-SERVO_RANGE_L;
   tpm_pwm_duty(TPM2, TPM_CH0, (uint32)PWM_duoji);
}

void Servo_Debug(void)    //���ٴε��� �븴λ ������ ��ʱ����SERVO_MID 
{   
    if(Ser_Debug_Enable>=1&&ServoEnable==0&&Ser_Flash_Saved==0)
    {
        tpm_pwm_duty(TPM2, TPM_CH0,SerMid_Debug);
        Debug_Sccess=1;
    } 
    else if(Ser_Flash_Saved==0&&Debug_Sccess==1)
    {
        WriteFlash_ServoMid();                      
        Ser_Flash_Saved=1;
    }
}

void Cal_Servo_Angle(void)
{
    ServoAngle=Servo_PWM_abs/SERVO_MID*SERVO_MAX_ANGLE;  
}

void Servo_PID(void)     //��ͨ�ֶ�PID
{
   volatile static float last_e=0,derr_F=0, last_err_N=0,derr_N=0; 
   volatile static float Servo_PWM=0,Servo_PWM_Pre=0;
   volatile static float KD,KP,kp,kd;
   float de_F,kp_temp;//ֻ��Ϊ�˷�ֹ������
   KP=Servo_P; 
   KD=Servo_D;
   derr_F=e-last_e;
   de_F=derr_F;//ֻ��Ϊ�˷�ֹ������

  if(e<70&&e>-70)	// ||Road_Message==1
  { 
    kp=KP*0.014;	 
    kd=de_F*KD*0.2;
  }
  else if((e>=70&&e<140)||(e<=-70&&e>-140))	  	   
  {
    kp=(KP+P1)*0.020;	 
    kd=de_F*(KD+22)*0.1;	  	 
  }                 
  else if((e>=140&&e<230)||(e<=-140&&e>-230))	  	   
  {
    kp=(KP+P2)*0.020;	 
    kd=de_F*(KD+22)*0.1;	  	 
  }                
  else if((e>=230&&e<270)||(e<=-230&&e>-270))	  	   
  { 
    kp=(KP+P3)*0.020;	 
    kd=de_F*(KD+32)*0.1;
  }
  else if(e>=270||e<=-270)	  	   
  { 
    kp=(KP+P4)*0.020;	 
    kd=de_F*(KD+42)*0.1;
  }
   kp_temp=kp;//ֻ��Ϊ�˷�ֹ������            
   Servo_PWM=e*kp_temp+kd; 
   Servo_PWM_Pre=Servo_PWM;       		 
   last_e=e; 
   if(RoadType==WD_Lose)
   {
        if(e>20)  Servo_PWM = SERVO_RANGE_L-40;
         if(e<-20) Servo_PWM = -(SERVO_RANGE_R-40);
   }
   else if(RoadType==ZD_Lose)
   {
          if(e>20) Servo_PWM = 980;
          if(e<-20)Servo_PWM =-980;
   }
   Set_Servo_PWM((int)Servo_PWM);   
}

void PDleadtoSpd(float* fp,float* fd)
{
    if(Real_Speed<ZhiDaoSpeed-66)
    {
        *fp=*fp-20;
        *fd=*fd-10;
    }
    else if(Real_Speed<ZhiDaoSpeed-118)
    {
        *fp=*fp-40;
        *fd=*fd-20;
    }
}
/************������ ֱ��2��P ���ģ��P ***********************/
void Servo_ExpertFuzzyPID(void)                 //ר�ҡ�ģ��PID  ��������PСD  ���� СP��D
{
     FuzzyField i,j;                         //�����Ķ�ά����ĺ������� ģ����
     static float e_bef=0;         //�������e��ǰ������ǰǰ�����
     static float ec=0;            //�������仯��
     volatile static float Servo_PWM=SERVO_MID,Servo_PWM_bef=SERVO_MID;     //�������Ĵ�Ǽ�ǰ�δ�ǵ�PWM
     volatile static float ServoInitial_P,ServoInitial_D;     
     float ServoFuzzy_P,ServoFuzzy_D,ServoOut_P,ServoOut_D;  //����ģ�������Ķ�� P,D   
     ec=e-e_bef;                                  //���仯��
     if(ec_max<=(int16)ec)
       ec_max=(int16)ec;             //������
     else if(ec_min>=(int16)ec)
       ec_min=(int16)ec;             //������    
     ServoInitial_P=Servo_P;                      //ģ������ǰ�Ķ��P
     ServoInitial_D=Servo_D;                      //ģ������ǰ�Ķ��D  ���ж����PD��getsensor.c�иı� 
    /* if(BendOut_Flag==1&absi(e)>150)
     {
        ServoInitial_P= Servo_D-20;                      //ģ������ǰ�Ķ��P
        ServoInitial_D= Servo_P+50;                    //ģ������ǰ�Ķ��D  ���ж����PD��getsensor.c�иı�
     }
     else
     {
         ServoInitial_P=Servo_P;                      //ģ������ǰ�Ķ��P
         ServoInitial_D=Servo_D;                      //ģ������ǰ�Ķ��D  ���ж����PD��getsensor.c�иı�
     }  */    
     if(RoadType==ZhiDao||RoadType==ShiZiWan||RoadType==PoDao)
     {
        /*if (e<0)
        {
	    if (e<S_E_NB_Z) 
            {
               i=NB;
               ServoFuzzyJiance=11;
            }
	    else if (e>=S_E_NB_Z&&e<S_E_NM_Z)
            {
               i=NM;
               ServoFuzzyJiance=12;
            }
	    else if (e>=S_E_NM_Z&&e<S_E_NS_Z)
            {
               i=NS;
               ServoFuzzyJiance=13;
            }
	    else
            {
               i=ZO;
               ServoFuzzyJiance=14;
            }
        }
        else
        {
	    if(e>S_E_PB_Z)
            {
               i=PB;
               ServoFuzzyJiance=15;
            }
	    else if (e<=S_E_PB_Z&&e>S_E_PM_Z)
            {
               i=PM;
               ServoFuzzyJiance=16;
            }
	    else if (e<=S_E_PM_Z&&e>S_E_PS_Z)
            {
               i=PS;
               ServoFuzzyJiance=17;
            }
	    else
            {
               i=ZO;
               ServoFuzzyJiance=14;
            }
        }
        if(ec<0)
        {
	    if (ec<S_EC_NB_Z) 
            {
               j=NB;
               ServoFuzzyJiance=21;
            }
	    else if (ec>=S_EC_NB_Z&&ec<S_EC_NM_Z)
            {
               j=NM;
               ServoFuzzyJiance=22;
            }
	    else if (ec>=S_EC_NM_Z&&ec<S_EC_NS_Z)
            {
               j=NS;
               ServoFuzzyJiance=23;
            }
	    else 
            {
               j=ZO;
               ServoFuzzyJiance=24;
            }
        }
        else 
        {
	    if(ec>S_EC_PB_Z)
            {
               j=PB;
               ServoFuzzyJiance=25;
            }
	    else if (ec<=S_EC_PB_Z&&ec>S_EC_PM_Z)
            {
               j=PM;
               ServoFuzzyJiance=26;
            }
	    else if (ec<=S_EC_PM_Z&&ec>S_EC_PS_Z)
            {
               j=PS;
               ServoFuzzyJiance=27;
            }
	    else 
            {
               j=ZO;
               ServoFuzzyJiance=24;
            }
        } */   
        //ServoFuzzy_P = ServoInitial_P+Servo_FuzzyCtlPID_ExP[i][j]*Servo_P_Deta_Z;
        //ServoFuzzy_D = ServoInitial_D+Servo_FuzzyCtlPID_ExD[i][j]*Servo_D_Deta_Z;
       if(absi(e)<177)    //ֱ�� �� ģ��P ��Ϊ �ֶ�2��P Ч���� ��������ͬʱ ע������ֵ�ĵ���
       {
          ServoFuzzy_P = kpc * absi(e)*absi(e);
          ServoFuzzy_D = 100;  
       }
       else
       {
          ServoFuzzy_P = kpc_ * absi(e)*absi(e);
          ServoFuzzy_D = 10;  
       }
     }
     else
     {
        if (e<0)
        {
	    if (e<S_E_NB_W) 
            {
               i=NB;
               ServoFuzzyJiance=11;
            }
	    else if (e>=S_E_NB_W&&e<S_E_NM_W)
            {
               i=NM;
               ServoFuzzyJiance=12;
            }
	    else if (e>=S_E_NM_W&&e<S_E_NS_W)
            {
               i=NS;
               ServoFuzzyJiance=13;
            }
	    else
            {
               i=ZO;
               ServoFuzzyJiance=14;
            }
        }
        else
        {
	    if(e>S_E_PB_W)
            {
               i=PB;
               ServoFuzzyJiance=15;
            }
	    else if (e<=S_E_PB_W&&e>S_E_PM_W)
            {
               i=PM;
               ServoFuzzyJiance=16;
            }
	    else if (e<=S_E_PM_W&&e>S_E_PS_W)
            {
               i=PS;
               ServoFuzzyJiance=17;
            }
	    else
            {
               i=ZO;
               ServoFuzzyJiance=14;
            }
        }
        if(ec<0)
        {
	    if (ec<S_EC_NB_W) 
            {
               j=NB;
               ServoFuzzyJiance=21;
            }
	    else if (ec>=S_EC_NB_W&&ec<S_EC_NM_W)
            {
               j=NM;
               ServoFuzzyJiance=22;
            }
	    else if (ec>=S_EC_NM_W&&ec<S_EC_NS_W)
            {
               j=NS;
               ServoFuzzyJiance=23;
            }
	    else 
            {
               j=ZO;
               ServoFuzzyJiance=24;
            }
        }
        else 
        {
	    if(ec>S_EC_PB_W)
            {
               j=PB;
               ServoFuzzyJiance=25;
            }
	    else if (ec<=S_EC_PB_W&&ec>S_EC_PM_W)
            {
               j=PM;
               ServoFuzzyJiance=26;
            }
	    else if (ec<=S_EC_PM_W&&ec>S_EC_PS_W)
            {
               j=PS;
               ServoFuzzyJiance=27;
            }
	    else 
            {
               j=ZO;
               ServoFuzzyJiance=24;
            }
        }
        ServoFuzzy_P = ServoInitial_P+Servo_FuzzyCtlPID_ExP[i][j]*Servo_P_Deta_W;
        ServoFuzzy_D = ServoInitial_D+Servo_FuzzyCtlPID_ExD[i][j]*Servo_D_Deta_W;
        
     }
     //if(RoadType==ZhiDao)
       // PDleadtoSpd(&ServoFuzzy_P,&ServoFuzzy_D);    //���PD��΢��
     ServoOut_P=0.015*ServoFuzzy_P;   //תΪϵͳ����ʵP
     ServoOut_D=0.1*ServoFuzzy_D;     //תΪϵͳ����ʵD
     //����PD�����޸Ĳ��� ���յ���ʱ Ҫ����ϵ��
     Servo_PWM=ServoOut_P*e+ServoOut_D*ec;    
     e_bef=e;

     if(RoadType==WD_Lose)
     {
#ifdef NA_Car
         if(e>20)  Servo_PWM = SERVO_RANGE_L-40;
         if(e<-20) Servo_PWM = -(SERVO_RANGE_R-40);
#endif
#ifdef NB_Car
        if(e>20)  Servo_PWM = SERVO_RANGE_L-180;
         if(e<-20) Servo_PWM = -(SERVO_RANGE_R-680); 
#endif
     }
     else if(RoadType==ZD_Lose)
     {
#ifdef NA_Car
         if(e>20)  Servo_PWM = SERVO_RANGE_L-40;
         if(e<-20) Servo_PWM = -(SERVO_RANGE_R-40);
#endif
#ifdef NB_Car
        if(e>20)  Servo_PWM = SERVO_RANGE_L-140;
         if(e<-20) Servo_PWM = -(SERVO_RANGE_R-680); 
#endif
     }
     Servo_PWM_bef=Servo_PWM;
     Servo_PWM_abs=absi(Servo_PWM);
     Set_Servo_PWM((int)Servo_PWM);
}


