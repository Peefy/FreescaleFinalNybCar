#ifndef _POSE_H
#define _POSE_H

extern void MPU_6050_Init(void);

//****************************************
// 定义MPU6050内部地址
//****************************************
#define	SMPLRT_DIV		0x19	//陀螺仪采样率，典型值：0x07(125Hz)
#define	CONFIG			0x1A	//低通滤波频率，典型值：0x06(5Hz)
#define	GYRO_CONFIG		0x1B	//陀螺仪自检及测量范围，典型值：0x18(不自检，2000deg/s)
#define	ACCEL_CONFIG	        0x1C	//加速计自检、测量范围及高通滤波频率，典型值：0x01(不自检，2G，5Hz)
#define	ACCEL_XOUT_H	        0x3B    //X轴加速度  加速度
#define	ACCEL_XOUT_L	        0x3C
#define	ACCEL_YOUT_H	        0x3D    //X轴加速度
#define	ACCEL_YOUT_L	        0x3E
#define	ACCEL_ZOUT_H	        0x3F    //X轴加速度
#define	ACCEL_ZOUT_L	        0x40
#define	TEMP_OUT_H		0x41
#define	TEMP_OUT_L		0x42
#define	GYRO_XOUT_H		0x43    //X轴角速度  陀螺仪
#define	GYRO_XOUT_L		0x44	
#define	GYRO_YOUT_H		0x45    //X轴角速度
#define	GYRO_YOUT_L		0x46
#define	GYRO_ZOUT_H		0x47    //X轴角速度
#define	GYRO_ZOUT_L		0x48
#define	PWR_MGMT_1		0x6B	//电源管理，典型值：0x00(正常启用)
#define	WHO_AM_I		0x75	//IIC地址寄存器(默认数值0x68，只读)
#define	SlaveAddress	        0x68	//IIC写入时的地址字节数据，+1为读取

extern void CarPoseGet(void);
extern void MPU6050_setFullScaleAccelRange(uint8_t range);
extern uint8 MPU6050_testConnection(void);
extern void Offest_Init(void);
extern int GetData(uint8 REG_Address);
extern void PoseCal(void);
extern void KalmanFilterMPU(float ,float );

//////互补滤波姿态解算参数配置 

    //~~~~~~~~~~~~~~~X轴~~~~~~~~~~~/
#define ACCE_Y_RATIO      19     //Y轴加速度归一化系数        
#define GYRO_X_RATIO      45     //X轴陀螺仪归一化系数
#define ACCE_XY_RATIO     10     //XY轴角度反馈系数 0.45

    //~~~~~~~~~~~~~~~Y轴~~~~~~~~~~~/
#define ACCE_X_RATIO      19     //X轴加速度归一化系数        
#define GYRO_Y_RATIO      50     //Y轴陀螺仪归一化系数
#define ACCE_YX_RATIO     10     //YX轴角度反馈系数 0.45

    //~~~~~~~~~~~~~~~Z轴~~~~~~~~~~~/
#define ACCE_Z_RATIO      19     //Z轴加速度归一化系数        
#define GYRO_Z_RATIO      50     //Z轴陀螺仪归一化系数
#define ACCE_ZZ_RATIO     10     //ZZ轴角度反馈系数 0.45

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