#ifndef _ULTRASONIC_H_
#define _ULTRASONIC_H_

/********������0�ӿں궨��********/
#define Trigger0_Pin PTA14     //������������  
#define Trigger0      PTXn_T(Trigger0_Pin,OUT)
#define Echo0_Pin PTA15        //�ز�����
#define Echo0         gpio_get(Echo0_Pin)

/********������1�ӿں궨��********/
#define Trigger1_Pin PTC3     //������������  
#define Trigger1      PTXn_T(Trigger1_Pin,OUT)
#define Echo1_Pin PTC4        //�ز�����
#define Echo1         gpio_get(Echo1_Pin)

/**********����Թܳ�ʼ��****************/
#define InfraredTube_Pin PTA14
#define InfraredTube gpio_get(InfraredTube_Pin)
#define Detected 1

extern uint16 NB_DisCount0;
extern uint16 NB_DisCount1; //�Ұ���
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