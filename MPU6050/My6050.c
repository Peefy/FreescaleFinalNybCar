#include "Include.h"

static signed char gyro_orientation[9] = {-1, 0, 0,
                                           0,-1, 0,
                                           0, 0, 1};
#define q30  1073741824.0f
float q0=1.0f,q1=0.0f,q2=0.0f,q3=0.0f;
char num[50];
float Pitch,Roll,Yaw;
unsigned long sensor_timestamp;
short gyro[3], accel[3], sensors;
unsigned char more;
long quat[4];

void My6050_Init(void)
{
    i2c_init(I2C0,400 * 1000);   ////初始化i2c，设置波特率 400k
    int result; 
    result = mpu_init();
    if(!result)
    {	 		 
	  PrintChar("mpu initialization complete......\n ");	 	  //mpu_set_sensor
	  if(!mpu_set_sensors(INV_XYZ_GYRO | INV_XYZ_ACCEL))
	  	 PrintChar("mpu_set_sensor complete ......\n");

	  else
	  	 PrintChar("mpu_set_sensor come across error ......\n");
	  if(!mpu_configure_fifo(INV_XYZ_GYRO | INV_XYZ_ACCEL))	   	  //mpu_configure_fifo
	  	 PrintChar("mpu_configure_fifo complete ......\n");
	  else
	  	 PrintChar("mpu_configure_fifo come across error ......\n");
	  if(!mpu_set_sample_rate(DEFAULT_MPU_HZ))	   	  //mpu_set_sample_rate
	  	 PrintChar("mpu_set_sample_rate complete ......\n");
	  else
	  	 PrintChar("mpu_set_sample_rate error ......\n");
	  if(!dmp_load_motion_driver_firmware())   	  //dmp_load_motion_driver_firmvare
	  	PrintChar("dmp_load_motion_driver_firmware complete ......\n");
	  else
	  	PrintChar("dmp_load_motion_driver_firmware come across error ......\n");
	  if(!dmp_set_orientation(inv_orientation_matrix_to_scalar(gyro_orientation))) 	  //dmp_set_orientation
	  	 PrintChar("dmp_set_orientation complete ......\n");
	  else
	  	 PrintChar("dmp_set_orientation come across error ......\n");
	  if(!dmp_enable_feature(DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_TAP |
	        DMP_FEATURE_ANDROID_ORIENT | DMP_FEATURE_SEND_RAW_ACCEL | DMP_FEATURE_SEND_CAL_GYRO |
	        DMP_FEATURE_GYRO_CAL))		   	  //dmp_enable_feature
	  	 PrintChar("dmp_enable_feature complete ......\n");
	  else
	  	 PrintChar("dmp_enable_feature come across error ......\n");
	  if(!dmp_set_fifo_rate(DEFAULT_MPU_HZ))   	  //dmp_set_fifo_rate
	  	 PrintChar("dmp_set_fifo_rate complete ......\n");
	  else
	  	 PrintChar("dmp_set_fifo_rate come across error ......\n");
	  run_self_test();
	  if(!mpu_set_dmp_state(1))
	  	 PrintChar("mpu_set_dmp_state complete ......\n");
	  else
	  	 PrintChar("mpu_set_dmp_state come across error ......\n");
      }
}

void Get6050Data(void)
{
    dmp_read_fifo(gyro, accel, quat, &sensor_timestamp, &sensors,
                &more);	
    if (sensors & INV_WXYZ_QUAT )
	 {
	 	 q0=quat[0] / q30;	
		 q1=quat[1] / q30;
		 q2=quat[2] / q30;
		 q3=quat[3] / q30;
		 Pitch  = asin(2 * q1 * q3 - 2 * q0* q2)* 57.3; // pitch
    	 Roll = atan2(2 * q2 * q3 + 2 * q0 * q1, -2 * q1 * q1 - 2 * q2* q2 + 1)* 57.3; // roll
		 Yaw = 	atan2(2*(q1*q2 + q0*q3),q0*q0+q1*q1-q2*q2-q3*q3) * 57.3;
//		sprintf(num,"%f",q0);//	in Calculating quaternion steps.....
//		sprintf(num,"%f",q1);
		sprintf(num,"%f,%f,%f",Pitch,Roll,Yaw);	
	    PrintChar(num);
	    PrintChar("\n");
//		UART1_ReportIMU(Yaw*10, Pitch*10, Roll*10,0,0,0,100);
	 }
    else
      PrintChar("My_error");
}

