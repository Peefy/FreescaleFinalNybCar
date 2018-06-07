//���� NYB_Car �ĳ���  ������������dugu diaoling 
#include "common.h"
#include "include.h"   //������Ҫ��ͷ�ļ�

uint16 ControlTime=0;          //���PIT����ʱ����� 
uint8  PITCount=0;             //�ٶȻ�ȡ��ʱ����
uint8  HCSR04_PITCount=0;      //����������Ƶ��

void main(void)
{    
     NYB_Car_init();          //NYB ţA��ţB С����ʼ������      
     while(1)                     
     {   
        Start();                 //��ʱ����
        TimerRun();              //��ʱ��     
#ifdef  SlaveComputer_Enable     //��λ������
        LC_SendData();           //��λ�����ͺ���
        LC_ReceivedData();       //��λ�����ܺ���
        DELAY_MS(20);            //common ��ʱ20����
#endif 
#ifdef  NA_Car                                    //˫����������ģʽ ţA��ţB��������  
        #ifdef NRF24L01_EN
        Send_To_OC_Mes();                         //ţA��ţB��������
        nrf_tx(Send_buff,DATA_PACKET);            //����һ�����ݰ���Send_buff����Ϊ32�ֽڣ� 
        while(nrf_tx_state() == NRF_TXING);      //�ȴ��������
        //relen = nrf_rx(Recv_buff,DATA_PACKET);    //�ȴ�����һ�����ݰ������ݴ洢��Recv_buff�� �ⲿ�ж������ȡ����
        //Recieve_OC_Mes();                         //ţA������ܵ�������                      
        #endif
        DELAY_MS(10);                             //����NRF24L01�շ�Ƶ�ʼ�Һ����ˢ��Ƶ��
#endif  
#ifdef  NB_Car                                    //˫����������ģʽ ţA��ţB�������� 
        #ifdef NRF24L01_EN
        Send_To_OC_Mes();                         //ţB��ţA��������
        nrf_tx(Send_buff,DATA_PACKET);            //����һ�����ݰ���Send_buff����Ϊ32�ֽڣ�
        while(nrf_tx_state() == NRF_TXING);      //�ȴ��������
        relen = nrf_rx(Recv_buff,DATA_PACKET);    //�ȴ�����һ�����ݰ������ݴ洢��Recv_buff�� �ⲿ�ж������ȡ����
        Recieve_OC_Mes();                         //ţB������ܵ�������
        #endif
        #ifdef Game_EN
        Telecontrol();                            //ţAң��ţB
        #endif      
        DELAY_MS(18);                             //����NRF24L01�շ�Ƶ�ʼ�Һ����ˢ��Ƶ�� ţB��ţA��΢���� 
#endif                           
#ifdef  HMIDisplay_Enable     
        Gui();                                    //�����ʾ
        DisplayRoadType();                        //��ʾ·��
#endif                  
#ifdef  MyDisplay_Enable                 
        MyDisplay();                              //�����ʾ
#endif
        Scan_BoMaKaiGuan();                       //ɨ�貦�뿪�� 
#ifdef  HCSR04_Enable       
        Count_Dis();                              //�������
#endif   
     }
}

void PIT_IRQHandler(void)           //PIT�жϺ���
{
    if(PIT_TFLG(PIT0) == 1 )         //�ж��Ƿ� PIT0 �����ж� 5ms�ж�һ��
    {  
       DectectStartLine();           //��������� 
       #ifdef NA_Car
       Select_Speed();               //���� �ҽ�ֹ LOWFLAG  
       //wdog_feed();                //ι��
       #endif
#ifdef HMIDisplay_Enable
       key_IRQHandler();             //GUI�İ�������
#endif       
       AD_GetValue();                //��ʱ��ȡADֵ 
#ifdef GyroAccelScope_Enable 
       if(DisEn==0)                  //�ɼ���Ưʱ��������
          CarPoseGet();              //5ms��ȡmpu6050��ֵ
#endif
       New_AnalysisDecision();       //ͨ����з�����������������    
#ifdef Encoder_EN
       
       if(PITCount>2)               
       {  
          PITCount=0;
          Get_Real_Speed();         //10ms��ȡ������ת������ 
       } 
#endif
#ifdef Servo_EN
       if(ServoEnable>=1)           //�������ת������
       {
       #ifdef Servo_Normal_PID_Enable 
       Servo_PID();                 //�����PID����   
       #endif
       #ifdef Servo_ExpertFuzzy_PID_Enable 
       Servo_ExpertFuzzyPID();     //�����PID����
       #endif 
       }
       Servo_Debug();              //������� �ѻ��޸Ķ����ֵ ������FLASH��/
#endif 
#ifdef Motor_EN
       if(ControlTime>2)           //���10ms����һ�Σ����ڹ���Ƶ�������𵴷��ȣ�
       {    
           ControlTime=0;        
           Motor_Ctl();            //������ƺ���   ���а����ٶȲ��Ժ͵��PID
       }
#endif 
#ifdef HCSR04_Enable
       ++HCSR04_PITCount;          //��������ʱ����+1
       if(HCSR04_PITCount>14)      //������70MS����һ��
       {
           Start_HCSR04();         //����������
           HCSR04_PITCount=0;      //��������
       }
       
#endif
       if(AutoStart==1&&StartFlag==0)
          StartTime++;             //������ʱ   ���ں���Start();
       if(TimerRun_EN==1&&TimerRun_Flag==0)
          TimerRun_Time++;         //��ʱ�ܼ�ʱ ���ں���TimerRun
       PITCount++;                 //��ȡ�ٶȱ���+1
       ControlTime++;              //������Ʊ���+1 
       PIT_Flag_Clear(PIT0);       //���жϱ�־λ
    }
}


