#include "include.h"   //包含必要的头文件

/**********超声波***********/

uint16 NB_DisCount0=0;
uint16 NB_DisCount1=0;

uint8 EnconterFlag=0;
uint16 EnconterCount=0;
uint16 PoDapDisCount=0;
uint8 PoDaoDisFlag=0;
uint8 Low_EN=1;
uint8 Low_EN_=1;
//uint8 OC_noEnFlag=0;  no use
uint16 LowFlagCount=0;
//uint8 NYB_Warning=0;  no use
uint8 CSB_EN=1;
uint8 CSB_EN_=1;
//uint8 HWTube_EN=1;    no use
extern uint16 csb_Count;

void InfraredTube_Init(void)
{
    gpio_init(InfraredTube_Pin, GPI, 1);          
    //port_init_NoALT(InfraredTube_Pin, PULLUP);
}

void HCSR04_Init(void)
{
/********超声波0初始化********/ 
    gpio_init(Trigger0_Pin, GPO, 0);      
    gpio_init(Echo0_Pin, GPI, 0);          
    port_init_NoALT(Echo0_Pin, PULLUP);
/********超声波1初始化********/    
    /*gpio_init(Trigger1_Pin, GPO, 0);      
    gpio_init(Echo1_Pin, GPI, 0);          
    port_init_NoALT(Echo1_Pin, PULLUP);*/
      
}

void Start_HCSR04(void)
{ 
     Trigger0=1;
     //Trigger1=1;    
     DELAY_US(11);    
     Trigger0=0;
     //Trigger1=0;
     DELAY_US(1);
     
}

void Count_Dis(void)
{   
    if(CSB_EN>=1)
    {
       while(!Echo0);
       pit_time_start(PIT1);  
       while(Echo0);   
       NB_DisCount0=(uint16)((uint16)pit_time_get_us(PIT1)*0.5+NB_DisCount0*0.5);
       pit_time_close(PIT1);
       /*while(!Echo1);
       pit_time_start(PIT1);
       while(Echo1);
       NB_DisCount1=(uint16)((uint16)pit_time_get_us(PIT1)*0.5+NB_DisCount1*0.5);
       pit_time_close(PIT1);*/
    }
    else
    {  
       NB_DisCount0=0;
       NB_DisCount1=0;
       pit_time_close(PIT1);
    }
}

void NYB_DisCtl(void)
{  
#ifdef NA_Car
  if(Low_EN>=1)
  {  
    if(Ramp_flag)
      Low_EN_=0;
    else
      Low_EN_=1;
    if(Low_EN_>=1)
    {
    if(Distance>888&&OC_Distance>666)
    {
        if(Distance-OC_Distance>184)
        {
             LowFlag=1;
             LowFlagCount=0;       
        }
        if(LowFlag>=1)
          ++LowFlagCount;
        if(LowFlagCount<20&&LowFlag>=1)
        {
          if(Distance-OC_Distance>368) 
          {
            if(Set_Speed>112)
            {  
               Set_Speed=Set_Speed-112;
            }
          } 
          else if(Distance-OC_Distance>184)
          {
            if(Set_Speed>66)
            {  
              Set_Speed=Set_Speed-(uint16)((Distance-OC_Distance)/1.8);
            }          
          }
        }
        else
        {
            LowFlagCount=0;
            LowFlag=0;
        }
    }
    }
}
#endif
#ifdef NB_Car
if(CSB_EN>=1)
{
    if(OC_Ramp_flag>=1)     
    {  
       PoDaoDisFlag=1;
       CSB_EN_=0;      
    }
    if(PoDaoDisFlag>=1)
      PoDapDisCount++;
    if(PoDapDisCount>888&&PoDaoDisFlag>=1)
    {
       PoDapDisCount=0;
       CSB_EN_=1;
       PoDaoDisFlag=0;
    }
    
    if(CSB_EN_>=1)  //超声波和坡道配合 防止超声波在坡道处回声 影响速度
    {      
      if(NB_DisCount0<KeepDis&&Distance>388)
      {
          EnconterFlag=1; 
          EnconterCount=0;
      }
      if(EnconterFlag==1)
          ++EnconterCount;
      if(EnconterCount<66&&EnconterFlag==1)
      {   
          if(OtherCar_Real_Speed>66)
            Set_Speed = OtherCar_Real_Speed-66;
          else if(OtherCar_Real_Speed>33)
            Set_Speed = OtherCar_Real_Speed-33;
          else
            Set_Speed = OtherCar_Real_Speed;
          if(Set_Speed<=0)
             Set_Speed=0; 
          if(Set_Speed+50>Real_Speed)
            Set_Speed=Set_Speed-20;
      }
      else
      {
          EnconterCount=0;
          EnconterFlag=0;
      }
    }
}
#endif
//#ifdef NB_Car         //红外对管 检测前车
 /*   if(OC_Ramp_flag>=1)     
    {  
       PoDaoDisFlag=1;
       CSB_EN=0;      
    }
    if(PoDaoDisFlag>=1)
      PoDapDisCount++;
    if(PoDapDisCount>888&&PoDaoDisFlag>=1)
    {
       PoDapDisCount=0;
       CSB_EN=1;
       PoDaoDisFlag=0;
    }
    if(CSB_EN>=1)  //超声波和坡道配合
    {  
      OC_noEnFlag=gpio_get(InfraredTube_Pin);   //测试用
      if(OC_noEnFlag==0&&Distance>488)
      {
          EnconterFlag=1; 
          EnconterCount=0;
      }
      if(EnconterFlag==1)
          ++EnconterCount;
      if(EnconterCount<20&&EnconterFlag==1)
      {   
          if(OtherCar_Real_Speed>66)
            Set_Speed = OtherCar_Real_Speed-66;
          else if(OtherCar_Real_Speed>33)
            Set_Speed = OtherCar_Real_Speed-33;
          else
            Set_Speed = OtherCar_Real_Speed;
          if(Set_Speed<=0)
             Set_Speed=0; 
          if(Set_Speed+50>Real_Speed)
            Set_Speed=Set_Speed-20;
      }
      else
      {
          EnconterCount=0;
          EnconterFlag=0;
      }
    }*/
//#endif 
}

