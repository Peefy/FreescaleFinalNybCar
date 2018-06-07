#ifndef _NYB_CAR_INIT_H_
#define _NYB_CAR_INIT_H_


/*****************AD IO�ں궨��*****************/
#define AD_L        ADC0_SE4a   //  PTE21 
#define AD_M        ADC0_SE2    //  PTE18
#define AD_R        ADC0_SE6a   //  PTE19
#define AD_FL       ADC0_SE0    //  PTE20
#define AD_FR       ADC0_SE5a   //  PTE17
#define Cell_AD     ADC0_SE3    //  PTE22
#define Key_AD      ADC0_SE1    //  PTE16

#define StartLine PTA13

/********8*******����ȫ�ֺ���******************/
extern void NYB_Car_init(void);
extern void PIT_IRQHandler(void);      // ����һ��PIT����
extern void uart1_test_handler(void);  // ����һ��UART1����
extern void CarUARTSendbyte(uint8 data);
extern void UART1_init(void);
extern void MyDelay_MS(uint16 ms);
extern void All_Test(void);

//#define SlaveComputer_Enable 1     //��������λ��ģʽ ����˫��ͨ��ģʽ


#define NA_Car    1           //�궨��NA�� ��˫����A ��������ͬʱ�� �������
//#define NB_Car    1         //�궨��NB�� ��˫����B 
//#define HCSR04_Enable 1       //���ó��������� ������λ��ģʽ

#define NRF24L01_EN 1
//#define GyroAccelScope_Enable 1
#define SoundEnable 1    //�Ƿ������� ţB���� ţA����ֻ�п�����
#define PIT_Enable 1

#endif