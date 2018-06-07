#include "include.h"

void NYB_Car_init(void)
{
       led_init(LED0);      //���İ���Ŀǰ�������ƿ���ʹ��
       led_init(LED1);
       led(LED0,LED_OFF);  
       led(LED1,LED_OFF);   //����ָʾ��

       gpio_init(StartLine, GPI, 1);
       port_init_NoALT(StartLine, PULLUP);   //�����߼���ʼ�� ���� ţA��ͣ ţB��ͣ
      
       //��м��AD��ʼ�� �����������������
       adc_init(AD_FL);   //AD1��ʼ��  ����
       adc_init(AD_L);    //AD2��ʼ��  ����
       adc_init(AD_M);    //AD3��ʼ��  ����
       adc_init(AD_R);    //AD4��ʼ��  ����
       adc_init(AD_FR);   //AD5��ʼ��  ����    
       adc_init(Cell_AD);  //��ص������AD��ʼ��  //Cell_AD��ʼ��
       
       //OLEDҺ������ʼ������
       LCD_Init();
              
       flash_init();         //MKL26Z4�ڲ�flash��ʼ�� ���ڴ洢AD��һ������ �Ͷ����ֵ
       
       BoMaKaiGuan_init(); //���뿪�س�ʼ�� 
       //���������ʼ�� ��¼���������ص��������ڵ����PID
       lptmr_pulse_init(LPT0_ALT2,0xffff,LPT_Falling);   
       lptmr_pulse_clean();        
       
       ReadFlash_();       //��ȡ������ֵ�������ֵ����������Ư
        
       //MotorPWM��ʼ��,10KHz,��ռ�ձ�Ϊ1000
       tpm_pwm_init(TPM0,TPM_CH0,MOTOR_Hz,0); //��ʼ�� PWM PTD0
       tpm_pwm_init(TPM0,TPM_CH1,MOTOR_Hz,0); //��ʼ�� PWM PTD1  �����PWM
       //SevorPWM��ʼ����100Hz,��ռ�ձ�Ϊ1000
       if(SerMid_Debug<8000&&SerMid_Debug>3000)             //��ֹ��FLASH�ж����������쳣
           tpm_pwm_init(TPM2, TPM_CH0,SERVO_Hz,SerMid_Debug);   //��ʼ�� PWM PTB2  �����PWM
       //else
       //tpm_pwm_init(TPM2, TPM_CH0,SERVO_Hz,SERVO_MID);    //��ʼ�� PWM PTB2  �����PWM
       
#ifdef MyDisplay_Enable                //�Զ������ʾ ������
       LCD_P6x8Str(0,0,"AD_000");
       LCD_P6x8Str(45,0,"AD_Max");
       LCD_P6x8Str(85,0,"AD_1000"); 
       LCD_P6x8Str(0,6,"Cell");
       LCD_P6x8Str(65,6,"Key");
#endif
#ifdef KalmanFilter_Enable     //�Ƿ���õ����뵥����������˲�
       AllKalmanFilterInit();  //�������˲�����ʼ�� �Ե�еĲ���ֵ�������˲�
#endif    
#ifdef SoundEnable      
       sound_init();           //������������ʼ������       
#endif  
#ifdef NB_Car     
       kaiji_fmq();            //������ 
#endif 
#ifdef HCSR04_Enable       
       HCSR04_Init();          //NB�ĳ�������ʼ��
       //InfraredTube_Init();  //����Թܵĳ�ʼ��
#endif       
       pit_init_ms(PIT0, 5);    //PIT0��ʼ������ʱʱ��5ms        
       set_vector_handler(PIT_VECTORn ,PIT_IRQHandler);  //����PIT0���жϷ�����Ϊ PIT0_IRQHandler
#ifdef PIT_Enable       
       enable_irq (PIT_IRQn);   //ʹ��PIT��������PIT�����ж�
#endif 
       //pit_init_us(PIT1,1);   //PIT1��ʼ������ʱʱ��1us
#ifdef SlaveComputer_Enable   
       HIT_LC_Init();  //��λ����ʼ������ ���� ���� ���ڳ�ʼ��  
#endif
       HIT_LC_Init();  //���ǳ�ʼ������ ��ֹ����
#ifdef NRF24L01_EN       
       while(!nrf_init()){}                 //��ʼ��NRF24L01+ ,�ȴ���ʼ���ɹ�Ϊֹ
       set_vector_handler(PORTC_PORTD_VECTORn ,PORTC_PORTD_IRQHandler);   //���� PORTE ���жϸ�λ����Ϊ PORTE_VECTORn
       enable_irq(PORTC_PORTD_IRQn);         //ʼ���ж�
#endif  
#ifdef GyroAccelScope_Enable      
       MPU_6050_Init();                      //��������ٶȼƵĳ�ʼ�� ���ڽ��㳵����̬
#endif        
       Stop();         //ÿ�γ�ʼ��Ϊͣ�� ����λ����������ֹͣ
}
//��λ����ش�����������
void UART1_init(void)
{
   uart_init(UART1,115200);            //���ڲ�����Ϊ115200
   uart_rx_irq_en(UART1);              //ʹ�ܴ����ж� �жϽ�������
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

void All_Test(void)      //������� ���Զ�����
{
   Set_Servo_PWM((int)(+SERVO_RANGE_L/2.0));   //���
   DELAY_MS(300);
   Set_Servo_PWM((int)(-SERVO_RANGE_R/2.0));   //�Ҵ�
   DELAY_MS(300);
   Set_Servo_PWM(0);                           //����
   DELAY_MS(200);
   ok_fmq(); 
   Run();
}
 
void All_Init(void)     //������� �����־λ �ٵ���һ�ο���CSB ,����ֹ��������������ģʽ
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

