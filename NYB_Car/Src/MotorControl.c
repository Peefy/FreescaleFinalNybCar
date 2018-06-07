#include "Include.h"

uint8 jiance=0;               //�����ͨMotorPID�������
uint8 ShangWeiJiStop=1;       //��λ��ͣ������0Ϊʹ�� 1 Ϊͣ��
uint8 ItStop=1;          //���뿪��ͣ������0Ϊʹ�� 1 Ϊͣ��
uint8 AutoStart=0;            //�˱�����1 ����ʱ����
uint8 StartFlag=0;            
uint16 StartTime=0;

uint8 TimerRun_s = 2;         //��ʱ�ܵ�ʱ��&��ʱ����ʱ����һ������ ��λ����
uint8 TimerRun_Flag=0;
uint16 TimerRun_Time=0;    
uint8 TimerRun_EN=0;          //�˱�����1��ʱ��

uint8 Car_Cmd=0;
uint16 BeeCount=0;
int16 RunCount=0;
uint8 SpeedingFlag=0;
int16 OutofRangeCount=0; 
uint8 OutofRangeFlag=0;
int16 MotorOverloadCount=0;
uint8 MotorOverloadFlag=0;
uint8 DetectD_EN=1;

uint16 Distance=0;     //���߹��ľ���(���͸���һ����)
float fDistance=0;    //���߹��ľ���
uint16 MOTOR_P=130;   //������Ƶ�P
uint16 MOTOR_I=35;    //������Ƶ�I
uint16 MOTOR_D=0;     //������Ƶ�D

uint16  ZhiDaoSpeed=460;   //ֱ���ٶ�
uint16  WanDaoSpeed=250;   //����ٶ�
uint16  LoseSpeed=260;

uint16  OtherCar_ZhiDaoSpeed=0;   //��һ������ֱ���趨�ٶ�
uint16  OtherCar_WanDaoSpeed=0;   //��һ����������趨�ٶ�
uint16  OtherCar_Real_Speed=0;    //��һ������ʵ���ٶ�
uint16  OC_Distance=0;            //��һ�������߹��ľ���
 
#define JiaSu_M_PWM     700  
#define Brake_M_PWM    -200

uint16 Set_Speed=470;    //�趨Ŀ���ٶ� 
uint16 Real_Speed=0;     //��⵽����ʵ�ٶ�

uint16 HMI_err_I=0;
uint16 ERR_I_MAX = 10500;
uint8 Mtr_Debug_Enable=0;
uint8 DisCharage_Enable=0;   
uint16 KeepDis=2333;   //����������Ҫ���ֵ���������
/*****ѧϰpid����*********/
uint8 LearnTime=0;
float Motor_Kp[4];
float Motor_Ki[4];
const float V_p=3.0;
const float V_i=1.0;
/********ģ��PID����***********/
uint8 MotorFuzzyJiance=0;              //���ר��ģ��PID ģ�����ּ�����
uint8 MotorExpertJiance=0;             //���ר��ģ��PID ר�Ҳ��ּ�����
const float Motor_P_Deta =10.0;       //���P����
const float Motor_I_Deta =  3.5;      //���I����
const float Motor_PID_RefineB = 200.0;  //���������
const float Motor_PID_RefineS = 60.0;  //С��������
const float M_BuffConstant     = 1.1;     //����ϵ��05
const float M_DebuffConstant   = 0.1;     //����ϵ��
//kpģ�������
const float Motor_FuzzyCtlPID_ExP[7][7]=                           //           ec���仯��
{                                                                   //   e   NB NM NS ZO PS PM PB      
    { 0.895, 0.895, 0.667, 0.667, 0.333, 0.000, 0.000},             //  NB   PB PB PM PM PS ZO ZO
    { 0.895, 0.895, 0.667, 0.333, 0.333, 0.000,-0.333},             //  NM   PB PB PM PS PS ZO NS
    { 0.667, 0.667, 0.667, 0.333, 0.000,-0.333,-0.333},             //  NS   PM PM PM PS ZO NS NS 
    { 0.667, 0.667, 0.333, 0.000,-0.333,-0.667,-0.667},             //  ZO   PM PM PS ZO NS NM NM
    { 0.333, 0.333, 0.000,-0.333,-0.333,-0.667,-0.667},             //  PS   PS PS ZO NS NS NM NM
    { 0.333, 0.000,-0.333,-0.667,-0.667,-0.667,-0.895},             //  PM   PS ZO NS NM NM NM NB
    { 0.000, 0.000,-0.667,-0.667,-0.667,-0.895,-0.895},             //  PB   ZO ZO NM NM NM NB NB
};                                                                  //kiģ�������
const float Motor_FuzzyCtlPID_ExI[7][7]=                           //           ec���仯��
{                                                                   //    e   NB NM NS ZO PS PM PB
    {-0.895,-0.895,-0.667, 0.667,-0.433, 0.000, 0.000},             //   NB   NB NB NM NM NS ZO ZO
    {-0.895,-0.895,-0.667, 0.433,-0.433, 0.000, 0.000},             //   NM   NB NB NM NS NS ZO ZO
    {-0.895,-0.667,-0.433, 0.433, 0.000, 0.433, 0.433},             //   NS   NB NM NS NS ZO PS PS
    {-0.667,-0.667,-0.433, 0.000, 0.433, 0.667, 0.667},             //   ZO   NM NM NS ZO PS PM PM
    {-0.667,-0.433, 0.000, 0.433, 0.433, 0.667, 0.895},             //   PS   NM NS ZO PS PS PM PB
    { 0.000, 0.000, 0.433, 0.433, 0.667, 0.895, 0.895},             //   PM   ZO ZO PS PS PM PB PB
    { 0.000, 0.000, 0.433, 0.667, 0.667, 0.895, 0.895},             //   PB   ZO ZO PS PM PM PB PB
};                                                                  //kdģ�������
const float Motor_FuzzyCtlPID_ExD[7][7]=                           //           ec���仯��
{                                                                   //   e   NB NM NS ZO PS PM PB
    { 0.333,-0.333,-0.895,-0.895,-0.895,-0.667, 0.333},             //  NB   PS NS NB NB NB NM PS
    { 0.333,-0.333,-0.895,-0.667,-0.667,-0.333, 0.000},            //   NM   PS NS NB NM NM NS ZO
    { 0.000,-0.333,-0.667,-0.667,-0.333,-0.333, 0.000},            //   NS   ZO NS NM NM NS NS ZO
    { 0.000,-0.333,-0.333,-0.333,-0.333,-0.333, 0.000},            //   ZO   ZO NS NS NS NS NS ZO
    { 0.000, 0.000, 0.000, 0.000, 0.000, 0.000, 0.000},            //   PS   ZO ZO ZO ZO ZO ZO ZO
    { 0.895,-0.333, 0.333, 0.333, 0.333, 0.333, 0.895},            //   PM   PB NS PS PS PS PS PB
    { 0.895, 0.667, 0.667, 0.667, 0.333, 0.333, 0.895},            //   PB   PB PM PM PM PS PS PB
};  

void Start(void)
{
   if( StartTime>200*TimerRun_s && StartFlag==0) //2��󷢳�
   { 
      StartFlag=1;
      Run(); 
   }
   if(AutoStart==0)
   {
      StartTime=0;
      StartFlag=0;
   }
#ifdef NA_Car
   Car_Cmd=TimerRun_EN*2+AutoStart;
#endif
}

void DectectStartLine(void)
{  
  if(ShangWeiJiStop==1)
    ServoEnable=1;
  if(Distance>1000)
  {
     if(0 == gpio_get(StartLine) ) 
     {
#ifdef NA_Car
        ShangWeiJiStop=0;
#endif
#ifdef NB_Car
        ItStop=0;
#endif
     }
  }

}

void TimerRun(void)
{   
   if(TimerRun_Flag==0&&TimerRun_Time<=TimerRun_s*200&&TimerRun_EN==1)
   {
       Run();
   }
   if(TimerRun_Time>TimerRun_s*200)
   {
       Stop();
       TimerRun_Flag=1;;
   }
   if(TimerRun_EN==0)
   {
       TimerRun_Flag=0;
       TimerRun_Time=0;
   }
}

void Timer20sRun(void)
{
   TimerRun_s=20;
   TimerRun_EN=1;
   ok_fmq();
}

void Delay2sDepart(void)
{
   TimerRun_s=2;
   AutoStart=1;
   ok_fmq();
}

float abs_float(float data_s)   //�������ֵ����
{
     return data_s>=0?data_s:-data_s;  //�����ж�
}

void DetectDanger(void)
{
     if(Real_Speed>ZhiDaoSpeed+200)  //��ֹ���ת��
        Stop_();
     if(EnconterFlag|OutofRangeFlag|MotorOverloadFlag|SpeedingFlag)
        BeeCount++;
     else 
        BeeCount=0;
     Car_Cmd=TimerRun_EN*2+AutoStart;
#ifdef NA_Car     
     if(TimerRun_EN|AutoStart)
#endif
#ifdef NB_Car 
     if(TimerRun_EN|AutoStart|ShangWeiJiStop)  
#endif
     {  
        //����ܵ�ͣ��
        if(ALL_add<10)
           ++OutofRangeCount;
        else
           --OutofRangeCount;
        if(OutofRangeCount>48)    
        {
           Stop_();
           TimerRun_EN=0;
           AutoStart=0;
           OutofRangeCount=0; 
           OutofRangeFlag=1;
        }
        else if(OutofRangeCount<=0)
        {
           OutofRangeCount=0;
           OutofRangeFlag=0;
        }
        //�����תͣ��
        if(Distance>666)
        {
           if(Real_Speed<10)
             ++MotorOverloadCount;
           else
             --MotorOverloadCount;       
         
           if(MotorOverloadCount>5)
           {
              Stop_();
              TimerRun_EN=0;
              AutoStart=0;
              MotorOverloadCount=0;
              MotorOverloadFlag=1;
           }  
           else if(MotorOverloadCount<=0)
           {
              MotorOverloadCount=0;
              MotorOverloadFlag=0;
           }    
        } 
        //��������·ͣ��  ��2����ʱ������ͻ
        /*++RunCount;
        if(RunCount>30000)
           RunCount=0;
        if(RunCount>100)
        {
           if(Distance<10||Real_Speed<10)
           {
              Stop_(); 
              TimerRun_EN=0;
              AutoStart=0;
              SpeedingFlag=1;
              RunCount=0;
           }
        } */        
     }
     else
     {
        MotorOverloadCount=0;
        OutofRangeCount=0;
        RunCount=0;
     }
}

void Get_Real_Speed(void)
{ 
     Real_Speed = (uint16)(Real_Speed*0.5 + lptmr_pulse_get()*4.488*0.5);//һ������Ϊ0.04488CM
     lptmr_pulse_clean(); 
     if(ShangWeiJiStop==1)
     {
        fDistance+=(float)(Real_Speed/100.0);
        Distance=(uint16)fDistance;
     }
#ifdef DetectDanger_EN
     if(DetectD_EN>=1)
       DetectDanger();
#endif
}
        
void Motor_Zheng(float pwm)    //�����ת����
{
    if(pwm>1000)  
    {
       tpm_pwm_duty(TPM0, TPM_CH0, 0);
       tpm_pwm_duty(TPM0, TPM_CH1, 1000);
    }
    else if(pwm<0)
    {
       tpm_pwm_duty(TPM0, TPM_CH0, 0);
       tpm_pwm_duty(TPM0, TPM_CH1, 0);
    }
    else
    {
       tpm_pwm_duty(TPM0, TPM_CH0, 0);
       tpm_pwm_duty(TPM0, TPM_CH1, (uint32)(pwm));
    }    
}
 
void Motor_Fan(float pwm)       //�����ת����
{
    if(pwm>1000)
    {
       tpm_pwm_duty(TPM0, TPM_CH0, 1000);
       tpm_pwm_duty(TPM0, TPM_CH1, 0);
    }
    else if(pwm<0)
    {
       tpm_pwm_duty(TPM0, TPM_CH0, 0);
       tpm_pwm_duty(TPM0, TPM_CH1, 0);
    }
    else
    {
       tpm_pwm_duty(TPM0, TPM_CH0, (uint32)(pwm));
       tpm_pwm_duty(TPM0, TPM_CH1, 0);
    }    
}

void Run(void)     //��λ��С����������
{    
    ShangWeiJiStop=1; 
    ServoEnable=1;    
    led(LED0,LED_ON);
}

void Stop(void)    //��λ��С��ֹͣ����
{
    ShangWeiJiStop=0;     
    //Motor_Zheng(0);
    //ServoEnable=0;
    tpm_pwm_duty(TPM0, TPM_CH0, 0);
    tpm_pwm_duty(TPM0, TPM_CH1, 0);
    led(LED0,LED_OFF);   
}

void Stop_(void)
{
#ifdef NA_Car
        ShangWeiJiStop=0;
#endif
#ifdef NB_Car
        ItStop=0;
#endif
}

void Motor_PID(float v_set)     //���PID����
{
    volatile static float err_pre=0; 
    volatile static float err_D=0; 
    volatile static float err_I=0; 
    float e_D,e_I;
    float err=0;
    float Motor_PWM=0; 
    float MotorOut_P,MotorOut_I;
    MotorOut_P=MOTOR_P*0.01;
    MotorOut_I=MOTOR_I*0.01;  
    err=v_set-Real_Speed;
    err_D = err - err_pre;
    err_pre =err;
    /*
    //�������
    if(err>(v_set/2.0))
    {
       Motor_Zheng(JiaSu_M_PWM);
       err_I=600;
       jiance=1;   //���PID���Ա���
    }
    
    if(abs_float(err)<50)
    {  */
       err_I=err_I+ err;
       e_I=err_I;
       e_D=err_D;
       Motor_PWM = MotorOut_P*err + MotorOut_I*e_I + MOTOR_D*e_D; 
       Motor_Zheng((int)Motor_PWM);
      // jiance=2;
    //}
    //������� 
   /*  if(err<-50 && err>-100)
     {
        Motor_Fan(150);
        jiance=3;
     }
     if(err<-100 && err>-200)
     {
        Motor_Fan(200);
        jiance=4;
     }
     if(err<-200)
     {
        Motor_Fan(300);
        jiance=5;
     }
  } */
}

void Speed_Decision_ToE(void)
{   

    if(RoadType==ZhiDao||RoadType==ShiZiWan) 
    {
         Set_Speed=ZhiDaoSpeed;
    }
    else if (RoadType==SharpWan)
    {
         Set_Speed=(int)(WanDaoSpeed+130);
    }
    else if(RoadType==ZD_Lose||RoadType==WD_Lose)
    {
         #ifdef NA_Car
         Set_Speed=(int)(WanDaoSpeed+80);      
         #endif
         #ifdef NB_Car
         Set_Speed=(int)(WanDaoSpeed+80);      
         #endif        
    }       
    else
    {    
         if((ec_retern>160&&e>20)||(ec_retern<-160&&e<-20))
           Set_Speed=(int)(WanDaoSpeed+0.90*(float)(e_pRefine-absi(e))*(ZhiDaoSpeed-WanDaoSpeed)/e_pRefine);
         else if((ec_retern>100&&e>20)||(ec_retern<-100&&e<-20))
           Set_Speed=(int)(WanDaoSpeed+1.00*(float)(e_pRefine-absi(e))*(ZhiDaoSpeed-WanDaoSpeed)/e_pRefine);
         else if((ec_retern>40&&e>20)||(ec_retern<-40&&e<-20))
           Set_Speed=(int)(WanDaoSpeed+1.08*(float)(e_pRefine-absi(e))*(ZhiDaoSpeed-WanDaoSpeed)/e_pRefine);           
         else
           Set_Speed=(int)(WanDaoSpeed+1.15*(float)(e_pRefine-absi(e))*(ZhiDaoSpeed-WanDaoSpeed)/e_pRefine);
           
    }
    /*if(ZD_count>200)
    {
         Set_Speed=ZhiDaoSpeed-66;
    }
    else
    {
        Set_Speed=Set_Speed; 
    }*/                                            
     NYB_DisCtl();   //����Ҳ���п��Ƶ���ٶȵĳ���
}

void NA_stop(void)
{
    if(Real_Speed>400)
       Motor_Zheng(100);
    else if(Real_Speed>300)
       Motor_Zheng(75);
    else if(Real_Speed>200)
       Motor_Zheng(50);
    else if(Real_Speed>100)
       Motor_Zheng(25);
    else
    {
       tpm_pwm_duty(TPM0, TPM_CH0, 0);
       tpm_pwm_duty(TPM0, TPM_CH1, 0);
    }
}

void NB_stop(void)
{
    if(Real_Speed>400)
       Motor_Fan(100);
    else if(Real_Speed>300)
       Motor_Fan(75);
    else if(Real_Speed>200)
       Motor_Fan(50);
    else if(Real_Speed>100)
       Motor_Fan(25);
    else
    {
       tpm_pwm_duty(TPM0, TPM_CH0, 0);
       tpm_pwm_duty(TPM0, TPM_CH1, 0);
    }     
}

void DisCharage(void)     //ͣ���ĳ��� ţA��zheng�Ƿ�ת ţB��zheng����ת�� ������ע���������߲�һ��
{
     if(DisCharage_Enable&&ShangWeiJiStop==0)
     {        
         if(AD_Value_Cell>=6000)
           Motor_Zheng(200);
         else
           Motor_Zheng(0);
     }
#ifdef NA_Car
     else if(DisCharage_Enable==0&&ShangWeiJiStop==0)
     {
         NA_stop();
     }
#endif
#ifdef NB_Car
     else if(DisCharage_Enable==0) 
     {
         switch(Car_Cmd)
         {
         case 0: //������
           if(ShangWeiJiStop==0||ItStop==0)
             NB_stop();
           break;  
         case 1: //2����ʱ����
           if(ItStop==0)
             NB_stop();             
           else
           {
              if(Distance<18)
              {
                  NB_stop();
              }
              else
              { 
              if(Mtr_Debug_Enable==0)
              {
                 Speed_Decision_ToE();
              }
              #ifdef  Motor_Normal_PID_Enable      
              Motor_PID(Set_Speed);
              #endif
              #ifdef  Motor_ExpertFuzzy_PID_Enable
              Motor_ExpertFuzzyPID(Set_Speed);
              #endif 
              #ifdef  Motor_Learning_PID_Enable     
              Motor_LearningPID(Set_Speed); 
              ServoEnable=1;
              #endif 
              }
           }
           break;
         case 2:     //��ʱ��
           if(ShangWeiJiStop==0)
             NB_stop();
          break;
         }    
     }
#endif 
}

void Motor_Ctl(void)
{   
      if(ShangWeiJiStop==1&&ItStop==1)    //�ٶȷ���
      {
        if(Mtr_Debug_Enable==0)
        {
            Speed_Decision_ToE();
        }
#ifdef  Motor_Normal_PID_Enable      
        Motor_PID(Set_Speed);
#endif
#ifdef  Motor_ExpertFuzzy_PID_Enable
        Motor_ExpertFuzzyPID(Set_Speed);
#endif 
#ifdef  Motor_Learning_PID_Enable     
        Motor_LearningPID(Set_Speed); 
        ServoEnable=1;
#endif   
     }
     DisCharage();  

}

void Motor_ExpertFuzzyPID(float v_set)       //ר�ҡ�ģ��PID
{
     FuzzyField i,j;                              //�����Ķ�ά����ĺ�������;
     static float err_bef=0;                     //�������e��ǰ������ǰǰ�����
     static float errc=0;             //�������仯��     
     float err=0;                                 //�������
     volatile static float err_I=2500.0;
     volatile static float Motor_PWM=0,Motor_PWM_bef=0;
     volatile static float MotorInitial_P,MotorInitial_I;
     float MotorFuzzy_P,MotorFuzzy_I,MotorOut_P,MotorOut_I;  //����ģ�������ĵ��P ,I
     errc=err-err_bef;
     MotorInitial_P=MOTOR_P;
     MotorInitial_I=MOTOR_I;
     err=v_set-Real_Speed;
     err_I=err_I+ err;
     if(err_I>ERR_I_MAX)   //������λ
     {
        err_I=ERR_I_MAX;
     }
     if(err_I<-ERR_I_MAX)  //������λ
     {
        err_I=-ERR_I_MAX;
     }
     HMI_err_I=(uint16)err_I;
     if (err<0)
     {
	 if (err<M_E_NB) 
         {          
            i=NB;
            MotorFuzzyJiance=11;
         }
	 else if (err>=M_E_NB&&err<M_E_NM)
         {
            i=NM;
            MotorFuzzyJiance=12;
         }
	 else if (err>=M_E_NM&&err<M_E_NS)
         {
            i=NS;
            MotorFuzzyJiance=13;
         }
	 else 
         {
            i=ZO;
            MotorFuzzyJiance=14;
         }
         
     }
     else
     {
	 if(err>M_E_PB) 
         {
            i=PB;
            MotorFuzzyJiance=15;
         }
	 else if (err<=M_E_PB&&err>M_E_PM)
         {
            i=PM;
            MotorFuzzyJiance=16;
         }
	 else if (err<=M_E_PM&&err>M_E_PS)
         {
            i=PS;
            MotorFuzzyJiance=17;
         }
	 else 
         {
            i=ZO;
            MotorFuzzyJiance=14;
         }
     }
     if(errc<0)
     {
	 if (errc<M_EC_NB) 
         {
            j=NB;
            MotorFuzzyJiance=21;
         }
	 else if (errc>=M_EC_NB&&errc<M_EC_NM)
         {
            j=NM;
            MotorFuzzyJiance=22;
         }
	 else if (errc>=M_EC_NM&&errc<M_EC_NS)
         {
            j=NS;
            MotorFuzzyJiance=23;
         }
	 else 
         {
            j=ZO; 
            MotorFuzzyJiance=24;
         }         
     }
     else 
     {
	 if(errc>M_EC_PB)
         {
            j=PB;
            MotorFuzzyJiance=25;
         }
	 else if (errc<=M_EC_PB&&errc>M_EC_PM)
         {
            j=PM;
            MotorFuzzyJiance=26;
         }
	 else if (errc<=M_EC_PM&&errc>M_EC_PS)
         {
            j=PS;
            MotorFuzzyJiance=27;
         }
	 else 
         {
            j=ZO;
            MotorFuzzyJiance=24;
         }         
     }
     MotorFuzzy_P = MotorInitial_P+Motor_FuzzyCtlPID_ExP[i][j]*Motor_P_Deta;
     MotorFuzzy_I = MotorInitial_I+Motor_FuzzyCtlPID_ExI[i][j]*Motor_I_Deta;
     MotorOut_P = 0.01*MotorFuzzy_P;
     MotorOut_I = 0.001*MotorFuzzy_I;
     if(err>160)
     {
          Motor_PWM = JiaSu_M_PWM;
          MotorExpertJiance=11; 
     }                   
     else if(err<-50)
     {
          Motor_PWM = Brake_M_PWM+err; 
          MotorExpertJiance=12;
     }  
     else
         Motor_PWM=MotorOut_P*err+MotorOut_I*err_I;
     err_bef=err;
     
#ifdef NB_Car                    //B
     if(Motor_PWM>=0)
        Motor_Zheng(Motor_PWM);
     else
        Motor_Fan(-Motor_PWM); 
#endif

#ifdef NA_Car                    //A
     if(Motor_PWM>=0)
        Motor_Fan(Motor_PWM);
     else
        Motor_Zheng(-Motor_PWM); 
#endif 
     
/*#ifdef SlaveComputer_Enable   //A
     if(Motor_PWM>=0)
        Motor_Zheng(Motor_PWM);
     else
        Motor_Fan(-Motor_PWM);    
#endif   */  
}

void Motor_LearningPID(float v_set)
{
     float err=0;                                 //�������
     static float err_bef=0;                     //�������e��ǰ������ǰǰ�����
     static float errc=0;             //�������仯��
     volatile static float err_I=0.0;
     float MotorOut_P,MotorOut_I;
     volatile static float Motor_PWM=0;
     Motor_Kp[LearnTime]= 0.01 *MOTOR_P;
     Motor_Ki[LearnTime]= 0.001*MOTOR_I;
     err=v_set-Real_Speed;
     err_I=err_I+ err;
     errc=err-err_bef;
     if(err>150)
     {
            Motor_PWM = JiaSu_M_PWM;
            MotorExpertJiance=11; 
     }                   
     else if(err<-50)
     {
          Motor_PWM = Brake_M_PWM+err; 
          MotorExpertJiance=12;
     }
     else
     {
     if(absi(err)<50)    //���ַ���
     {
         if(err*errc<0)
         {
             Motor_Kp[LearnTime+1]=Motor_Kp[LearnTime]-0.0001*V_p;
             if(err*err_I>0)
             Motor_Ki[LearnTime+1]=Motor_Ki[LearnTime]+0.001*V_i;
             else
             Motor_Ki[LearnTime+1]=Motor_Ki[LearnTime]-0.001*V_i; 
         }
         else if(err*errc>0)
         {
             Motor_Kp[LearnTime+1]=Motor_Kp[LearnTime]+0.0001*V_p;
             if(err*err_I>0)
             Motor_Ki[LearnTime+1]=Motor_Ki[LearnTime]+0.001*V_i;
             else
             Motor_Ki[LearnTime+1]=Motor_Ki[LearnTime]-0.001*V_i;
         }
         else if(err*errc==0)
         {
             Motor_Kp[LearnTime+1]=Motor_Kp[LearnTime];
             Motor_Ki[LearnTime+1]=Motor_Ki[LearnTime];
         }
         MotorOut_P=Motor_Kp[LearnTime+1];
         MotorOut_I=Motor_Ki[LearnTime+1];        
     }    
     else if(absi(err)>50)
     {
         MotorOut_P=380/absi(err);
         err_I=0;
     }
     Motor_PWM=MotorOut_P*err+MotorOut_I*err_I;
     }    
     if(Motor_PWM>=0)
         Motor_Zheng(Motor_PWM);
     else
         Motor_Fan(-Motor_PWM); 
     LearnTime++;
     if(LearnTime>2)
         LearnTime=0;
}


