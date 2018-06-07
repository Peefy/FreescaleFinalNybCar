#ifndef _KALMANFILTER_H
#define _KALMANFILTER_H

typedef struct str_kalman
{
  float32_t  KalmanGain;                 //卡尔曼增益
  float32_t  EstimateCovariance;         //估计协方差
  float32_t  MeasureCovariance;          //测量协方差
  float32_t  EstimateValue;              //输出估计值
} STR_KALMAN;

extern STR_KALMAN Kalman[10];            //定义一个结构体数组
/******************五个卡尔曼滤波器******************/
extern float32_t KalmanFilter0(float32_t Measure);
extern float32_t KalmanFilter1(float32_t Measure);
extern float32_t KalmanFilter2(float32_t Measure);
extern float32_t KalmanFilter3(float32_t Measure);
extern float32_t KalmanFilter4(float32_t Measure);
extern float32_t KalmanFilter5(float32_t Measure);
extern STR_KALMAN KalmanFilterInit(STR_KALMAN kalman);    //单个卡尔曼滤波器初始化
extern void AllKalmanFilterInit(void);                   //所有的卡尔曼滤波器初始化
extern void AD_F_KalmanFilter(void);                     //电感的AD值进行卡尔曼滤波 
extern void Communication_KalmanFilter(void);
#define Kalman_MIN 0.0001                //数据最小值限幅
#define KalmanFilter_Enable 1           //是否采用卡尔曼滤波

#endif