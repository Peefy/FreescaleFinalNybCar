#include "include.h"

#define DataQuantity  5    //数据的数量 控制发送变量的个数 牛A向牛B传送的数据数量 B发A接
#define DataQuantity_ 1    //数据的数量 控制发送变量的个数 牛B向牛A传送的数据数量 A发B接
int16 Send_Data16s[16]={0};     //存放16个16位数据，为发送的自己的参数
int16 Recv_Data16s[16]={0};     //存放16个16位数据，为接受的另一辆车的参数
uint8 Send_Enable=1;       //发送允许变量
uint8 Rcev_Enable=1;       //接收允许变量
uint8  RecvData8sBUFF[DataQuantity*2+2];   //接收缓冲区
uint8 Recv_Grade=0;        //接收到的第N个变量的标号
int16 Null=0;
/*************NRF24l01部分*************/
uint8 Send_buff[DATA_PACKET];
uint8 Recv_buff[DATA_PACKET];
uint8 relen;
/************以下是A发B接*************/
#ifdef NA_Car
void Send_To_OC_Mes(void)   //16位数据要拆成两个8位发送
{   
    char i;
    if(Send_Enable)
    {
       Send_Data16s[0]= (uint16)Real_Speed;      //用变量标识代替NULL时 同时修改 DataQuantity
       Send_Data16s[1]= (uint16)ShangWeiJiStop;
       Send_Data16s[2]= (uint16)Ramp_flag;
       Send_Data16s[3]= (uint16)ZhiDaoSpeed;     
       Send_Data16s[4]= (uint16)Car_Cmd;
       Send_Data16s[5]= (uint16)Null;
       Send_Data16s[6]= (uint16)Null;
       Send_Data16s[7]= (uint16)Null;  
       Send_Data16s[8]= (uint16)Null;
       Send_Data16s[9]= (uint16)Null;
       Send_Data16s[10]=(uint16)Null;
       Send_Data16s[11]=(uint16)Null;  
       Send_Data16s[12]=(uint16)Null;
       Send_Data16s[13]=(uint16)Null;
       Send_Data16s[14]=(uint16)Null;
       Send_Data16s[15]=(uint16)Null;
    }
    for(i=0;i<DataQuantity;i++)
    {
       Send_buff[i*2]   = (uint8)(Send_Data16s[i]>>8);  //发送高八位
       Send_buff[i*2+1] = (uint8)(Send_Data16s[i]);     //发送低八位    
    }  
}
#endif
#ifdef NB_Car
void Recieve_OC_Mes(void)
{  
   if(Rcev_Enable)
   {
   for(Recv_Grade=0;Recv_Grade<DataQuantity;Recv_Grade++)
   {
       Recv_Data16s[Recv_Grade] = Recv_buff[Recv_Grade*2]*256+Recv_buff[Recv_Grade*2+1];
       switch (Recv_Grade)       //用变量标识代替NULL时 同时修改 DataQuantity     
       {
         case 0  : OtherCar_Real_Speed  = Recv_Data16s[Recv_Grade];break;
         case 1  : ShangWeiJiStop       = Recv_Data16s[Recv_Grade];break;
         case 2  : OC_Ramp_flag         = Recv_Data16s[Recv_Grade];break;
         case 3  : OtherCar_ZhiDaoSpeed = Recv_Data16s[Recv_Grade];break;
         case 4  : Car_Cmd              = Recv_Data16s[Recv_Grade];break;
         case 5  : Null = Recv_Data16s[Recv_Grade];break;
         case 6  : Null = Recv_Data16s[Recv_Grade];break;
         case 7  : Null = Recv_Data16s[Recv_Grade];break; 
         case 8  : Null = Recv_Data16s[Recv_Grade];break; 
         case 9  : Null = Recv_Data16s[Recv_Grade];break; 
         case 10 : Null = Recv_Data16s[Recv_Grade];break; 
         case 11 : Null = Recv_Data16s[Recv_Grade];break; 
         case 12 : Null = Recv_Data16s[Recv_Grade];break; 
         case 13 : Null = Recv_Data16s[Recv_Grade];break; 
         case 14 : Null = Recv_Data16s[Recv_Grade];break; 
         case 15 : Null = Recv_Data16s[Recv_Grade];break;        
       }
       ZhiDaoSpeed=OtherCar_ZhiDaoSpeed+10;
       WanDaoSpeed=OtherCar_ZhiDaoSpeed-210;
   }
   }
}
#endif
/************以下是B发A接*************/
#ifdef NB_Car
void Send_To_OC_Mes(void)   //16位数据要拆成两个8位发送
{   
    char i;
    if(Send_Enable)
    {
       Send_Data16s[0]= (uint16)Distance;      //用变量标识代替NULL时 同时修改 DataQuantity
       Send_Data16s[1]= (uint16)Null;
       Send_Data16s[2]= (uint16)Null;
       Send_Data16s[3]= (uint16)Null;     
       Send_Data16s[4]= (uint16)Null;
       Send_Data16s[5]= (uint16)Null;
       Send_Data16s[6]= (uint16)Null;
       Send_Data16s[7]= (uint16)Null;  
       Send_Data16s[8]= (uint16)Null;
       Send_Data16s[9]= (uint16)Null;
       Send_Data16s[10]=(uint16)Null;
       Send_Data16s[11]=(uint16)Null;  
       Send_Data16s[12]=(uint16)Null;
       Send_Data16s[13]=(uint16)Null;
       Send_Data16s[14]=(uint16)Null;
       Send_Data16s[15]=(uint16)Null;
    }
    for(i=0;i<DataQuantity_;i++)
    {
       Send_buff[i*2]   = (uint8)(Send_Data16s[i]>>8);  //发送高八位
       Send_buff[i*2+1] = (uint8)(Send_Data16s[i]);     //发送低八位    
    }  
}
#endif
#ifdef NA_Car
void Recieve_OC_Mes(void)
{  
   if(Rcev_Enable)
   {
   for(Recv_Grade=0;Recv_Grade<DataQuantity_;Recv_Grade++)
   {
       Recv_Data16s[Recv_Grade] = Recv_buff[Recv_Grade*2]*256+Recv_buff[Recv_Grade*2+1];
       switch (Recv_Grade)       //用变量标识代替NULL时 同时修改 DataQuantity     
       {
         case 0  : OC_Distance = Recv_Data16s[Recv_Grade];break;
         case 1  : Null = Recv_Data16s[Recv_Grade];break;
         case 2  : Null = Recv_Data16s[Recv_Grade];break;
         case 3  : Null = Recv_Data16s[Recv_Grade];break;
         case 4  : Null = Recv_Data16s[Recv_Grade];break;
         case 5  : Null = Recv_Data16s[Recv_Grade];break;
         case 6  : Null = Recv_Data16s[Recv_Grade];break;
         case 7  : Null = Recv_Data16s[Recv_Grade];break; 
         case 8  : Null = Recv_Data16s[Recv_Grade];break; 
         case 9  : Null = Recv_Data16s[Recv_Grade];break; 
         case 10 : Null = Recv_Data16s[Recv_Grade];break; 
         case 11 : Null = Recv_Data16s[Recv_Grade];break; 
         case 12 : Null = Recv_Data16s[Recv_Grade];break; 
         case 13 : Null = Recv_Data16s[Recv_Grade];break; 
         case 14 : Null = Recv_Data16s[Recv_Grade];break; 
         case 15 : Null = Recv_Data16s[Recv_Grade];break;        
       }
   }
   }
}
#endif

/*************NRF24l01部分*************/
void PORTC_PORTD_IRQHandler()
{
    uint8  n = 0;    //引脚号
    
    //PTC18
    n = 18;
    if(PORTC_ISFR & (1 << n))          
    {
        PORTC_ISFR  = (1 << n);        //写1清中断标志位
#ifdef  NRF24L01_EN
        /*  以下为用户任务  */
        nrf_handler();
        relen = nrf_rx(Recv_buff,DATA_PACKET);            //等待接收一个数据包，数据存储在Recv_buff里
        Recieve_OC_Mes();
#endif
        
        //led(LED0,LED_ON);
        /*  以上为用户任务  */
    }
}
