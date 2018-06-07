#include "Include.h"

STR_KALMAN Kalman[10];

STR_KALMAN KalmanFilterInit(STR_KALMAN kalman)   //单个 单输入单输出 卡尔曼滤波器 初始化
{   
   kalman.KalmanGain=0.0;
   kalman.EstimateValue=0.0;
   kalman.EstimateCovariance=0.3;
   kalman.MeasureCovariance=2.0;
   return kalman;  
}

void AllKalmanFilterInit(void)        //所有的卡尔曼滤波器初始化
{
    int8 m;
    for(m=0;m<10;m++)
     Kalman[m] = KalmanFilterInit(Kalman[m]);
}

float32_t KalmanFilter0(float32_t Measure)
{
    float32_t Temp1,Temp2;   //中间变量  用于计算
    arm_sqrt_f32(1.0/(Kalman[0].EstimateCovariance*Kalman[0].EstimateCovariance
                      +Kalman[0].MeasureCovariance*Kalman[0].MeasureCovariance),&Temp1);
    Kalman[0].KalmanGain=Temp1*Kalman[0].EstimateCovariance;
    if (Kalman[0].KalmanGain <Kalman_MIN)
        Kalman[0].KalmanGain =Kalman_MIN;
    Kalman[0].EstimateValue=Kalman[0].EstimateValue+
                            Kalman[0].KalmanGain*(Measure-Kalman[0].EstimateValue);
    arm_sqrt_f32(1-Kalman[0].KalmanGain,&Temp2);
    Kalman[0].EstimateCovariance=Temp2*Kalman[0].EstimateCovariance;
    if (Kalman[0].EstimateCovariance<Kalman_MIN)
        Kalman[0].EstimateCovariance =Kalman_MIN;
    Kalman[0].MeasureCovariance=Temp2*Kalman[0].MeasureCovariance;
    if(Kalman[0].MeasureCovariance<Kalman_MIN)
       Kalman[0].MeasureCovariance=Kalman_MIN;
    return Kalman[0].EstimateValue; 
}

float32_t KalmanFilter1(float32_t Measure)
{
    float32_t Temp1,Temp2;   //中间变量  用于计算
    arm_sqrt_f32(1.0/(Kalman[1].EstimateCovariance*Kalman[1].EstimateCovariance
                      +Kalman[1].MeasureCovariance*Kalman[1].MeasureCovariance),&Temp1);
    Kalman[1].KalmanGain=Temp1*Kalman[1].EstimateCovariance;
    if (Kalman[1].KalmanGain <Kalman_MIN)
        Kalman[1].KalmanGain =Kalman_MIN;
    Kalman[1].EstimateValue=Kalman[1].EstimateValue+
                            Kalman[1].KalmanGain*(Measure-Kalman[1].EstimateValue);
    arm_sqrt_f32(1-Kalman[1].KalmanGain,&Temp2);
    Kalman[1].EstimateCovariance=Temp2*Kalman[1].EstimateCovariance;
    if (Kalman[1].EstimateCovariance<Kalman_MIN)
        Kalman[1].EstimateCovariance =Kalman_MIN;
    Kalman[1].MeasureCovariance=Temp2*Kalman[1].MeasureCovariance;
    if(Kalman[1].MeasureCovariance<Kalman_MIN)
       Kalman[1].MeasureCovariance=Kalman_MIN;
    return Kalman[1].EstimateValue; 
}

float32_t KalmanFilter2(float32_t Measure)
{
    float32_t Temp1,Temp2;   //中间变量  用于计算
    arm_sqrt_f32(1.0/(Kalman[2].EstimateCovariance*Kalman[2].EstimateCovariance
                      +Kalman[2].MeasureCovariance*Kalman[2].MeasureCovariance),&Temp1);
    Kalman[2].KalmanGain=Temp1*Kalman[2].EstimateCovariance;
    if (Kalman[2].KalmanGain <Kalman_MIN)
        Kalman[2].KalmanGain =Kalman_MIN;
    Kalman[2].EstimateValue=Kalman[2].EstimateValue+
                            Kalman[2].KalmanGain*(Measure-Kalman[2].EstimateValue);
    arm_sqrt_f32(1-Kalman[2].KalmanGain,&Temp2);
    Kalman[2].EstimateCovariance=Temp2*Kalman[2].EstimateCovariance;
    if (Kalman[2].EstimateCovariance<Kalman_MIN)
        Kalman[2].EstimateCovariance =Kalman_MIN;
    Kalman[2].MeasureCovariance=Temp2*Kalman[2].MeasureCovariance;
    if(Kalman[2].MeasureCovariance<Kalman_MIN)
       Kalman[2].MeasureCovariance=Kalman_MIN;
    return Kalman[2].EstimateValue; 
}

float32_t KalmanFilter3(float32_t Measure)
{
    float32_t Temp1,Temp2;   //中间变量  用于计算
    arm_sqrt_f32(1.0/(Kalman[3].EstimateCovariance*Kalman[3].EstimateCovariance
                      +Kalman[3].MeasureCovariance*Kalman[3].MeasureCovariance),&Temp1);
    Kalman[3].KalmanGain=Temp1*Kalman[3].EstimateCovariance;
    if (Kalman[3].KalmanGain <Kalman_MIN)
        Kalman[3].KalmanGain =Kalman_MIN;
    Kalman[3].EstimateValue=Kalman[3].EstimateValue+
                            Kalman[3].KalmanGain*(Measure-Kalman[3].EstimateValue);
    arm_sqrt_f32(1-Kalman[3].KalmanGain,&Temp2);
    Kalman[3].EstimateCovariance=Temp2*Kalman[3].EstimateCovariance;
    if (Kalman[3].EstimateCovariance<Kalman_MIN)
        Kalman[3].EstimateCovariance =Kalman_MIN;
    Kalman[3].MeasureCovariance=Temp2*Kalman[3].MeasureCovariance;
    if(Kalman[3].MeasureCovariance<Kalman_MIN)
       Kalman[3].MeasureCovariance=Kalman_MIN;
    return Kalman[3].EstimateValue; 
}

float32_t KalmanFilter4(float32_t Measure)
{
    float32_t Temp1,Temp2;   //中间变量  用于计算
    arm_sqrt_f32(1.0/(Kalman[4].EstimateCovariance*Kalman[4].EstimateCovariance
                      +Kalman[4].MeasureCovariance*Kalman[4].MeasureCovariance),&Temp1);
    Kalman[4].KalmanGain=Temp1*Kalman[4].MeasureCovariance;
    if (Kalman[4].KalmanGain <Kalman_MIN)
       Kalman[4].KalmanGain =Kalman_MIN;
    Kalman[4].EstimateValue=Kalman[4].EstimateValue+
                            Kalman[4].KalmanGain*(Measure-Kalman[4].EstimateValue);
    arm_sqrt_f32(1-Kalman[4].KalmanGain,&Temp2);
    Kalman[4].EstimateCovariance=Temp2*Kalman[4].EstimateCovariance;
    if (Kalman[4].EstimateCovariance<Kalman_MIN)
        Kalman[4].EstimateCovariance =Kalman_MIN;
    Kalman[4].MeasureCovariance=Temp2*Kalman[4].MeasureCovariance;
    if(Kalman[4].MeasureCovariance<Kalman_MIN)
       Kalman[4].MeasureCovariance=Kalman_MIN;
    return Kalman[4].EstimateValue; 
}

float32_t KalmanFilter5(float32_t Measure)
{
    float32_t Temp1,Temp2;   //中间变量  用于计算
    arm_sqrt_f32(1.0/(Kalman[5].EstimateCovariance*Kalman[5].EstimateCovariance
                      +Kalman[5].MeasureCovariance*Kalman[5].MeasureCovariance),&Temp1);
    Kalman[5].KalmanGain=Temp1*Kalman[5].MeasureCovariance;
    if (Kalman[5].KalmanGain <Kalman_MIN)
       Kalman[5].KalmanGain =Kalman_MIN;
    Kalman[5].EstimateValue=Kalman[5].EstimateValue+
                            Kalman[5].KalmanGain*(Measure-Kalman[5].EstimateValue);
    arm_sqrt_f32(1-Kalman[5].KalmanGain,&Temp2);
    Kalman[5].EstimateCovariance=Temp2*Kalman[5].EstimateCovariance;
    if (Kalman[5].EstimateCovariance<Kalman_MIN)
        Kalman[5].EstimateCovariance =Kalman_MIN;
    Kalman[5].MeasureCovariance=Temp2*Kalman[5].MeasureCovariance;
    if(Kalman[5].MeasureCovariance<Kalman_MIN)
       Kalman[5].MeasureCovariance=Kalman_MIN;
    return Kalman[5].EstimateValue; 
}

float32_t KalmanFilter6(float32_t Measure)
{
    float32_t Temp1,Temp2;   //中间变量  用于计算
    arm_sqrt_f32(1.0/(Kalman[6].EstimateCovariance*Kalman[6].EstimateCovariance
                      +Kalman[6].MeasureCovariance*Kalman[6].MeasureCovariance),&Temp1);
    Kalman[6].KalmanGain=Temp1*Kalman[6].MeasureCovariance;
    if (Kalman[6].KalmanGain <Kalman_MIN)
       Kalman[6].KalmanGain =Kalman_MIN;
    Kalman[6].EstimateValue=Kalman[6].EstimateValue+
                            Kalman[6].KalmanGain*(Measure-Kalman[6].EstimateValue);
    arm_sqrt_f32(1-Kalman[6].KalmanGain,&Temp2);
    Kalman[6].EstimateCovariance=Temp2*Kalman[6].EstimateCovariance;
    if (Kalman[6].EstimateCovariance<Kalman_MIN)
        Kalman[6].EstimateCovariance =Kalman_MIN;
    Kalman[6].MeasureCovariance=Temp2*Kalman[6].MeasureCovariance;
    if(Kalman[6].MeasureCovariance<Kalman_MIN)
       Kalman[6].MeasureCovariance=Kalman_MIN;
    return Kalman[6].EstimateValue; 
}

void AD_F_KalmanFilter(void)
{
    AD_Filted_F_L=(uint16)(KalmanFilter0((float32_t)AD_Value_F_L0));    
    AD_Filted_F_M=(uint16)(KalmanFilter1((float32_t)AD_Value_F_M0));
    AD_Filted_F_R=(uint16)(KalmanFilter2((float32_t)AD_Value_F_R0));
    AD_Filted_F_FL=(uint16)(KalmanFilter3((float32_t)AD_Value_F_FL0));
    AD_Filted_F_FR=(uint16)(KalmanFilter4((float32_t)AD_Value_F_FR0));
}


