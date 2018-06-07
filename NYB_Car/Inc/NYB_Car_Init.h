#ifndef _NYB_CAR_INIT_H_
#define _NYB_CAR_INIT_H_


/*****************AD IO口宏定义*****************/
#define AD_L        ADC0_SE4a   //  PTE21 
#define AD_M        ADC0_SE2    //  PTE18
#define AD_R        ADC0_SE6a   //  PTE19
#define AD_FL       ADC0_SE0    //  PTE20
#define AD_FR       ADC0_SE5a   //  PTE17
#define Cell_AD     ADC0_SE3    //  PTE22
#define Key_AD      ADC0_SE1    //  PTE16

#define StartLine PTA13

/********8*******声明全局函数******************/
extern void NYB_Car_init(void);
extern void PIT_IRQHandler(void);      // 声明一下PIT函数
extern void uart1_test_handler(void);  // 声明一下UART1函数
extern void CarUARTSendbyte(uint8 data);
extern void UART1_init(void);
extern void MyDelay_MS(uint16 ms);
extern void All_Test(void);

//#define SlaveComputer_Enable 1     //决定是上位机模式 还是双车通信模式


#define NA_Car    1           //宏定义NA后 是双车的A 两个不能同时宏 否则出错
//#define NB_Car    1         //宏定义NB后 是双车的B 
//#define HCSR04_Enable 1       //启用超声波必须 禁用上位机模式

#define NRF24L01_EN 1
//#define GyroAccelScope_Enable 1
#define SoundEnable 1    //是否开启声音 牛B有音 牛A无音只有开机音
#define PIT_Enable 1

#endif