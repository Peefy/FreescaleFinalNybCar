#ifndef __BOMAKAIGUAN_H__
#define __BOMAKAIGUAN_H__

#define BoMa_Key1 PTB10       //宏定义拨码开关四个IO口
#define BoMa_Key2 PTB17
#define BoMa_Key3 PTA12
#define BoMa_Key4 PTB18

#define BoMa_Key_Up   1       //拨码开关状态宏定义
#define BoMa_Key_Down 0
//声明外部函数
extern void BoMaKaiGuan_init(void);        //拨码开关初始化
extern uint8 GetKeyStatus(PTXn_e ptxn);     //获取拨码开关状态
extern void Select_Direction(void);
extern void Scan_BoMaKaiGuan(void);
extern void Select_Speed(void);             //选择速度参数   
extern uint8 ServoEnable;

#endif