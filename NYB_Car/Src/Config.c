#include "include.h"   //包含必要的头文件

#define ConfigDataQuantity 14 //尽量保证此处是偶数

#define SECTOR_NUM_CONFIG   (FLASH_SECTOR_NUM-5)         //Flash扇区尽量用最后面的扇区，确保安全
#define Flash_L16 ConfigRead32sBuff[ConfigNum]%65536     //存储低16位
#define Flash_H16 ConfigRead32sBuff[ConfigNum]/65536     //存储高16位

uint32 ConfigWrite32sBuff[16];                           //中间变量
uint32 ConfigRead32sBuff[16];                            //中间变量

void Save_All(void)
{
    uint16 NoData=0xffff;
    uint8 ConfigNum=0;
    /*****存入数组 便于存储*****/
    ConfigWrite32sBuff[0]  = ZhiDaoSpeed    + WanDaoSpeed*65536 ;
    ConfigWrite32sBuff[1]  = MOTOR_P        + MOTOR_I *65536    ;
    ConfigWrite32sBuff[2]  = ERR_I_MAX      + KeepDis *65536;
    ConfigWrite32sBuff[3]  = ZhiDao_Servo_P + ZhiDao_Servo_D*65536 ;
    ConfigWrite32sBuff[4]  = WanDao_Servo_P + WanDao_Servo_D*65536; 
    ConfigWrite32sBuff[5]  = Q_angle_HMI    + Q_gyro_HMI*65536 ;
    ConfigWrite32sBuff[6]  = R_angle_HMI    + dt_HMI*65536 ;
    ConfigWrite32sBuff[7]  = NoData + NoData*65536 ;
    ConfigWrite32sBuff[8]  = NoData + NoData*65536 ;
    ConfigWrite32sBuff[9]  = NoData + NoData*65536 ;
    ConfigWrite32sBuff[10] = NoData + NoData*65536 ;
    ConfigWrite32sBuff[11] = NoData + NoData*65536 ;
    ConfigWrite32sBuff[12] = NoData + NoData*65536 ;
    ConfigWrite32sBuff[13] = NoData + NoData*65536 ;
    ConfigWrite32sBuff[14] = NoData + NoData*65536 ;
    ConfigWrite32sBuff[15] = NoData + NoData*65536 ;
    flash_erase_sector(SECTOR_NUM_CONFIG);
    for(;ConfigNum<ConfigDataQuantity/2;++ConfigNum)
    {
        flash_write(SECTOR_NUM_CONFIG,ConfigNum*8,ConfigWrite32sBuff[ConfigNum]);      
                     
    }
    kaiji_fmq();
    
}

void Config_All(void)       
{
    uint16 NoData=0xffff;
    uint8 ConfigNum=0;    
    for(;ConfigNum<ConfigDataQuantity/2;++ConfigNum)
    {
       ConfigRead32sBuff[ConfigNum]=\
       flash_read(SECTOR_NUM_CONFIG,ConfigNum*8,uint32); 
       switch(ConfigNum)  
       {
       case 0 :
         ZhiDaoSpeed    = Flash_L16;
         WanDaoSpeed    = Flash_H16;break;
       case 1 :
         MOTOR_P        = Flash_L16;
         MOTOR_I        = Flash_H16;break;
       case 2 :
         ERR_I_MAX      = Flash_L16;
         KeepDis        = Flash_H16;break;
       case 3 :
         ZhiDao_Servo_P = Flash_L16;
         ZhiDao_Servo_D = Flash_H16;break;
       case 4 :
         WanDao_Servo_P = Flash_L16;
         WanDao_Servo_D = Flash_H16;break;
       case 5 :
         Q_angle_HMI     =Flash_L16;
         Q_gyro_HMI      =Flash_H16;break;
       case 6 :
         R_angle_HMI     =Flash_L16;
         dt_HMI          =Flash_H16;break;
       case 7 :
         NoData=Flash_L16;
         NoData=Flash_H16;break;
       case 8 :
         NoData=Flash_L16;
         NoData=Flash_H16;break;
       case 9 :
         NoData=Flash_L16;
         NoData=Flash_H16;break;
       case 10:
         NoData=Flash_L16;
         NoData=Flash_H16;break;
       case 11:
         NoData=Flash_L16;
         NoData=Flash_H16;break;
       case 12:
         NoData=Flash_L16;
         NoData=Flash_H16;break;
       case 13:
         NoData=Flash_L16;
         NoData=Flash_H16;break;
       case 14:
         NoData=Flash_L16;
         NoData=Flash_H16;break;;
       case 15:
         NoData=Flash_L16;
         NoData=Flash_H16;break;
       }
    }
    kaiji_fmq();
}

void SpeedSelect_HIGH(void)   //高速档
{   
    ZhiDaoSpeed = ZD_Spd_H;
    WanDaoSpeed = WD_Spd_H;
    ok_fmq();
}

void SpeedSelect_MEDIUM(void)  //中速档
{
    ZhiDaoSpeed = ZD_Spd_M;
    WanDaoSpeed = WD_Spd_M;
    ok_fmq();
}

void SpeedSelect_LOW(void)   //低速档
{
    ZhiDaoSpeed = ZD_Spd_L;
    WanDaoSpeed = WD_Spd_L;
    ok_fmq();
}
