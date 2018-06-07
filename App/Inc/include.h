#ifndef __INCLUDE_H__
#define __INCLUDE_H__

#include  "common.h"

/*
 * Include 用户自定义的头文件
 */
//#include  "MKL_BME.h"           //位操作
#include  "MKL_wdog.h"          //看门狗
#include  "MKL_gpio.h"          //IO口操作
#include  "MKL_uart.h"          //串口
#include  "MKL_SysTick.h"       //滴答定时器
#include  "MKL_lptmr.h"         //低功耗定时器(延时、脉冲计数、定时、计时)

#include  "MKL_i2c.h"
#include  "MKL_tpm.h"           //TPM（类似K60的 FTM ，pwm、脉冲计数）
#include  "MKL_pit.h"           //PIT
#include  "MKL_adc.h"           //ADC
#include  "MKL_dac.h"           //DAC
#include  "MKL_dma.h"           //DMA
#include  "MKL_FLASH.h"         //FLASH
#include  "FIRE_LED.H"          //LED
#include  "FIRE_NRF24L0.h"      //无线模块NRF24L01+ 
#include  "arm_math.h"                    //CMSIS library

#include  "NYB_Car_Init.h"             //NYB小车初始化
#include  "BoMaKaiGuan.h"              //拨码开关
#include  "OLED.h"                     //OLED显示屏
#include  "sound.h"                    //蜂鸣器
#include  "Pose.h"
#include  "MotorControl.h"             //电机控制
#include  "ServoControl.h"             //舵机控制
#include  "GetSensor.h"                //电感AD处理及位置检测
#include  "Display.h"                  //电感AD处理及位置检测
#include  "KalmanFilter.h"             //卡尔曼滤波
#include  "TwoCars_Communication.h"    //双车通信
#include  "LowerComputer_V2.h"         //小车下位机部分
#include  "GUI.h"                      //人机交互
#include  "Key.h"                      //按键
#include  "Game.h"                     //各种杂物。。
#include  "Config.h"                   //配置存储
#include  "Ultrasonic.h"               //超声波
/*******MPU6050的库*****/  //参考
/*#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "dmpKey.h"
#include "dmpmap.h"
#include "My6050.h"*/

#endif  //__INCLUDE_H__
