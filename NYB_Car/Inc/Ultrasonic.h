#ifndef _ULTRASONIC_H_
#define _ULTRASONIC_H_

/********超声波0接口宏定义********/
#define Trigger0_Pin PTA14     //产生脉冲引脚  
#define Trigger0      PTXn_T(Trigger0_Pin,OUT)
#define Echo0_Pin PTA15        //回波引脚
#define Echo0         gpio_get(Echo0_Pin)

/********超声波1接口宏定义********/
#define Trigger1_Pin PTC3     //产生脉冲引脚  
#define Trigger1      PTXn_T(Trigger1_Pin,OUT)
#define Echo1_Pin PTC4        //回波引脚
#define Echo1         gpio_get(Echo1_Pin)

/**********红外对管初始化****************/
#define InfraredTube_Pin PTA14
#define InfraredTube gpio_get(InfraredTube_Pin)
#define Detected 1

extern uint16 NB_DisCount0;
extern uint16 NB_DisCount1; //我爱你
extern uint8 NYB_Warning;
extern uint8 EnconterFlag;
extern uint8 CSB_EN;
extern uint8 Low_EN;
extern uint8 OC_noEnFlag;
extern void Start_HCSR04(void);
extern void Count_Dis(void);
extern void HCSR04_Init(void);
extern void InfraredTube_Init(void);
extern void NYB_DisCtl(void);

#endif