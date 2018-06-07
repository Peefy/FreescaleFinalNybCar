#ifndef _KALMANFILTER_H
#define _KALMANFILTER_H

typedef struct str_kalman
{
  float32_t  KalmanGain;                 //����������
  float32_t  EstimateCovariance;         //����Э����
  float32_t  MeasureCovariance;          //����Э����
  float32_t  EstimateValue;              //�������ֵ
} STR_KALMAN;

extern STR_KALMAN Kalman[10];            //����һ���ṹ������
/******************����������˲���******************/
extern float32_t KalmanFilter0(float32_t Measure);
extern float32_t KalmanFilter1(float32_t Measure);
extern float32_t KalmanFilter2(float32_t Measure);
extern float32_t KalmanFilter3(float32_t Measure);
extern float32_t KalmanFilter4(float32_t Measure);
extern float32_t KalmanFilter5(float32_t Measure);
extern STR_KALMAN KalmanFilterInit(STR_KALMAN kalman);    //�����������˲�����ʼ��
extern void AllKalmanFilterInit(void);                   //���еĿ������˲�����ʼ��
extern void AD_F_KalmanFilter(void);                     //��е�ADֵ���п������˲� 
extern void Communication_KalmanFilter(void);
#define Kalman_MIN 0.0001                //������Сֵ�޷�
#define KalmanFilter_Enable 1           //�Ƿ���ÿ������˲�

#endif