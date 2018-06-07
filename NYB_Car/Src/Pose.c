#include "Include.h"

#define GYRO_Sensitivity  16.4     //根据选定的量程来确定，MPU6050的GYRO四个量程正负250,500,1000,2000对应的GYRO_Sensitivity分别为131,65.5,32.8,16.4. 
#define Pitch (Angle_ShuiPing-Angle_Y)  //车体俯仰角
int32   Accel_X,Accel_Y,Accel_Z;
int32   Gyro_X,Gyro_Y,Gyro_Z;
int16   Gyro_X_Offest=0,Gyro_Y_Offest=10,Gyro_Z_Offest=0;   //存在Flash中 开机读取
int16   Accel_X_Offest=41,Accel_Y_Offest=0,Accel_Z_Offest=1553;
int32   Accel_X_Add=0,Accel_Y_Add=0,Accel_Z_Add=0;
int32   Gyro_X_Add=0,Gyro_Y_Add=0,Gyro_Z_Add=0;
int16   Angle_Y;

int32  Angle_ShuiPing=0;
uint8  DisEn=0;
/***************以下是卡尔曼滤波解算***************/
float Qingjiao = 0 ,Qingjiao_Pre, Acc_Qingjiao = 0 , Gyro_Qingjiao = 0 , Gyro_out = 0;
int32 Gyro_out_SC=0;int16 Acc_Qingjiao_SC,Qingjiao_SC;
float Acc_x = 0,Acc_z = 0, Gyro = 0;

float P[2][2] =   
            {
               { 1, 0 },
	       { 0, 1 }
	    };
	
char  C_0 = 1;
float E;  
float q_bias;    
float Angle_err;
float PCt_0, PCt_1;
float K_0, K_1;
float t_0, t_1;
float Pdot[4] ={0,0,0,0};

float Q_angle=0.060, Q_gyro=0.006, R_angle=3, dt=0.0180;   	//dt的取值为kalman滤波器采样时间;

#ifdef NA_Car
uint16 Q_angle_HMI=64,Q_gyro_HMI=3,R_angle_HMI=36,dt_HMI=40;    //液晶屏显示方便修改参数
#endif

#ifdef NB_Car
uint16 Q_angle_HMI=130,Q_gyro_HMI=3,R_angle_HMI=5,dt_HMI=38;    //液晶屏显示方便修改参数
#endif

void PoseCal(void)
{   
    Q_angle=(float)Q_angle_HMI/1000.0;
    Q_gyro=(float)Q_gyro_HMI/1000.0;
    R_angle=(float)R_angle_HMI/10;
    dt=(float)dt_HMI/10000.0;
    float x_z ,x_z2;  //中间量，用于计算
    Gyro =  (float)(Gyro_Y_Offest - Gyro_Y)/16.4;
    Acc_z = (float)(Accel_Z - Accel_Z_Offest) /16384;
    Acc_x = (float)(Accel_X - Accel_X_Offest) /16384; 
    x_z=(float)((float)Accel_X/Accel_Z);
    x_z2=x_z*x_z;
    Acc_Qingjiao = x_z * (1 - x_z2 * (0.3333333 + 0.2 * x_z2)) * 57.325;  //反正切函数的泰勒展开atan2 可求负数
    if(Acc_Qingjiao > 30) 
      Acc_Qingjiao = 30;               
    if(Acc_Qingjiao < -30) 
      Acc_Qingjiao = -30;
    Acc_Qingjiao_SC=(int16)Acc_Qingjiao;
    KalmanFilterMPU(Acc_Qingjiao,Gyro);           //卡尔曼滤波 5ms
}

void KalmanFilterMPU(float angle_m, float gyro_m)
{
     Qingjiao += (gyro_m-q_bias) * dt;    //先验估计
     //以下均为卡尔曼算法层面	
     Pdot[0] = Q_angle - P[0][1] - P[1][0];// Pk-' 先验估计误差协方差的微分
     Pdot[1] =- P[1][1];
     Pdot[2] =- P[1][1];
     Pdot[3] = Q_gyro;
	
     P[0][0] += Pdot[0] * dt;        // Pk- 先验估计误差协方差微分的积分 = 先验估计误差协方差
     P[0][1] += Pdot[1] * dt;
     P[1][0] += Pdot[2] * dt;
     P[1][1] += Pdot[3] * dt;
		
     Angle_err = angle_m - Qingjiao;    //zk-先验估计	
     
     PCt_0 = C_0 * P[0][0];
     PCt_1 = C_0 * P[1][0];
	
     E = R_angle + C_0 * PCt_0;
	
     K_0 = PCt_0 / E;                //Kk
     K_1 = PCt_1 / E;
	
     t_0 = PCt_0;
     t_1 = C_0 * P[0][1];

     P[0][0] -= K_0 * t_0;           //后验估计误差协方差
     P[0][1] -= K_0 * t_1;
     P[1][0] -= K_1 * t_0;
     P[1][1] -= K_1 * t_1;
		
     Qingjiao += K_0 * Angle_err;       //后验估计	    //此处为角度值
     q_bias += K_1 * Angle_err;       //后验估计       //个人觉得这个位置就是求偏差的地方
     Gyro_out = gyro_m - q_bias;      //输出值（后验估计）的微分 = 角速度   //此处为角速度值
     //Gyro_out_SC=(int32)Gyro_out;
     Qingjiao_SC=(int16)Qingjiao;
     Angle_Y=(int16)(Qingjiao*1000);
        
}

uint8 MPU_Flash_Saved=0;                //flash保存变量
uint8 MPU_Scces=0;

void Offest_Init(void)
{   
    static uint8 Wtime=0; 
    uint16 i;   
    DisEn=1;
    LCD_P6x8Str(31,7,"Offest_Init !  ");
    for(i=0;i<500;i++) //零点漂移与补偿
    { 
        Gyro_X = GetData(GYRO_XOUT_H);	      
        Gyro_Y = GetData(GYRO_YOUT_H);	      //use
        Gyro_Z = GetData(GYRO_ZOUT_H);
        Accel_X  = GetData(ACCEL_XOUT_H);     //use
        Accel_Y  = GetData(ACCEL_YOUT_H);     
        Accel_Z  = GetData(ACCEL_ZOUT_H);     //use
        DELAY_MS(1);               //延时	
        Gyro_X_Add += Gyro_X;	
        Gyro_Y_Add += Gyro_Y;	
        Gyro_Z_Add += Gyro_Z; 
        Accel_X_Add += Accel_X;
        Accel_Y_Add += Accel_Y;
        Accel_Z_Add += Accel_Z;
    } 


/*采集两次零飘,注意采集顺序 Wtime==0 车体水平 先采集Y轴陀螺仪和X轴加速度的零飘
                            Wtime==1 车体垂直 后采集Z轴加速度零飘  */ 
            
    switch(Wtime)     
    {
      case 0:
        Gyro_Y_Offest = Gyro_Y_Add/500;
        Accel_X_Offest =Accel_X_Add/500;
        break;
      case 1:
        Accel_Z_Offest =Accel_Z_Add/500;
        WriteFlash_MPUoffset();
        break;
    }     
    if(++Wtime>=2)
      Wtime=0; 
    Accel_X_Add=0;Accel_Y_Add=0;Accel_Z_Add=0;  //清零
    Gyro_X_Add=0;Gyro_Y_Add=0;Gyro_Z_Add=0;     //清零 
    DisEn=0;
    ok_fmq();    
}

void Angle_ShuiPing_get(void)
{
   uint16 i;
   DisEn=1;
   Angle_ShuiPing=0;
   LCD_P6x8Str(31,7,"Angle Get !    ");
   for(i=0;i<200;i++)
   {
      CarPoseGet();
      Angle_ShuiPing += Angle_Y;
      
   }
   Angle_ShuiPing=Angle_ShuiPing/200;  //角度的零点位置
   WriteFlash_Angle_ShuiPing();
   DisEn=0;
   ok_fmq(); 
}

void JudgeIsRamp(void)
{ 
     if(Distance>1666)
     {
        Ramp_EN=1;
     }
     if(Ramp_EN>=1)
     {
         if((AD_Value_F_M>1500||(AD_Value_F_L>999&&AD_Value_F_R>999))&& Ramp_up_flag==0 ) //电感检测类坡标识，可能上坡
            Ramp_possible_flag=1;           //可能上坡标志
         if((Ramp_possible_flag==1&&Pitch>7000))
            Ramp_up_flag=1;
         if((Ramp_up_flag==1&&Pitch<-7000))
         {  
            Ramp_down_flag=1;
         }
         if(Ramp_down_flag==1)     //下坡清上坡,如果陀螺仪失灵，走一段距离也消
         {
            Ramp_up_flag=0;               
            Ramp_way=Ramp_way+Real_Speed/10;  //下坡计位移
         }
         if(Ramp_way>888)    //下坡1m
         {
             Ramp_down_flag=0;
             Ramp_possible_flag=0;
             Ramp_up_flag=0;
             Ramp_way=0;
         }
     }
}

void CarPoseGet(void)
{    
      Accel_X  = GetData(ACCEL_XOUT_H);     //读取X轴加速度
      Accel_Y  = GetData(ACCEL_YOUT_H);
      Accel_Z  = GetData(ACCEL_ZOUT_H);
      Gyro_X   = GetData(GYRO_XOUT_H);	   
      Gyro_Y   = GetData(GYRO_YOUT_H);	
      Gyro_Z   = GetData(GYRO_ZOUT_H);
      PoseCal();
#ifdef Ramp_Mode 
      JudgeIsRamp();
#endif
}

void MPU_6050_Init(void)
{      
    i2c_init(I2C0,200 * 1000);   //初始化i2c，设置波特率 200k  太高容易初始化失败
    i2c_write_reg(I2C0,SlaveAddress,PWR_MGMT_1,0x00);
    i2c_write_reg(I2C0,SlaveAddress,SMPLRT_DIV,0x07);
    i2c_write_reg(I2C0,SlaveAddress,CONFIG,0x06);
    i2c_write_reg(I2C0,SlaveAddress,GYRO_CONFIG,0x18);
    i2c_write_reg(I2C0,SlaveAddress,ACCEL_CONFIG,0x01);
}

int GetData(uint8 REG_Address)//合成数据
{
    char H,L;
    H=i2c_read_reg(I2C0,SlaveAddress,REG_Address);
    Pause();//延时，否则无数据
    
    L=i2c_read_reg(I2C0,SlaveAddress,REG_Address+1);
    Pause();//延时，否则无数据 
    
    return (H<<8)+L;   //合成数据
}

uint8 MPU6050_testConnection(void) 
{
   
   if(i2c_read_reg(I2C0,SlaveAddress,WHO_AM_I) == 0x68)  //0b01101000;
   return 1;
   else return 0;

}
/**************************实现函数********************************************
*函数原型:		void MPU6050_setFullScaleAccelRange(uint8_t range)
*功　　能:	    设置  MPU6050 加速度计的最大量程
*******************************************************************************/

void MPU6050_setFullScaleAccelRange(uint8_t range) 
{    
  i2c_write_reg(I2C0,SlaveAddress, ACCEL_CONFIG, range);
}



