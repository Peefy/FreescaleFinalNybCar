#include "include.h"

#define DataQuantity  5    //���ݵ����� ���Ʒ��ͱ����ĸ��� ţA��ţB���͵��������� B��A��
#define DataQuantity_ 1    //���ݵ����� ���Ʒ��ͱ����ĸ��� ţB��ţA���͵��������� A��B��
int16 Send_Data16s[16]={0};     //���16��16λ���ݣ�Ϊ���͵��Լ��Ĳ���
int16 Recv_Data16s[16]={0};     //���16��16λ���ݣ�Ϊ���ܵ���һ�����Ĳ���
uint8 Send_Enable=1;       //�����������
uint8 Rcev_Enable=1;       //�����������
uint8  RecvData8sBUFF[DataQuantity*2+2];   //���ջ�����
uint8 Recv_Grade=0;        //���յ��ĵ�N�������ı��
int16 Null=0;
/*************NRF24l01����*************/
uint8 Send_buff[DATA_PACKET];
uint8 Recv_buff[DATA_PACKET];
uint8 relen;
/************������A��B��*************/
#ifdef NA_Car
void Send_To_OC_Mes(void)   //16λ����Ҫ�������8λ����
{   
    char i;
    if(Send_Enable)
    {
       Send_Data16s[0]= (uint16)Real_Speed;      //�ñ�����ʶ����NULLʱ ͬʱ�޸� DataQuantity
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
       Send_buff[i*2]   = (uint8)(Send_Data16s[i]>>8);  //���͸߰�λ
       Send_buff[i*2+1] = (uint8)(Send_Data16s[i]);     //���͵Ͱ�λ    
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
       switch (Recv_Grade)       //�ñ�����ʶ����NULLʱ ͬʱ�޸� DataQuantity     
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
/************������B��A��*************/
#ifdef NB_Car
void Send_To_OC_Mes(void)   //16λ����Ҫ�������8λ����
{   
    char i;
    if(Send_Enable)
    {
       Send_Data16s[0]= (uint16)Distance;      //�ñ�����ʶ����NULLʱ ͬʱ�޸� DataQuantity
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
       Send_buff[i*2]   = (uint8)(Send_Data16s[i]>>8);  //���͸߰�λ
       Send_buff[i*2+1] = (uint8)(Send_Data16s[i]);     //���͵Ͱ�λ    
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
       switch (Recv_Grade)       //�ñ�����ʶ����NULLʱ ͬʱ�޸� DataQuantity     
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

/*************NRF24l01����*************/
void PORTC_PORTD_IRQHandler()
{
    uint8  n = 0;    //���ź�
    
    //PTC18
    n = 18;
    if(PORTC_ISFR & (1 << n))          
    {
        PORTC_ISFR  = (1 << n);        //д1���жϱ�־λ
#ifdef  NRF24L01_EN
        /*  ����Ϊ�û�����  */
        nrf_handler();
        relen = nrf_rx(Recv_buff,DATA_PACKET);            //�ȴ�����һ�����ݰ������ݴ洢��Recv_buff��
        Recieve_OC_Mes();
#endif
        
        //led(LED0,LED_ON);
        /*  ����Ϊ�û�����  */
    }
}
