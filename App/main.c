//这是 NYB_Car 的程序  ——————dugu diaoling 
#include "common.h"
#include "include.h"   //包含必要的头文件

uint16 ControlTime=0;          //电机PIT控制时间变量 
uint8  PITCount=0;             //速度获取计时变量
uint8  HCSR04_PITCount=0;      //超声波工作频率

void main(void)
{    
     NYB_Car_init();          //NYB 牛A和牛B 小车初始化部分      
     while(1)                     
     {   
        Start();                 //延时起跑
        TimerRun();              //定时跑     
#ifdef  SlaveComputer_Enable     //上位机调试
        LC_SendData();           //下位机发送函数
        LC_ReceivedData();       //下位机接受函数
        DELAY_MS(20);            //common 延时20毫秒
#endif 
#ifdef  NA_Car                                    //双车比赛发车模式 牛A给牛B发送数据  
        #ifdef NRF24L01_EN
        Send_To_OC_Mes();                         //牛A给牛B发送数据
        nrf_tx(Send_buff,DATA_PACKET);            //发送一个数据包：Send_buff（包为32字节） 
        while(nrf_tx_state() == NRF_TXING);      //等待发送完成
        //relen = nrf_rx(Recv_buff,DATA_PACKET);    //等待接收一个数据包，数据存储在Recv_buff里 外部中断里面读取数据
        //Recieve_OC_Mes();                         //牛A处理接受到的数据                      
        #endif
        DELAY_MS(10);                             //控制NRF24L01收发频率及液晶屏刷新频率
#endif  
#ifdef  NB_Car                                    //双车比赛发车模式 牛A给牛B发送数据 
        #ifdef NRF24L01_EN
        Send_To_OC_Mes();                         //牛B给牛A发送数据
        nrf_tx(Send_buff,DATA_PACKET);            //发送一个数据包：Send_buff（包为32字节）
        while(nrf_tx_state() == NRF_TXING);      //等待发送完成
        relen = nrf_rx(Recv_buff,DATA_PACKET);    //等待接收一个数据包，数据存储在Recv_buff里 外部中断里面读取数据
        Recieve_OC_Mes();                         //牛B处理接受到的数据
        #endif
        #ifdef Game_EN
        Telecontrol();                            //牛A遥控牛B
        #endif      
        DELAY_MS(18);                             //控制NRF24L01收发频率及液晶屏刷新频率 牛B比牛A稍微慢点 
#endif                           
#ifdef  HMIDisplay_Enable     
        Gui();                                    //面板显示
        DisplayRoadType();                        //显示路况
#endif                  
#ifdef  MyDisplay_Enable                 
        MyDisplay();                              //面板显示
#endif
        Scan_BoMaKaiGuan();                       //扫描拨码开关 
#ifdef  HCSR04_Enable       
        Count_Dis();                              //距离计算
#endif   
     }
}

void PIT_IRQHandler(void)           //PIT中断函数
{
    if(PIT_TFLG(PIT0) == 1 )         //判断是否 PIT0 进入中断 5ms中断一次
    {  
       DectectStartLine();           //检测起跑线 
       #ifdef NA_Car
       Select_Speed();               //发车 且禁止 LOWFLAG  
       //wdog_feed();                //喂狗
       #endif
#ifdef HMIDisplay_Enable
       key_IRQHandler();             //GUI的按键输入
#endif       
       AD_GetValue();                //定时获取AD值 
#ifdef GyroAccelScope_Enable 
       if(DisEn==0)                  //采集零漂时辅助变量
          CarPoseGet();              //5ms获取mpu6050的值
#endif
       New_AnalysisDecision();       //通过电感分析赛道并做出处理    
#ifdef Encoder_EN
       
       if(PITCount>2)               
       {  
          PITCount=0;
          Get_Real_Speed();         //10ms获取编码器转速脉冲 
       } 
#endif
#ifdef Servo_EN
       if(ServoEnable>=1)           //舵机允许转动变量
       {
       #ifdef Servo_Normal_PID_Enable 
       Servo_PID();                 //舵机的PID函数   
       #endif
       #ifdef Servo_ExpertFuzzy_PID_Enable 
       Servo_ExpertFuzzyPID();     //舵机的PID函数
       #endif 
       }
       Servo_Debug();              //舵机调试 脱机修改舵机中值 并存入FLASH中/
#endif 
#ifdef Motor_EN
       if(ControlTime>2)           //电机10ms控制一次，调节过于频繁容易震荡发热！
       {    
           ControlTime=0;        
           Motor_Ctl();            //电机控制函数   其中包括速度策略和电机PID
       }
#endif 
#ifdef HCSR04_Enable
       ++HCSR04_PITCount;          //超声波计时变量+1
       if(HCSR04_PITCount>14)      //超声波70MS启动一次
       {
           Start_HCSR04();         //启动超声波
           HCSR04_PITCount=0;      //计数清零
       }
       
#endif
       if(AutoStart==1&&StartFlag==0)
          StartTime++;             //发车计时   用于函数Start();
       if(TimerRun_EN==1&&TimerRun_Flag==0)
          TimerRun_Time++;         //定时跑计时 用于函数TimerRun
       PITCount++;                 //获取速度变量+1
       ControlTime++;              //电机控制变量+1 
       PIT_Flag_Clear(PIT0);       //清中断标志位
    }
}


