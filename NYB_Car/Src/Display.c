#include "include.h"

int MyPageNum=0;                  //OLED翻页变量

void Judge_OLEDkey_Status(void)     //AD按键是否按下状态判断
{
     //判断OLED上Key的状态
    if(absi(AD_Value_Key0 - Key_UP_Value)<15)
    {
       OLED_Key_Status = UP;
    }
    else if(absi(AD_Value_Key0 - Key_DOWN_Value)<15)
    {
       OLED_Key_Status = DOWN;
    }
    else if(absi(AD_Value_Key0 - Key_LEFT_Value)<15)
    {
       OLED_Key_Status = LEFT;
    }
    else if(absi(AD_Value_Key0 - Key_RIGHT_Value)<15)
    {
       OLED_Key_Status = RIGHT;
    }
    else if(absi(AD_Value_Key0 - Key_OK_Value)<15)
    {
       OLED_Key_Status = OK;
    }
    else
    {
       OLED_Key_Status = NO;
    }
#ifdef NB_Car
    if(absi(AD_Value_Key0 - 33)<15)
    {
       OLED_Key_Status = UP;
    }
    else if(absi(AD_Value_Key0 - 915)<15)
    {
       OLED_Key_Status = DOWN;
    }
    else if(absi(AD_Value_Key0 - 476)<15)
    {
       OLED_Key_Status = LEFT;
    }
    else if(absi(AD_Value_Key0 - 649)<15)
    {
       OLED_Key_Status = RIGHT;
    }
    else if(absi(AD_Value_Key0 - 294)<15)
    {
       OLED_Key_Status = OK;
    }
    else
    {
       OLED_Key_Status = NO;
    }
#endif
}

uint8 KeyScan(void)     //用于面板模块
{
    if(absi(AD_Value_Key0 - Key_UP_Value)<15)
    {
       OLED_Key_Status = UP;
    }
    else if(absi(AD_Value_Key0 - Key_DOWN_Value)<15)
    {
       OLED_Key_Status = DOWN;
    }
    else if(absi(AD_Value_Key0 - Key_LEFT_Value)<15)
    {
       OLED_Key_Status = LEFT;
    }
    else if(absi(AD_Value_Key0 - Key_RIGHT_Value)<15)
    {
       OLED_Key_Status = RIGHT;
    }
    else if(absi(AD_Value_Key0 - Key_OK_Value)<15)
    {
       OLED_Key_Status = OK;
    }
    else
    {
       OLED_Key_Status = NO;
    }
    return OLED_Key_Status;
}

void DisplayAD(void)
{
        char string[6];      
        //显示原始AD值
        sprintf(string, "%5d",AD_Value_F_FL0);   //sprintf 将数据打印到字符串中
        LCD_P6x8Str(0,1,string);
        sprintf(string, "%5d",AD_Value_F_L0);
        LCD_P6x8Str(0,2,string);
        sprintf(string, "%5d",AD_Value_F_M0);
        LCD_P6x8Str(0,3,string);
        sprintf(string, "%5d",AD_Value_F_R0);
        LCD_P6x8Str(0,4,string);
        sprintf(string, "%5d",AD_Value_F_FR0);
        LCD_P6x8Str(0,5,string);
        //显示最大AD值
        sprintf(string, "%5d",F_FL_MAX);
        LCD_P6x8Str(45,1,string);
        sprintf(string, "%5d",F_L_MAX);
        LCD_P6x8Str(45,2,string);
        sprintf(string, "%5d",F_M_MAX);
        LCD_P6x8Str(45,3,string);
        sprintf(string, "%5d",F_R_MAX);
        LCD_P6x8Str(45,4,string);
        sprintf(string, "%5d",F_FR_MAX);
        LCD_P6x8Str(45,5,string);
        //显示归一化AD值
        sprintf(string, "%5d",AD_Value_F_FL);
        LCD_P6x8Str(85,1,string);
        sprintf(string, "%5d",AD_Value_F_L);
        LCD_P6x8Str(85,2,string);
        sprintf(string, "%5d",AD_Value_F_M);
        LCD_P6x8Str(85,3,string);
        sprintf(string, "%5d",AD_Value_F_R);
        LCD_P6x8Str(85,4,string);
        sprintf(string, "%5d",AD_Value_F_FR);
        LCD_P6x8Str(85,5,string);
        //显示电池电量
        sprintf(string, "%5d",AD_Value_Cell);
        LCD_P6x8Str(24,6,string);
        //显示舵机打角
        sprintf(string, "%5d",AD_Value_Key);
        LCD_P6x8Str(85,6,string);
}
void DisplayAD_max(void)
{
  char string[6];
  sprintf(string, "%5d",(uint32)max[0][0]);
  LCD_P6x8Str(0,1,string);
  sprintf(string, "%5d",(uint32)max[1][0]);
  LCD_P6x8Str(0,2,string);
  sprintf(string, "%5d",(uint32)max[2][0]);
  LCD_P6x8Str(0,3,string);
  sprintf(string, "%5d",AD_Value_F_L);
  LCD_P6x8Str(0,6,string);
  
  sprintf(string, "%5d",(uint32)max[0][1]);
  LCD_P6x8Str(45,1,string);
  sprintf(string, "%5d",(uint32)max[1][1]);
  LCD_P6x8Str(45,2,string);
  sprintf(string, "%5d",(uint32)max[2][1]);
  LCD_P6x8Str(45,3,string);
  sprintf(string, "%5d",AD_Value_F_M);
  LCD_P6x8Str(45,6,string);
  
  sprintf(string, "%5d",(uint32)max[0][2]);
  LCD_P6x8Str(85,1,string);
  sprintf(string, "%5d",(uint32)max[1][2]);
  LCD_P6x8Str(85,2,string);
  sprintf(string, "%5d",(uint32)max[2][2]);
  LCD_P6x8Str(85,3,string);
  sprintf(string, "%5d",AD_Value_F_R);
  LCD_P6x8Str(85,6,string);
}
void DisplayPage1(void)
{
  char string[6];
  
  sprintf(string,"%5d",(int)Real_Speed);
  LCD_P6x8Str(0,1,string);
  sprintf(string, "%5d",(int32)Servo_P);
  LCD_P6x8Str(45,1,string);
  sprintf(string, "%5d",(int32)Servo_D);
  LCD_P6x8Str(85,1,string); 
  
  sprintf(string, "%5d",MOTOR_P);
  LCD_P6x8Str(0,3,string);
  sprintf(string, "%5d",MOTOR_I);
  LCD_P6x8Str(45,3,string);
  sprintf(string, "%5d",MOTOR_D);
  LCD_P6x8Str(85,3,string);
  
  sprintf(string, "%5d",ZhiDaoCount);
  LCD_P6x8Str(0,5,string);
  sprintf(string, "%5d",WanDaoCount);
  LCD_P6x8Str(45,5,string);
  sprintf(string, "%5d",YiChangCount);
  LCD_P6x8Str(85,5,string);
  sprintf(string, "%4d",ShiZiWanCount);
  LCD_P6x8Str(45,6,string);
}
void DisplayPage2(void)
{
  char string[6];
  sprintf(string, "%5d",(int32)AD_Value_F_L);
  LCD_P6x8Str(0,1,string);
  sprintf(string, "%5d",(int32)AD_Value_F_M);
  LCD_P6x8Str(45,1,string);
  sprintf(string, "%5d",(int32)AD_Value_F_R);
  LCD_P6x8Str(85,1,string); 
  
  sprintf(string, "%5d",(int32)AD_Value_F_FL);
  LCD_P6x8Str(0,3,string);
  sprintf(string, "%5d",(int32)AD_Value_F_FR);
  LCD_P6x8Str(45,3,string);
  sprintf(string, "%5d",(int32)FL_FR_add);
  LCD_P6x8Str(85,3,string);
  
  sprintf(string, "%5d",(int32)e_Heng);
  LCD_P6x8Str(0,5,string);

  sprintf(string, "%5d",(int32)e_Shu);
  LCD_P6x8Str(45,5,string);
  sprintf(string, "%5d",(int32)e);
  LCD_P6x8Str(85,5,string); 

  sprintf(string, "%5d",(int32)F_L_M_add);
  LCD_P6x8Str(7,6,string); 
 
  LCD_P6x8Str(45,6,"             ");

  switch (RoadType)
  {    
  case ZhiDao  : LCD_P6x8Str(69,6,"ZhiDao  ");break;
  case WanDao  : LCD_P6x8Str(69,6,"WanDao  ");break;
  case ShiZiWan: LCD_P6x8Str(69,6,"ShiZiWan");break;
  case SharpWan: LCD_P6x8Str(69,6,"SharpWan");break;
  case YiChang : LCD_P6x8Str(69,6,"YiChang ");break;
  case PoDao   : LCD_P6x8Str(69,6,"PoDao   ");break;
  case ZD_Lose : LCD_P6x8Str(69,6,"ZD_Lose ");break;
  case WD_Lose : LCD_P6x8Str(69,6,"WD_Lose ");break;
  
  default      : LCD_P6x8Str(69,6,"default ");break;  
  }

}

void DisplayPage3(void)
{ 
    char string[6];
    sprintf(string, "%5d",ZhiDaoSpeed);
    LCD_P6x8Str(0,1,string);
    sprintf(string, "%5d",WanDaoSpeed);
    LCD_P6x8Str(45,1,string);
}

void DisplayDangerType(void)
{ 
  if(EnconterFlag)
  {
     LCD_P6x8Str(7,7,"    Warning !    "); 
     if(BeeCount<233)
       kaiji_fmq();
     else
       offWARNING;
       
  }
  else if(Ramp_flag)
  {
     LCD_P6x8Str(7,7,"    Po Dao !    ");  
     WARNING;
  }
  else if(LowFlag)
  {
     LCD_P6x8Str(7,7,"    Low Low !   ");  
     WARNING;
  }
  else if(OutofRangeFlag) 
  {
     LCD_P6x8Str(7,7,"    OutOfRace!   "); 
     if(BeeCount<233)
       WARNING;
     else
       offWARNING;
       
  }
  else if(MotorOverloadFlag)
  {
     LCD_P6x8Str(7,7,"    Overload !    "); 
     if(BeeCount<233)
       WARNING;
     else
       offWARNING;
  }
  else if(SpeedingFlag)
  {
     LCD_P6x8Str(7,7,"    Speeding !    "); 
     if(BeeCount<233)
       WARNING;
     else
       offWARNING;  
  }
#ifdef GyroAccelScope_Enable
  else if(Accel_Z==0||Angle_Y==-1)
  {
     #ifdef  NA_Car
     LCD_P6x8Str(9,7,"NAmpu init lose!");
     #endif
     #ifdef  NB_Car
     LCD_P6x8Str(9,7,"NBmpu init lose!");
     #endif
  }
#endif 
  else
  {
  #ifdef  NA_Car 
  LCD_P6x8Str(31,7,"NA  Car !  ");
  #endif
  #ifdef  NB_Car 
  LCD_P6x8Str(31,7,"NB  Car !  ");
  #endif
  offWARNING;
  }
}

void DisplayRoadType(void)
{  
  LCD_P6x8Str(0,6,"RoadType");
  switch (RoadType)
  {    
  case ZhiDao  : LCD_P6x8Str(69,6,"ZhiDao  ");break;
  case WanDao  : LCD_P6x8Str(69,6,"WanDao  ");break;
  case ShiZiWan: LCD_P6x8Str(69,6,"ShiZiWan");break;
  case SharpWan: LCD_P6x8Str(69,6,"SharpWan");break;
  case YiChang : LCD_P6x8Str(69,6,"YiChang ");break;
  case PoDao   : LCD_P6x8Str(69,6,"PoDao   ");break;
  case ZD_Lose : LCD_P6x8Str(69,6,"ZD_Lose ");break;
  case WD_Lose : LCD_P6x8Str(69,6,"WD_Lose ");break;
  default      : LCD_P6x8Str(69,6,"default ");break;  
  
  }
  DisplayDangerType();
}
void MyDisplay(void)
{
     if(OLED_Key_Status == DOWN)  //下方向按键按下
        { 
          down_fmq();                //下方向按键键音
          DELAY_MS(500);             //延时消抖
          MyPageNum++;                 //翻页变量加一          
          if(MyPageNum>3)
          {
            MyPageNum=0;
          }
          if(MyPageNum==0)
          {  
             LCD_CLS();                  //清屏
             LCD_P6x8Str(0,0,"AD_000");
             LCD_P6x8Str(45,0,"AD_Max");
             LCD_P6x8Str(85,0,"AD_1000");   
             LCD_P6x8Str(0,6,"Cell");
             LCD_P6x8Str(65,6,"PWM");                         
          }
          else if (MyPageNum==1)
          {  
             LCD_CLS();
             LCD_P6x8Str(0,0,"Spd");
             LCD_P6x8Str(45,0,"Se_P");
             LCD_P6x8Str(85,0,"Se_D");
             LCD_P6x8Str(0,2,"Mo_P");
             LCD_P6x8Str(45,2,"Mo_I");
             LCD_P6x8Str(85,2,"Mo_D");
             LCD_P6x8Str(0,4,"Zhi_c");
             LCD_P6x8Str(45,4,"Wan_c");
             LCD_P6x8Str(85,4,"Yi_c");
             LCD_P6x8Str(0,6,"ShiZi_c");
          }
          else if (MyPageNum==2)
          {  
             LCD_CLS();                  //清屏
             LCD_P6x8Str(0,0,"AD_L");
             LCD_P6x8Str(45,0,"AD_M");
             LCD_P6x8Str(85,0,"AD_R");
             LCD_P6x8Str(0,2,"AD_FL");
             LCD_P6x8Str(45,2,"AD_FR");
             LCD_P6x8Str(85,2,"Shu");
             LCD_P6x8Str(0,4,"e_Heng");
             LCD_P6x8Str(45,4,"e_Shu");
             LCD_P6x8Str(85,4,"e");
             LCD_P6x8Str(0,6,"Hen");
          }
          else if (MyPageNum==3)
          {
             LCD_CLS();                 //清屏 
             LCD_P6x8Str(0,0,"Z_Spd");
             LCD_P6x8Str(45,0,"W_Spd");  
          }
        } 
        if(OLED_Key_Status == RIGHT)  //右方向按键按下
        { 
            DELAY_MS(500);             //延时消抖 
            MOTOR_I+=0.01;
        } 
        if(OLED_Key_Status == LEFT)  //右方向按键按下
        { 
            DELAY_MS(500);             //延时消抖 
            MOTOR_P+=0.1;
        } 
         /**********显示AD值*********/         
        if(MyPageNum==0)
        {  
           DisplayAD();
        }
        else if(MyPageNum==1)
        {   
           DisplayPage1();
        }
        else if(MyPageNum==2)
        {     
           DisplayPage2();
        }
        else if(MyPageNum==3)
        {     
           DisplayPage3();
        }
}
