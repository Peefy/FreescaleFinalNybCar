#ifndef __TWOCARS_COMMUNICATION_H__
#define __TWOCARS_COMMUNICATION_H__

#define A_To_B_S_NO1 0xcc
#define A_To_B_S_NO2 0xdd

#define B_To_A_S_NO1 0xbe
#define B_To_A_S_NO2 0xbf

/*************NRF24l01部分*************/
extern uint8 Send_buff[DATA_PACKET];
extern uint8 Recv_buff[DATA_PACKET];
extern uint8 Send_Enable;       //发送允许变量
extern uint8 Rcev_Enable;       //接收允许变量
extern uint8 relen;

extern void Send_To_OC_Mes(void);
extern void Recieve_OC_Mes(void);
extern void PORTC_PORTD_IRQHandler(void);

#endif