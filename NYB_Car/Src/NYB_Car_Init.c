#include "include.h"

void NYB_Car_init(void)
{
       led_init(LED0);      //核心版上目前就两个灯可以使用
       led_init(LED1);
       led(LED0,LED_OFF);  
       led(LED1,LED_OFF);   //开机指示灯

       gpio_init(StartLine, GPI, 1);
       port_init_NoALT(StartLine, PULLUP);   //起跑线检测初始化 上拉 牛A先停 牛B后停
      
       //电感检测AD初始化 三个横电感两个竖电感
       adc_init(AD_FL);   //AD1初始化  左上
       adc_init(AD_L);    //AD2初始化  左下
       adc_init(AD_M);    //AD3初始化  中下
       adc_init(AD_R);    //AD4初始化  右下
       adc_init(AD_FR);   //AD5初始化  右上    
       adc_init(Cell_AD);  //电池电量检测AD初始化  //Cell_AD初始化
       
       //OLED液晶屏初始化部分
       LCD_Init();
              
       flash_init();         //MKL26Z4内部flash初始化 用于存储AD归一化数据 和舵机中值
       
       BoMaKaiGuan_init(); //拨码开关初始化 
       //脉冲计数初始化 记录编码器返回的脉冲用于电机的PID
       lptmr_pulse_init(LPT0_ALT2,0xffff,LPT_Falling);   
       lptmr_pulse_clean();        
       
       ReadFlash_();       //读取电感最大值、舵机中值、陀螺仪零漂
        
       //MotorPWM初始化,10KHz,满占空比为1000
       tpm_pwm_init(TPM0,TPM_CH0,MOTOR_Hz,0); //初始化 PWM PTD0
       tpm_pwm_init(TPM0,TPM_CH1,MOTOR_Hz,0); //初始化 PWM PTD1  电机的PWM
       //SevorPWM初始化，100Hz,满占空比为1000
       if(SerMid_Debug<8000&&SerMid_Debug>3000)             //防止从FLASH中读出的数据异常
           tpm_pwm_init(TPM2, TPM_CH0,SERVO_Hz,SerMid_Debug);   //初始化 PWM PTB2  舵机的PWM
       //else
       //tpm_pwm_init(TPM2, TPM_CH0,SERVO_Hz,SERVO_MID);    //初始化 PWM PTB2  舵机的PWM
       
#ifdef MyDisplay_Enable                //自定义的显示 测试用
       LCD_P6x8Str(0,0,"AD_000");
       LCD_P6x8Str(45,0,"AD_Max");
       LCD_P6x8Str(85,0,"AD_1000"); 
       LCD_P6x8Str(0,6,"Cell");
       LCD_P6x8Str(65,6,"Key");
#endif
#ifdef KalmanFilter_Enable     //是否采用单输入单输出卡尔曼滤波
       AllKalmanFilterInit();  //卡尔曼滤波器初始化 对电感的采样值的噪声滤波
#endif    
#ifdef SoundEnable      
       sound_init();           //蜂鸣器声音初始化部分       
#endif  
#ifdef NB_Car     
       kaiji_fmq();            //开机音 
#endif 
#ifdef HCSR04_Enable       
       HCSR04_Init();          //NB的超声波初始化
       //InfraredTube_Init();  //红外对管的初始化
#endif       
       pit_init_ms(PIT0, 5);    //PIT0初始化，定时时间5ms        
       set_vector_handler(PIT_VECTORn ,PIT_IRQHandler);  //设置PIT0的中断服务函数为 PIT0_IRQHandler
#ifdef PIT_Enable       
       enable_irq (PIT_IRQn);   //使能PIT，即允许PIT产生中断
#endif 
       //pit_init_us(PIT1,1);   //PIT1初始化，定时时间1us
#ifdef SlaveComputer_Enable   
       HIT_LC_Init();  //下位机初始化函数 其中 包括 串口初始化  
#endif
       HIT_LC_Init();  //总是初始化串口 防止死机
#ifdef NRF24L01_EN       
       while(!nrf_init()){}                 //初始化NRF24L01+ ,等待初始化成功为止
       set_vector_handler(PORTC_PORTD_VECTORn ,PORTC_PORTD_IRQHandler);   //设置 PORTE 的中断复位函数为 PORTE_VECTORn
       enable_irq(PORTC_PORTD_IRQn);         //始能中断
#endif  
#ifdef GyroAccelScope_Enable      
       MPU_6050_Init();                      //陀螺体加速度计的初始化 用于解算车的姿态
#endif        
       Stop();         //每次初始化为停车 由上位机启动或者停止
}
//上位机相关串口三个函数
void UART1_init(void)
{
   uart_init(UART1,115200);            //串口波特率为115200
   uart_rx_irq_en(UART1);              //使能串口中断 中断接受数据
   set_vector_handler(UART1_VECTORn , uart1_test_handler); 
}
void CarUARTSendbyte(uint8 data)
{
   uart_putByte(UART1, data);
}

void MyDelay_MS(uint16 ms)
{
   DELAY_MS(ms);
}

void All_Test(void)      //用于面板 测试舵机电机
{
   Set_Servo_PWM((int)(+SERVO_RANGE_L/2.0));   //左打
   DELAY_MS(300);
   Set_Servo_PWM((int)(-SERVO_RANGE_R/2.0));   //右打
   DELAY_MS(300);
   Set_Servo_PWM(0);                           //打正
   DELAY_MS(200);
   ok_fmq(); 
   Run();
}
 
void All_Init(void)     //用于面板 清零标志位 再调用一次开启CSB ,即禁止超声波开启单车模式
{  
   LCD_P6x8Str(7,7,"   init !      ");
   static uint8 Inittime=0;
   TimerRun_EN=0;
   AutoStart=0;
   TimerRun_s = 2;   
   fDistance=0;
   Distance=0; 
   SpeedingFlag=0;
   MotorOverloadFlag=0;
   OutofRangeFlag=0;
   EnconterFlag=0;
   Stop();   
   switch(Inittime)     
    {
      case 0:
        CSB_EN=0; 
        Rcev_Enable=1;
        break;
      case 1:
        CSB_EN=1;
        Rcev_Enable=0;
        break;
    }     
    if(++Inittime>=2)
      Inittime=0;   
    ok_fmq();
}

