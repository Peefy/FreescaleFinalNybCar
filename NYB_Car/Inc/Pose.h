#ifndef _POSE_H
#define _POSE_H

extern void MPU_6050_Init(void);

//****************************************
// ����MPU6050�ڲ���ַ
//****************************************
#define	SMPLRT_DIV		0x19	//�����ǲ����ʣ�����ֵ��0x07(125Hz)
#define	CONFIG			0x1A	//��ͨ�˲�Ƶ�ʣ�����ֵ��0x06(5Hz)
#define	GYRO_CONFIG		0x1B	//�������Լ켰������Χ������ֵ��0x18(���Լ죬2000deg/s)
#define	ACCEL_CONFIG	        0x1C	//���ټ��Լ졢������Χ����ͨ�˲�Ƶ�ʣ�����ֵ��0x01(���Լ죬2G��5Hz)
#define	ACCEL_XOUT_H	        0x3B    //X����ٶ�  ���ٶ�
#define	ACCEL_XOUT_L	        0x3C
#define	ACCEL_YOUT_H	        0x3D    //X����ٶ�
#define	ACCEL_YOUT_L	        0x3E
#define	ACCEL_ZOUT_H	        0x3F    //X����ٶ�
#define	ACCEL_ZOUT_L	        0x40
#define	TEMP_OUT_H		0x41
#define	TEMP_OUT_L		0x42
#define	GYRO_XOUT_H		0x43    //X����ٶ�  ������
#define	GYRO_XOUT_L		0x44	
#define	GYRO_YOUT_H		0x45    //X����ٶ�
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47    //X����ٶ�
#define	GYRO_ZOUT_L		0x48
#define	PWR_MGMT_1		0x6B	//��Դ��������ֵ��0x00(��������)
#define	WHO_AM_I		0x75	//IIC��ַ�Ĵ���(Ĭ����ֵ0x68��ֻ��)
#define	SlaveAddress	        0x68	//IICд��ʱ�ĵ�ַ�ֽ����ݣ�+1Ϊ��ȡ

extern void CarPoseGet(void);
extern void MPU6050_setFullScaleAccelRange(uint8_t range);
extern uint8 MPU6050_testConnection(void);
extern void Offest_Init(void);
extern int GetData(uint8 REG_Address);
extern void PoseCal(void);
extern void KalmanFilterMPU(float ,float );

//////�����˲���̬����������� 

    //~~~~~~~~~~~~~~~X��~~~~~~~~~~~/
#define ACCE_Y_RATIO      19     //Y����ٶȹ�һ��ϵ��        
#define GYRO_X_RATIO      45     //X�������ǹ�һ��ϵ��
#define ACCE_XY_RATIO     10     //XY��Ƕȷ���ϵ�� 0.45

    //~~~~~~~~~~~~~~~Y��~~~~~~~~~~~/
#define ACCE_X_RATIO      19     //X����ٶȹ�һ��ϵ��        
#define GYRO_Y_RATIO      50     //Y�������ǹ�һ��ϵ��
#define ACCE_YX_RATIO     10     //YX��Ƕȷ���ϵ�� 0.45

    //~~~~~~~~~~~~~~~Z��~~~~~~~~~~~/
#define ACCE_Z_RATIO      19     //Z����ٶȹ�һ��ϵ��        
#define GYRO_Z_RATIO      50     //Z�������ǹ�һ��ϵ��
#define ACCE_ZZ_RATIO     10     //ZZ��Ƕȷ���ϵ�� 0.45

extern int16 Gyro_X_Offest;
extern int16 Gyro_Y_Offest;
extern int16 Gyro_Z_Offest;
extern int16 Accel_X_Offest;
extern int16 Accel_Y_Offest;
extern int16 Accel_Z_Offest;
extern int32 Angle_ShuiPing;
extern uint8 DisEn;

//#define Ramp_Mode 1

#endif