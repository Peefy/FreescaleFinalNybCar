#ifndef __INCLUDE_H__
#define __INCLUDE_H__

#include  "common.h"

/*
 * Include �û��Զ����ͷ�ļ�
 */
//#include  "MKL_BME.h"           //λ����
#include  "MKL_wdog.h"          //���Ź�
#include  "MKL_gpio.h"          //IO�ڲ���
#include  "MKL_uart.h"          //����
#include  "MKL_SysTick.h"       //�δ�ʱ��
#include  "MKL_lptmr.h"         //�͹��Ķ�ʱ��(��ʱ�������������ʱ����ʱ)

#include  "MKL_i2c.h"
#include  "MKL_tpm.h"           //TPM������K60�� FTM ��pwm�����������
#include  "MKL_pit.h"           //PIT
#include  "MKL_adc.h"           //ADC
#include  "MKL_dac.h"           //DAC
#include  "MKL_dma.h"           //DMA
#include  "MKL_FLASH.h"         //FLASH
#include  "FIRE_LED.H"          //LED
#include  "FIRE_NRF24L0.h"      //����ģ��NRF24L01+ 
#include  "arm_math.h"                    //CMSIS library

#include  "NYB_Car_Init.h"             //NYBС����ʼ��
#include  "BoMaKaiGuan.h"              //���뿪��
#include  "OLED.h"                     //OLED��ʾ��
#include  "sound.h"                    //������
#include  "Pose.h"
#include  "MotorControl.h"             //�������
#include  "ServoControl.h"             //�������
#include  "GetSensor.h"                //���AD����λ�ü��
#include  "Display.h"                  //���AD����λ�ü��
#include  "KalmanFilter.h"             //�������˲�
#include  "TwoCars_Communication.h"    //˫��ͨ��
#include  "LowerComputer_V2.h"         //С����λ������
#include  "GUI.h"                      //�˻�����
#include  "Key.h"                      //����
#include  "Game.h"                     //���������
#include  "Config.h"                   //���ô洢
#include  "Ultrasonic.h"               //������
/*******MPU6050�Ŀ�*****/  //�ο�
/*#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "dmpKey.h"
#include "dmpmap.h"
#include "My6050.h"*/

#endif  //__INCLUDE_H__
