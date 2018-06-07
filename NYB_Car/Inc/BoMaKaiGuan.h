#ifndef __BOMAKAIGUAN_H__
#define __BOMAKAIGUAN_H__

#define BoMa_Key1 PTB10       //�궨�岦�뿪���ĸ�IO��
#define BoMa_Key2 PTB17
#define BoMa_Key3 PTA12
#define BoMa_Key4 PTB18

#define BoMa_Key_Up   1       //���뿪��״̬�궨��
#define BoMa_Key_Down 0
//�����ⲿ����
extern void BoMaKaiGuan_init(void);        //���뿪�س�ʼ��
extern uint8 GetKeyStatus(PTXn_e ptxn);     //��ȡ���뿪��״̬
extern void Select_Direction(void);
extern void Scan_BoMaKaiGuan(void);
extern void Select_Speed(void);             //ѡ���ٶȲ���   
extern uint8 ServoEnable;

#endif