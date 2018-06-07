#include "include.h"

uint8 DepartFlag=0;

void BoMaKaiGuan_init(void)   //拨码开关初始化
{
    gpio_init(BoMa_Key1, GPI, 1);          //四路拨码开关均初始化为上拉输入  
    port_init_NoALT(BoMa_Key1, PULLUP);
    gpio_init(BoMa_Key2, GPI, 1);
    port_init_NoALT(BoMa_Key1, PULLUP);
    gpio_init(BoMa_Key3, GPI, 1);
    port_init_NoALT(BoMa_Key1, PULLUP);
    gpio_init(BoMa_Key4, GPI, 1);
    port_init_NoALT(BoMa_Key1, PULLUP);
}
uint8 GetKeyStatus(PTXn_e ptxn)
{
    return gpio_get(ptxn);    //获取拨码开关状态
}

void Select_Direction(void)
{     
     if( BoMa_Key_Down == gpio_get(BoMa_Key3)) //开关ON：0 == GetKeyStatus(BoMa_Key1)  向下拨 拨码开关
     {       
        delay_fmq(10);                     
        if( BoMa_Key_Down == gpio_get(BoMa_Key3))
        {
            Race=AntiClockWise;  //跑道为逆时针
        }
     } 
     else if( BoMa_Key_Up == gpio_get(BoMa_Key3)) //开关ON：1 == GetKeyStatus(BoMa_Key1)  向上拨 拨码开关
     {       
        delay_fmq(10);                     
        if( BoMa_Key_Up == gpio_get(BoMa_Key3))
        {
            Race=ClockWise;      //跑道为顺时针
        }
     } 
}

void Select_Speed(void)
{
     if( BoMa_Key_Down == GetKeyStatus(BoMa_Key3)) //开关ON：0 == GetKeyStatus(BoMa_Key1)  向下拨 拨码开关
     {       
        delay_fmq(10);                     
        if( BoMa_Key_Down == GetKeyStatus(BoMa_Key3))
        {
             // ZhiDaoSpeed = ZD_Spd_L;
             // WanDaoSpeed = WD_Spd_L;
          //CSB_EN=0;
           Low_EN=0;
           if(DepartFlag==0)
           {  
              DepartFlag=1;
              if(OC_Distance<66)
                 AutoStart=1;
              else
              {
                 AutoStart=1;
                 ShangWeiJiStop=1;
              }
           }
        }
     } 
     else if( BoMa_Key_Up == GetKeyStatus(BoMa_Key3)) //开关ON：1 == GetKeyStatus(BoMa_Key1)  向上拨 拨码开关
     {       
        delay_fmq(10);                     
        if( BoMa_Key_Up == GetKeyStatus(BoMa_Key3))
        {
             //ZhiDaoSpeed = ZD_Spd_M;
             //WanDaoSpeed = WD_Spd_M;
          //CSB_EN=1;
          Low_EN=1;
          
        }
     }
}

void Scan_BoMaKaiGuan(void)
{
    WriteFlash_ADmax();         //只有拨码开关1按下使此函数才有效
#ifdef NA_Car
    //Select_Speed();             //选择速度参数   
#endif
}
