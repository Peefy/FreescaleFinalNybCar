#ifndef _DISPLAY_H_
#define _DISPLAY_H_

/****************��ʾģʽѡ��******************/
//#define MyDisplay_Enable  1       //�궨����ʾ����������ʾģʽ�͸ı���ģʽ
#define HMIDisplay_Enable  1

extern void DisplayAD(void);
extern void DisplayAD_max(void);
extern void DisplayPage1(void);
extern void DisplayPage2(void);
extern void DisplayPage3(void);
extern void DisplayRoadType(void);
extern void MyDisplay(void);
extern uint8 KeyScan(void);
extern void Judge_OLEDkey_Status(void);

#endif